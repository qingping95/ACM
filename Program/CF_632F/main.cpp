#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <bitset>
//#include <unordered_map>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 2555;
struct node{
    int u, v, d;
    bool operator<(const node& o)const{return d < o.d;}
}e[N*N];
bitset<N> b[N];
int a[N][N];
int main()
{
    //Open();
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) scanf("%d", &a[i][j]);
    for(int i = 0; i < n; i++) if(a[i][i]){printf("NOT MAGIC\n");return 0;}
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) if(a[i][j] != a[j][i]){printf("NOT MAGIC\n");return 0;}

    int tail = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            e[tail++] = (node){i, j, a[i][j]};
    sort(e, e+tail);
    int cur = 0;
    for(int i = 0; i < tail; i++)
    {
        while(cur < tail && e[cur].d < e[i].d)
        {
            b[e[cur].u][e[cur].v] = 1;
            cur++;
        }
        if((b[e[i].u] & b[e[i].v]).any()){printf("NOT MAGIC\n");return 0;}
    }
    printf("MAGIC\n");
    return 0;
}

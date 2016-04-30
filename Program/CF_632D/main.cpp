#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
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
int a[1000010];
int c[1000010];
int len[1000010];
int main()
{
    //Open();
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++)scanf("%d", &a[i]);
    for(int i = 0; i < n; i++)if(a[i] <= m) c[a[i]]++;
    for(int i = 1; i <= m; i++)
        for(int j = i; j <= m; j += i)
            len[j] += c[i];
    int lcm = 0, ans = 0;
    for(int i = 1; i <= m; i++)
        if(ans < len[i])
        {
            ans = len[i];
            lcm = i;
        }
    if(lcm == 0) lcm = 1;
    printf("%d %d\n", lcm, ans);
    for(int i = 0; i < n; i++) if(lcm % a[i] == 0) printf("%d ", i+1);
    return 0;
}

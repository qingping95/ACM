#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
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
const int N = 1001010;
int vis[N];
int dif[N];
int a[5555];
int n, k;
bool check(int m)
{
    int sum = 0;
    for(int i = 0; i <= a[n-1]+1; i+=m)
        sum += dif[i];
    if(sum > k*(k+1)/2) return false;
    int res = 0;
    for(int i = 0; i < n; i++)
    {
        if(vis[a[i]%m] == m) res++;
        if(res > k) return false;
        vis[a[i]%m] = m;
    }
    return true;
}
int main()
{
    //Open();
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    sort(a, a+n);
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            dif[a[j]-a[i]]++;
    for(int i = 1; i <= a[n-1]+1; i++)
    if(check(i)) {printf("%d\n", i);break;}
    return 0;
}

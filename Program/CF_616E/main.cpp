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
const LL mod = 1e9+7;
LL n, m;
LL cal(LL s, LL t)
{
    if(s == t) return 0;
    LL a = s+1+t;
    LL b = t-s;
    if(a&1) return b/2%mod*(a%mod)%mod;
    else return a/2%mod*(b%mod)%mod;
}
int main()
{
    //Open();
    scanf("%I64d%I64d", &n, &m);
    LL ans = n%mod * (m%mod) %mod;
    LL sub = 0;
    m = min(n, m);
    LL i = m;
    for(i = 1; i * i <= n && i <= m; i++)
    {
        sub = (sub + i * (n/i)%mod)%mod;
    }
    for(LL v = 1; v * v < n; v++)
    {
        LL st = n/(v+1);
        LL ed = min(m, n/v);
        if(st >= ed) continue;
        if(ed < i) break;
        sub = (sub + v * cal(max(i-1, st), ed)%mod)%mod;
    }
    ans = (ans - sub)%mod;

    if(ans < 0) ans += mod;
    printf("%I64d\n", ans);
    return 0;
}

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
const int mod = 1000000009;
LL fac[100010];
LL inv[100010];
LL pow_mod(LL x, int n, int mod)
{
    LL rnt = 1;
    while(n)
    {
        if(n & 1) rnt = rnt * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return rnt;
}
void init()
{
    fac[0] = fac[1] = 1;
    inv[0] = inv[1] = 1;
    for(int i = 1; i < 100010; i++)
        fac[i] = fac[i-1]*i%mod, inv[i] = pow_mod(fac[i], mod-2, mod);
}
int main()
{
//    Open();
    int n, m;
    init();
    while(~scanf("%d%d", &n, &m))
    {
        int l = 0, r = 0;
        for(int i = 0; i < n; i++)
        {
            int x;
            scanf("%d", &x);
            int tl = INF, tr = 0;
            if(x >= l && x <= r) tl = abs(x - l) & 1;
            else if(x < l) tl = min(tl, l - x);
            else if(x > r) tl = min(tl, x - r);
            if(r + x > m) tl = min(tl, m*2-(r + x));

            if(r + x <= m) tr = max(tr, r + x);
            if(l + x > m) tr = max(tr, m*2-(l+x));
            if(r + x > m) tr = max(tr, m*2-(r+x));
            if(l + x <= m && m <= r + x) tr = max(tr, m-((m-(l+x))&1));

            l = tl, r = tr;
        }
        LL ans = 0;
        for(int i = l; i <= r; i+= 2)
        {
            ans = (ans + fac[m]*inv[m-i]%mod *inv[i]%mod)%mod;
        }
        printf("%I64d\n", ans);
    }
    return 0;
}

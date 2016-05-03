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
LL phi(LL n)
{
    LL res = n, a = n;
    for(LL i = 2; i * i <= a; i++)
    {
        if(a % i) continue;
        res = res / i *(i-1);
        while(a%i == 0) a /= i;
    }
    if(a > 1) res = res/a*(a-1);
    return res;
}
LL sta[11];
LL n;
LL pow_mod(LL x, LL k, LL mod)
{
    LL res = 1;
    while(k)
    {
        if(k & 1) res = res * x % mod;
        x = x * x % mod;
        k >>= 1;
    }
    return res%mod;
}
LL solve(LL idx, LL mod)
{
    if(idx == n-1) return sta[idx]%mod;
    LL p = phi(mod);
    LL mi = solve(idx+1, p);
    return pow_mod(sta[idx], mi+p, mod)%mod;
}
int main()
{
    //Open();
    LL cas = 1, m;
    char str[111];
    while(~scanf("%s", str) && (str[0] != '#'))
    {
        sscanf(str, "%lld", &m);
//        cout<<m<<endl;
        scanf("%lld", &n);
        for(LL i = 0; i < n; i++) scanf("%lld", &sta[i]);
        printf("Case #%lld: %lld\n", cas++, solve(0, m));
    }
    return 0;
}

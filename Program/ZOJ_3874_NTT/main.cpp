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
const LL mod = 786433;
LL wn[40];
int g,prime[10010],L=0;
LL pow(LL x,LL n,LL mod)
{
    LL res=1;
    while(n>0){
        if(n&1)res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}
bool check(int x)
{
    for(int i=0;i<L;i++){
        if(pow(x,(mod-1)/prime[i],mod)==1)return false;
    }
    return true;
}
void init()
{
    LL x=mod-1;
    L=0;
    for(int i=2;i<=sqrt(x)+1;i++){
        if(x%i!=0)continue;
        while(x%i==0)x/=i;
        prime[L++]=i;
    }
    if(x!=1)prime[L++]=x;
    for(g=2;;g++){
        if(check(g))break;
    }
    for(int i=0;i<20;i++){
        LL x=1<<i;
        wn[i]=pow(g,(mod-1)/x,mod);
    }
}
void NTT(LL a[], int len, int on)
{
    int j = len >> 1;
    for(int i=1; i<len-1; i++)
    {
        if(i < j) swap(a[i], a[j]);
        int k = len >> 1;
        while(j >= k)
        {
            j -= k;
            k >>= 1;
        }
        if(j < k) j += k;
    }
    int id = 0;
    for(int h = 2; h <= len; h <<= 1)
    {
        id++;
        for(int j = 0; j < len; j += h)
        {
            LL w = 1;
            for(int k = j; k < j + h / 2; k++)
            {
                LL u = a[k] % mod;
                LL t = w * (a[k + h / 2] % mod) % mod;
                a[k] = (u + t) % mod;
                a[k + h / 2] = ((u - t) % mod + mod) % mod;
                w = w * wn[id] % mod;
            }
        }
    }
    if(on == -1)
    {
        for(int i = 1; i < len / 2; i++)
            swap(a[i], a[len - i]);
        LL Inv = pow(len, mod - 2, mod);
        for(int i = 0; i < len; i++)
            a[i] = a[i] % mod * Inv % mod;
    }
}
const int N = 200020;
LL dp[N/2], fac[N/2], a[N], b[N];
void divide(int l, int r)
{
    if(l >= r) return ;
    int mid = l + r >> 1;
    divide(l, mid);
    int len = 1;
    while(len < r - l + 1) len <<= 1;
    for(int i = 0; i <= mid - l; i++) a[i] = dp[i+l];
    for(int i = mid-l+1; i < len; i++) a[i] = 0;
    for(int i = 0; i < len; i++) b[i] = fac[i];
    NTT(a, len, 1);
    NTT(b, len, 1);
    for(int i = 0; i < len; i++)
        a[i] = a[i]*b[i]%mod;
    NTT(a, len, -1);
    for(int i = mid+1; i <= r; i++)
        dp[i] = (dp[i] - a[i-l] + mod)%mod;
    divide(mid+1, r);
}
int main()
{
    Open();
    init();
    fac[0] = 1;
    for(int i = 1; i <= N/2; i++)
        fac[i] = (LL)fac[i-1]*i%mod, dp[i] = fac[i];
    divide(1, N/2);
    int T;scanf("%d", &T);
    while(T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        LL ans = 1;
        while(m--)
        {
            int num;scanf("%d", &num);
            int ma = 0, mi = n+10;
            for(int i = 0; i < num; i++)
            {
                int x;scanf("%d", &x);
                ma = max(x, ma);
                mi = min(x, mi);
            }
            if(ma - mi + 1 != num) ans = 0;
            else ans = ans * dp[num] % mod;
        }
        if(ans < 0) ans += mod;
        printf("%lld\n", ans);
    }
    return 0;
}

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
const int N = 100010;
const LL mod = 1000000007;
LL l, r, G, T;
LL getans(LL vR, LL ansR)
{
    LL res = 0, pre = 0;
    for(LL i = 63; i >=0; i--)
    {
        LL Ttmp = T&(1LL<<i), xtmp = vR&(1LL<<i), rtmp = ansR&(1LL<<i);
        if(Ttmp^xtmp){
            if(xtmp){
                if(rtmp){
                    res = (res + (1LL<<(i)))%mod;
                }
            }else if(!rtmp) break;
        }else {
            if(rtmp){
                if(!xtmp){
                    res = (res + vR&((1LL<<i)-1))%mod;
                    break;
                }
            }
        }
        if(i == 0) res++;
    }
    return res%mod;
}
int main()
{
//    Open();
    LL Cas;scanf("%I64d", &Cas);
    while(Cas--)
    {
        scanf("%I64d%I64d%I64d%I64d", &l, &r, &G, &T);
        T = G^T;
        LL ans = 0;
        ans = (getans(r, r) - getans(r, l-1) - (getans(l, r) - getans(l, l-1)))%mod;
        ans = (r - l + 1)%mod*2 - ans;
        while(ans < 0) ans += mod;
        printf("%I64d\n", ans%mod);
    }
    return 0;
}

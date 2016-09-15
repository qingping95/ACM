/*
*	CF原题，不过当时没做出来2333，由于障碍数有限，很容易考虑反过来的情况，将通过障碍的路径全部减去，这里需要容斥
*	注意到n有100，但是由于人只能往下或者往右走，可以用dp[i][j]表示从起点走到第i个障碍经过j个障碍的方案数，利用这个
*	dp即可
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <climits>
#include <bitset>
using namespace std;
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define PII pair<ll,ll>
#define MP(x,y) make_pair((x),(y))
#define ll long long
#define ull unsigned ll
#define scan(x) scanf("%d",&(x))
#define scan2(x,y) scanf("%d%d",&(x),&(y))
#define scan3(x,y,z) scanf("%d%d%d",&(x),&(y),&(z))
#define scan4(x,y,z,k) scanf("%d%d%d%d",&(x),&(y),&(z),&(k))
#define Max(a,b) a=max(a,b)
#define Min(a,b) a=min(a,b)
#define fuck(x) cout<<#x<<" "<<x<<endl
const ll mod = 110119;
ll fac[122222];
ll nfac[122222];
ll qPow (ll a, ll k, ll p) {
    ll ans = 1;
    while (k) {
        if (k&1)
            ans = (ans * a) % p;
        a = (a * a) % p;
        k /= 2;
    }
    return ans;
}

ll C (ll a, ll b, ll p) {
    if (a < b)
        return 0;
    if (b > a - b)
        b = a - b;
    ll up = 1, down = 1;

//    for (ll i = 0; i < b; i++) {
//        up = up * (a-i) % p;
//        down = down * (i+1) % p;
//    }
    up = fac[a] * nfac[a-b] % p;
    //down = fac[b];
    return up * nfac[b] % p; // 逆元
}
ll lucas (ll a, ll b, ll p) {
    if (b == 0)
        return 1;
    return C(a%p, b%p, p) * lucas(a/p, b/p, p) % p;
}
ll dp[111][111];//
PII p[222];//
#define F first
#define S second

inline ll get(ll j,ll i){
    ll dx = p[i].F - p[j].F;
    ll dy = p[i].S - p[j].S;
    ll x = dy - (dx+dy)/3;
    ll y = dx - (dx+dy)/3;
    if((dx+dy) % 3 != 0) return 0;
    if(x<0 || y<0) return 0;
    return lucas(x+y,x,mod);
}

int main(){
    //freopen("/home/rainto96/in.txt","r",stdin);
    nfac[0] = fac[0] = 1;
    for(ll i = 1;i<122222;i++) fac[i] = fac[i-1] * i %mod;
    for(ll i = 1;i<122222;i++) nfac[i] = qPow(fac[i],mod-2,mod);

    ll n,m,r;
    ll cas=1;
    while(scanf("%I64d%I64d%I64d",&n,&m,&r) == 3){
        p[200] = MP(1,1);
        p[201] = MP(n,m);
        memset(dp,0,sizeof(dp));
        for(ll i=1;i<=r;i++){
            ll x,y;
            scanf("%I64d%I64d",&x,&y);
            p[i] = MP(x,y);
        }
        sort(p+1,p+1+r);
        for(ll i=1;i<=r;i++){
            dp[i][1] = get(200, i);
        }
        for(ll i=1;i<=r;i++){
            for(ll j=1;j<i;j++){
                if(i == j) continue;
                if(p[j].S <= p[i].S){
                    for(ll k=2;k<=i;k++){
                        if(dp[j][k-1] == 0) continue;
                        dp[i][k] = (dp[i][k] + dp[j][k-1] * get(j,i) % mod)%mod;
                    }
                }
            }
        }
        if((m+n-2)%3 != 0){
            printf("Case #%I64d: 0\n",cas++);
            continue;
        }
        //ll x = (m-1) - (m+n-2)/3, y = n-1 - (m+n-2)/3;
        //ll ans = lucas(x+y,y,mod);
        ll ans = get(200, 201);
        for(ll i=1;i<=r;i++){
            for(ll k=1;k<=r;k++){
                if(k&1) ans = (ans - dp[i][k] * get(i,201))%mod;
                else ans = (ans + dp[i][k] * get(i,201))%mod;
            }
        }
        printf("Case #%I64d: %I64d\n",cas++, (ans%mod+mod)%mod );
    }
    return 0;
}


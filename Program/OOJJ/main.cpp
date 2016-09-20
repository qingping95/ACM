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
using namespace std;
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define PII pair<ll,ll>
#define MP(x,y) make_pair((x),(y))
#define ll long long
#define ull unsigned ll
#define Max(a,b) a=max(a,b)
#define Min(a,b) a=min(a,b)
#define F first
#define S second
const ll N = 101111;
struct edge{
    ll to, w;
};
vector<edge> g[N];
ll ni10[N];
ll extend_gcd(ll a,ll b,ll &x,ll &y)
{
    if(b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    else
    {
        ll r = extend_gcd(b, a%b, y, x);
        y -= x*(a/b);
        return r;
    }
}
ll n,M;
ll mod_r(ll a,ll n)
{
    ll x,y;
    ll d=extend_gcd(a,n,x,y);
    return (x%n+n)%n;
}
ll z10[N];
ll del[N];
ll wt[N];
ll newroot;
ll maxn=0x3f3f3f3f;
ll dfs(ll now,ll fa,ll all,ll& newroot , ll dep){
    wt[now]=1;
    ll mx=0;
    //if(dep>100000) cerr<<"fuck";
    for(edge nxt : g[now])
    {
        ll to = nxt.to;
        if(to==fa || del[to]) continue;
        ll siz=dfs(to,now,all,newroot,dep+1);
        Max(mx,siz);
        wt[now]+=siz;
    }
    Max(mx,all-wt[now]);
    if(mx < maxn) maxn=mx ,newroot=now;
    return wt[now];
}

ll searchit(ll root,ll all){
    maxn=0x3f3f3f3f;
    dfs(root,-1,all,newroot,1);
    return newroot;
}
map<ll,ll> mp;
ll ans=0;
ll tque[101111];
ll tl=0;
void gao(ll u,ll fa,ll zv,ll fv, ll dep, ll fir){
    //in son
    ll cha = -zv * ni10[dep] % M;
    if(cha < 0) cha += M;
    if(mp.count(cha)) ans += mp[cha];
    //self
    if(zv%M == 0 && fir) ans++;
    if(fv%M == 0 && fir) ans++;
    //in map!
    tque[tl++] = fv;
    for(ll i=0;i<g[u].size();i++){
        ll to = g[u][i].to;
        if(to == fa || del[to]) continue;
        ll w = g[u][i].w;
        ll nzv = zv * 10 + w;
        nzv %= M;if(nzv < 0) nzv += M;
        ll nfv = w * z10[dep]%M + fv;
        nfv %= M;if(nfv < 0) nfv += M;
        gao(to, u, nzv, nfv, dep+1, fir);
    }
}

void fz(ll rt,ll sz){
    queue<PII > sq;
    sq.push(MP(rt,sz));
    while(!sq.empty()){
        PII now = sq.front(); sq.pop();
        ll nr = searchit(now.F , now.S);
        del[nr] = true;
        mp.clear();
        for(ll i=0;i<g[nr].size();i++){
            ll to = g[nr][i].to;
            ll w = g[nr][i].w;
            if(del[to]) continue;
            tl=0;
            gao(to, nr, w, w, 1, 1);
            for(ll j=0;j<tl;j++) mp[tque[j]]++;
            sq.push(MP(to, wt[to]));
        }
        mp.clear();
        ll sz = g[nr].size();
        for(ll i=sz-1;i>=0;i--){
            ll to = g[nr][i].to;
            ll w = g[nr][i].w;
            if(del[to]) continue;
            tl=0;
            gao(to, nr, w, w, 1, 0);
            for(ll j=0;j<tl;j++) mp[tque[j]]++;
        }
    }
}

int main(){
//    freopen("F:/in.txt","r",stdin);
    scanf("%I64d%I64d",&n,&M);

    ni10[0] = 1;
    z10[0] = 1;
    ll nn10 = mod_r(10,M);
    for(ll i=1;i<N;i++){
        z10[i] = z10[i-1] * 10 % M;
        ni10[i] = mod_r(z10[i], M)%M;
    }

    for(ll i=0;i<n-1;i++){
        ll u,v,w;
        scanf("%I64d%I64d%I64d",&u,&v,&w);
        w %= M;
        g[u].pb((edge){v, w});
        g[v].pb((edge){u, w});
    }
    fz(0,n);
    cout<<ans<<endl;
    return 0;
}

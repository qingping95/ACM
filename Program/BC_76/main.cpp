#pragma comment(linker, "/STACK:102400000,102400000")
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
const int N = 200020;
struct edge{
    LL to, nxt;
    edge(){}
    edge(LL _t, LL _n)
    {
        to = _t, nxt = _n;
    }
}e[N*2];
LL head[N], eN = 0;
void addedge(LL u, LL v)
{
    e[eN] = edge(v, head[u]);
    head[u] = eN++;
}
LL root, s[N], f[N];
bool vis[N];
LL maxn;
LL n;
LL getroot(LL now, LL fa, LL sz)
{
    LL cnt=1;
    LL mx=0;
    for(LL i=head[now]; i!=-1; i=e[i].nxt)
    {
        LL to=e[i].to;
        if(to==fa || vis[to]) continue;
        f[to]=getroot(to,now,sz);
        mx = max(mx,f[to]);
        cnt+=f[to];
    }
    mx = max(mx,sz-cnt);
    if(mx<maxn)
    {
        maxn=mx, root=now;
        for(LL i = head[now]; i != -1; i = e[i].nxt)
        {
            LL to = e[i].to;
            if(vis[to]) continue;
            if(to == fa)
            {
                s[to] = sz - cnt;
                continue;
            }
            s[to] = f[to];
        }
    }
    return cnt;
}
const LL mod = 1000000007;
#define ADD(x, y) ((x)=((x%mod)+(y%mod))%mod)
#define MUL(x, y) ((x)=((x%mod)*(y%mod))%mod)
LL num[N], ns[N];
void dfsgao(LL u, LL fa, LL d, LL& wv, LL& sv)
{
    ADD(wv, d), ADD(sv, 1);
    num[u] = 1, ns[u] = 0;
    for(LL i = head[u]; ~i; i = e[i].nxt)
    {
        LL v = e[i].to;
        if(vis[v] || v == fa) continue;
        dfsgao(v, u, d+1, wv, sv);
        num[u] += num[v];
        ns[u] += ns[v];
    }
    ns[u] += num[u];
}
LL wv[N], sv[N], pre[N], suf[N];
void dfs(LL u, LL& ans)
{
    maxn = INF;
    getroot(u, 0, s[u]);
    LL trt = root;
    vis[trt] = 1;
    //dfsgao(trt, 0);
    LL allwv = 0, allsv = 0, mulsv = 1;
    LL tail = 1;
    for(LL i = head[trt]; ~i; i = e[i].nxt)
    {
        LL v = e[i].to;
        if(vis[v]) continue;
        wv[tail] = sv[tail] = 0;
        dfsgao(v, u, 1, wv[tail], sv[tail]);
        //ADD(allwv, wv[tail]), ADD(allsv, sv[tail]);
        sv[tail]++;
        MUL(mulsv, sv[tail]);
        tail++;
    }
    LL cur = 0;
    pre[0] = suf[tail] = 1;
    for(LL i = 1; i < tail; i++) pre[i] = pre[i-1]*sv[i]%mod;
    for(LL i = tail-1; i>0; i--) suf[i] = suf[i+1]*sv[i]%mod;
    tail = 1;
    for(LL i = head[trt]; ~i; i = e[i].nxt)
    {
        LL v = e[i].to;
        if(vis[v]) continue;
        ADD(ans, ns[v]*pre[tail-1]%mod*suf[tail+1]%mod);
        tail++;
    }
    ADD(ans, mulsv);
//    for(LL i = 0; i < tail; i++)
//    {
//        ADD(ans, wv[i] * (allsv - sv[i]));
//        ADD(cur, sv[i] * (allsv - sv[i]));
//    }
//    ADD(ans, allwv);
//    ADD(ans, allsv);
//    ADD(ans, 1);
//    ADD(ans, cur/2);
    for(LL i = head[trt]; ~i; i = e[i].nxt)
    {
        LL v = e[i].to;
        if(vis[v]) continue;
        dfs(v, ans);
    }
}
int main()
{
    Open();
    LL T;scanf("%I64d", &T);
    while(T--)
    {
        eN = 0;
        memset(head, -1, sizeof(head));
        memset(vis, 0, sizeof(vis));
        memset(s, 0, sizeof(s));
        memset(f, 0, sizeof(f));
        scanf("%I64d", &n);
        for(LL i = 2; i <= n; i++)
        {
            LL x;
            scanf("%I64d", &x);
            addedge(x, i);
            addedge(i, x);
        }
        s[1] = n;
        LL ans = 0;
        dfs(1, ans);
        printf("%I64d\n", ADD(ans, mod));
    }
    return 0;
}

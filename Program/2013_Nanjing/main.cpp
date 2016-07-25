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
#include <sstream>
using namespace std;
typedef pair<int, int> PII;
#define ll long long

const int INF = 0x3f3f3f3f;
const int mod = 1000003;
const int N = 100010;
//vector<int> G[N];
int ve[N*2];
int nxt[N*2];
int head[N];
int et;
inline void add_edge(int u, int v)
{
    ve[et] = v;
    nxt[et] = head[u];
    head[u] = et++;
}
int a[N];
int root, s[N], f[N];//
bool vis[N];//
int n, maxn, K;
int ansu, ansv;
int minval[1000050][2];//
int inv[1000050];
int Ti;
int pow_mod(int x, int k, int mod)
{
    int res = 1;
    while(k)
    {
        if(k & 1) res = (ll)res * x %mod;
        x = (ll)x * x % mod;
        k >>= 1;
    }
    return res;
}

int get_root(int u, int fa, int sz)
{
    int cnt = 1;
    int mx = 0;
//    for(int i = 0; i < G[u].size(); i++)
//    {
    for(int i = head[u]; ~i; i = nxt[i])
    {
        int v = ve[i];
        if(v == fa || vis[v]) continue;
        f[v] = get_root(v, u, sz);
        mx = max(mx, f[v]);
        cnt += f[v];
    }
    mx = max(mx, sz-cnt);
    if(mx < maxn)
    {
        maxn = mx, root = u;
//        for(int i = 0; i < G[u].size(); i++)
        for(int i = head[u]; ~i; i = nxt[i])
        {
            int v = ve[i];
            if(vis[v]) continue;
            if(v == fa)
            {
                s[v] = sz - cnt;
                continue;
            }
            s[v] = f[v];
        }
    }
    return cnt;
}
PII sta[N];
int t;
void dfsgao(int u, int fa, int val)
{
    sta[t++] = PII(u, val);
//    int R = (ll)K*pow_mod(val, mod-2, mod)%mod;
    int R = (ll)K*inv[val]%mod;
    if(minval[R][1] == Ti && minval[R][0] != INF){
        int cu = u, cv = minval[R][0];
        if(cu > cv) swap(cu, cv);
        if(cu < ansu || (cu == ansu && cv < ansv))
            ansu = cu, ansv = cv;
    }


//    for(int i = 0 ; i < G[u].size(); i++)
    for(int i = head[u]; ~i; i = nxt[i])
    {
        int v = ve[i];
        if(v == fa || vis[v]) continue;
        dfsgao(v, u, (ll)val*a[v]%mod);
    }
}
void dfs(int u)
{
    maxn = INF;
    get_root(u, 0, s[u]);
    int trt = root;
    vis[trt] = 1;
    Ti++;
    minval[1][0] = trt;
    minval[1][1] = Ti;
    for(int i = head[trt]; ~i; i = nxt[i])
    {
//    for(int i = 0; i < G[trt].size(); i++)
//    {
        int v = ve[i];
        if(vis[v]) continue;
        t = 0;
        dfsgao(v, trt, (ll)a[trt]*a[v]%mod);
        for(int j = 0; j < t; j++)
        {
            int val = sta[j].second;
            int v = sta[j].first;
//            int L = (ll)val * pow_mod(a[trt], mod-2, mod)%mod;
            int L = (ll)val * inv[a[trt]]%mod;
            if(minval[L][1] != Ti){
                minval[L][1] = Ti;
                minval[L][0] = v;
            }else{
                minval[L][0] = min(minval[L][0], v);
            }
        }
    }
//    dfsgao(trt, 0, a[trt]);
//    for(int i = 0; i < G[trt].size(); i++)
//    {
    for(int i = head[trt]; ~i; i = nxt[i])
    {
        int v = ve[i];
        if(vis[v]) continue;
        dfs(v);
    }
}
int main()
{
    //freopen("/home/rainto96/in.txt", "r", stdin);
    for(int i = 0; i < mod; i++)
        inv[i] = pow_mod(i, mod-2, mod);
    Ti = 0;
    while(~scanf("%d%d", &n, &K))
    {
        memset(vis, 0, sizeof(vis));
        memset(s, 0, sizeof(s));
        memset(f, 0, sizeof(f));
        et = 0;
        memset(head, -1, sizeof(head));
//        for(int i = 0; i <= n; i++) G[i].clear();

        ansu = INF, ansv = INF;
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        for(int i = 1; i < n; i++)
        {
            int u,v;
            scanf("%d%d", &u, &v);
            add_edge(u, v);
            add_edge(v, u);
//            G[u].push_back(v);
//            G[v].push_back(u);
        }
        s[1] = n;
        dfs(1);
        if(ansu == INF){
            printf("No solution\n");
        }else{
            printf("%d %d\n", ansu, ansv);
        }
    }
    return 0;
}

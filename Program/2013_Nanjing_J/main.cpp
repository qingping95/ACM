#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 100010
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

struct node{
    int go[2];
    int cnt;
}pool[N*20];
int tot;//
vector<int> G[N];//
int pa[20][N];//
int w[N];//
int dep[N];//
int n,m;
int root[N];//

int insert(int pre, int val)
{
    int p = ++tot, ret = p;
    pool[p] = pool[pre];
    for(int i = 15; i >= 0; i--)
    {
        int tmp = (val>>i)&1;
        int cur = ++tot;
        pool[cur] = pool[pool[p].go[tmp]];
        pool[cur].cnt++;
        pool[p].go[tmp] = cur;
        p = cur;
    }
    return ret;
}
void dfs(int v, int p, int d)
{
    root[v] = insert(root[max(0, p)], w[v]);
    pa[0][v] = p;
    dep[v] = d;
    for(int i = 0; i < G[v].size(); i ++)
        if(G[v][i] != p) dfs(G[v][i], v, d+1);
}
void init()
{
    tot = 0;
    root[0] = 0;
    memset(pool, 0, sizeof(pool));
    dfs(1, -1, 0);
    for(int k = 0; k + 1 < 20; k++)
        for(int v = 1; v <= n; v++)
            if(pa[k][v] < 0) pa[k+1][v] = -1;
            else pa[k+1][v] = pa[k][pa[k][v]];
}
int lca(int u, int v)
{
    if(dep[u] > dep[v]) swap(u, v);
    for(int k = 0; k < 20; k++)
        if((dep[v] - dep[u]) >> k & 1)
            v = pa[k][v];
    if(u == v) return u;
    for(int k = 19; k >= 0; k--)
        if(pa[k][u] != pa[k][v])
            u = pa[k][u], v = pa[k][v];
    return pa[0][u];
}
int getans(int u, int v, int val)
{
    int LCA = lca(u, v);
    int pu = root[u], pv = root[v], pl = root[LCA];
    int ans = 0;
    for(int i = 15; i >= 0; i--)
    {
        int tmp = (val >> i)&1;
        int sum = pool[pool[pu].go[!tmp]].cnt + pool[pool[pv].go[!tmp]].cnt - 2 * pool[pool[pl].go[!tmp]].cnt;
        if(sum > 0){
            pu = pool[pu].go[!tmp];
            pv = pool[pv].go[!tmp];
            pl = pool[pl].go[!tmp];
            ans += 1<<i;
        }else{
            pu = pool[pu].go[tmp];
            pv = pool[pv].go[tmp];
            pl = pool[pl].go[tmp];
        }
    }
    return max(val ^ w[LCA], ans);
}
int main()
{
//    Open();
    while(~scanf("%d%d", &n, &m))
    {
        for(int i = 1; i <= n; i++)
            scanf("%d", &w[i]), G[i].clear();
        for(int i = 1; i < n; i++)
        {
            int u, v;scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        init();
        while(m--)
        {
            int u, v, z;
            scanf("%d%d%d", &u, &v, &z);
            printf("%d\n", getans(u, v, z));
        }
    }
    return 0;
}

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
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int deep[N], pa[20][N];
int n, m;
vector<int > G[N];
vector<int > depid[N];
int Tn = 1;
int ans[N];
int st[N], ed[N];
int dfs_init(int u, int fa, int dep)
{
    deep[u] = dep; pa[0][u] = fa;
    st[u] = Tn++;
    depid[dep].push_back(st[u]);
    for(int i = 0; i < G[u].size(); i++)
        dfs_init(G[u][i], u, dep+1);
    ed[u] = Tn;
}
void lca_init()
{
    int root = 0;
    dfs_init(root, -1, 0);
    for(int k = 0; k + 1 < 20; k ++)
        for(int v = 0; v <= n; v++)
            if(pa[k][v] < 0) pa[k+1][v] = -1;
            else pa[k+1][v] = pa[k][pa[k][v]];
}
int find_pfa(int u, int p)
{
    for(int i = 19; i >= 0; i--)
        if(p & (1 << i)) u = pa[i][u];
    return u;
}
int find_ans(int u, int dep){
    int l = st[u], r = ed[u];
    int lid = lower_bound(depid[dep].begin(), depid[dep].end(), l) - depid[dep].begin();
    int rid = upper_bound(depid[dep].begin(), depid[dep].end(), r) - depid[dep].begin();
    return max(0, rid - lid - 1);
}
int main()
{
    Open();
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        G[x].push_back(i);
    }
    scanf("%d", &m);
    lca_init();
    for(int i = 0; i < m; i++)
    {
        int v, p;
        scanf("%d%d", &v, &p);
        int pfa = find_pfa(v, p);
        if(pfa > 0) printf("%d", find_ans(pfa, deep[v]));
        else printf("0");
        if(i == m - 1) putchar('\n');
        else putchar(' ');
    }
    return 0;
}

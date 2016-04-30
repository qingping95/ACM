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
int depn[N];
int n, m;
vector<int > G[N];
vector<PII > que[N];
vector<int > quepre[N];
int ans[N];
int dfs_init(int u, int fa, int dep)
{
    deep[u] = dep; pa[0][u] = fa;
    for(int i = 0; i < G[u].size(); i++)
        dfs_init(G[u][i], u, dep+1);
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
void dfs(int u)
{
    for(int i = 0; i < que[u].size(); i ++)
        quepre[u].push_back(depn[que[u][i].first]);//求u子树的信息前，先记录之前的信息，
    for(int i = 0; i < G[u].size(); i++)
    {
        dfs(G[u][i]);
    }
	//回溯之后用当前信息与之前的信息比较就能得出当前子树的信息。
    for(int i = 0; i < que[u].size();i ++)
        ans[que[u][i].second] = max(0, depn[que[u][i].first] - 1 - quepre[u][i]);
    depn[deep[u]] ++;
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
        if(pfa > 0) que[pfa].push_back(PII(deep[v], i));
    }
    dfs(0);
    for(int i = 0; i < m; i ++)
    {
        printf("%d%c", ans[i], " \n"[i == m-1]);
    }
    return 0;
}
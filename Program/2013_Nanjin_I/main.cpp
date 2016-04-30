#include<iostream>
#include<stdio.h>
#include<string.h>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
#define scan(x) scanf("%d",&(x))
#define scan2(x,y) scanf("%d%d",&(x),&(y))
#define scan3(x,y,z) scanf("%d%d%d",&(x),&(y),&(z))
#define scan4(x,y,z,k) scanf("%d%d%d%d",&(x),&(y),&(z),&(k))
const int maxn = 1010;
const int maxm = maxn * maxn;
const double inf = 0x3f3f3f3f3f3f3f3fLL;
typedef pair<double, double> PDD;
const double eps = 1e-8;

int n, k;
double mst;
double mp[maxn][maxn], dp[maxn][maxn], best[maxn][maxn], dis[maxn];
int pre[maxn];//
bool vis[maxn];//
vector<int> edge[maxn];//
PDD p[maxn];//
void init()
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            dp[i][j] = inf;
        edge[i].clear();
        vis[i] = 0;
        pre[i] = -1;
        dis[i] = inf;
    }
}
#define D(x) (x)*(x)
double dist(int i, int j)
{
    return sqrt((double)D(p[i].first - p[j].first) + D(p[i].second - p[j].second));
}
void input()
{
    for(int i = 0; i < n; i++)
        scanf("%lf%lf", &p[i].first, &p[i].second);
    for(int i=0; i<n; i++)
        for(int j=i; j<n; j++)
            mp[i][j] = mp[j][i] = dist(i, j);
}
void prim()
{
    int i, j, k;
    for(i = 1; i < n; i++)
    {
        dis[i] = mp[0][i];
        pre[i] = 0;
    }
    dis[0] = inf;
    vis[0] = 1;
    pre[0] = -1;
    mst = 0;

    for(i = 0; i < n-1; i++)
    {
        k = 0;
        for(j = 1; j < n; j++)
            if(!vis[j] && dis[k] > dis[j] + eps)
                k = j;

        vis[k] = 1;
        mst += dis[k];
        //建最小生成树
        if(pre[k] != -1)
            edge[k].push_back(pre[k]),
                 edge[pre[k]].push_back(k);

        for(j = 1; j < n; j++)
            if(!vis[j] && dis[j] > mp[k][j] + eps)
                dis[j] = mp[k][j], pre[j] = k;
    }
}
double dfs1(int u, int fa, int rt) // 求 点rt 到 以u为根的数及其子树的最小距离
{
    int i;
    for(i = 0; i < edge[u].size(); i++)
    {
        int v = edge[u][i];
        if(v == fa) continue;
        dp[rt][u] = min(dp[rt][u], dfs1(v, u, rt));
    }
    if(fa != rt) dp[rt][u] = min(dp[rt][u], mp[rt][u]);
    return dp[rt][u];
}
double dfs2(int u, int fa, int rt) // 求 以rt为根的数及其子树 到 以u为根的数及其子树的最小距离
{
    int i;
    double ans = dp[u][rt];
    for(i = 0; i < edge[u].size(); i++)
    {
        int v = edge[u][i];
        if(v == fa) continue;
        ans = min(ans, dfs2(v, u, rt));
    }
    return ans;
}
void solve()
{
    int i,j;
    for(i = 0; i < n; i++)
        dfs1(i, -1, i);
    for(i = 0; i < n; i++)
        for(j = 0; j < edge[i].size(); j++)
        {
            int v = edge[i][j];
            best[i][v] = best[v][i] = dfs2(v, i, i);
        }
}
void query()
{
    double ans = mst;
    for(int i=1; i<n; i++)
    {
        int x=i;
        for(int j=0; j<edge[i].size() ; j++)
        {
            int y=edge[i][j];
            if(y == 0) continue;
//            if(x<y) continue;
            double sum = mst - mp[x][y] + best[x][y];
            ans = max(sum, ans);
        }
    }
    printf("%.2f\n",ans*k);
}

int main()
{
#ifndef ONLINE_JUDGE
    //freopen("F:/in.txt","r",stdin);
#endif
    int T;
    scan(T);
    while(T--)
    {
        scanf("%d%d", &n, &k);
        init();
        input();
        prim();
        solve();
        query();
    }
}

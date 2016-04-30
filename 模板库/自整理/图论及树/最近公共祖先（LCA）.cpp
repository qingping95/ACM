
//最近公共祖先（LCA）
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

#include <vector>

vector<int> g[N];//
int root;
int parent[LOG_N][N];
int depth[N];

void dfs(int v,int p,int d)
{
    parent[0][v]=p;
    depth[v]=d;
    for(int i=0;i<g[v].size();i++)
    {
        if(g[v][i]!=p) dfs(g[v][i],v,d+1);
    }
}

//预处理
void init()//预处理出parent
{
    root = 0; // or 1
    dfs(root,-1,0);
    for(int k=0;k+1<LOG_N;k++)
    {
        for(int v=1;v<=n;v++)//这里根据顶点的起始下标改变
        {
            if(parent[k][v]<0) parent[k+1][v]=-1;
            else parent[k+1][v]=parent[k][parent[k][v]];
        }
    }
}
//计算u和v的LCA
int lca(int u,int v)
{
    //让u和v向上走到同一深度
    if(depth[u]>depth[v]) swap(u,v);
    for(int k=0;k<LOG_N;k++)
        if((depth[v]-depth[u])>>k&1)
            v=parent[k][v];
    if(u==v) return u;
    //利用二分搜索计算LCA
    for(int k=LOG_N-1;k>=0;k--)
        if(parent[k][u]!=parent[k][v])
            u=parent[k][u], v=parent[k][v];
    return parent[0][u];
}
//最近公共祖先（LCA）


//tarjan离线LCA，先将询问全部存下来，然后一次DFS求出所有询问的答案
struct info{
    int u, v, id;
    info(int u = 0, int v = 0, int id = 0):u(u), v(v), id(id){}
};
int n, m;
vector<int> g[N];
vector<PII> query[N];
vector<info> rt[N];
int Uto[N], toU[N], ma[N], mi[N], sn[N], ans[N], fa[N];
bool vis[N];
void init()
{
    for(int i=0;i<=n;i++)
    {
        vis[i] = 0;
        g[i].clear();
        query[i].clear();
        rt[i].clear();
        fa[i] = i;
        Uto[i] = toU[i] = 0;
        ma[i] = mi[i] = sn[i];
    }
}
int Find(int u)
{
    if(fa[u] == u) return u;
    int root = Find(fa[u]);
    Uto[u] = max(Uto[u], max(Uto[fa[u]], ma[fa[u]] - mi[u]));
    toU[u] = max(toU[u], max(toU[fa[u]], ma[u] - mi[fa[u]]));
    ma[u] = max(ma[u], ma[fa[u]]);
    mi[u] = min(mi[u], mi[fa[u]]);
    return fa[u] = root;
}
void lca(int u)
{
    vis[u] = 1;
    for(int i=0;i<query[u].size();i++)
    {
        int v = query[u][i].first, id = query[u][i].second;
        if(vis[v])
        {
            int root = Find(v);
            if(id < 0) rt[root].push_back(info(v, u, -id));
            else rt[root].push_back(info(u, v, id));
        }
    }
    for(int i=0;i<g[u].size();i++)
    {
        int v = g[u][i];
        if(vis[v]) continue;
        lca(v);
        fa[v] = u;
    }

    for(int i=0;i<rt[u].size(); i++)
    {
        int x = rt[u][i].u, y = rt[u][i].v, id = rt[u][i].id;
        //cout<<"lca: "<<u<<"("<<x<<","<<y<<")  ans:";
        Find(x), Find(y);
        ans[id] = max(Uto[x], max(toU[y], ma[y] - mi[x]));
        //cout<<id<<":"<<ans[id]<<endl;
    }
}
//离线LCA

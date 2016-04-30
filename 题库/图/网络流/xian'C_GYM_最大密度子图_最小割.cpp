#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 222
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
const double eps = 1e-9;
void Open()
{
#ifndef ONLINE_JUDGE
    freopen("D:/in.txt","r",stdin);
    //freopen("D:/my.txt","w",stdout);
#endif // ONLINE_JUDGE
}
int dcmp(double x)
{
    if(fabs(x) < eps) return 0;
    return x > eps;
}
struct Edge
{
    int from, to;
    double cap, flow;
};
struct ISAP
{
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[N];   // 邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
    bool vis[N];        // BFS使用
    int d[N];           // 从起点到i的距离
    int cur[N];        // 当前弧指针
    int p[N];          // 可增广路上的上一条弧
    int num[N];        // 距离标号计数

    void AddEdge(int from, int to, double cap)
    {
        edges.push_back((Edge)
        {
            from, to, cap, 0
        });
        edges.push_back((Edge)
        {
            to, from, 0, 0
        });
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool BFS()
    {
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        Q.push(t);
        vis[t] = 1;
        d[t] = 0;
        while(!Q.empty())
        {
            int x = Q.front();
            Q.pop();
            for(int i = 0; i < G[x].size(); i++)
            {
                Edge& e = edges[G[x][i]^1];
                if(!vis[e.from] && dcmp(e.cap - e.flow) > 0)
                {
                    vis[e.from] = 1;
                    d[e.from] = d[x] + 1;
                    Q.push(e.from);
                }
            }
        }
        return vis[s];
    }

    void ClearAll(int n)
    {
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void ClearFlow()
    {
        for(int i = 0; i < edges.size(); i++) edges[i].flow = 0;
    }

    double Augment()
    {
        int x = t;
        double a = INF;
        while(x != s)
        {
            Edge& e = edges[p[x]];
            a = min(a, e.cap-e.flow);
            x = edges[p[x]].from;
        }
        x = t;
        while(x != s)
        {
            edges[p[x]].flow += a;
            edges[p[x]^1].flow -= a;
            x = edges[p[x]].from;
        }
        return a;
    }

    double Maxflow(int s, int t)
    {
        this->s = s;
        this->t = t;
        double flow = 0;
        BFS();
        memset(num, 0, sizeof(num));
        for(int i = 0; i < n; i++) num[d[i]]++;
        int x = s;
        memset(cur, 0, sizeof(cur));
        while(d[s] < n)
        {
            if(x == t)
            {
                flow += Augment();
                x = s;
            }
            int ok = 0;
            for(int i = cur[x]; i < G[x].size(); i++)
            {
                Edge& e = edges[G[x][i]];
                if(dcmp(e.cap - e.flow) > 0 && d[x] == d[e.to] + 1)   // Advance
                {
                    ok = 1;
                    p[e.to] = G[x][i];
                    cur[x] = i; // 注意
                    x = e.to;
                    break;
                }
            }
            if(!ok)   // Retreat
            {
                int m = n-1; // 初值注意
                for(int i = 0; i < G[x].size(); i++)
                {
                    Edge& e = edges[G[x][i]];
                    if(dcmp(e.cap - e.flow) > 0) m = min(m, d[e.to]);
                }
                if(--num[d[x]] == 0) break;
                num[d[x] = m+1]++;
                cur[x] = 0; // 注意
                if(x != s) x = edges[p[x]].from;
            }
        }
        return flow;
    }

    vector<int> Mincut()   // call this after maxflow
    {
        BFS();
        vector<int> ans;
        for(int i = 0; i < edges.size(); i++)
        {
            Edge& e = edges[i];
            if(!vis[e.from] && vis[e.to] && e.cap > 0) ans.push_back(i);
        }
        return ans;
    }

    void Reduce()
    {
        for(int i = 0; i < edges.size(); i++) edges[i].cap -= edges[i].flow;
    }

    void print()
    {
        printf("Graph:\n");
        for(int i = 0; i < edges.size(); i++)
            printf("%d->%d, %d, %d\n", edges[i].from, edges[i].to , edges[i].cap, edges[i].flow);
    }
};


ISAP mf;

int U;
int n, a[N];
int deg[N];
int source, sink;
int check(double g)
{
    mf.ClearAll(n+2);
    memset(deg, 0, sizeof(deg));
    for(int i=1; i<=n; i++)
        for(int j = i+1; j <= n; j++)
            if(a[j] < a[i]) mf.AddEdge(i, j, 1), mf.AddEdge(j, i, 1), deg[i]++, deg[j]++;
    for(int i=1; i<=n; i++)
        mf.AddEdge(source, i, U);
    for(int i=1; i<=n; i++)
        mf.AddEdge(i, sink, g*2.0 + 1.0*U - 1.0*deg[i]);
    double curf = mf.Maxflow(source, sink);
    return dcmp((U*n - curf)/2.0);
}
int main()
{
    Open();
    int T;
    scanf("%d", &T);
    int cas = 1;
    while(T--)
    {
        scanf("%d", &n);
        for(int i=1; i<=n; i++)
            scanf("%d", &a[i]);
        sink = n+1, source = 0;
        U = n+3;
        double lb = 0, ub = n*n;
//        int tmp = check(6.25);
        while(lb + eps < ub)
        {
            double mid = (lb + ub) / 2;
            int tmp = check(mid);
            if(tmp > 0) lb = mid;
            else ub = mid;
        }
        printf("Case #%d: %.12f\n", cas++, lb+eps);
    }
    return 0;
}
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<n)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
//        freopen("/home/qingping/out.txt","w",stdout);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 625*500;
struct Edge
{
    int from, to;
    int cap, flow;
};
struct DINIC
{
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[N];   // 邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
    bool vis[N];        // BFS使用
    int d[N];           // 从起点到i的距离
    int cur[N];        // 当前弧指针

    void AddEdge(int from, int to, int cap)
    {
        edges.push_back((Edge){from, to, cap, 0});
        edges.push_back((Edge){to, from, 0, 0});
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool BFS()
    {
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        Q.push(s);
        vis[s] = 1;
        d[s] = 0;
        while(!Q.empty())
        {
            int x = Q.front();
            Q.pop();
            for(int i = 0; i < G[x].size(); i++)
            {
                Edge& e = edges[G[x][i]];
                if(!vis[e.to] && e.cap - e.flow > 0)
                {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    void ClearAll(int n)
    {

        this -> n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void ClearFlow()
    {
        for(int i = 0; i < edges.size(); i++) edges[i].flow = 0;
    }
    int DFS(int x, int a)
    {
        if(x == t||a == 0) return a;
        int flow = 0, f;
        for(int &i = cur[x]; i < G[x].size(); i++)
        {
            Edge& e = edges[G[x][i]];
            if(d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap-e.flow))) > 0)
            {
                e.flow += f;
                edges[G[x][i]^1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }

    int Maxflow(int s, int t)
    {
        this->s = s;
        this->t = t;
        int flow = 0;
        while(BFS())
        {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF);
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
            if(edges[i].cap != 0)
                printf("%d->%d, %d, %d\n", edges[i].from, edges[i].to , edges[i].cap, edges[i].flow);
    }
};

DINIC mf;
char str[35][35];
int dir[][2] = {-1, 0, 0, -1, 1, 0, 0, 1, 0, 0};
int main()
{
//    Open();
    int n;
    int cas = 1;
    while(~scanf("%d", &n) && n)
    {
        for(int i = 0; i < n; i++)
            scanf("%s", &str[i]);
        bool flag = false;
        for(int st = n; !flag; st++)
        {
//            cout<<"fUCK"<<endl;
            int s = 2*n*n*st;
            int t = s+1;
            mf.ClearAll(t+1);
            for(int i = 0; i < n; i++)
            {
                mf.AddEdge(s, i*n, 1);
                mf.AddEdge(2*(st-1)*n*n+n*n+i*n+n-1, t, 1);
            }
            for(int ct = 0; ct+1 < st; ct++)
            {
                for(int i = 0; i < n; i++)
                    for(int j = 0; j < n; j++)
                    {
                        for(int k = 0; k < 5; k++)
                        {
                            int cx = i + dir[k][0];
                            int cy = j + dir[k][1];
                            if(!CHECK(cx, cy) || str[cx][cy] == 'X') continue;
                            mf.AddEdge(2*ct*n*n+i*n+j+n*n, 2*(ct+1)*n*n+cx*n+cy, 1);
                        }
                        mf.AddEdge(2*ct*n*n+i*n+j, 2*ct*n*n+i*n+j+n*n, 1);
                    }
            }
            int ct = st-1;
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                {
//                    cerr<<2*ct*n*n+i*n+j<<"->"<<2*ct*n*n+i*n+j+n*n<<endl;
                    mf.AddEdge(2*ct*n*n+i*n+j, 2*ct*n*n+i*n+j+n*n, 1);
                }
//            mf.print();
//            cout<<mf.Maxflow(s, t)<<endl;
            int tmp = mf.Maxflow(s, t);
//            cout<<st<<"->"<<tmp<<endl;
            if(tmp == n)
            {
                flag = true;
                printf("Case %d: %d\n", cas++, st-1);
                break;
            }
//            if(st == 4) break;
        }
//        break;
    }

    return 0;
}


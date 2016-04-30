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
const int N = 20*20;
struct Edge{
    int u, v, cap, flow, cost;
};
struct MCMF{
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[N];
    int inq[N];
    int d[N];
    int p[N];
    int a[N];

    void init(int n, int s, int t) {
        this -> n = n;
        this -> s = s;
        this -> t = t;
        for(int i = 0; i<n; i++) G[i].clear();
        edges.clear();
    }
    void addedge(int u, int v, int cap, int cost){
        edges.push_back((Edge){u, v, cap, 0, cost});
        edges.push_back((Edge){v, u, 0, 0, -cost});
        m = edges.size();
        G[u].push_back(m-2);
        G[v].push_back(m-1);
        //cerr<<u<<" -> "<<v<<" : "<<cap<<", "<<cost<<endl;
    }
    bool SPFA(int& flow, int& cost, bool can){
        for(int i=0;i<n;i++) d[i] = INF;
        memset(inq, 0, sizeof(inq));
        d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;
        queue<int> Q;
        Q.push(s);
        while(!Q.empty()){
            int u = Q.front(); Q.pop();
            inq[u] = 0;
            for(int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(e.cap > e.flow && d[e.v] > d[u] + e.cost){
                    d[e.v] = d[u] + e.cost;
                    p[e.v] = G[u][i];
                    a[e.v] = min(a[u], e.cap - e.flow);
                    if(!inq[e.v]) {Q.push(e.v); inq[e.v] = 1;}
                }
            }
        }
        if(d[t] == INF) return false;
        if(d[t] >= 0 && can) return false;
        flow += a[t];
        cost += d[t];
        int u = t;
        while(u != s){
            edges[p[u]].flow += a[t];
            edges[p[u]^1].flow -= a[t];
            u = edges[p[u]].u;
        }
        return true;
    }
    int Mincost(int &flow, int &cost, bool can) {
        while(SPFA(flow, cost, can));
        return cost;
    }
}mcmf;
char mar[N][N];
#define ID(x, y) (x*m + y)
int du[N*N];
int main()
{
//    Open();
    int T;scanf("%d", &T);
    int cas = 0;
    while(T--)
    {
        printf("Case %d : ", ++cas);
        int n, m, K;
        memset(du, 0, sizeof(du));
        scanf("%d%d%d", &n, &m, &K);
        for(int i = 0; i < n; i++) scanf("%s", mar[i]);
        int ts = n*m*2;
        int s = ts+1, t = s+1, ss = t+1, tt = ss+1;
        mcmf.init(tt+1, ss, tt);
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                int u = ID(i, j);
                int ru = u*2;
                int chu = ru+1;

                du[ru]--;
                du[chu]++;

                mcmf.addedge(ts, ru, 1, 0);
                mcmf.addedge(chu, t, 1, 0);
                for(int k = j+1; k < m; k++)
                {
                    int v = ID(i, k);
                    int w = -(k - j - 1);
                    if(mar[i][j] == mar[i][k]) w += mar[i][k] - '0';
                    mcmf.addedge(chu, v*2, 1, -w);
                }
                for(int k = i+1; k < n; k++)
                {
                    int v = ID(k, j);
                    int w = -(k - i - 1);
                    if(mar[i][j] == mar[k][j]) w += mar[i][j] - '0';
                    mcmf.addedge(chu, v*2, 1, -w);
                }
            }
        }
        mcmf.addedge(s, ts, K, 0);
        mcmf.addedge(t, s, n*m*5, 0);
        int sum = 0;
        for(int i = 0; i < n*m*2; i++)
        {
            if(du[i] > 0) sum += du[i], mcmf.addedge(ss, i, du[i], 0);
            if(du[i] < 0) mcmf.addedge(i, tt, -du[i], 0);
        }
        int flow = 0, cost = 0;
        mcmf.Mincost(flow, cost, false);

        if(flow != sum) printf("-1\n");
        else {
            mcmf.G[mcmf.n--].clear();
            mcmf.G[mcmf.n--].clear();
            mcmf.s = s, mcmf.t = t;
            mcmf.Mincost(flow, cost, true);
            printf("%d\n", max(0, -cost));
        }
    }
    return 0;
}

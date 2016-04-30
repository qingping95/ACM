#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 1000
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}

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
//        cerr<<u<<" -> "<<v<<" : "<<cost<<endl;
    }
    bool SPFA(int& flow, int& cost){
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
        if(d[t] >= 0) return false;
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
    int Mincost() {
        int flow = 0, cost = 0;
        while(SPFA(flow, cost));
        return cost;
    }
}mcmf;
struct info{int ty, lv, atk;}mons[N];
vector<int> G[2];
int val[N][N];
int n, m;
int main()
{
    Open();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        memset(val, 0, sizeof(val));
        G[0].clear();G[1].clear();
        for(int i = 1; i <= n; i++)
        {
            int ty, lv, atk;
            scanf("%d%d%d", &ty, &lv, &atk);
            mons[i] = (info){ty, lv, atk};
            G[ty].push_back(i);
        }
        while(m--)
        {
            int lv, atk, r;
            scanf("%d%d%d", &lv, &atk, &r);
            if(r == 0){
                for(int i = 0; i < G[1].size();i++)
                    for(int j = 0; j < G[0].size(); j++) if(mons[G[1][i]].lv + mons[G[0][j]].lv== lv)
                        val[G[1][i]][G[0][j]] = max(val[G[1][i]][G[0][j]], atk);
            }
            if(r == 1){
                int x;
                scanf("%d", &x);
                if(mons[x].ty) {
                    for(int i = 0; i < G[0].size(); i++) if(mons[x].lv + mons[G[0][i]].lv == lv)
                        val[x][G[0][i]] = max(val[x][G[0][i]], atk);
                }else{
                    for(int i = 0; i < G[1].size(); i++) if(mons[x].lv + mons[G[1][i]].lv == lv)
                        val[G[1][i]][x] = max(val[G[1][i]][x], atk);
                }
            }
            if(r == 2){
                int x,y;
                scanf("%d%d", &x, &y);
                if(mons[y].ty) swap(x, y);
                val[x][y] = max(val[x][y], atk);
            }
        }
        int s = 0, t = n + 1;
        mcmf.init(t+1, s, t);
        for(int i = 0; i < G[1].size(); i++) mcmf.addedge(s, G[1][i], 1, -mons[G[1][i]].atk), mcmf.addedge(G[1][i], t, 1, 0);
        for(int i = 0; i < G[0].size(); i++) mcmf.addedge(G[0][i], t, 1, -mons[G[0][i]].atk), mcmf.addedge(s, G[0][i], 1, 0);
        for(int i = 0; i < G[1].size(); i++)
            for(int j = 0; j < G[0].size(); j++)
            {
                int l = G[1][i], r = G[0][j];
                if(val[l][r]) mcmf.addedge(l, r, 1, mons[l].atk + mons[r].atk - val[l][r]);
            }
        printf("%d\n", -mcmf.Mincost());
    }
    return 0;
}

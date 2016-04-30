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
struct ZKW_flow{
    const static int MAXN = 210;
    const static int MAXE = 210*210;
    int st, ed, ecnt, n;
    int head[MAXN];
    int cap[MAXE], cost[MAXE], to[MAXE], next[MAXE];

    void init(){
        memset(head, 0, sizeof(head));
        ecnt = 2;
    }
    //cc容量，ww花费
    void addEdge(int u, int v, int cc, int ww){
        cap[ecnt] = cc; cost[ecnt] = ww; to[ecnt] = v;
        next[ecnt] = head[u]; head[u] = ecnt++;
        cap[ecnt] = 0; cost[ecnt] = -ww; to[ecnt] = u;
        next[ecnt] = head[v]; head[v] = ecnt++;
    }

    int dis[MAXN];

    void SPFA(){
        for(int i = 1; i <= n; ++i) dis[i] = INF;
        priority_queue<pair<int, int> > Q;
        dis[st] = 0;
        Q.push(make_pair(0, st));
        while(!Q.empty()){
            int u = Q.top().second, d = -Q.top().first;
            Q.pop();
            if(dis[u] != d) continue;
            for(int p = head[u]; p; p = next[p]){
                int &v = to[p];
                if(cap[p] && dis[v] > d + cost[p]){
                    dis[v] = d + cost[p];
                    Q.push(make_pair(-dis[v], v));
                }
            }
        }
        for(int i = 1; i <= n; ++i) dis[i] = dis[ed] - dis[i];
    }

    int minCost, maxFlow;
    bool use[MAXN];

    int add_flow(int u, int flow){
        if(u == ed){
            maxFlow += flow;
            minCost += dis[st] * flow;
            return flow;
        }
        use[u] = true;
        int now = flow;
        for(int p = head[u]; p; p = next[p]){
            int &v = to[p];
            if(cap[p] && !use[v] && dis[u] == dis[v] + cost[p]){
                int tmp = add_flow(v, min(now, cap[p]));
                cap[p] -= tmp;
                cap[p^1] += tmp;
                now -= tmp;
                if(!now) break;
            }
        }
        return flow - now;
    }

    bool modify_label(){
        int d = INF;
        for(int u = 1; u <= n; ++u) if(use[u])
            for(int p = head[u]; p; p = next[p]){
                int &v = to[p];
                if(cap[p] && !use[v]) d = min(d, dis[v] + cost[p] - dis[u]);
            }
        if(d == INF) return false;
        for(int i = 1; i <= n; ++i) if(use[i]) dis[i] += d;
        return true;
    }

    //nn表示图中点的数量，图中的点编号从1开始。
    PII min_cost_flow(int ss, int tt, int nn){
        st = ss, ed = tt, n = nn;
        minCost = maxFlow = 0;
        SPFA();
        while(true){
            while(true){
                for(int i = 1; i <= n; ++i) use[i] = 0;
                if(!add_flow(st, INF)) break;
            }
            if(!modify_label()) break;
        }
        return PII(minCost, maxFlow);
    }
}G;
int n;
struct Point
{
    int x, y, z, w;
    void read()
    {
        scanf("%d%d%d%d", &x, &y, &z, &w);
    }
    inline int D(int x)
    {
        return x*x;
    }
    inline int dist(Point& o)
    {
        return floor(sqrt((double)D(o.x - x) + D(o.y - y) + D(o.z - z)))+0.5;
    }
}p[111];
int main()
{
//    Open();
    while(~scanf("%d", &n), n)
    {
        int allw = 0;
        for(int i = 1; i <= n; i++)
        {
            p[i].read();
            allw += p[i].w;
        }
        G.init();
        int s = 2 * n + 1, t = s + 1;
        for(int i = 1; i <= n; i++){
            G.addEdge(s, i, p[i].w, 0);
            G.addEdge(i+n, t, p[i].w, 0);
            for(int j = 1; j <= n; j++){
                if(i == j) continue;
                G.addEdge(i, j+n, INF, p[i].dist(p[j]));
            }
        }
        PII res = G.min_cost_flow(s, t, t);
        if(res.second != allw) res.first = -1;
        printf("%d\n", res.first);
    }
    return 0;
}

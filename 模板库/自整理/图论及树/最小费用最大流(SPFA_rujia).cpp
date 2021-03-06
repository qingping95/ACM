#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
#include <climits>
#include <assert.h>
#include <bitset>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> PII;
const int N = 201;
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
		//记得判断不可达的情况！！！！！！！！！！！！！！！！！
        if(d[t] == INF) return false;
        flow += a[t];
        cost += d[t]*a[t];
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
vector<Edge> pe;
int w[N];
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++)
    {
        int u, v, c, f;
        scanf("%d%d%d%d", &u, &v, &c, &f);
        w[v] += f;
        w[u] -= f;
        pe.push_back((Edge){u, v, c, f, 0});
    }
    int s = 0, t = n+1;
    mcmf.init(t+1, s, t);
    mcmf.addedge(n, 1, INF, 0);
    for(int i = 1; i <= n; i++)
    {
        if(w[i] > 0) mcmf.addedge(s, i, w[i], 0);
        if(w[i] < 0) mcmf.addedge(i, t, -w[i], 0);
    }
    int ans = 0;
    for(int i = 0; i < m; i++)
    {
        int u = pe[i].u, v = pe[i].v, c = pe[i].cap, f = pe[i].flow;
        if(f > c) {
            ans += f-c;
            mcmf.addedge(u, v, INF, 2);
            mcmf.addedge(v, u, f-c, 0);
            mcmf.addedge(v, u, c, 1);
        }else{
            mcmf.addedge(u, v, c-f, 1);
            mcmf.addedge(u, v, INF, 2);
            mcmf.addedge(v, u, f, 1);
        }
    }
    ans += mcmf.Mincost();
    printf("%d\n", ans);
    return 0;
}


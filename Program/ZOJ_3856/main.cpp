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
const int N = 2010;
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
        if(d[t] == INF) return false;
        flow += a[t];
        cost += d[t]*flow;
        int u = t;
        while(u != s){
            edges[p[u]].flow += a[t];
            edges[p[u]^1].flow -= a[t];
            u = edges[p[u]].u;
        }
        return true;
    }
    int Mincost(int limit) {
        int flow = 0, cost = 0;
        while(SPFA(flow, cost));
        if(flow != limit) cost = -1;
        return cost;
    }
}mcmf;
int a[N];
char op[3];
char str[11];
int f[344];
bool judge(char *s, int val, bool isp)
{
    int len = strlen(s);
    for(int i = 0; i < len; i++)
    {
        int idx = isp ? 8 - i - 1 : len - i - 1;
        if(((val >> idx) & 1) != s[i] - '0') return false;
    }
    return true;
}
int main()
{
    Open();
    f['P'] = 1;
    int T;
    scanf("%d", &T);
    int cas = 1;
    while(T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
        }
        int s = n+m, t = s+1;
        mcmf.init(t+1, s, t);
        for(int i = 0; i < m; i++)
        {
            scanf("%s%s", op, str);
            int w;
            scanf("%d", &w);
            int cnt = 0;
            for(int j = 0; j < n;j++) if(judge(str, a[j], f[op[0]]))
            {
                mcmf.addedge(n+i, j, 1, 0);
                cout<<i<<" -> "<<j<<" : "<<str<<" -> "<<a[j]<<endl;
                cnt++;
            }
            mcmf.addedge(s, n+i, cnt, w);
        }
        for(int i = 0; i < n; i++)
        {
            mcmf.addedge(i, t, 1, 0);
        }
        printf("Case #%d: %d\n", cas++, mcmf.Mincost(n));
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 2020
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef pair<long long,long long> PII;
const int INF=0x3f3f3f3f;
const long int mod = 1000000007;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
struct node
{
    int h, d;
    bool operator<(const node& o)const{
        return h > o.h || (h == o.h && d < o.d);
    }
}app[N];

struct Edge{
    int u, v, cap, flow, cost;
};
int cas = 1;
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
        for(int i=0;i<n;i++) d[i] = INF, inq[i] = 0;
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

template <class T>
void read(T &x) {
	for (++ch; *ch <= 32; ++ch);
	for (x = 0; '0' <= *ch; ch++)	x = x * 10 + *ch - '0';
}

int main()
{
    Open();
    ch = buf - 1;
	fread(buf, 1, 1000 * 35 * 1024, stdin);

    long long T;
    read(T);
//    scanf("%I64d", &T);
    while(T--)
    {
        cas++;
        int n;
        read(n);
//        scanf("%d", &n);
        for(int i = 0; i < n; i++){
            read(app[i].h); read(app[i].d);
//            scanf("%d%d", &app[i].h, &app[i].d);
        }
        sort(app, app+n);
        int s = 2*n, t = 2*n+1, ss = 2*n+2;
        mcmf.init(2*n+3, s, t);
        for(int i = 0; i < n; i++) mcmf.addedge(i, n+i, 1, -1), mcmf.addedge(i, n+i, 1, 0);//由于下面的剪枝，这里必须加一条边使得该流不花费费用(不吃这个苹果)经过这个点
        for(int i = 0; i < n; i++){
            int pre = INF;
            for(int j = i + 1; j < n; j++)
            {
                if(app[i].d <= app[j].d && app[j].d < pre)
                    mcmf.addedge(i+n, j, 2, 0), pre = app[j].d;
            }
        }
        mcmf.addedge(s, ss, 2, 0);
        for(int i = 0; i < n; i++){
            mcmf.addedge(ss, i, 2, 0);
            mcmf.addedge(i+n, t, 2, 0);
        }
        write(-mcmf.Mincost());
        puts("");
//        printf("%d\n", -mcmf.Mincost());
    }
    return 0;
}

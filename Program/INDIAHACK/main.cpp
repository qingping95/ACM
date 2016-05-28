#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
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
struct Edge{
    int u, v;
    double cap, flow;
    void clearFlow()
    {
        flow = 0;
    }
};
vector<Edge> edges;
vector<int> G[2111];

int n, m, x;
int p[55];
bool in[55];
double a[55];
const double eps = 1e-10;
int dcmp(double x)
{
    return (x>eps)-(x<-eps);
}
void addedge(int u, int v, int cap){
    edges.push_back((Edge){u, v, cap, 0});
    edges.push_back((Edge){v, u, 0, 0});
    int m = edges.size();
    G[u].push_back(m-2);
    G[v].push_back(m-1);
//        cerr<<u<<" -> "<<v<<" : "<<cost<<endl;
}
bool SPFA(double unit)
{
    for(int i = 0; i <= n; i++) a[i] = 0;
    memset(in, 0, sizeof(in));
    queue<int> q;
    q.push(1);
    in[1] = 1;
    a[1] = INF;
    while(!q.empty())
    {
        int u = q.front();q.pop();
        in[u] = 0;
        for(int i = 0; i < G[u].size(); i++)
        {
            Edge& e = edges[G[u][i]];
            if(e.cap > e.flow + eps && a[e.v] < min(a[u], e.cap-e.flow)){
                a[e.v] = min(a[u], e.cap-e.flow);
                p[e.v] = G[u][i];
                if(!in[e.v]){q.push(e.v);in[e.v] = 1;}
            }
        }
    }
    if((int)(a[n] / unit) <= 0) return false;
    return true;
}
bool check(double unit)
{
    for(int i = 0; i < edges.size(); i++)
        edges[i].clearFlow();
    int res = 0;
    while(res < x)
    {
        bool flag = SPFA(unit);
        if(flag == true) {
            int num = a[n] / unit;
            res += num;
            int u = n;
            while(u != 1)
            {
                edges[p[u]].flow += unit * num;
                edges[p[u]^1].flow -= unit * num;
                u = edges[p[u]].u;
            }
        }else return false;
    }
    if(res >= x) return true;
    else return false;
}
int main()
{
    //Open();
    scanf("%d%d%d", &n, &m, &x);
    int ma = 0;
    for(int i = 0; i < m; i++)
    {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        addedge(u, v, c);
//        G[u].push_back((edge){v, c, 0});
//        G[v].push_back((edge){u, 0, 0});
        ma = max(ma, c);
    }
    double lb = 0, ub = ma + 10;
    double ans = 0;
    //cout<<check(10.2222/23)<<endl;
    for(int i = 0; i < 200; i++)
//    while(lb + eps < ub)
    {
        double mid = (ub + lb) / 2;
        if(check(mid)) lb = ans = mid;
        else ub = mid;
    }
    printf("%.12f\n", ans*x);
    return 0;
}

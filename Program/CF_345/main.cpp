#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
//#include <unordered_map>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int a[1001111];
int d[1001111];
const int N = 1000111;

int pa[N];
void init(int n)
{
    for(int i = 0; i < n; i++)
        pa[i] = i;
}
int find(int x)
{
    return pa[x] == x ? x : pa[x] = find(pa[x]);
}
int unite(int u, int v)
{
    u = find(u);
    v = find(v);
    pa[u] = v;
}
vector<PII> G[1001111];
PII b[1001111];
bool vis[1001111];
void SPFA(int s)
{
    priority_queue<PII> q;
    memset(d, 0, sizeof(d));
    d[s] = 0;
    q.push(PII(0, s));
    while(!q.empty())
    {
        int u = q.top().second, dist = q.top().first;
        q.pop();
        if(d[u] > dist) continue;
        for(int i = 0; i < G[u].size(); i++)
        {
            int v = G[u][i].first, w = G[u][i].second;
            if(d[v] < d[u] + w)
            {
                d[v] = d[u] + w;
                q.push(PII(d[v], v));
            }
        }
    }
}
int main()
{
    //Open();
    int n, m;
    scanf("%d%d", &n, &m);
    init(n*m+1);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &a[i*m+j]);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            b[j] = PII(a[i*m+j], i*m+j);
        sort(b, b+m);
        for(int j = 0; j < m-1; j++)
        {
            if(b[j].first == b[j+1].first)
                unite(b[j+1].second, b[j].second);
        }
    }
    for(int j = 0; j < m; j++)
    {
        for(int i = 0; i < n; i++)
            b[i] = PII(a[i*m+j], i*m+j);
        sort(b, b+n);
        for(int i = 0; i < n-1; i++)
        {
            if(b[i].first == b[i+1].first)
                unite(b[i+1].second, b[i].second);
        }
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            b[j] = PII(a[i*m+j], i*m+j);
        sort(b, b+m);
        for(int j = 0; j < m-1; j++)
        {
            if(b[j].first != b[j+1].first)
                G[find(b[j+1].second)].push_back(PII(find(b[j].second), 1));
        }
    }
    for(int j = 0; j < m; j++)
    {
        for(int i = 0; i < n; i++)
            b[i] = PII(a[i*m+j], i*m+j);
        sort(b, b+n);
        for(int i = 0; i < n-1; i++)
        {
            if(b[i].first != b[i+1].first)
                G[find(b[i+1].second)].push_back(PII(find(b[i].second), 1));
        }
    }
    for(int i = 0; i < n*m; i++)
    {
        G[n*m].push_back(PII(i, 1));
    }
    for(int i = 0; i <= n*m; i++)
    {
        sort(G[i].begin(), G[i].end());
        G[i].erase(unique(G[i].begin(), G[i].end()), G[i].end());
    }
    SPFA(n*m);
    for(int i = 0; i < n*m;i++) d[i] = -d[i];
    int mi = *min_element(d, d+n*m);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            printf("%d%c", d[find(i*m+j)]-mi+1, " \n"[j == m-1]);
        }
    }
    return 0;
}

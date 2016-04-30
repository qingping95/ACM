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
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f3f3f3f3fLL;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
LL x[N], y[N], c[N];
LL val[N];
LL d[N];
bool vis[N];
vector<PII > G[N];//
queue<LL> que;//
void SPFA()
{
    while(!que.empty())
    {
        LL u = que.front(); que.pop();
        vis[u] = 0;
        for(LL i = 0; i < G[u].size(); i++)
        {
            LL v = G[u][i].first;
            LL w = G[u][i].second;
            if(d[v] > d[u] + w)
            {
                d[v] = d[u] + w;
                if(!vis[v])
                {
                    vis[v] = 1;
                    que.push(v);
                }
            }
        }
    }
}
int main()
{
    Open();
    LL T;scanf("%lld", &T);
    LL cas = 1;
    while(T--)
    {
        while(!que.empty()) que.pop();
        LL n, m;
        scanf("%lld%lld", &n, &m);
        for(LL i = 1; i <= n; i++) scanf("%lld", &x[i]);
        for(LL i = 1; i <= n; i++) scanf("%lld", &y[i]);
        for(LL i = 1; i <= n; i++) scanf("%lld", &c[i]);
        memset(d, 0x3f, sizeof(d));
        memset(vis, 0, sizeof(vis));
        for(LL i = 1; i <= m; i++)
        {
            G[i].clear();
            scanf("%lld", &val[i]);
            if(!val[i])
            {
                d[i] = 0;
                que.push(i);
                vis[i] = 1;
            }
        }
        for(LL i = 1; i <= n; i++) G[y[i]].push_back(PII(x[i], c[i]));
        SPFA();
        LL ans = 0;
        for(LL i = 1; i <= m && ans != -1; i++){
            if(val[i] == 2)
            {
                if(d[i] == INF)
                {
                    ans = -1;
                    break;
                }
                ans += d[i];
            }
        }
        printf("Case #%lld: %lld\n", cas++, ans);
    }
    return 0;
}

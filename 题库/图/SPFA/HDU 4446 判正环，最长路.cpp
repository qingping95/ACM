#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 10010
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
//    #ifndef ONLINE_JUDGE
//        freopen("D:/in.txt","r",stdin);
//        //freopen("D:/my.txt","w",stdout);
//    #endif // ONLINE_JUDGE

//        freopen("D:/17","r",stdin);
        freopen("journey.in","r",stdin);
        freopen("journey.out","w",stdout);
}
LL n, s, t;
vector<PII > G[2][N];
bool vis[N][2];
LL drt[N][2], dans[N][2];
LL num[N];
LL spfa(LL s, LL t, bool same, LL idx, LL d[][2])
{
    queue<PII > que;
    memset(vis, 0, sizeof(vis));
    memset(num, 0, sizeof(num));
    que.push(PII(s, idx));
    d[s][idx] = 0;
    vis[s][idx] = 1;
    while(!que.empty())
    {
        LL u = que.front().first;
        idx = que.front().second;
        vis[u][idx] = 0;
        int nxtidx = idx;
        if(!same) nxtidx ^= 1;
        que.pop();
        for(LL i = 0; i < G[nxtidx][u].size(); i++)
        {
            LL v = G[nxtidx][u][i].first, w = G[nxtidx][u][i].second;
            LL tmpw = d[u][idx] + w;
            if((same == 1 && d[v][nxtidx] > tmpw) || (same == 0 && d[v][nxtidx] < tmpw && drt[u][nxtidx] > drt[v][nxtidx]))
            {
                d[v][nxtidx] = tmpw;
                if(vis[v][nxtidx] == 0){
                    num[v] ++;
                    if(num[v] == n) return -1;
                    que.push(PII(v, nxtidx));
                    vis[v][nxtidx] = 1;
                }
            }
        }
    }
    if(d[t][0] == INF) return d[t][1];
    if(d[t][1] == INF) return d[t][0];
    return max(d[t][1], d[t][0]);
}
int main()
{
    Open();
    while(~scanf("%I64d%I64d%I64d",&n, &s, &t)){
        for(LL i = 0; i <= n; i++) G[0][i].clear(), G[1][i].clear();
        LL m;
        scanf("%I64d", &m);
        for(LL i = 0; i < m; i++)
        {
            LL u, v, w;
            scanf("%I64d%I64d%I64d", &u, &v, &w);
            G[0][u].push_back(PII(v, w));
            G[0][v].push_back(PII(u, w));
        }
        scanf("%I64d", &m);
        for(LL i = 0; i < m; i++)
        {
            LL u, v, w;
            scanf("%I64d%I64d%I64d", &u, &v, &w);
            G[1][u].push_back(PII(v, w));
            G[1][v].push_back(PII(u, w));
        }
        memset(drt, 0x3f, sizeof(drt));
        memset(dans, 0, sizeof(dans));
        spfa(t, s, 1, 0, drt);
        spfa(t, s, 1, 1, drt);
        printf("%I64d\n", spfa(s, t, 0, 1, dans));
    }
    return 0;
}

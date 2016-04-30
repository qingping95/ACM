/*
* 题意：一个公园里面有n(<=50)个地区，m条边相连，这个公园中有k(<=8)个景区，每个景区需要排队，如果没有
*       通行证那么将会花费FTi,否则花费Fi的时间，需要求出从节点1出发经过所有景区再回到节点1的最小时间
*       花费。会告诉你每个景区在哪个地区，同时能在哪些地区获得这个景区的通行证。
*
* 解法：其实这个比较简单，以(当前节点，当前经过那些景区，当前持有那些景区的票)为状态，然后用dijkstra
*       去更新就行了，但是这里比较坑的地方就是一个地区可能有很多个状态，那么这里就必须要先处理一下。
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 10
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
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
// bool vis[1 << 8][55][1 << 8];
int dp[1 << 8][55][1 << 8];
int n, m, k;
vector<PII > G[55];
vector<int> isinter[55];
int tic[55];
struct node
{
    int s1, s2, u;
    int dist;
    node(){}
    node(int _s1, int _u, int _s2, int d){
        s1 = _s1, s2 = _s2, u = _u, dist = d;
    }
    bool operator < (const node& o) const{
        return dist > o.dist;
    }
};
int inter[N], oriT[N], curT[N];

int dijsktra()
{
    // memset(vis, 0, sizeof(vis));
    memset(dp, 0x3f, sizeof(dp));
    priority_queue<node> que;
    int s1 = 0, s2 = 0;
    int d = 0;
    que.push(node(s1, 1, s2, d));
    dp[s1][1][s2] = d;
    while(!que.empty())
    {
        node nod = que.top();que.pop();
        s1 = nod.s1, s2 = nod.s2;
        int u = nod.u, dist = nod.dist;
        if(dp[s1][u][s2] < dist) continue;
        // if(vis[s1][u][s2]) continue;
        // vis[s1][u][s2] = 1;
        if((s1 == ((1 << k) - 1)) && u == 1) return dist;
        for(int i = 0 ; i < G[u].size();i ++)
        {
            int v = G[u][i].first;
            int w = G[u][i].second;
            int ns2 = s2 | tic[v];
            int nd = dist + w;
            if(nd < dp[s1][v][ns2])
                que.push(node(s1, v, ns2, nd)), dp[s1][v][ns2] = nd;
            for(int j = 0; j < isinter[v].size(); j++)
            {
                int nd1 = nd;
                int idx = isinter[v][j];
                int ns1 = s1;
                if((ns1 & (1 << idx)) == 0)
                {
                    if(ns2 & (1 << idx)){
                        nd1 += curT[idx];
                    }else {
                        nd1 += oriT[idx];
                    }
                }
                ns1 |= (1 << idx);
                if(nd1 < dp[ns1][v][ns2])
                que.push(node(ns1, v, ns2, nd1)), dp[ns1][v][ns2] = nd1;
            }
        }
    }
    return -1;
}
int main()
{
//    Open();
    int T;int cas = 1;
    scanf("%d", &T);
    while(T--)
    {
        memset(tic, 0, sizeof(tic));
        scanf("%d%d%d", &n, &m, &k);
        for(int i = 0 ;i <= n; i++) G[i].clear(), G[i].push_back(PII(i, 0)), isinter[i].clear();
        for(int i = 0; i < m; i++)
        {
            int u, v, w;scanf("%d%d%d", &u, &v, &w);
            G[u].push_back(PII(v, w));
            G[v].push_back(PII(u, w));
        }
        for(int i = 0; i < k; i++)
        {
            scanf("%d%d%d", &inter[i], &oriT[i], &curT[i]);
            isinter[inter[i]].push_back(i);
//            if(isinter[inter[i]] != -1) while(1);
//            isinter[inter[i]] = i;
            int ni;
            scanf("%d", &ni);
            while(ni--)
            {
                int x;
                scanf("%d", &x);
                tic[x] |= (1<<i);
            }
        }
        printf("Case #%d: %d\n", cas++, dijsktra());
    }
    return 0;
}
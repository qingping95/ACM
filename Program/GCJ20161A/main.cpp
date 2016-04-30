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
        freopen("C-small-attempt3.in","r",stdin);
        freopen("C-small-attempt3.out","w",stdout);
    #endif // ONLINE_JUDGE
}
int f[1222];
vector<int> G[1222];
int du[1222];
int dp[1222];
bool vis[1222];
void dfs(int u, int fa, int dist, int &ans)
{
    vis[u] = 1;
    if(G[u].size() == 0) ans = max(dist, ans);
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(v == fa) continue;
        if(f[u] == v) continue;
        if(vis[v]) continue;
        dfs(v, u, dist+1, ans);
    }
}
int main()
{
//    Open();
//    freopen("F:/in.txt", "r", stdin);
    int T;scanf("%d", &T);
    int cas = 1;
    while(T--)
    {
        memset(vis, 0, sizeof(vis));
        memset(du, 0, sizeof(du));
        int n;scanf("%d", &n);
        for(int i = 1; i <= n; i++) G[i].clear();
        for(int i = 1; i <= n; i++)
        {
            scanf("%d", &f[i]);
            du[f[i]]++;
            G[f[i]].push_back(i);
        }
        for(int i = 1; i <= n; i++)
        {
            memset(vis, 0, sizeof(vis));
            dp[i] = 0;
            dfs(i, -1, 0, dp[i]);
        }

        int ans = 0;
        for(int i = 1; i <= n; i++)
        {
            memset(vis, 0, sizeof(vis));
            vis[i] = 1, vis[f[i]] = 1;
            int pre = i;
            int cur = f[i];
            int num = 2;
            while(true)
            {
                if(f[cur] == pre)
                {
                    ans = max(ans, num+dp[cur]);
                    for(int j = 1; j <= n; j++)
                    {
                        if(vis[j]) continue;
                        if(vis[f[j]]) continue;
                        if(j == f[f[j]]) {
                            vis[j] = vis[f[j]] = 1;
                            num += 2;
                        }
                    }
                    ans = max(ans, num);
                    break;
                }
                pre = cur;
                cur = f[pre];
                if(vis[cur]){
                    if(cur == i) ans = max(ans, num);
                    break;
                }
                vis[cur] = 1;
                num++;
            }
        }
        printf("Case #%d: %d\n", cas++, ans);
    }
    return 0;
}

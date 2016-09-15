/*
*	这个题主要还是要思考哪些是不变的东西，或者说是类似结论的事实，面对难题一来直接思考DP方法是不可取的，容易被
*	定式思维影响，或者在思考DP的过程中紧密联系题目背景，考虑复杂度的真实值。
*	考虑这样的dp[i][j],从根到点i的路径长度为j，目的点在i的子树内的旅行者的最大贡献
*		dp[i][j] = j * num(i,j) + sigma(dp[v][k]) (k >= j)
*	num(i,j)表示目的点为i，预算大于等于j的个数，后面的sigma可以做一个后缀和O(1)得到。
*	但是这里j的范围特别大，1e9，但是稍作推论这里可以发现从根到点i的路径和一定在旅行者的预算集合中，所以复杂度为O(nm)
*	我认为要想到这样的DP有这样几个关键点：
*		1. n和m都只有1000，很有可能就是一个[n][m]的dp，再基于这个推出上述结论。
*		2. 考虑dp的含义，树上的信息，要不就是从上到下，要不就是从下到上，分别考虑一下如何能够表示一个状态。
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <climits>
#include <bitset>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PII;
const int INF = 0x3f3f3f3f;
const int mod = 1e9+7.5;
const int N = 1010;
vector<int> tr[N];//
vector<PII> G[N];//
int sta[N];//
int t;//
LL dp[N][N];//
int num[N][N];//
int ans[N];//
void dfs(int u, int fa)
{
    for(int i = 0; i < t; i++)
        dp[u][i] = (LL)sta[i] * (tr[u].end() - lower_bound(tr[u].begin(), tr[u].end(), i));
    for(PII cur : G[u])
    {
        int v = cur.first;
        if(v == fa) continue;
        dfs(v, u);
        for(int i = 0; i < t; i++)
            dp[u][i] += dp[v][i];
    }
    if(u == 1) return;
    dp[u][t] = num[u][t] = -1;
    for(int i = t-1; i >= 0; i--)
    {
        if(dp[u][i] > dp[u][i+1]) {
            num[u][i] = i;
        }else{
            dp[u][i] = dp[u][i+1];
            num[u][i] = num[u][i+1];
        }
    }
}
void rfs(int u, int fa, int bgt)
{
    for(PII cur : G[u])
    {
        int v = cur.first;
        if(v == fa) continue;
        ans[cur.second] = sta[num[v][bgt]] - sta[bgt];
        rfs(v, u, num[v][bgt]);
    }
}
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
    int T;
    scanf("%d", &T);
    while(T--)
    {
        memset(G, 0, sizeof(G));
        memset(tr, 0, sizeof(tr));
        t = 0;
        int n, m;
        scanf("%d%d", &n, &m);
        for(int i = 1; i < n; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(PII(v, i));
            G[v].push_back(PII(u, i));
        }
        sta[t++] = 0;
        for(int i = 0; i < m; i++)
        {
            int u, b;
            scanf("%d%d", &u,&b);
            tr[u].push_back(b);
            sta[t++] = b;
        }
        for(int i = 1; i <= n; i++)
            sort(tr[i].begin(), tr[i].end());
        sort(sta, sta+t);
        t = unique(sta, sta+t) - sta;
        for(int i = 1; i <= n; i++)
            for(int j = 0; j < tr[i].size(); j++)
                tr[i][j] = lower_bound(sta, sta+t, tr[i][j]) - sta;

        dfs(1, -1);
        printf("%I64d\n", dp[1][0]);
        rfs(1, -1, 0);
        for(int i = 1; i < n; i++)
            printf("%d%c", ans[i], " \n"[i == n-1]);
    }
    return 0;
}


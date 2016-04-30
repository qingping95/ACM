/*
* In The City of Eternal Festivities, there are ?? street junctions and ??? 1 bidirectional streets,
* each street connecting two of the junctions. Between every two junctions, there is exactly one
* (direct or indirect) path connecting them. No junction is an endpoint for more than 10 streets.
* Every 13th of September (the 256th day of the year), there are many festivities going on in
* The City. In particular, the citizens want to organize ?? parades. The parade number ?? starts at
* junction ???? and ends at ????, following the unique path between the endpoints.
* As the mayor of The City, you are responsible for citizens’ safety. Therefore you decreed that
* no two parades are ever allowed to use the same street, though they can have common junctions,
* or even common endpoints.
* To appease your citizens, try to organize as many parades as possible, without breaking the
* safety regulations.
*
* Input
* The first line of input contains the number of test cases ??. The descriptions of the test cases
* follow:
* The first line of each test case contains a single integer: the number of junctions ?? (2 ? ?? ?
* 1000). Each of the next ?? ? 1 lines contains two integers ??, ?? (1 ? ?? ?= ?? ? ??), denoting that
* junctions ?? and ?? are connected by a street. Each junction has at most 10 streets leaving it.
* The next line contains a single integer: the number of planned parades ??, 0 ? ?? ? (??? 2)?.
* Each of the next ?? lines contains two integers ????, ???? (1 ? ???? ?= ???? ? ??), meaning that a parade is
* planned to start at junction ????, and finish at junction ????. No two parades share both endpoints.
*
* Output
* For each test case, output one line containing the largest number of parades that can be
* organized with no street used by more than one parade.

* 题意：一个城市中有n个点，n-1条边，形成一棵树，节日的时候，有很多队伍想要在(ui, vi)之间的街上游行
*		市长为了保证每个队伍的安全，需要保证没有一条街同时在两个队伍的游行路线上，所以需要选择一种
*		方案，使得能够游行的队伍尽可能多，输出这个数量。
*
* 做法：树形DP，内部状压...大概能这么说，每个dfs(u)返回u这个节点子树的最大游行队伍数量，同时维护好
*		那些节点还能够往上传。具体解释在代码注释中。
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 2010
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
int n, m;
vector<int> G[N];
bool pa[N][N];
int use[N][N];
int tail[N];

/*
* 这里dfs返回的是以u为根节点的子树上的最大的答案。然后每次dfs计算出以u为LCA的点对的最大数量
* 之所以能这样做是因为对每个节点的某个儿子来说，只可能有一个节点传上来(答案只可能增加1)。
* use[u]中存储的是以u为根节点的子树中有哪些点可以走到当前节点。
*/
int dfs(int u, int fa)
{
    int ans = 0;
    int siz = G[u].size();
    siz--;
    for(int i = 0; i < siz; i ++)
    {
        if(G[u][i] == fa) {
            swap(G[u][i], G[u][siz]);
        }
        int v = G[u][i];
        ans += dfs(v, u);
    }
	
	//首先处理子树中的点直接到根节点的
    for(int i = 0; i < siz; i++)
    {
        int v = G[u][i];
        for(int j = 0; j < tail[v]; j++)
        {
            if(pa[ use[v][j] ][u] ){
                ans ++, tail[v] = 0;
            }
        }
    }
	
	//这里处理的是哪些子树可以连接
    bool link[11][11];
    memset(link, 0, sizeof(link));
    for(int i = 0; i < siz; i ++)
        for(int j = i + 1 ; j < siz; j++)
        {
            int v1 = G[u][i], v2 = G[u][j];
            bool flag = true;
            for(int n1 = 0; n1 < tail[v1] && flag; n1++)
                for(int n2 = 0; n2 < tail[v2] && flag; n2 ++)
                    if(pa[ use[v1][n1] ][ use[v2][n2] ])
                    {
                        link[i][j] = link[j][i] = true;
                        flag = false;
                    }
        }
		
	//状压DP计算当前状态的子树被选择能得到的最大的点对数
    int limit = 1 << siz;
    int dp[1111];
    dp[0] = 0;
    for(int s = 1; s < limit; s++)
    {
        int a = s & -s;
        int idx = __builtin_ctz(a);
        int tmps = s - a;
        dp[s] = dp[tmps];
        for(int i = 0; i < siz; i++)
        {
            if((tmps & (1 << i)) && link[idx][i])
            {
                dp[s] = max(dp[s], dp[tmps ^ (1 << i)] + 1);
            }
        }
    }
    ans += dp[limit - 1];//更新答案
	
	//维护当前节点的子树有哪些点可以往上传
    use[u][tail[u] ++] = u;
    for(int i = 0; i < siz; i++)
    {
        if(dp[(limit - 1) ^ (1 << i)] == dp[limit - 1])//表示这个点无所谓不影响答案
        {
            for(int j = 0; j < tail[G[u][i]]; j++)
                use[u][tail[u]++] = use[G[u][i]][j];
        }
    }
    return ans;
}
int main()
{
    Open();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        memset(tail, 0, sizeof(tail));
        memset(pa, 0, sizeof(pa));
        scanf("%d", &n);
        for(int i = 0; i <= n; i++) G[i].clear();
        for(int i = 1; i < n; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        scanf("%d", &m);
        for(int i = 0 ;i < m; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            pa[u][v] = pa[v][u] = 1;
        }
        G[1].push_back(-1);
        int ans = dfs(1, -1);
        printf("%d\n", ans);
    }
    return 0;
}

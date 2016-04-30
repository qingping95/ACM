/*
* In The City of Eternal Festivities, there are ?? street junctions and ??? 1 bidirectional streets,
* each street connecting two of the junctions. Between every two junctions, there is exactly one
* (direct or indirect) path connecting them. No junction is an endpoint for more than 10 streets.
* Every 13th of September (the 256th day of the year), there are many festivities going on in
* The City. In particular, the citizens want to organize ?? parades. The parade number ?? starts at
* junction ???? and ends at ????, following the unique path between the endpoints.
* As the mayor of The City, you are responsible for citizens�� safety. Therefore you decreed that
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

* ���⣺һ����������n���㣬n-1���ߣ��γ�һ���������յ�ʱ���кܶ������Ҫ��(ui, vi)֮��Ľ�������
*		�г�Ϊ�˱�֤ÿ������İ�ȫ����Ҫ��֤û��һ����ͬʱ���������������·���ϣ�������Ҫѡ��һ��
*		������ʹ���ܹ����еĶ��龡���ܶ࣬������������
*
* ����������DP���ڲ�״ѹ...�������ô˵��ÿ��dfs(u)����u����ڵ�������������ж���������ͬʱά����
*		��Щ�ڵ㻹�ܹ����ϴ�����������ڴ���ע���С�
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
* ����dfs���ص�����uΪ���ڵ�������ϵ����Ĵ𰸡�Ȼ��ÿ��dfs�������uΪLCA�ĵ�Ե��������
* ֮����������������Ϊ��ÿ���ڵ��ĳ��������˵��ֻ������һ���ڵ㴫����(��ֻ��������1)��
* use[u]�д洢������uΪ���ڵ������������Щ������ߵ���ǰ�ڵ㡣
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
	
	//���ȴ��������еĵ�ֱ�ӵ����ڵ��
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
	
	//���ﴦ�������Щ������������
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
		
	//״ѹDP���㵱ǰ״̬��������ѡ���ܵõ������ĵ����
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
    ans += dp[limit - 1];//���´�
	
	//ά����ǰ�ڵ����������Щ��������ϴ�
    use[u][tail[u] ++] = u;
    for(int i = 0; i < siz; i++)
    {
        if(dp[(limit - 1) ^ (1 << i)] == dp[limit - 1])//��ʾ���������ν��Ӱ���
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

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 150010
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int INF=0x3f3f3f3f;
const double eps = 1e-10;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
vector<int> G[N];
int d[N], ffa[N], did[N], fid[N];
int FA[N];
bool isatt[N];
void dfs1(int u, int fa)
{
    FA[u] = fa;
    if(isatt[u]) d[u] = 0, did[u] = u;
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(v == fa) continue;
        dfs1(v, u);
        if(d[v] != -1 && (d[u] < d[v] + 1 || (d[u] == d[v] + 1 && did[u] > did[v])))
        {
            d[u] = d[v]+1;
            did[u] = did[v];
        }
    }
}
void dfs2(int u, int fa, int w, int wid)
{
    ffa[u] = w, fid[u] = wid;
    if(d[u] == -1) return ;
    bool flag = true;
    int ma = -1, maid = -1;
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(v == fa) continue;
        if(d[v] != -1){
            if(d[v] + 1 > ma || (d[v] + 1 == ma && did[v] < maid))
            {
                if(d[v] + 1 != d[u] || did[v] != did[u])
                {
                    ma = d[v] + 1, maid = did[v];
                }
            }
        }
    }
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(v == fa) continue;
        if(d[v] == -1) continue;
        int curw = w+1, curid = wid;
        if(d[v]+1 < d[u]){
            if(d[u] > curw || (d[u] == curw && did[u]< wid)){
                curw = d[u], curid = did[u];
            }
        }
        else if(ma != -1)
        {
            if(ma > curw || (ma == curw && maid < wid)){
                curw = ma, curid = maid;
            }
        }
        dfs2(v, u, curw, curid);
    }
}
int dfs3(int u, int fa)
{
    int res = 0;
    for(int i = 0; i < G[u].size(); i ++)
    {
        int v = G[u][i];
        if(v == fa) continue;
        if(d[v] == -1) continue;
        res += dfs3(v, u) + 1;
    }
    return res;
}
PII ans[N];
int main()
{
    Open();
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    int fir = 1;
    while(m--)
    {
        int x;scanf("%d", &x);
        isatt[x] = 1;
        fir = x;
    }
    memset(d, -1, sizeof(d));
    memset(did, -1, sizeof(did));
    memset(ffa, -1, sizeof(ffa));
    memset(fid, -1, sizeof(fid));
    dfs1(fir, 0);
    dfs2(fir, 0, 0, fir);
    int answ = -1, ansid = INF;
    for(int i = 1; i <= n; i++)
    {
        int tail = 0;
        ans[tail++] = PII(ffa[i], fid[i]);
        for(int j =0 ; j < G[i].size(); j++)
        {
            int v = G[i][j];
            if(v == FA[i]) continue;
            if(d[v] != -1) ans[tail++] = PII(d[v]+1, did[v]);
        }
        sort(ans, ans+tail);
        if(tail < 2) continue;
        int curw = ans[tail-1].first + ans[tail-2].first;
        if(answ < curw || (answ == curw && ansid > min(ans[tail-1].second, ans[tail-2].second)))
        {
            answ = ans[tail-1].first + ans[tail-2].first;
            ansid = min(ans[tail-2].second, ans[tail-1].second);
        }
    }
    if(answ == -1){
        printf("%d\n0\n", fir);
        return 0;
    }
    printf("%d\n", ansid);
    int res = dfs3(fir, 0);
    printf("%d\n", res*2 - answ);
    return 0;
}

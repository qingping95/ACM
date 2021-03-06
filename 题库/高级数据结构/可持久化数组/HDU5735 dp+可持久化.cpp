/*
*   dp[i] = sigma(dp[j] + wl[i] op wl[j] + wr[i] op wr[j])
*   wl[i]表示w[i]的前8位， wr[i]表示w[i]的后8位
*   用ds(x,y)存储的是表示对于某个w[i]​​的后8位为y, 对于某个
*   w[j]​​的前8位为x时, (dp(j)+[w[i]​​后8位] op [w[​j]​​后8位])的最值
*   那么更新dp[i]的时候只需要枚举ds(x,y)中的x即可更行该数组。
*   更新ds(x,y)的时候类似，由于每更新一个dp[i]只会对ds(x,)造成影响
*   于是将第一维可持久化
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
#include <ctime>
//#include <unordered_map>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
//        freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int mod = 1e9+7.5;
const int N = 130010;
LL pl[N][1<<8];
int pt;//
int R[(1<<16)+10][1<<8];//
LL dp[(1<<16)+10];//
int w[(1<<16)+10];//

int opt = 0;
LL makeopt(LL a1, LL a2)
{
    if(opt == 0) return a1 & a2;
    if(opt == 1) return a1 | a2;
    if(opt == 2) return a1 ^ a2;
}
int newArray(int old)
{
    if(old == -1) memset(pl[pt], 0, sizeof(pl[pt]));
    else memcpy(pl[pt], pl[old], sizeof(pl[old]));
    return pt++;
}
vector<int> G[(1<<16)+10];//
void upd(int u, int root)
{
    memcpy(R[u], R[root], sizeof(R[root]));
    int x = w[u] >> 8;
    int y = w[u] - (x<<8);
    R[u][x] = newArray(R[u][x]);

    int rt = R[u][x];
    for(int i = 0; i < (1<<8); i++)
    {
        pl[rt][i] = max((LL)pl[rt][i], dp[u] + makeopt(y, i));
    }
}
void dfs(int u)
{
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        dp[v] = 0;
        int x = w[v] >> 8;
        int y = w[v] - (x<<8);
        for(int s = 0; s < (1<<8); s++)
        {
            if(R[u][s] != -1)
            {
                int rt = R[u][s];
                dp[v] = max(dp[v], pl[rt][y] + (makeopt(s, x)<<8));
            }
        }
        upd(v, u);
        dfs(v);
    }
}
int main(){
//    Open();
    //init();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        pt = 0;
        int n;
        char op[44];
        scanf("%d%s", &n, op);
        if(op[0] == 'A') opt = 0;
        if(op[0] == 'O') opt = 1;
        if(op[0] == 'X') opt = 2;
        memset(R[0], -1, sizeof(R[0]));
        for(int i = 1; i <= n; i++)
        {
            scanf("%d", &w[i]);
            G[i].clear();
            memset(R[i], -1, sizeof(R[i]));
        }
        for(int i = 2; i <= n; i++)
        {
            int f;
            scanf("%d", &f);
            G[f].push_back(i);
        }
        dp[1] = 0;
        upd(1, 0);
        dfs(1);
        int ans = 0;
        for(int i = 1; i <= n; i++)
        {
            ans = ((LL)ans + (LL)i*(dp[i]+w[i])%mod)%mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}


#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
//        freopen("/home/qingping/in.txt","r",stdin);
//        freopen("/home/qingping/out.txt","w",stdout);
//        freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const LL N = 100100;
vector<LL> b;
vector<PII> G[N];
LL f[N];
void insert(LL v, vector<LL>& b)
{
    for(LL i = 0; i < b.size(); i++)
    {
        LL val = b[i];
//        cout<<val<<endl;
        if((val & -val) & v)
        {
            v ^= val;
        }
    }
    if(!v) return ;
    for(int i = 0; i < b.size(); i++)
    {
        if(b[i] & (v & -v)) b[i] ^= v;
    }
    b.push_back(v);
}
bool vis[N];
void dfs(LL u, LL fa)
{
    vis[u] = 1;
    for(LL i = 0; i < G[u].size(); i++)
    {
        PII cur = G[u][i];
//        if(cur.first == fa) continue;
        LL v = cur.first, w = cur.second;
        if(vis[v]) insert(w^f[v]^f[u], b);
        else
        {
            f[v] = f[u] ^ w;
            dfs(v, u);
        }
    }
}
int main()
{
//    Open();
    LL T;
    scanf("%lld", &T);
    int cas = 1;
    while(T--)
    {
        b.clear();
        memset(vis, 0, sizeof vis);
        LL n, m;
        scanf("%lld%lld", &n, &m);
        for(LL i = 0; i <= n; i++) G[i].clear();
        while(m--)
        {
            LL u, v, w;
            scanf("%lld%lld%lld", &u, &v, &w);
            G[u].push_back(PII(v, w));
            G[v].push_back(PII(u, w));
        }
        f[1] = 0;
        dfs(1, 0);
        LL ans = 0;
//        cout<<b.size()<<endl;
        for(int i = 59; i >= 0; i--)
        {
            for(int j = 0; j < b.size(); j++)
            {
                if(b[j] & (1ll<<i))
                {
                    ans = max(ans, ans^b[j]);
                    LL v = b[j];
                    for(int k = 0; k < b.size(); k++)
                    {
                        if(b[k] & (1ll << i)) b[k] ^= v;
                    }
                    break;
                }
            }
        }
        printf("Case #%d: %lld\n", cas++, ans);
    }
    return 0;
}

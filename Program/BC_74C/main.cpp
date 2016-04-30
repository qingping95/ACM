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
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 100010;
const int mod = 1000000007;
bool vis[N];
int in[N];
int n, m, k, T;
vector<int> G[N];

int main()
{
    //Open();
    set<int> s;
    scanf("%d", &T);
    while(T--)
    {
        s.clear();
        memset(G, 0, sizeof(G));
        memset(in, 0, sizeof(in));
        memset(vis, 0, sizeof(vis));
        scanf("%d%d%d", &n, &m, &k);
        //for(int i = 1; i <= n; i++) s.push(i);
        for(int i = 0; i < m; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            in[v]++;
        }
        for(int i = 1; i <= n; i++)
        {
            if(in[i] == 0) s.insert(i);
        }
        LL ans = 0;
        int tail = 1;
        for(int i = 1; i <= n;i++)
        {
            if(vis[i]) continue;
            if(in[i] <= k){
                k -= in[i];
                ans += tail*i;
                ans %= mod;
                tail++;
                vis[i] = 1;
            }else{

            }
        }
    }
    return 0;
}

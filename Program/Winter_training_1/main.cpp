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
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 200020;
int n, m, q;
vector<PII> G[N];
bool vis[N];
bool vvv[N];
int num[N];
int d[N];
bool spfa(int s)
{
    queue<int> que;
    memset(vis, 0, sizeof(vis));
    memset(num, 0, sizeof(num));
    memset(d, 0x3f, sizeof(d));
    que.push(s);
    d[s] = 0;
    while(!que.empty())
    {
        int u = que.front();
        vvv[u] = 1;
        que.pop();
        vis[u] = 0;
        for(int i = 0; i < G[u].size(); i++)
        {
            int v = G[u][i].first, w = G[u][i].second;
            if(d[v]>d[u]+w)
            {
                d[v] = d[u]+w;
                if(!vis[v])
                {
                    if(num[v] == n+m) return false;
                    num[v]++;
                    vis[v] = 1;
                    que.push(v);
                }
            }
        }
    }
    return true;
}

int main()
{
//    Open();
    while(~scanf("%d%d%d", &n, &m, &q), (n||m||q))
    {
        for(int i = 0; i <= n+m; i++)
        {
            G[i].clear();
        }
        memset(vvv, 0, sizeof(vvv));
        while(q--)
        {
            int u, v, w;
            char op[33];
            scanf("%d %d %s %d", &u, &v, op, &w);
            //printf("%d %d %s %d\n", u, v, op, w);
            if(op[0] == '<')

                G[n+v].push_back(PII(u, w));
            else
                G[u].push_back(PII(n+v, -w));
        }
        bool flag = true;
        for(int i = 1; i <= n+m && flag; i++)
        {
            if(vvv[i]) continue;
            if(!spfa(i)) flag = false;
        }
        if(flag) {
            printf("Possible\n");
        }else {
            printf("Impossible\n");
        }

    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 100010
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef pair<long long,long long> PII;
const long long INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
//        freopen("improvements.in","r",stdin);
//        freopen("improvements.out","w",stdout);
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}

long long n;
long long Q;
vector<PII> G[N];
long long dist[N];
long long num[N*2];
long long tmp[N*2];
void dfs(long long u, long long fa, long long dis){
    dist[u] = dis;
    for(long long i = 0; i < G[u].size(); i++){
        long long v = G[u][i].first;
        if(v == fa) continue;
        long long w = G[u][i].second;
        dfs(v, u, dis ^ w);
    }
}
int main()
{
    Open();
    long long T;
    scanf("%I64d",&T);
    while(T--)
    {
        memset(num, 0, sizeof(num));
        scanf("%I64d", &n);
        for(long long i = 0; i <= n; i++) G[i].clear();
        for(long long i = 1; i < n; i++){
            long long u, v, w;
            scanf("%I64d%I64d%I64d", &u, &v, &w);
            G[u].push_back(PII(v, w));
            G[v].push_back(PII(u, w));
        }
        scanf("%I64d", &Q);
        dfs(1, -1, 0);
        for(long long i = 1; i <= n; i++)
            num[dist[i]]++;
        for(long long i = 0 ;i < Q; i++){
            long long q;
            scanf("%I64d", &q);
            if(n == 1){
                printf("0\n");
                continue;
            }
            long long ans = 0;
            if(q == 0){
                memcpy(tmp, num, sizeof(num));
                for(long long u = 1; u <= n; u++)
                {
                    int ntmp = tmp[dist[u]];
                    if(ntmp){
                        ans += (long long)ntmp * (ntmp - 1) / 2;
                        tmp[dist[u]] = 0;
                    }
                }
                ans += n;
            }else{
                for(long long u = 1; u <= n; u++)
                {
                    ans += num[q ^ dist[u]];
                }
                ans /= 2;
            }
            printf("%I64d\n", ans);
        }
    }
    return 0;
}
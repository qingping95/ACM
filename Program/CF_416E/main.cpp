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
int wei[555][555];
int d[555][555];
int ans[555][555];
vector<int> mi[555][555];
int n, m;
void floyd()
{
    memcpy(d, wei, sizeof(wei));
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
int main()
{
    //Open();
    memset(wei, 0x3f, sizeof(wei));
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        wei[u][v] = wei[v][u] = min(wei[u][v], w);
    }
    for(int i = 1; i <= n; i++) wei[i][i] = 0;
    floyd();
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            for(int k = 1; k <= n; k++)
                if(i != j && d[k][i] + d[i][j] == d[k][j])
                    mi[i][j].push_back(k);
//    for(int i = 1; i <= n; i++)
//        for(int j = 1; j <= n; j++)
//        {
//            printf("%d %d:\n", i, j);
//            for(int k = 0; k < mi[i][j].size(); k++)
//            {
//                printf("%d ", mi[i][j][k]);
//            }
//            printf("\n");
//        }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            if(i == j) continue;
            int num = 0;
            for(int k = 1; k <= n; k++)
                if(i != k && wei[i][k] != INF && d[i][j] == wei[i][k] + d[k][j])
                    num++;
            for(int k = 0; k < mi[i][j].size(); k++)
            {
                ans[mi[i][j][k]][j] += num;
            }
        }
    for(int i = 1; i <= n; i++)
        for(int j = i+1; j <= n; j++)
            printf("%d ", ans[i][j]);
    printf("\n");
    return 0;
}

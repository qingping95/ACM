#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 25000
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
const double eps = 1e-8;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int t[211][11111];
int f[211][11111];
int dp[211][11111];
int c1[21111], c2[21111];
void inspre(int x, int val)
{
    for(int i = x; i <= 11111 + 10; i += i & (-i)) c1[i] = min(c1[i], val);
}
int getmapre(int x)
{
    int res = INF;
    for(int i = x; i ; i -= i & (-i)) res = min(res, c1[i]);
    return res;
}
void inssuf(int x, int val)
{
    for(int i = x; i ; i -= i & (-i)) c2[i] = min(c2[i], val);
}
int getmasuf(int x)
{
    int res = INF;
    for(int i = x; i <= 11111 + 10 ; i += i & (-i)) res = min(res, c2[i]);
    return res;
}
PII cal[2][11111];
bool cmp(PII a, PII b)
{
    return a.first > b.first;
}
int main()
{
//    Open();
    int n, m;
    while(~scanf("%d%d", &n, &m), n||m)
    {
        memset(dp, 0x3f, sizeof(dp));
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                scanf("%d", &t[i][j]);
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                scanf("%d", &f[i][j]);
        for(int i = 1; i <= m; i++){
            dp[1][i] = t[1][i];
        }
        for(int i = 2; i <= n; i++)
        {
            memset(c1, 0x3f, sizeof(c1));
            memset(c2, 0x3f, sizeof(c2));
            for(int j = 1; j <= m; j++)
            {
                cal[0][j] = PII(f[i-1][j] + j, j);
                cal[1][j] = PII(j - f[i][j], j);
            }
            sort(cal[0]+1, cal[0] + m + 1, cmp);
            sort(cal[1]+1, cal[1] + m + 1, cmp);
            int k = 1;
            for(int j = 1 ; j <= m; j++)
            {
                while(k <= m && cal[0][k].first >= cal[1][j].first){
                    inspre(cal[0][k].second, dp[i-1][cal[0][k].second]);
                    k++;
                }
                int curid = cal[1][j].second;
                dp[i][curid] = min(dp[i][curid], getmapre(curid)+t[i][curid]);
            }
            for(int j = 1; j <= m; j++)
            {
                cal[0][j] = PII(j - f[i-1][j], j);
                cal[1][j] = PII(j + f[i][j], j);
            }
            sort(cal[0]+1, cal[0] + m + 1);
            sort(cal[1]+1, cal[1] + m + 1);
            k = 1;
            for(int j = 1 ; j <= m; j++)
            {
                while(k <= m && cal[0][k].first <= cal[1][j].first)
                {
                    int curid = cal[0][k].second;
                    inssuf(curid, dp[i-1][curid]);
                    k++;
                }
                int curid = cal[1][j].second;
                dp[i][curid] = min(dp[i][curid], getmasuf(curid)+t[i][curid]);
            }
        }
        int ans = *min_element(dp[n]+1, dp[n]+m+1);
        printf("%d\n", ans);
    }
    return 0;
}

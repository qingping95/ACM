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
typedef pair<double,int> PDI;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 2210;
int n, m, k;
int dp[55][55][55][10][10];
int UP = 8;
int main()
{
    //Open();
    mesmet(dp, 0x3f, sizeof(dp));
    dp[0][0][0][3][3] = 0;
    for(int n = 0; n <= 50; n++)
        for(int m = 0; m <= 50; m++)
            for(int k = 0; k <= 50; k++)
                for(int i = 0; i < UP; i++)
                    for(int j = 0; j < UP; j++)
            {
                if(dp[n][m][k][i][j] == INF) continue;
                if(i > j + 4){
                    dp[n+1][m][k][i][j+2] = min(dp[n+1][m][k][i][j+2], dp[n][m][k][i][j]);
                    dp[n][m+1][k][i][j+3] = min(dp[n][m+1][k][i][j+3], dp[n][m][k][i][j]);
                    dp[n][m][k+1][i][j+4] = min(dp[n][m][k+1][i][j+4], dp[n][m][k][i][j]);
                }
                else if(j > i + 4){
                    dp[n+1][m][k][i+2][j] = min(dp[n+1][m][k][i+2][j], dp[n][m][k][i][j]);
                    dp[n][m+1][k][i+3][j] = min(dp[n][m+1][k][i+3][j], dp[n][m][k][i][j]);
                    dp[n][m][k+1][i+3][j] = min(dp[n][m][k+1][i+4][j], dp[n][m][k][i][j]);
                }else{
                    if(j+2<UP)dp[n+1][m][k][i][j+2] = min(dp[n+1][m][k][i][j+2], dp[n][m][k][i][j]);
                    if(j+2<UP)dp[n][m+1][k][i][j+3] = min(dp[n][m+1][k][i][j+3], dp[n][m][k][i][j]);
                    if(j+2<UP)dp[n][m][k+1][i][j+4] = min(dp[n][m][k+1][i][j+4], dp[n][m][k][i][j]);

                    if(j+2<UP)dp[n+1][m][k][i+2][j] = min(dp[n+1][m][k][i+2][j], dp[n][m][k][i][j]);
                    if(j+2<UP)dp[n][m+1][k][i+3][j] = min(dp[n][m+1][k][i+3][j], dp[n][m][k][i][j]);
                    if(j+2<UP)dp[n][m][k+1][i+3][j] = min(dp[n][m][k+1][i+4][j], dp[n][m][k][i][j]);
                }
            }
    int T;
    scanf("%d", &T);
    while(T--)
    {
        printf("%d %d\n", ans, idx+1);
    }
    return 0;
}

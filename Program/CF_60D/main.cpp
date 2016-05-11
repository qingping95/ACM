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
int dp[655][655];

PII vec[44];
int x0, y0, n, d;
int dcmp(int x, int y, int d)
{
    if(x*x+y*y == d*d) return 0;
    if(x*x+y*y < d*d) return -1;
    if(x*x+y*y > d*d) return 1;
}
int dfs(int x, int y)
{
    if(dp[x+200][y+200] != -1) return dp[x+200][y+200];
    if(dcmp(x, y, d) >= 0) return dp[x+200][y+200] = 0;
    bool flag = true;
    for(int i = 0; i < n; i++)
    {
        int cx = x + vec[i].first;
        int cy = y + vec[i].second;
        if(dfs(cx, cy)) flag = false;
    }
    return dp[x+200][y+200] = flag;
}
int main()
{
    //Open();
    memset(dp, -1, sizeof(dp));
    scanf("%d%d%d%d", &x0, &y0, &n, &d);
//    for(int i = 0; i < 444; i++)
//        for(int j = 0; j < 444; j++)
//            if(dcmp(i-200, j-200, d) >= 0) dp[i][j] = 0;

    for(int i = 0; i < n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        vec[i] = PII(x, y);
    }
    if(dfs(x0, y0))
        printf("Dasha\n");
    else
        printf("Anton\n");
    return 0;
}

/*
* 题意：给出n个数, 以及k，可以重排序列顺序，要求使得sigma(abs(a[i] - a[k+i]))(1 <= i <= n - k)最小
*
* 做法：首先分析题目，这个题相当于有k条链子，如果想象吧同一条链子上面的值放在一起，并且从小到大排序
*       ，那么会发现实际上每条链子上的贡献就是这条链子的最大值-最小值。那么如果把整个a数组排序，
*       相同链子中的值一定是连续的，这样才会使得答案最小，那么做法就是首先将整个数组排序，然后将这n
*       个数分成k个部分即可，但是当n不整除k的时候，各条链子中的值不一样，会有一部分(第一类)比另一部分
*		(第二类)多1；所以这里就需要一个dp，dp[i][j]表示当前处理好了i条第一类链子，j条第二类链子的最小值
*		那么答案就是dp[n%k][k - (n%k)];n%k为第一类链子的数量
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 220
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef pair<long long,long long> PII;
const long long INF=0x3f3f3f3f;
const double eps = 1e-10;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
long long dp[5050][5050];
long long a[303333];
long long n, k;
int main()
{
    Open();
    scanf("%I64d%I64d", &n, &k);
    for(long long i = 0; i < n; i++){
        scanf("%I64d", &a[i]);
    }
    sort(a, a+n);
    dp[0][0] = 0;
    long long len = n / k;
    long long limit = n % k;
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for(long long i=0;i<=limit;i++){
        for(long long j=0;j<=k-limit;j++){
            long long pos = (len+1)*(i) + len*j;
            dp[i+1][j] = min(dp[i+1][j] , dp[i][j] + a[pos+len+1-1] - a[pos] );
            dp[i][j+1] = min(dp[i][j+1] , dp[i][j] + a[pos+len-1] - a[pos] );
        }
    }
    printf("%I64d\n", dp[limit][k - limit]);
    return 0;
}
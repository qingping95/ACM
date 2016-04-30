/*
* 题意：这里有一栋计划修建的豪华大楼，总共有n层楼，每一层都会修建一个乒乓球馆或者游泳馆，
* 		同时每一层都有Ti个人打乒乓球，Pi个人游泳，但是每层只会修建一种场馆，这就导致有一
*		部分人会跑到距离这一层最近的有相应设施的楼层去玩。那么对于每个人来说都会有一个花
*		费(花费即为这个人的起始层与目标层的层数差)，要用一种修建方案使得总花费最小。输出
*		最小花费
* 
* dp[i][j][k],表示第i个位置放置的设施为k(0/1)，前面有连续j个!k设施的最小花费。
* 所以dp[i][j][k] = min(dp[i-j][l][!k]) + sum(i-j, i);这里l不需要枚举，只需要
* 计算过程中记一下这一维的最小值即可。sum(i-j, i)预处理可得。
* 这里处理sum(i, j)之间的答案也有一些技巧，首先不考虑i==1/j==n的情况，那么[i, j]这个区间
* 的花费为v[i]*1 + v[i+1]*2 + v[i+2]*3 + ... + v[j-2]*3 + v[j-1]*2 + v[j]*1,也就是可以看
* 做是两个等差序列的和，形如sigma(v[i+k]*k)(1<=k<=j)这种形式的区间和，我们可以先处理出
* v[i]*i和v[i]的前缀和prei[i]和pre[i]，那么sigma(v[i+k]*k)(1<=k<=j) = prei[j+k] - prei[i]
*  - (pre[j+k] - pre[i])*i;
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <ctime>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 4050
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;

typedef long long LL;
typedef pair<LL, LL> PII;
const LL INF=0x3f3f3f3f;
const double eps = 1e-10;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
LL v[N][2];
LL prei[N][2];
LL sufi[N][2];
LL pre[N][2];
LL n;
//LL dp[N][N][2];
LL res[N][2];
LL getsum(LL l, LL r, LL k)
{
    if(l == 1) return sufi[1][k] - sufi[r+1][k] - pre[r][k]*(n-r);
    if(r == n) return prei[n][k] - prei[l-1][k] - (pre[n][k] - pre[l-1][k])*(l-1);
    if(l == r) return v[l][k];
    if(l == r - 1) return v[l][k] + v[r][k];
    LL mid = l + r >> 1;
    LL res = prei[mid][k] - prei[l-1][k] - (pre[mid][k] - pre[l-1][k])*(l-1);
    l = mid+1;
    res += (sufi[l][k] - sufi[r+1][k]) - (pre[r][k] - pre[l-1][k])*(n-r);
    return res;
}
int main()
{
//    Open();
    LL T;scanf("%lld",&T);
    for(LL Cas = 1; Cas <= T;Cas++){
        printf("Case #%lld: ",Cas);
        scanf("%lld", &n);
        memset(res, 0x3f, sizeof(res));
        pre[0][0] = pre[0][1] = 0;
        prei[0][0] = prei[0][1] = 0;
        for(LL i = 1; i <= n; i++)
        {
            scanf("%lld%lld" ,&v[i][0], &v[i][1]);
            pre[i][0] = pre[i-1][0] + v[i][0];
            pre[i][1] = pre[i-1][1] + v[i][1];
            prei[i][0] = prei[i-1][0] + v[i][0] * i;
            prei[i][1] = prei[i-1][1] + v[i][1] * i;
        }
        sufi[n+1][0] = sufi[n+1][1] = 0;
        for(LL i = n, cnt = 1; i >= 1; i--, cnt++)
            for(LL k = 0; k < 2; k++)
                sufi[i][k] = sufi[i+1][k] + v[i][k]*cnt;
        res[0][0] = res[0][1] = 0;
        for(LL i = 1; i <= n; i++)
            for(LL j = 1; j <= i; j++)
                for(LL k = 0; k < 2; k++){
                    LL tmpans = res[i-j][!k] + getsum(i-j+1, i, !k);
                    if(j != n)res[i][k] = min(res[i][k], tmpans);
                }
        LL ans = min(res[n][0], res[n][1]);
        printf("%lld\n", ans);
    }
    return 0;
}


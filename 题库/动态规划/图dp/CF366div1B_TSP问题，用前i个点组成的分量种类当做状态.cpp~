/*
*  题意：给一个n个点的完全图、图上的权值计算方法，以及起点和终点，要从起点到终点，并经过每个点恰好一次。问最小花费是多少
*	
*  做法：考虑DP，由于给定的两点之间的特殊权值计算方法，将某个点放入图中的时候不需要考虑具体与谁相连，只需要考虑放在链的
*        左边或者右边即可，那么对于前i个点来说，存在的链子只有三种：
*		1. 不包含s和e，左端右端都能加点
*		2. 包含s，只能在右端加入点
*		3. 包含e，只能在左端加入点
*	 这样的话，用dp[i][j][k][l]表示前i个点中，有j个类型1链，k个类型2链，j个类型3链，转移的时候考虑情况在代码中有注释
*	 有的转移方式在最后一个点处不能转移，这个需要注意，在s和e两点时也要特殊处理
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <climits>
#include <bitset>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PII;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
const LL mod = 1e9+7.5;
const LL N = 5050;
LL n, s, e;
LL x[N];
LL a[N], b[N], c[N], d[N];
LL dp[2][N][2][2];
LL getw(LL i, LL j)
{
    if(i == j) return INF;
    if(i > j) return x[i] - x[j] + c[i] + b[j];
    else return x[j] - x[i] + d[i] + a[j];
}
LL setL(LL i){return x[i] + c[i];}
LL setR(LL i){return x[i] + a[i];}
LL empL(LL i){return -x[i] + b[i];}
LL empR(LL i){return -x[i] + d[i];}
void upd(LL& a, LL b){if(a > b) a = b;}
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
    scanf("%I64d%I64d%I64d", &n, &s, &e);
    for(LL i = 1; i <= n; i++) scanf("%I64d", &x[i]);
    for(LL i = 1; i <= n; i++) scanf("%I64d", &a[i]);
    for(LL i = 1; i <= n; i++) scanf("%I64d", &b[i]);
    for(LL i = 1; i <= n; i++) scanf("%I64d", &c[i]);
    for(LL i = 1; i <= n; i++) scanf("%I64d", &d[i]);
    int cur = 0;
    memset(dp[cur], 0x3f, sizeof(dp[cur]));
    dp[cur][0][0][0] = 0;

    for(LL i = 1; i <= n; i++)
    {
        cur ^= 1;
        memset(dp[cur], 0x3f, sizeof(dp[cur]));
        for(LL j = 0; j <= i; j++)
        {
            LL k = i > s;
            LL l = i > e;
            if(i != s && i != e){
                if(i!=n && j) upd(dp[cur][j][k][l], dp[cur^1][j-1][k][l]+empL(i)+empR(i));//另外开一个分量
                if(i!=n && (j||l)) upd(dp[cur][j][k][l], dp[cur^1][j][k][l]+setL(i)+empL(i));//放在某分量的左边
                if(i!=n && (j||k)) upd(dp[cur][j][k][l], dp[cur^1][j][k][l]+setR(i)+empR(i));//放在某分量的右边
    //            if(k) upd(dp[cur][j][k][l],dp[cur^1][j][k][l]+)
                if(i != n && (j >= 1 || (j == 0 && (k||l)))) upd(dp[cur][j][k][l], dp[cur^1][j+1][k][l]+setL(i)+setR(i));//链接不同的两个分量
                if(i == n && k && l && j == 0) upd(dp[cur][j][k][l], dp[cur^1][j][k][l]+setL(i)+setR(i));//链接最后的两个分量
            }
            if(i == s)
            {
                if(i != n)
                {
                    upd(dp[cur][j][1][l], dp[cur^1][j+1][0][l]+setL(i));//与另一个分量合并
                    upd(dp[cur][j][1][l], dp[cur^1][j][0][l]+empR(i));//自己成为一个分量
                }
                else if(j == 0) upd(dp[cur][j][1][l], dp[cur^1][j][0][l]+setL(i));//与另一个分量合并
            }
            if(i == e)
            {
                if(i != n)
                {
                    upd(dp[cur][j][k][1], dp[cur^1][j+1][k][0]+setR(i));
                    upd(dp[cur][j][k][1], dp[cur^1][j][k][0]+empL(i));
                }
                else if(j == 0) upd(dp[cur][j][k][1], dp[cur^1][j][k][0]+setR(i));
            }
        }
    }
    printf("%I64d\n", dp[cur][0][1][1]);
    return 0;
}


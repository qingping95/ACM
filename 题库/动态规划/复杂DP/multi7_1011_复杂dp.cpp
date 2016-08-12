/*
*	仍然是需要从简单情况考虑：从第n个点考虑，那么最终哪些点会与n点决斗呢？由于大家行进的速度相同，所以这些点一定
*	全是往右移动，一个个与n决斗，再从第一个点开始考虑，不管第一个点的方向如何，最后都会向右走，那么接下来如果遇
*	到一个向右移动的点，那么必然是和点1一起向右移动，不会发生决斗；如果遇到一个向左移动的点，那么一定会与左边来
*	的点发生决斗，最终的结果仍然是还剩至少一个点向右移动。想到这里的话，不难想到这样的dp[i][j]，表示前i个点有j个
*	点往右走的概率
*		dp[i][j] = sigma(dp[i-1][j+k] * 1/2^(k+1) )	a[i] == 0;
*		dp[i][j] = dp[i-1][j-1]				a[i] == 1;
*	直接转移的话是n^3的复杂度，但是可以做一个sum[j] = sigma(dp[i][j] * 1/2^(j+1))的后缀和,这样
*		dp[i][j] = sum[j]*2^j
*	不过a[i]值不同的时候需要不同的处理，并且，当j为1的时候，因为还可以是i这个点打倒了所有前面点，最后反转方向往右
*	所以还需要乘以2;
*	至于要求的输出p*inv(q)只需要做除法的时候全用逆元乘即可。
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
const LL INF = 0x3f3f3f3f;
const LL mod = 1e9+7.5;
const LL N = 1010;
LL dp[N][N];
LL a[N];
LL two[N];
LL inv[N];
LL pow_mod(LL x, LL k)
{
    LL res = 1;
    while(k)
    {
        if(k & 1) res = res * x % mod;
        x = x * x % mod;
        k >>= 1;
    }
    return res;
}

int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
//    freopen("1011.in","r",stdin);
    two[0] = inv[0] = 1;
    for(int i = 1; i < N; i++) two[i] = two[i-1]*2%mod, inv[i] = pow_mod(two[i], mod-2);
//    cout<<inv[999]<<endl;
    LL cas = 0;
    LL T;
    scanf("%I64d", &T);
    while(T--)
    {
        LL n;
        scanf("%I64d", &n);
        for(LL i = 0; i < n; i++)
            scanf("%I64d", &a[i]);
        if(n == 1) {
            printf("Case #%I64d: 1\n", ++cas);
            continue;
        }
        memset(dp, 0, sizeof(dp));
        dp[0][0] = dp[0][1] = inv[1+1];
        for(LL i = 1; i < n-1; i++)
        {
            for(LL j = i+1; j > 0; j--)
            {
                if(a[i] == 1) dp[i][j] = (dp[i-1][j-1] - dp[i-1][j])*two[j]%mod;
                if(a[i] == 0){
                    dp[i][j] = dp[i-1][j]*two[j]%mod;
                    if(j == 1) dp[i][j] = dp[i][j] * 2 % mod;
                }
//                    dp[i][j] = (dp[i][j]*pow_mod(pow_mod(2, j), mod-2)%mod+dp[i][j+1])%mod;
                dp[i][j] = (dp[i][j]*inv[j+1]%mod+dp[i][j+1])%mod;
            }
            dp[i][0] = dp[i][1];
        }
        LL ans = 0;
        for(LL i = 1; i <= n-1; i++)
        {
            ans = (ans + (dp[n-2][i] - dp[n-2][i+1])*2%mod)%mod;
//            ans = (ans + dp[n-2][i]*pow_mod(pow_mod(2, i), mod-2)%mod)%mod;
        }
        if(ans < 0) ans += mod;
        printf("Case #%I64d: %I64d\n", ++cas, ans);
    }
    return 0;
}


/*
*		dp[i][j]=sigma(dp[i-1][k]*b[f(k^j)]
*	
*	这个吊模板就是用来解决上述式子的，更为标准的是CF#259div1D那个题中的表达式。
*	可以很快速的求解dp[n]的每一项。复杂度为m*log(n)，m为第二维大小
*
* 	这个题，我的想法是这样的：首先枚举X，那么也就是需要在[x, m+x]中找出n个数，使得这n个数异或和为0，
*   然后方案数加起来即可。那么对于每个枚举的X来说，我们记dp[i][j]表示前i个数，异或和为j的方案数，
*   那么dp[i][j]=sigma(dp[i-1][k]*b[k^j])。其中b[i]=1当且仅当x <= i <=x+m，否则为0；那么上述式子其实
*   和上一题CF的题就没多大区别了。然后就直接套用fwt，当然这里需要注意的是模数必须乘上做fwt的那个数组
*   的大小len(这里的len也和NTT,FFT一样必须是大于等于N的最小二次幂数)。最后答案也需要除以这个len。
*	下面的解法中，直接用a[i]数组pow_mod,我认为是因为dp[0][j]的初始值都与b[i]数组相同；
*   验证发现的确两种方法都可以AC。
*/
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
typedef long long LL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
const LL basemod = 1000000007;
LL mod = basemod;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
//防爆long long mul_mod
LL mul(LL a, LL b, LL p) {
    return (a * b - (LL)((long double)a / p * b + 1e-3) * p + p) % p;
}
void arrMul(LL n, LL *c, LL *a, LL *b) {
    for (int i = 0; i < n; ++i)
        c[i] = mul(a[i], b[i], mod);
}
LL pow_mod(LL x, LL k, LL mod)
{
    LL res = 1;
    while(k)
    {
        if( k & 1) res = mul(res, x, mod);
        x = mul(x, x, mod);
        k >>= 1;
    }
    return res;
}
void FWT(LL *a, int n) {
    if (n == 1) return;
    int m = n >> 1;
    FWT(a, m);
    FWT(a + m, m);
    for (int i = 0; i < m; ++i) {
        LL u = a[i], v = a[i + m];
        a[i] = (u + v) % mod;
        a[i + m] = (u - v + mod) % mod;
    }
}
void dFWT(LL *a, int n) {
    if (n == 1) return;
    int m = n >> 1;
    for (int i = 0; i < m; ++i) {
        LL u = a[i], v = a[i + m];
        a[i] = (u + v) % mod;
        a[i + m] = (u - v + mod) % mod;
    }
    dFWT(a, m);
    dFWT(a + m, m);
}
void Conv(LL *A, LL *B, int n, int t)//t -> 运算次数，n -> 运算长度, B -> 为转换数组, A -> 结果/初值数组。
{
	FWT(A, n);
    FWT(B, n);
    for (; t; t >>= 1, arrMul(n, B, B, B)) //类似快速幂
        if (t & 1) arrMul(n, A, A, B);
    dFWT(A, n);
}
LL a[1<<12], b[1<<12];
LL solve(int n, int m, int L, int R)
{
    LL len = 1;
    while(len <= R) len *= 2;
    mod = basemod * len;
    for(int i = 0; i < len ;i++)
        a[i] = b[i] = (i >= L && i <= R);
//    FWT(a, len);
//    for(int i = 0; i < len; i++)
//        a[i] = pow_mod(a[i], 2 * n + 1, mod);
//    dFWT(a, len);
    Conv(a, b, len, 2*n);
    return (a[0] + mod)%mod/len;
}
int main()
{
    Open();
    int n, m, L, R;
    while(~scanf("%d%d%d%d", &n, &m, &L, &R))
    {
        LL ans = 0;
        for(int i = L; i <= R; i++)
            ans = (ans + solve(n, m, i, i+m))%basemod;
        printf("%lld\n", ans);
    }
    return 0;
}

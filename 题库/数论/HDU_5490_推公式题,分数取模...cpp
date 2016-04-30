/*
*	Problem Description
As we know, sequence in the form of an=a1+(n?1)d is called arithmetic progression and sequence in the form of bn=b1qn?1(q>1,b1≠0) is called geometric progression. Huazheng wants to use these two simple sequences to generate a simple matrix. Here is what he decides to do:
Use the geometric progression as the first row of the simple matrix: c[0,n]=bn
Use the arithmetic progression as the first column of the simple matrix: c[n,0]=an
Calculate the item at n-th row, m-th column of the simple matrix as c[n,m]=c[n?1,m]+c[n,m?1], where n≥1 and m≥1.
Given the two sequences, Huazheng wants to know the value of cn,m, but he is too busy with his research to figure it out. Please help him to work it out. By the way, you can assume that c0,0=0.
 

Input
The first line of input contains a number T indicating the number of test cases (T≤200).
For each test case, there is only one line containing six non-negative integers b1,q,a1,d,n,m. (0≤n≤10000). All integers are less than 231.
 

Output
For each test case, output a single line consisting of “Case #X: Y”. X is the test case number starting from 1. Y is cn,m module 1000000007.

*
*	这个题极其恶心...简易题解链接：http://talk.icpc-camp.org/d/84-2015-g-simple-matrix/2
*	由于n小于10000,对于等差数列那一项我们可以利用链接中的公式直接暴力求和，但是m的范围及其大，等比数列那边不能
*	(sum = (1<=i<=n)C(n+m-i-1, n-i)*a[i] + (1<=i<=m)C(n+m-i-1, m-i)*b[i])
*	我们考虑简化等比那边的计算方法，第0行为等比数列，那么第一行为等比数列前n项和，通项公式化开之后发现其实新的
*	数列格式为一个等比+常数。那么我们可以将每一行的常数丢给a[i]去处理，这样只剩下一行等比数列，继续往下递归。
*	这里蛋疼的地方在于每次扔出来的这个常数并不是整数。。可能是分数，但是最终结果一定是整数，而且得取模，炒鸡蛋疼
*	我这里中途一直维护了分子和分母，直到最终一行的等比数列算出来之后再加上去，此时结果一定为整数，在对分母取逆元
*	乘上去即可。
*	常数的格式为：			-b1*q^(i-1)/(q-1)^i
*	每一行等比数列首项为：	 b1*q^(i)  /(q-1)^i
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
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
const LL mod = 1000000007;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
LL a[N];
LL pow_mod(LL x, LL k, LL mod)
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
int main()
{
//    Open();
    LL T;scanf("%I64d", &T);LL cas = 1;
    while(T--)
    {
        LL b1, q, a1, d, n, m;
        scanf("%I64d%I64d%I64d%I64d%I64d%I64d", &b1, &q, &a1, &d, &n, &m);
        a[1] = a1;
        for(LL i = 2; i <= n; i++){
            a[i] = (a[i-1] + d)%mod;
        }
        LL ans = a[n];
        LL C = 1;
        for(LL i = n-1; i >= 1; i--)
        {
            C = C * (n + m - i - 1) % mod * pow_mod(n - i, mod - 2, mod)%mod;
            ans = (ans + a[i] * C)%mod;
        }

        LL zi = 0;
        LL mu = 1;
        LL qpow = 1;
        for(LL i = 1; i < n; i++){
            mu = mu * (q-1) % mod;
            zi = (zi * (q-1) % mod - C * qpow % mod * b1 % mod) % mod;
            qpow = qpow * q % mod;
            C = C * (n - i) %mod * pow_mod(n+m-i-1, mod-2, mod)%mod;
        }
        mu = mu * (q-1)%mod;
        zi = zi * (q-1)%mod;//n次
        zi = (zi + b1 * pow_mod(q, n-1, mod) %mod * (pow_mod(q, m, mod) - 1) % mod) %mod;
        ans = (ans + zi * pow_mod(mu, mod-2, mod)%mod)%mod;
        if(ans < 0) ans += mod;
        printf("Case #%I64d: %I64d\n", cas++, ans%mod);
    }
    return 0;
}

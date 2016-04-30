/*
*	Problem Description
As we know, sequence in the form of an=a1+(n?1)d is called arithmetic progression and sequence in the form of bn=b1qn?1(q>1,b1��0) is called geometric progression. Huazheng wants to use these two simple sequences to generate a simple matrix. Here is what he decides to do:
Use the geometric progression as the first row of the simple matrix: c[0,n]=bn
Use the arithmetic progression as the first column of the simple matrix: c[n,0]=an
Calculate the item at n-th row, m-th column of the simple matrix as c[n,m]=c[n?1,m]+c[n,m?1], where n��1 and m��1.
Given the two sequences, Huazheng wants to know the value of cn,m, but he is too busy with his research to figure it out. Please help him to work it out. By the way, you can assume that c0,0=0.
 

Input
The first line of input contains a number T indicating the number of test cases (T��200).
For each test case, there is only one line containing six non-negative integers b1,q,a1,d,n,m. (0��n��10000). All integers are less than 231.
 

Output
For each test case, output a single line consisting of ��Case #X: Y��. X is the test case number starting from 1. Y is cn,m module 1000000007.

*
*	����⼫�����...����������ӣ�http://talk.icpc-camp.org/d/84-2015-g-simple-matrix/2
*	����nС��10000,���ڵȲ�������һ�����ǿ������������еĹ�ʽֱ�ӱ�����ͣ�����m�ķ�Χ����󣬵ȱ������Ǳ߲���
*	(sum = (1<=i<=n)C(n+m-i-1, n-i)*a[i] + (1<=i<=m)C(n+m-i-1, m-i)*b[i])
*	���ǿ��Ǽ򻯵ȱ��Ǳߵļ��㷽������0��Ϊ�ȱ����У���ô��һ��Ϊ�ȱ�����ǰn��ͣ�ͨ�ʽ����֮������ʵ�µ�
*	���и�ʽΪһ���ȱ�+��������ô���ǿ��Խ�ÿһ�еĳ�������a[i]ȥ��������ֻʣ��һ�еȱ����У��������µݹ顣
*	���ﵰ�۵ĵط�����ÿ���ӳ�������������������������������Ƿ������������ս��һ�������������ҵ�ȡģ����������
*	��������;һֱά���˷��Ӻͷ�ĸ��ֱ������һ�еĵȱ����������֮���ټ���ȥ����ʱ���һ��Ϊ�������ڶԷ�ĸȡ��Ԫ
*	����ȥ���ɡ�
*	�����ĸ�ʽΪ��			-b1*q^(i-1)/(q-1)^i
*	ÿһ�еȱ���������Ϊ��	 b1*q^(i)  /(q-1)^i
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
        zi = zi * (q-1)%mod;//n��
        zi = (zi + b1 * pow_mod(q, n-1, mod) %mod * (pow_mod(q, m, mod) - 1) % mod) %mod;
        ans = (ans + zi * pow_mod(mu, mod-2, mod)%mod)%mod;
        if(ans < 0) ans += mod;
        printf("Case #%I64d: %I64d\n", cas++, ans%mod);
    }
    return 0;
}

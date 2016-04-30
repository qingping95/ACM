/*
*		dp[i][j]=sigma(dp[i-1][k]*b[f(k^j)]
*	
*	�����ģ����������������ʽ�ӵģ���Ϊ��׼����CF#259div1D�Ǹ����еı��ʽ��
*	���Ժܿ��ٵ����dp[n]��ÿһ����Ӷ�Ϊm*log(n)��mΪ�ڶ�ά��С
*
* 	����⣬�ҵ��뷨�������ģ�����ö��X����ôҲ������Ҫ��[x, m+x]���ҳ�n������ʹ����n��������Ϊ0��
*   Ȼ�󷽰������������ɡ���ô����ÿ��ö�ٵ�X��˵�����Ǽ�dp[i][j]��ʾǰi����������Ϊj�ķ�������
*   ��ôdp[i][j]=sigma(dp[i-1][k]*b[k^j])������b[i]=1���ҽ���x <= i <=x+m������Ϊ0����ô����ʽ����ʵ
*   ����һ��CF�����û��������ˡ�Ȼ���ֱ������fwt����Ȼ������Ҫע�����ģ�����������fwt���Ǹ�����
*   �Ĵ�Сlen(�����lenҲ��NTT,FFTһ�������Ǵ��ڵ���N����С��������)������Ҳ��Ҫ�������len��
*	����Ľⷨ�У�ֱ����a[i]����pow_mod,����Ϊ����Ϊdp[0][j]�ĳ�ʼֵ����b[i]������ͬ��
*   ��֤���ֵ�ȷ���ַ���������AC��
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
//����long long mul_mod
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
void Conv(LL *A, LL *B, int n, int t)//t -> ���������n -> ���㳤��, B -> Ϊת������, A -> ���/��ֵ���顣
{
	FWT(A, n);
    FWT(B, n);
    for (; t; t >>= 1, arrMul(n, B, B, B)) //���ƿ�����
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

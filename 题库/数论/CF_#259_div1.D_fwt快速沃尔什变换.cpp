//详细解释在Onenote上有
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = (1 << 20) + 10;
int m, n;
LL t, mod;
int b[22];
LL A[N], B[N];
LL aa[N];
int count(int s) {
    int ret = 0;
    while (s) s -= s & -s, ++ret;
    return ret;
}
LL mul(LL a, LL b, LL p) {
    return (a * b - (LL)((long double)a / p * b + 1e-3) * p + p) % p;
}
void arrMul(LL *c, LL *a, LL *b) {
    for (int i = 0; i < n; ++i)
        c[i] = mul(a[i], b[i], mod);
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
    for (; t; t >>= 1, arrMul(B, B, B)) //类似快速幂
        if (t & 1) arrMul(A, A, B);
    dFWT(A, n);
}
int main() {  
    cin >> m >> t >> mod;
    n = 1 << m;
    mod *= n;
    for (int i = 0; i < n; ++i) {
        scanf("%I64d", A + i);
        A[i] %= mod;
    }
    for (int i = 0; i <= m; ++i) {
        scanf("%d", b + i);
        b[i] %= mod;
    }
    for (int i = 0; i < n; ++i) {
        B[i] = b[count(i)];
    }
    
    Conv(A, B, n, t);
	for (int i = 0; i < n; ++i) {
		printf("%I64d\n", A[i] >> m);
    }
}

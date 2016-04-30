/*
* 题意：求bell[n]%m，n < 1<<31;
* 做法：由于给出的m是一个可分解为幂次全为1的质因数相乘的模数，所以可以用CRT去弄，再加上这个公式：
*		bell[n+p]%p = (bell[n+1]+bell[n])%p;这样就可以用矩阵快速幂求出结果，再让CRT去合并即可。
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 55
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
const LL mod[5] = {31, 37, 41, 43, 47};
void mul(LL A[N][N], LL B[N][N], LL t[N][N], LL n, LL m, LL l, LL id)
{
    LL tmp[N][N];
    for(LL i = 0; i < n; i++)
        for(LL j = 0; j < l; j++)
        {
            tmp[i][j] = 0;
            for(LL k = 0; k < m; k++)
                tmp[i][j] = (tmp[i][j] + A[i][k] * B[k][j])%mod[id];
        }
    for(LL i = 0; i < n; i++)
        for(LL j = 0; j < l; j++)
            t[i][j] = tmp[i][j];
}
void expo(LL p[N][N], LL e[N][N], LL k, LL n, LL id)
{
    for(LL i = 0; i < n; i++)
        for(LL j = 0; j < n; j++)
            e[i][j] = (i == j);
    while(k)
    {
        if(k & 1) mul(e, p, e, n, n, n, id);
        mul(p, p, p, n, n, n, id);
        k >>= 1;
    }
}
LL a[N][N], b[N][N], c[N][N], res[N];
LL s[N][N];
LL init(LL id, LL n)
{
    LL p = mod[id];
    for (int i = 0; i < p; ++i)
    {
        s[i][0] = s[i][i] = 1;
        for (int j = 1; j < i; ++j)
            s[i][j] = (s[i-1][j] + s[i - 1][j - 1])%p;
    }
    memset(a, 0, sizeof(a));
    a[0][0] = 1;
    a[0][1] = 1;
    for (int i = 2; i < p; ++i)
    {
        a[0][i] = 0;
        for (int j = 0; j < i; ++j)
            a[0][i] = (a[0][i] + s[i - 1][j] * a[0][j])%p;
    }
    if(n < p) return a[0][n];
    memset(b, 0, sizeof(b));
    memset(c, 0, sizeof(c));
    for(LL i = 0; i < p-1; i++)
        b[i][i] = b[i+1][i] = 1;
    b[p-1][p-1] = b[0][p-1] = b[1][p-1] = 1;
    expo(b, c, n/p, p, id);
    mul(a, c, a, 1, p, p, id);
    return a[0][n%p]%p;
}
void gcd(LL a, LL b, LL& d, LL& x, LL& y)
{
    if(!b)
    {
        d = a;
        x = 1;
        y = 0;
    }
    else
    {
        gcd(b, a%b, d, y, x);
        y -= x * (a / b);
    }
}
LL china(LL n, LL *a, const LL *m)
{
    LL M = 1, d, y, x = 0;
    for(LL i = 0; i < n; i++) M *= m[i];
    for(LL i = 0; i < n; i++)
    {
        LL w = M / m[i];
        gcd(m[i], w, d, d, y);
        x = (x + y*w%M*a[i]%M)%M;
    }
    return (x + M) % M;
}
int main()
{
//    Open();
    LL T;
    scanf("%I64d", &T);
    while(T--)
    {
        LL n;
        scanf("%I64d", &n);
        for(LL i = 0; i < 5; i++)
            res[i] = init(i, n);
        LL ans = china(5, res, mod);
        printf("%I64d\n", ans);
    }
    return 0;
}

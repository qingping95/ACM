#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
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
        //freopen("F:/in.txt","r",stdin);
        freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const LL mod = 1000000007;
void mul(LL A[3][3],LL B[3][3],LL t[3][3],LL n,LL m,LL l)//A 为n*m的矩阵，B为m*l的矩阵,t为结果矩阵
{
    LL tmp[3][3];//为了防止冲突
    for(LL i=0;i<n;i++)
        for(LL j=0;j<l;j++){
            tmp[i][j]=0;
            for(LL k=0;k<m;k++)
                tmp[i][j]=(tmp[i][j]+(LL)A[i][k]*B[k][j]%mod)%mod;
        }
    for(LL i=0;i<n;i++) for(LL j=0;j<l;j++) t[i][j]=tmp[i][j];
}
void expo(LL p[3][3],LL e[3][3],LL k,LL n)//P为n*n的矩阵，k为计算k次幂，e为结果矩阵
{
	for(LL i = 0; i < n; ++i) for(LL j = 0; j < n; ++j) e[i][j] = (i == j);
	while(k) {
		if(k&1) mul(e,p,e,n,n,n);
		mul(p,p,p,n,n,n);
		k>>=1;
	}
}
LL a[3][3];
LL b[3][3];
LL c[3][3];
int main()
{
    Open();
    for(int i = 0; i < 1000000; i++)
        putchar('a');
    putchar('\n');
    putchar('1');
    LL T;
    scanf("%I64d", &T);
    while(T--)
    {
        LL A, B, x, y;
        scanf("%I64d%I64d%I64d%I64d", &A, &B, &x, &y);
        a[0][0] = 2*A;
        a[1][0] = (B - A * A)%mod;
        a[0][1] = 1;
        a[1][1] = 0;
        expo(a, b, x, 2);
        expo(b, c, y, 2);
        a[0][0] = 2*A, a[0][1] = 2;
        mul(a, c, b, 1, 2, 2);
        printf("%I64d\n", b[0][1]%mod);
    }
    return 0;
}

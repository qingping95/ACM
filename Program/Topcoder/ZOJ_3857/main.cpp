#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 5
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
LL K, L;
void mul(LL A[N][N],LL B[N][N],LL t[N][N],LL n,LL m,LL l)//A 为n*m的矩阵，B为m*l的矩阵,t为结果矩阵
{
    LL tmp[N][N];//为了防止冲突
    for(LL i=0;i<n;i++)
        for(LL j=0;j<l;j++){
            tmp[i][j]=0;
            for(LL k=0;k<m;k++)
                tmp[i][j]=(tmp[i][j]+A[i][k]*B[k][j])%K;
        }
    for(LL i=0;i<n;i++) for(LL j=0;j<l;j++) t[i][j]=tmp[i][j];
}
void expo(LL p[N][N],LL e[N][N],LL k,LL n)//P为n*n的矩阵，k为计算k次幂，e为结果矩阵
{
	for(LL i = 0; i < n; ++i) for(LL j = 0; j < n; ++j) e[i][j] = (i == j);
	while(k) {
		if(k&1) mul(e,p,e,n,n,n);
		mul(p,p,p,n,n,n);
		k>>=1;
	}
}
LL a[N][N], b[N][N], c[N][N];
int main()
{
//    Open();
    while(~scanf("%lld%lld", &K, &L))
    {
        a[0][0] = 2%K, a[0][1] = 2LL * L % K;
        b[0][0] = 0, b[0][1] = (K-L)%K;
        b[1][0] = 1, b[1][1] = 2*L%K;
        expo(b, c, K, 2);
        mul(a, c, a, 1, 2, 2);
        printf("%lld\n", (a[0][0] - 1 + K)%K);
    }
    return 0;
}

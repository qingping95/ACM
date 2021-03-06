#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define N 6
using namespace std;
const int mod=1e9+7;
void printfm(int A[N][N],int n,int m)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            printf("%d%c",A[i][j],(j==m-1)?'\n':' ');
        }
    printf("\n");
}
void mul(int A[N][N],int B[N][N],int t[N][N],int n,int m,int l)//A 为n*m的矩阵，B为m*l的矩阵,t为结果矩阵
{
    int tmp[N][N];//为了防止冲突
    for(int i=0;i<n;i++)
        for(int j=0;j<l;j++){
            tmp[i][j]=0;
            for(int k=0;k<m;k++)
                tmp[i][j]=(tmp[i][j]+A[i][k]*B[k][j])%mod;
        }
    for(int i=0;i<n;i++) for(int j=0;j<l;j++) t[i][j]=tmp[i][j];
}
void expo(int p[N][N],int e[N][N],int k,int n)//P为n*n的矩阵，k为计算k次幂，e为结果矩阵
{
	for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) e[i][j] = (i == j);
	while(k) {
		if(k&1) mul(e,p,e,n,n,n);
		mul(p,p,p,n,n,n);
		k>>=1;
	}
}
int a[N][N];
int b[N][N];
int c[N][N];
int main()
{
#ifndef ONLINE_JUDGE
    //freopen("E:/in.txt","r",stdin);
    //freopen("E:/my.txt","w",stdout);
#endif
    int n,a0,ax,ay,b0,bx,by;
    while(~scanf("%d%d%d%d%d%d%d",&n,&a0,&ax,&ay,&b0,&bx,&by))
    {
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(c,0,sizeof(c));
        a[0][0]=0,a[0][1]=a0*b0%mod,a[0][2]=a0,a[0][3]=b0,a[0][4]=1;
        b[0][0]=1,b[1][0]=1,b[1][1]=ax*bx%mod,b[2][1]=ax*by%mod,b[2][2]=ax,b[3][1]=bx*ay%mod;
        b[3][3]=bx,b[4][1]=ay*by%mod,b[4][2]=ay,b[4][3]=by,b[4][4]=1;
        //printfm(a,1,5);
        //printfm(b,5,5);
        expo(b,c,n,5);
        mul(a,c,c,1,5,5);
        printf("%d\n",c[0][0]);
    }
    return 0;
}

//比较优雅的方式
struct Matrix
{
    ll a[2][2];
    Matrix()
    {
        memset(a,0,sizeof(a));
    }
    void init()
    {
         for(int i=0;i<2;i++)
             for(int j=0;j<2;j++)
                 a[i][j]=(i==j);
    }
    Matrix operator * (const Matrix &B)const
    {
        Matrix C;
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                for(int k=0;k<2;k++)
                    C.a[i][j]=(C.a[i][j]+a[i][k]*B.a[k][j])%Mod;
        return C;
    }
    Matrix operator ^ (const ll &t)const
    {
        Matrix res,A=(*this);
        ll p=t;
        res.init();
        while(p)
        {
            if(p&1)res=res*A;
            A=A*A;
            p>>=1;
        }
        return res;
    }
}t[MAXM];
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
//        freopen("/home/qingping/out.txt","w",stdout);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int MN = 110;
///该快速幂板子运算前一定要记得将矩阵的初始化
struct Mat{
    int n, m;
    LL mat[MN][MN];
    Mat(int _n = MN, int _m = MN){n = _n, m = _m;}
    void resize(int _n, int _m){n = _n, m = _m;memset(mat, 0, sizeof(mat));}
    void unit(int _n, int _m)
    {
        n = _n, m = _m;memset(mat, 0, sizeof(mat));
        for(int i = 0; i < n; i++) mat[i][i] = 1;
    }
    void print()
    {
        for(int i = 0; i < n; i++, printf("\n"))
            for(int j = 0; j < m; j++)
                printf("%d ", mat[i][j]);
    }
};
Mat operator*(Mat a, Mat b)
{
    int n = a.n, m = a.m, k = b.m;
    Mat c;
    c.resize(n, k);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < k; j++)
            for(int l = 0; l < m; l++)
            {
                if(a.mat[i][l] && b.mat[l][j])
                    c.mat[i][j] += a.mat[i][l]*b.mat[l][j];
            }
    return c;
}
Mat operator^(Mat A, int x)
{
    Mat c;
    c.unit(A.n, A.m);
    while(x)
    {
        if(x & 1) c = c*A;
        A = A*A;
        x >>= 1;
    }
    return c;
}
char op[3];
int main()
{
//    Open();
    int n, m, k;
    while(~scanf("%d%d%d", &n, &m, &k))
    {
        if(n+m+k == 0) break;

        Mat res, tmp, ini;
        res.unit(n+1, n+1);
        while(k--)
        {
            scanf("%s", op);
            int x, y;
            if(op[0] == 'g')
            {
                scanf("%d", &x);
                x--;
                for(int i = 0; i < n+1; i++)
                {
                    res.mat[i][x]+=res.mat[i][n];
                }
            }
            if(op[0] == 's')
            {
                scanf("%d%d", &x, &y);
                if(x == y) continue;
                x--, y--;
                for(int i = 0; i < n+1; i++)
                    swap(res.mat[i][x], res.mat[i][y]);
            }
            if(op[0] == 'e')
            {
                scanf("%d", &x);
                x--;
                for(int i = 0; i < n+1; i++)
                    res.mat[i][x] = 0;
            }
        }
        ini.resize(1, n+1);
        ini.mat[0][n] = 1;
        res = res^m;
        ini = ini*res;
        for(int i = 0; i < n; i++)
        {
            printf("%lld%c", ini.mat[0][i], " \n"[i == n-1]);
        }
    }
    return 0;
}


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

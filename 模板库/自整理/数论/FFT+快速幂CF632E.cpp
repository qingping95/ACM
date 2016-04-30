/*
*	CF_632E 有n种数，每种数可以无限拿，问取出正好K个数，能够组成的数有哪些。
*	设dp[i][j]=1,表示数字i可以用j个数字组成，那dp[i][j] = (sigma(dp[i-k][j-1]&v[k]))>0 v[k] = 1,当且仅当k是题中给出的数
*	那么就可以卷积+快速幂求得结果。复杂度n*logn*logn N=1000000;
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <bitset>
//#include <unordered_map>
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
const int N = 1000100;
const double PI = acos(-1.0);
struct complex
{
    double r,i;
    complex(double _r = 0,double _i = 0)
    {
        r = _r; i = _i;
    }
    complex operator +(const complex &b)
    {
        return complex(r+b.r,i+b.i);
    }
    complex operator -(const complex &b)
    {
        return complex(r-b.r,i-b.i);
    }
    complex operator *(const complex &b)
    {
        return complex(r*b.r-i*b.i,r*b.i+i*b.r);
    }
};
void change(complex y[],int len)
{
    int i,j,k;
    for(i = 1, j = len/2;i < len-1;i++)
    {
        if(i < j)swap(y[i],y[j]);
        k = len/2;
        while( j >= k)
        {
            j -= k;
            k /= 2;
        }
        if(j < k)j += k;
    }
}
void FFT(complex y[],int len,int on)
{
    change(y,len);
    for(int h = 2;h <= len;h <<= 1)
    {
        complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j = 0;j < len;j += h)
        {
            complex w(1,0);
            for(int k = j;k < j+h/2;k++)
            {
                complex u = y[k];
                complex t = w*y[k+h/2];
                y[k] = u+t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    if(on == -1)
        for(int i = 0;i < len;i++)
            y[i].r /= len;
}
complex x1[N*4], x2[N*4];
void mul(int a[], int b[], int &la, int lb)
{
    int len = 1;
    while(len <= la + lb) len <<= 1;
    for(int i = 0; i <= la; i++)
        x1[i] = complex(a[i], 0);
    for(int i = la+1; i < len; i++)
        x1[i] = complex(0, 0);
    for(int i = 0; i <= lb; i++)
        x2[i] = complex(b[i], 0);
    for(int i = lb+1; i < len; i++)
        x2[i] = complex(0, 0);
    FFT(x1, len, 1);
    FFT(x2, len, 1);
    for(int i = 0; i < len; i++) x1[i] = x1[i] * x2[i];
    FFT(x1, len, -1);
    for(int i = 0; i < len; i++)
        a[i] = ((int)(x1[i].r+0.5))>0;
    la += lb;
}
int dp[N*4];
int v[N*4];
int main()
{
    //Open();
    int n, k;
    scanf("%d%d", &n, &k);
    int ma = 0;
    for(int i = 0; i < n; i++)
    {
        int ttt;
        scanf("%d", &ttt);
        ma = max(ma, ttt);
        v[ttt] = 1;
    }
    ma;
    dp[0] = 1;
    int la = 1, lb = ma;
    while(k)
    {
        if(k & 1) mul(dp, v, la, lb);
        mul(v, v, lb, lb);
        k >>= 1;
    }
    for(int i = 1; i <= N; i++)
    {
        if(dp[i] != 0) printf("%d ", i);
    }
    return 0;
}

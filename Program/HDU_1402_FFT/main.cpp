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
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
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
int FFTstarto(char *a, char *b, int *res, int n, int m, complex *x1, complex *x2)
{
    int len1 = max(n, m);
    int len = 1;
    while(len < len1 * 2) len <<= 1;
    for(int i = 0; i < len; i++)
    {
        if(i < n) x1[i] = complex(a[n - i - 1] - '0', 0);
        else x1[i] = complex(0, 0);
        if(i < m) x2[i] = complex(b[m - i - 1] - '0', 0);
        else x2[i] = complex(0, 0);
    }

    FFT(x1, len, 1);
    FFT(x2, len, 1);
    for(int i = 0; i < len; i++)
        x1[i] = x1[i] * x2[i];
    FFT(x1, len, -1);
    for(int i = 0; i < len; i++)
        res[i] = x1[i].r + 0.5;
    return len;
}
const int N = 100050;
char a[N], b[N];
int sum[N*2];
complex x1[N*2], x2[N*2];
int main()
{
    //Open();
    while(~scanf("%s%s", a, b))
    {
        memset(sum, 0, sizeof(sum));
        int len = FFTstarto(a, b, sum, strlen(a), strlen(b), x1, x2);
        int ma = len;
        for(int i = 0; i < len || sum[i] != 0; i++)
        {
            ma = i;
            if(sum[i] >= 10) sum[i+1] += sum[i] / 10, sum[i] %= 10;
        }
        while(sum[ma] == 0 && ma) ma--;
        for(int i = ma; i >= 0; i--)
        {
            printf("%c", sum[i] + '0');
        }
        puts("");
    }
    return 0;
}

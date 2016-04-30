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
typedef pair<double,double> PDD;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}

///需要注意的是，有FFT的题目中，数组长度默认开四倍！否则会RE
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
//a, b:卷积数组，res结果数组，n,m 数组a,b的长度
complex x1[N], x2[N];
int FFTstarto(LL *a, LL *b, LL *res, int n, int m)
{
    int len1 = max(n, m);
    int len = 1;
    while(len < len1 * 2) len <<= 1;
    for(int i = 0; i < len; i++)
    {
        if(i < n) x1[i] = complex(a[i], 0);
        else x1[i] = complex(0, 0);
        if(i < m) x2[i] = complex(b[i], 0);
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
const int N = 400020;
int a[N];
LL num[N];
struct Reader
{
    static const int MSIZE = 1000 * 8 * 1024;
    char buf[MSIZE], *pt = buf, *o = buf;
    void init()
    {
        fread(buf, 1, MSIZE, stdin);
    }
    int getint()
    {
        int f = 1, x = 0;
        while(*pt != '-' && !isdigit(*pt)) pt++;
        if(*pt == '-') f = -1, pt++;
        else x = *pt++ - 48;
        while(isdigit(*pt)) x = x*10 + *pt++ - 48;
        return x * f;
    }
}frd;
int main()
{
    Open();
    frd.init();
    int T;
    T = frd.getint();
//    scanf("%d", &T);
    while(T--)
    {
        memset(num, 0, sizeof(num));
        int n;
        n = frd.getint();
//        scanf("%d", &n);
        int ma = 0;
        for(int i = 0; i < n; i++)
        {
            a[i] = frd.getint();
//            scanf("%d", &a[i]);
            ma = max(a[i], ma);
            num[a[i]]++;
        }
        sort(a, a+n);
        ma++;
        int len = FFTstarto(num, num, num, ma, ma, x1, x2);
        for(int i = 0; i < n; i++)
            num[a[i]+a[i]]--;
        for(int i = 0; i < len; i++)
            num[i] /= 2;
        for(int i = 1; i < len; i++)
            num[i] += num[i-1];
        LL ans = 0;
        for(int i = 0; i < n; i++)
        {
            ans += num[len-1] - num[a[i]];
            ans -= (LL)(n - i - 1) * i;
            ans -= (LL)(n - i - 1) * (n - i - 2) / 2;
            ans -= (LL)(n - 1);
        }
        printf("%.7f\n", ans*1.0 / ((LL)(n)*(n-1)/2*(n-2)/3));
    }
    return 0;
}

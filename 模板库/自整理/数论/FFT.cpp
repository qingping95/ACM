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

/*namespace FFT*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
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
const int N = 200050;
namespace FFT {
	int pos[N];
    struct comp {
        double r , i ;
        comp ( double _r = 0 , double _i = 0 ) : r ( _r ) , i ( _i ) {}
        comp operator + ( const comp& x ) {
            return comp ( r + x.r , i + x.i ) ;
        }
        comp operator - ( const comp& x ) {
            return comp ( r - x.r , i - x.i ) ;
        }
        comp operator * ( const comp& x ) {
            return comp ( r * x.r - i * x.i , i * x.r + r * x.i ) ;
        }
        comp conj () {
            return comp ( r , -i ) ;
        }
    } A[N] , B[N] ;

    const double pi = acos ( -1.0 ) ;
    void FFT ( comp a[] , int n , int t ) {
        for ( int i = 1 ; i < n ; ++ i ) if ( pos[i] > i ) swap ( a[i] , a[pos[i]] ) ;
        for ( int d = 0 ; ( 1 << d ) < n ; ++ d ) {
            int m = 1 << d , m2 = m << 1 ;
            double o = pi * 2 / m2 * t ;
            comp _w ( cos ( o ) , sin ( o ) ) ;
            for ( int i = 0 ; i < n ; i += m2 ) {
                comp w ( 1 , 0 ) ;
                for ( int j = 0 ; j < m ; ++ j ) {
                    comp& A = a[i + j + m] , &B = a[i + j] , t = w * A ;
                    A = B - t ;
                    B = B + t ;
                    w = w * _w ;
                }
            }
        }
        if ( t == -1 ) for ( int i = 0 ; i < n ; ++ i ) a[i].r /= n ;
    }
    void mul ( int *a , int *b , int *c ,int k) {
        int i , j ;
        for ( i = 0 ; i < k ; ++ i ) A[i] = comp ( a[i] , b[i] ) ;
        j = __builtin_ctz ( k ) - 1 ;
        for ( int i = 0 ; i < k ; ++ i ) {
            pos[i] = pos[i >> 1] >> 1 | ( ( i & 1 ) << j ) ;
        }
        FFT ( A , k , 1 ) ;
        for ( int i = 0 ; i < k ; ++ i ) {
            j = ( k - i ) & ( k - 1 ) ;
            B[i] = ( A[i] * A[i] - ( A[j] * A[j] ).conj () ) * comp ( 0 , -0.25 ) ;
        }
        FFT ( B , k , -1 ) ;
        for ( int i = 0 ; i < k ; ++ i ) {
            c[i] += ( B[i].r + 0.5 );
        }
    }
}
using namespace FFT;
int f[5];
int a[5][N], b[5][N], c[5][5][N];
int d[N];
char s1[N], s2[N];
int main()
{
//    Open();
    scanf("%s%s", s1, s2);
    int n = strlen(s1);
    for(int i = 0; i < n; i++)
        a[s1[i]-'A'][i] = a[s1[i]-'A'][i+n] = 1, b[s2[i]-'a'][n-i] = 1;
    for(int i = 0; i < 5; i++)
        f[i] = i;
    int len = 1;
    while(len<2*n) len <<= 1;
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
        {
            mul(a[i], b[j], c[i][j], len);
        }
    int ans = 0;
    do{
        for(int i = n; i<2*n; i++) d[i] = 0;
        for(int i = 0; i < 5; i++)
            for(int j = n; j < 2*n; j++)
                d[j] += c[i][f[i]][j];
        ans = max(ans, *max_element(d+n, d+2*n));
    }while(next_permutation(f, f+5));
//    cout<<ans<<endl;
    printf("%d\n", n-ans);
    return 0;
}


/////////////////////////对小模数取模的FFT/////////////////////////
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
const int N = 2000020;
const int mod=1000003;
const double PI=acos(-1.0);
struct Complex
{
    double x,y;
    Complex(double _x=0,double _y=0):x(_x),y(_y){}
    Complex operator + (const Complex &b)const
    {
        return Complex(x+b.x,y+b.y);
    }
    Complex operator - (const Complex &b)const
    {
        return Complex(x-b.x,y-b.y);
    }
    Complex operator * (const Complex &b)const
    {
        return Complex(x*b.x-y*b.y,x*b.y+y*b.x);
    }
    Complex operator / (const double &b)const
    {
        return Complex(x/b,y/b);
    }
};
void change(Complex y[],int len)
{
    for(int i=1,j=len/2;i<len-1;i++)
    {
        if(i<j)swap(y[i],y[j]);
        int k=len/2;
        while(j>=k)
        {
            j-=k;
            k/=2;
        }
        if(j<k)j+=k;
    }
}
void fft(Complex y[],int len,int on)
{
    change(y,len);
    for(int h=2;h<=len;h<<=1)
    {
        Complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j=0;j<len;j+=h)
        {
            Complex w(1,0);
            for(int k=j;k<j+h/2;k++)
            {
                Complex u=y[k];
                Complex v=w*y[k+h/2];
                y[k]=u+v;
                y[k+h/2]=u-v;
                w=w*wn;
            }
        }
    }
    if(on==-1)for(int i=0;i<len;i++)
        y[i]=y[i]/len;
}
Complex p1[N],p2[N],p3[N],q1[N],q2[N];
void multiply(int p[],int q[],int m)
{
    int t=sqrt(mod),len=1;
    while(len<2*m)len<<=1;
    for(int i=0;i<len;i++)
    {
        p1[i]=(i<m ? p[i]/t : 0);
        p2[i]=(i<m ? p[i]%t : 0);
        p3[i]=0;
        q1[i]=(i<m ? q[i]/t : 0);
        q2[i]=(i<m ? q[i]%t : 0);
    }
    fft(p1,len,1),fft(p2,len,1),fft(q1,len,1),fft(q2,len,1);
    for(int i=0;i<len;i++)
    {
        p3[i]=p1[i]*q2[i]+p2[i]*q1[i];
        p1[i]=p1[i]*q1[i];
        p2[i]=p2[i]*q2[i];
    }
    fft(p1,len,-1),fft(p2,len,-1),fft(p3,len,-1);
    for(int i=0;i<len;i++)
    {
        long long t1=p1[i].x+0.5,t2=p2[i].x+0.5,t3=p3[i].x+0.5;
        p[i]=(t1*t*t+t*t3+t2)%mod;
    }
    for(int i=m;i<len;i++)
    {
        p[i%m]=(p[i%m]+p[i])%mod;
        p[i]=0;
    }
}
int f[N], g[N], t[N];
LL pow_mod(LL x, LL k, LL m)
{
    LL res = 1;
    while(k)
    {
        if(k & 1) res = res * x % mod;
        x = x*x%mod;
        k >>= 1;
    }
    return res;
}
int main()
{
//    Open();
    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);
    for(int i = 'A'; i <= 'Z'; i++) g[i%m]++;
    f[0] = 1;
    while(n)
    {
        if(n&1)
        {
            memset(t, 0, sizeof(t));
            for(int i = 0; i < m; i++)
                t[i] = (t[i] + f[i*p%m])%mod;
            multiply(t, g, m);
            memcpy(f, t, sizeof(t));
        }
        memset(t, 0, sizeof(t));
        for(int i = 0; i < m; i++)
            t[i] = (t[i] + g[i*p%m])%mod;
        multiply(t, g, m);
        memcpy(g, t, sizeof(t));
        p = 1LL*p*p%m;
        n >>= 1;
    }
    LL ans = 0;
    LL inv2 = pow_mod(2, mod-2, mod);
//    cout<<inv2<<endl;
    for(int i = 0; i < m; i++)
    {
        ans = (ans + (LL)f[i]*(f[i]-1)*inv2%mod)%mod;
    }
    cout<<ans<<endl;
    return 0;
}


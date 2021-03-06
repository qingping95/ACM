/*
题意 ：给出两个串A ， B，每个串是若干个byte，A串的每个byte的最后一个bit是可以修改的。
问最少修改多少，使得B串是A的一个子串。

做法：前7位都是不能修改的，所以要完全匹配，那么先按前7位KMP一下，记录匹配的位置。之后就是统计以这些位置开始，需要修改多少位，然后 取最小值。
所以提取出最后一个bit，成了两个01串，统计hamming distance。
记得若干年前就和队友讨论过这个问题，不过当时不是01串，觉得不可在n * m之内解决，然后 就放弃了。结果这个01串是可以 在nlgn解决 的。吓傻。。
两个01串a , b。将b反转之后，求一次卷积，便可以得到a串中以i为起始位置，与b进行匹配有多少个位置同为1。
那么接下来把a,b的01反转一下，再求一次卷积，就可以得到原串中为多少个位置同为0。就得到了hamming距离。
卷积求的是c[i + j] = a[i] * b[j]。由于我们将b进行了反转，所以a串中以i为起始位置的。
c[i + m - 1] = a[i + 0] * b[m - 0 - 1] + a[i + 1] * b[m - 1 - 1] + …… a[i + j] * b[m - j - 1] + …… a[i + m - 1] * b[m - (m - 1) - 1]。
如果a , b中同为1,乘积为1,否则为0,这样就统计出了有多少位同为1了。吓傻。。。太神了。
预处理出这个之后，再枚举之前KMP所得到的匹配位置 就可以了。
*/
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
complex x1[N], x2[N];
int FFTstarto(int *a, int *b, int *res, int n, int m)
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
        res[i] += x1[i].r + 0.5;
    return len;
}
void getnext(int *T, int n, int *nxt)
{
    nxt[0] = -1;
    int tlen = n, j = 0, k = -1;
    while(j < tlen)
        if(k == -1 || T[j] == T[k]) nxt[++j] = ++k;
        else k = nxt[k];
}
void getmatchpos(int *s, int n, int *p, int m, int *nxt, int *pos, int &cnt)
{
    cnt = 0;
    if(n < m) return ;
    int i = 0, j = 0;
    while(i < n)
    {
        if(j == -1 || s[i] == p[j]) i++, j++;
        else j = nxt[j];
        if(j == m)
        {
            pos[cnt++] = i - m;
            j = nxt[j];
        }
    }
}
int a[N/4], b[N/4], c[N/4], d[N/4], nxt[N/4], pos[N/4];
int res[N];
int main()
{
    Open();
    int n, m;
    scanf("%d%d", &n, &m);
    char str[121];
    for(int i = 0 ; i < n; i++)
    {
        scanf("%s", str);
        a[i] = 0;
        for(int j = 0; j < 7; j++) a[i] = a[i] * 10 + str[j] - '0';
        c[i] = str[7] - '0';
    }
    for(int i = 0 ; i < m; i++)
    {
        scanf("%s", str);
        b[i] = 0;
        for(int j = 0; j < 7; j++) b[i] = b[i] * 10 + str[j] - '0';
        d[m-1-i] = str[7] - '0';
    }
    int cnt = 0;
    getnext(b, m, nxt);
    getmatchpos(a, n, b, m, nxt, pos, cnt);
    if(cnt == 0) puts("No");
    else {
        puts("Yes");
        int ans = INF, idx = -1;
        FFTstarto(c, d, res, n, m);
        for(int i = 0; i < n; i++) c[i] ^= 1;
        for(int i = 0; i < m; i++) d[i] ^= 1;
        FFTstarto(c, d, res, n, m);
        for(int i = 0; i < cnt; i++)
        {
            if(m - res[pos[i]+m-1] < ans)
            {
                ans = m - res[pos[i]+m-1];
                idx = pos[i];
            }
        }
        printf("%d %d\n", ans, idx+1);
    }
    return 0;
}

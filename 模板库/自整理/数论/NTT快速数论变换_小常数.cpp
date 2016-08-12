#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <climits>
#include <bitset>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PII;
const LL INF = 0x3f3f3f3f;
const LL mod = 1e9+7.5;
const LL N = 100020;
const int P = 998244353;//119*2^23 + 1
const LL g = 3;
const LL NUM = 40; //2^NUM > P
LL wn[NUM];
LL G[NUM], nG[NUM];
LL a[N*4], b[N*4];//这里要小心数组的大小要开大，一般原数组*4
LL c[N];
LL qpow_mod(LL x, LL k)
{
    LL res = 1;
    while(k)
    {
        if(k & 1) res = x * res % P;
        x = x*x%P;
        k >>= 1;
    }
    return res;
}
void init()/// /// /// /// /////////////////////////////////////// 一定要先调用这个函数
{
    LL now=(P-1)/2,ng=qpow_mod(g,P-2),len=0;
    while (now%2==0){
        len++;
        G[len]=qpow_mod(g,now);
        nG[len]=qpow_mod(ng,now);
        now>>=1;
    }
}
void NTT(LL x[],LL n,LL fl){
    for (LL i=(n>>1),j=1;j<n;j++){
        if (i<j) swap(x[i],x[j]);
        LL k;
        for (k=(n>>1);i&k;i^=k,k>>=1); i^=k;
    }
    LL now=0;
    for (LL m=2;m<=n;m<<=1){
        LL w; now++;
        if (fl==1) w=G[now];
        else w=nG[now];
        for (LL i=0;i<n;i+=m){
            LL cur=1;
            for (LL j=i;j<i+(m>>1);j++){
                LL u=x[j],v=1ll*x[j+(m>>1)]*cur%P;
                x[j]=(u+v)%P; x[j+(m>>1)]=(u-v+P)%P;
                cur=1ll*cur*w%P;
            }
        }
    }
    if(fl == -1){
        LL inv = qpow_mod(n, P - 2);
        for(LL i = 0; i < n; i++)
            x[i] = x[i] % P * inv % P;
    }
}

//求卷积
void Conv(LL a[], LL b[], LL n)
{
    NTT(a, n, 1);
    NTT(b, n, 1);
    for(LL i = 0; i < n; i++)
        a[i] = a[i] * b[i] % P;
    NTT(a, n, -1);
}

LL f[N], invf[N];
LL two[N];
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
    init();
    two[0] = f[0] = invf[0] = 1;
    for(LL i = 1; i < N; i++) f[i] = f[i-1]*i%P, invf[i] = qpow_mod(f[i], P-2), two[i] = two[i-1]*2%P;
    LL T;
//    T = frd.getint();
//    read(T);
    scanf("%I64d", &T);
    while(T--)
    {
        LL n;
        scanf("%I64d", &n);
        for(LL i = 0; i < n; i++)
        {
            scanf("%I64d", &c[i]);
        }
        sort(c, c+n);
        LL len = 1;
        while(len < n*2) len<<= 1;
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        for(LL i = 0; i < n; i++)
        {
            a[n-i] = two[i]*c[i]%P*f[n-i-1]%P;
            b[i] = invf[n-i];
        }
        b[n] = invf[0];
        Conv(a, b, len);
        LL last = 0;
        for(LL i = 1; i <= n; i++)
        {
            last += a[i+n]*invf[i-1]%P;
            last %= P;
            printf("%I64d ", last);
        }
        putchar('\n');
    }
    return 0;
}


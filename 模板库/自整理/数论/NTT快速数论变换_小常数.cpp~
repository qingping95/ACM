//第二类斯特林数的快速求解。ZOJ 3899
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 100010
#define lson x<<1
#define rson x<<1|1
#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}


const LL P = 880803841LL;//119*2^23 + 1
const LL G = 26;
const LL NUM = 26; //2^NUM > P
LL wn[NUM];
LL a[N*5], b[N*5];//这里要小心数组的大小要开大，一般原数组*4

LL qpow_mod(LL x, LL k, LL m)
{
    LL res = 1;
    while(k)
    {
        if(k & 1) res = x * res % m;
        x = x*x%m;
        k >>= 1;
    }
    return res;
}
void getwn()
{
    for(LL i = 0; i < NUM; i++)
    {
        LL t = 1LL << i;
        wn[i] = qpow_mod(G, (P-1)/t, P);
    }
}
void Rader(LL a[], LL len)
{
    LL j = len >> 1;
    for(LL i = 1; i < len - 1; i ++)
    {
        if(i < j) swap(a[i], a[j]);
        LL k = len >> 1;
        while(j >= k)
        {
            j -= k;
            k >>= 1;
        }
        if(j < k) j += k;
    }
}
void NTT(LL a[], LL len, LL on)
{
    Rader(a, len);
    LL id = 0;
    for(LL h = 2; h <= len; h <<= 1)
    {
        id ++;
        for(LL j = 0; j < len; j += h){
            LL w = 1;
            for(LL k = j; k < j + h / 2; k ++)
            {
                LL u = a[k] % P;
                LL t = w * (a[k + h / 2] % P) % P;
                a[k] = (u + t) % P;
                a[k + h / 2] = ((u - t) % P + P) % P;
                w = w * wn[id] % P;
            }
        }
    }
    if(on == -1){
        for(LL i = 1; i < len / 2; i++)
            swap(a[i], a[len - i]);
        LL inv = qpow_mod(len, P - 2, P);
        for(LL i = 0; i < len; i++)
            a[i] = a[i] % P * inv % P;
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

//这边是线段树部分，无关的地方
struct node
{
    LL l, r, lazy, cnt;
    node(){}
    node(LL ll, LL rr){l = ll, r = rr, lazy = 0, cnt = r - l + 1;}
    void UPDATE()
    {
        cnt = r - l + 1 - cnt;
    }
}lt[N * 8];
void build(LL l, LL r, LL x)
{
    lt[x] = node(l, r);
    if(l == r) return ;
    build(l, mid, lson);
    build(mid+1, r, rson);
}
void push_up(LL x)
{
    lt[x].cnt = lt[lson].cnt + lt[rson].cnt;
}
void push_down(LL x)
{
    if(lt[x].lazy){
        lt[lson].lazy ^= 1;
        lt[rson].lazy ^= 1;
        lt[x].lazy = 0;
        lt[lson].UPDATE();
        lt[rson].UPDATE();
    }
}
void update(LL l, LL r, LL x)
{
    if(lt[x].l >= l && lt[x].r <= r)
    {
        lt[x].UPDATE();
        lt[x].lazy ^= 1;
        return ;
    }
    push_down(x);
    if(r <= mid) update(l, r, lson);
    else if(l > mid) update(l, r, rson);
    else update(l, mid, lson), update(mid+1, r, rson);
    push_up(x);
}

int main()
{
//    Open();
    f[0] = invf[0] = 1;
    for(LL i = 1; i < N; i ++)
    {
        f[i] = f[i - 1] * i % P;
        invf[i] = qpow_mod(f[i], P - 2, P);
    }
    getwn();
    LL T;scanf("%lld", &T);
    while(T--)
    {
        LL n, m, d;
        scanf("%lld%lld%lld", &n, &m, &d);
        LL len = 1;
        while(len <= m * 2) len <<= 1;
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        for(LL i = 0; i <= n; i++){
            a[i] = (((i & 1) ? -1 : 1) * invf[i] + P) % P;
            b[i] = qpow_mod(i, n, P) * invf[i] % P;
        }
        Conv(a, b, len);
		//预处理数组的过程。
        build(1, m, 1);
        while(d--)
        {
            LL x, y;
            scanf("%lld%lld", &x, &y);
            update(x, y, 1);
            printf("%lld\n", a[lt[1].cnt]);
        }
    }
    return 0;
}

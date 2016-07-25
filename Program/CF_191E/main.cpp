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
const LL N = 100110;
LL a[N];
LL sum[N];
LL sta[N];
LL c[N];
LL t, n, k;
LL getsum(LL x)
{
    if(x < 1) return 0;
    LL res = 0;
    for(LL i = x; i < t+10; i += i & -i)
        res += c[i];
    return res;
}
void add(LL x, LL val)
{
    if(x < 1) return;
    for(LL i = x; i; i -= i & -i)
        c[i] += val;
}
LL check(LL x)
{
    for(LL i = 0; i < t+10; i++)
        c[i] = 0;
    LL res = 0;
    for(LL i = n-1; i >= 0; i--)
    {
        add(sum[i], 1);
        LL idx = (i > 0 ? sta[sum[i-1]-1] : 0)+ x;
        idx = lower_bound(sta, sta+t, idx) - sta + 1;
        res += getsum(idx);
    }
    return res;
}
int main()
{
    //Open();
    scanf("%I64d%I64d", &n, &k);
    for(LL i = 0; i < n; i++)
        scanf("%I64d", &a[i]);
    sta[0] = sum[0] = a[0];
    for(LL i = 1 ; i < n; i++)
        sta[i] = sum[i] = sum[i-1]+a[i];
    t = n;
    sort(sta, sta+t);
    t = unique(sta, sta+t) - sta;
    for(LL i = 0; i < n; i++)
        sum[i] = lower_bound(sta, sta+t, sum[i]) - sta + 1;
    LL lb = -1e15, ub = 1e15;
    while(lb+1 < ub)
    {
        LL mid = lb+ub >> 1;
        if(check(mid) < k)
            ub = mid;
        else
            lb = mid;
    }
    if(check(lb) >= k)
        printf("%I64d\n", lb);
    else
        printf("%I64d\n", ub);
    return 0;
}

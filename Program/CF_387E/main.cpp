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
const LL N = 1000010;
LL c[N];//
LL n, k;//
LL sta[N];//
LL ID[N];//
bool isb[N];
LL a[N];
LL L[N];
LL R[N];
void add(LL x, LL val)
{
    for(LL i = x; i <= n; i += i & -i) c[i] += val;
}
LL getsum(LL x)
{
    LL res = 0;
    for(LL i = x; i; i -= i & -i)
        res += c[i];
    return res;
}
int main()
{
    //Open();
    scanf("%I64d%I64d", &n, &k);
    for(LL i = 1; i <= n; i++)
    {
        scanf("%I64d", &a[i]);
        ID[a[i]] = i;
        add(i, 1);
    }
    for(LL i = 1; i <= k ;i++)
    {
        LL x;
        scanf("%I64d", &x);
        isb[x] = 1;
    }
    LL tail = 0;
    for(LL i = 1; i <= n; i++)
    {
        if(isb[a[i]]){
            while(tail > 0 && sta[tail-1] >= a[i]) tail--;
            sta[tail++] = a[i];
        }else{
            LL id = lower_bound(sta, sta+tail, a[i])-sta;
            if(id == 0) L[a[i]] = 0;
            else L[a[i]] = ID[sta[id-1]];
        }
    }
    tail = 0;
    for(LL i = n; i >= 1; i--)
    {
        if(isb[a[i]]){
            while(tail>0 && sta[tail-1] >= a[i]) tail--;
            sta[tail++] = a[i];
        }else{
            LL id = lower_bound(sta, sta+tail, a[i]) - sta;
            if(id == 0) R[a[i]] = n+1;
            else R[a[i]] = ID[sta[id-1]];
        }
    }
    LL ans = 0;
    for(LL i = 1; i <= n; i++)
    {
        if(isb[i]) continue;
        ans += getsum(R[i]-1) - getsum(L[i]);
        add(ID[i], -1);
    }
    printf("%I64d\n", ans);
    return 0;
}

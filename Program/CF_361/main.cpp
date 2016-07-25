#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <climits>
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
const LL N = 200010;
int c1[N], c2[N];
int n;
void upma(int x, int val)
{
    if(x == 0) return ;
    for(int i=x;i<=n;i+=i&-i) c1[i] = max(c1[i], val);
}
int getma(int x)
{
    if(x > n) return -INF;
    int rnt = -INF;
    for(int i=x;i>0;i-=i&-i) rnt = max(rnt, c1[i]);
    return rnt;
}
void upmi(int x, int val)
{
    if(x == 0) return ;
    for(int i=x;i<=n;i+=i&-i) c2[i] = min(c2[i], val);
}
int getmi(int x)
{
    if(x > n) return INF;
    int rnt = INF;
    for(int i=x;i>0;i-=i&-i) rnt = min(rnt, c2[i]);
    return rnt;
}
int a[N], b[N];
int main()
{
//    Open();
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) c1[i] = -INF, c2[i] = INF;
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++)
        scanf("%d", &b[i]);
    LL res = 0;
    for(int i = n; i >= 1; i--)
    {
        upma(i, a[i]);
        upmi(i, b[i]);
        int lb = i-1, ub = n+1;
        while(lb + 1 < ub)
        {
            int mid = lb + ub >> 1;
            if(getma(mid) - getmi(mid) <= 0)
                lb = mid;
            else
                ub = mid;
        }
        int l, r;
        if(getma(ub) - getmi(ub) == 0) l = ub;
        else if(getma(lb) - getmi(lb) == 0) l = lb;
        else continue;

        lb = i-1, ub = n+1;
        while(lb+1<ub)
        {
            int mid = lb + ub >> 1;
            if(getma(mid) - getmi(mid) >= 0)
                ub = mid;
            else
                lb = mid;
        }
        if(getma(ub) - getmi(ub) == 0) r = ub;
        else if(getma(lb) - getmi(lb) == 0) r = lb;
        else continue;
        if(l >= i && l <= n && r >= i && r <= n){
            if(r < l) swap(l, r);
            res += r - l + 1;
        }
    }
    printf("%I64d\n", res);
    return 0;
}

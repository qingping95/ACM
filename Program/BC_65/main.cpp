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
const int N = 100100;
LL c[N], a[N], ans[N];
LL n;
void add(LL x, LL val)
{
    for(LL i = x; i; i -= i & -i) c[i] += val;
}
LL getsum(LL x)
{
    if(x == 0) return 0;
    LL ret = 0;
    for(LL i = x; i < n + 10; i += i & -i) ret += c[i];
    return ret;
}
int main()
{
//    Open();
    LL T;
    scanf("%I64d", &T);
    while(T--)
    {
        memset(c, 0, sizeof(c));
        scanf("%I64d", &n);
        for(LL i = 1; i <= n; i++)
        {
            scanf("%I64d", &a[i]);
            add(i, 1);
        }
        a[0] = 0;
        for(LL i = n; i > 0; i--)
        {
            LL lb = 0, ub = n+1, res = -1;
            while(lb + 1 < ub)
            {
                LL mid = lb + ub >> 1;
                if(getsum(mid) >= a[i] - a[i-1] + 1) res = lb = mid;
                else ub = mid;
            }
            if(res == -1) n /= 0;
            ans[i] = res;
            add(res, -1);
        }
        for(LL i = 1; i <= n; i++)
            printf("%I64d%c", ans[i], " \n"[i == n]);
    }
    return 0;
}

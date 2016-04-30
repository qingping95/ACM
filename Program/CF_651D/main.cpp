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
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const LL N = 500010;
LL dp1[N], dp2[N];
char str[N], tmp[N];
LL n, a, b, T;
LL fuck(char str[])
{
    LL ans = 0;
    memset(dp1, 0, sizeof(dp1));
    memset(dp2, 0, sizeof(dp2));
    dp1[0] = 1 + (str[0] == 'w' ? b : 0);
    for(LL i = 1; i < n; i++)
    {
        dp1[i] = dp1[i-1] + a + a + 1;
        if(str[i] == 'w') dp1[i] += b;
        if(dp1[i] <= T) ans = i+1;
    }
    tmp[0] = str[0];
    tmp[n] = '\n';
    for(LL i = 1, tail = n-1; i < n; i++, tail--)
    {
        tmp[i] = str[tail];
    }
    dp2[0] = 0;
    for(LL i = 1; i < n; i++)
    {
        dp2[i] = dp2[i-1] + a + 1;
        if(tmp[i] == 'w') dp2[i] += b;
    }
    for(LL i = 0; i < n; i++)
    {
        if(dp1[i] > T) continue;
        ans = max(ans, (LL)i+(upper_bound(dp2, dp2+n, T - dp1[i]) - dp2));
    }
    strcpy(str, tmp);
    return ans;
}
int main()
{
    //Open();
    scanf("%I64d%I64d%I64d%I64d",&n, &a, &b, &T);
    scanf("%s", str);
    LL ans = fuck(str);
    ans = max(ans, fuck(str));
    printf("%I64d\n", min(n, ans));
    return 0;
}

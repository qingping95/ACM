#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
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
map<LL, int> mp;
LL a[100010];
int main()
{
    //Open();
    LL n;
    scanf("%I64d", &n);
    LL sum = 0;
    for(LL i = 0; i < n; i++)
    {
        scanf("%I64d", &a[i]);
        sum += a[i];
        mp[sum]++;
    }
    LL ans = n - mp[0], add = 0;
    for(LL i = 0; i < n; i++)
    {
        add += a[i];
        ans = min(ans, n - mp[add]);
    }
    cout<<ans<<endl;
    return 0;
}

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
char str[100];
LL dp[100];
LL ans;
LL ten[10];
LL nine[10];
LL dfs(int idx, bool up)
{
    if(!up && dp[idx] != -1) return dp[idx];
    LL rnt = 0;
    int limit = up ? str[idx]-'0' : 9;
    if(idx == 0) return limit >= 1;
    for(int i = 0; i <= limit; i++)
    {
        rnt += dfs(idx-1, up & (i == limit));
    }
    if(limit > 1)
    {
        rnt += ten[idx];
    }
    else if(limit == 1)
    {
        LL tmp = 0;
        for(int i = idx-1; i >= 0; i--)
            tmp = tmp * 10 + (str[i] - '0');
        tmp++;
        rnt += tmp;
    }
    if(up == false) dp[idx] = rnt;
    return rnt;
}
int main()
{
    //Open();
    ten[0] = nine[0] = 1;
    for(int i = 1; i < 10; i++) ten[i] = ten[i-1] * 10, nine[i] = nine[i-1]*9;
    memset(dp, -1, sizeof(dp));
    scanf("%s", str);
    int len = strlen(str);
    reverse(str, str+len);
    ans = dfs(len-1, true);
    printf("%I64d\n", ans);
    return 0;
}

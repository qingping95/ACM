#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
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
const int N = 1011;
int d[N], t[N];
char str[26][1111];
char pre[1<<16][22];
int dp[1<<16];
int n;
int getval(int s, int id)
{
    int ti = 0;
    for(int i = 0; i < n; i++)
        if(s & (1 << i))
        {
            ti += t[i];
        }
    ti += t[id];
    return max(0, ti - d[id]);
}
int ans[26];
char tmp[22];
int main()
{
//    Open();
    int T;scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
        {
            scanf("%s%d%d", str[i], &d[i], &t[i]);
        }
        memset(dp, 0x3f, sizeof(dp));
        memset(pre, 0, sizeof(pre));
        dp[0] = 0;
        int limit = 1 << n;
        for(int s = 1; s < limit; s++)
        {
            for(int i = 0; i < n; i++)
            {
                if(s & (1 << i))
                {
                    int val = dp[s ^ (1 << i)] + getval(s^(1<<i), i);
                    strcpy(tmp, pre[s^(1<<i)]);
                    tmp[__builtin_popcount(s)-1] = i+'A';
                    tmp[__builtin_popcount(s)] = '\0';
                    if(dp[s] > val || (dp[s] == val && (pre[s] == '\0' || strcmp(tmp, pre[s]) < 0)))
                    {
                        dp[s] = val;
                        strcpy(pre[s], tmp);
                    }
                }
            }
        }
        printf("%d\n", dp[limit-1]);
        for(int i = 0; i < n; i++)
        {
            printf("%s\n", str[pre[limit-1][i]-'A']);
        }
    }
    return 0;
}

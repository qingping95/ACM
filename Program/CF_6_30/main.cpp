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
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const LL N = 2010;
const LL mod = 1000000007;
LL dp[N][N];
char str[N];
LL sum[N];
int main()
{
    //Open();
    LL n, K;
    scanf("%I64d%I64d", &n, &K);
    scanf("%s", str+1);
    dp[0][0] = 1;
    sum[0] = 1;
    for(LL i = 1; i <= n; i++)
    {
        for(LL j = 0; j <= K; j++)
        {
            dp[i][j] = sum[j]*(str[i]-'a')%mod;
            for(LL k = i-1; j >= (i-k)*(n-i+1) && k >= 0; k--)
            {
                dp[i][j] = (dp[i][j] + dp[k][j-(i-k)*(n-i+1)]*('z' - str[i])%mod)%mod;
            }
//            if(dp[i][j] == 1) cout<<i<<" "<<j<<endl;
        }
        for(LL j = 0; j <= K; j++)
            sum[j] = (sum[j] + dp[i][j]) %mod;
    }
    printf("%I64d\n", sum[K]);
//    cout<<sum[K]<<endl;
    return 0;
}

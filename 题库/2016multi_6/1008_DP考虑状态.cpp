/*
*	观察题目中的公式，其中ij是必须选的，kl是必须不选的，也就是说ijkl都必须选取，那么可以dp这四个位置
*	有没有被选定，dp[i][j][2][2],表示前i个物品总和为j，后两个为0,1,2三个状态，分别表示ij(kl)选定了0个1个2个。
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <climits>
#include <bitset>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int INF = 0x3f3f3f3f;
const int mod = 1e9+7.5;
const int N = 1010;
int dp[N][3][3];
int v[N];
int main(){
//    freopen("1008.in","r",stdin);
//    freopen("/home/qingping/in.txt","r",stdin);
    int T;
    scanf("%d", &T);
    while(T--)
    {
//        memset(dp, -1, sizeof(dp));
        int n, s;
        scanf("%d%d", &n, &s);
        for(int i = 1; i <= n; i++)
        {
            scanf("%d", &v[i]);
        }
        int ans = 0;
        int cur = 0;
        memset(dp, -1, sizeof(dp));
        //memset(dp[cur], -1, sizeof(dp[cur]));
        dp[0][0][0] = 1;
        for(int i = 0; i < n; i++)
        {
            for(int j = s; j >= 0; j--)
            {
                for(int s1 = 2; s1 >= 0; s1--)
                {
                    for(int s2 = 2; s2 >= 0; s2--)
                    {
                        //if(dp[j][s1][s2] == -1) continue;
                        if(j - v[i+1] >= 0&& s1 > 0 && dp[j-v[i+1]][s1-1][s2] != -1)
                            dp[j][s1][s2] = (max(0, dp[j][s1][s2]) + dp[j-v[i+1]][s1-1][s2]) %mod;
                        if(s2 > 0 && dp[j][s1][s2-1] != -1)
                            dp[j][s1][s2] = (max(0, dp[j][s1][s2]) + dp[j][s1][s2-1])%mod;
                        if(j - v[i+1] >= 0 && dp[j-v[i+1]][s1][s2] != -1) dp[j][s1][s2] = (max(0, dp[j][s1][s2])+dp[j-v[i+1]][s1][s2])%mod;
                    }
                }
                if(i == n-1 && dp[j][2][2] != -1)
                    ans = (ans + dp[j][2][2])%mod;
            }
        }
        printf("%d\n", (int)((LL)ans*4%mod));
    }
    return 0;
}


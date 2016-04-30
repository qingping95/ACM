#include <iostream>
#include <cstdio>
using namespace std;
const int INF=0x3f3f3f3f;
int dp[2];
int a[22][510];
int n, m;
int main()
{
//    freopen("D:/in.txt", "r", stdin);
    int cas = 1;
    int T;scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                scanf("%d", &a[i][j]);
        int limit = 1 << n;
        int ans = -INF;
        for(int s = 1; s < limit ; s++)
        {
            int tmps = s;
            bool flag = false;
            int idx = -1, nxt = -1;
            while(tmps && !flag){
                nxt = __builtin_ffs(tmps);
                if(idx != -1 && (nxt - idx) % 2 == 0){
                    flag = true;
                    continue;
                }
                idx = nxt;
                tmps -= tmps & (-tmps);
            }
            if(flag) continue;
            dp[0] = dp[1] = -INF;
            int cur = 0;
            for(int i = 0; i < m; i++){
                int res = 0;
                tmps = s;
                while(tmps)
                {
                    res += a[__builtin_ffs(tmps)-1][i];
                    tmps -= tmps & (-tmps);
                }
                dp[cur] = max(dp[cur], max(res, dp[cur ^ 1] + res));
                cur ^= 1;
            }
            ans = max(ans, max(dp[0], dp[1]));
        }
        printf("Case #%d: %d\n", cas++, ans);
    }
    return 0;
}

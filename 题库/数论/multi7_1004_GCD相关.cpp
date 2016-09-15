/*
*	num[i] 表达数i质因数的个数，对于询问中的x来说，答案为如下：
*		num[lcm(x,a)/gcd(x,a)] = num[x/gcd(x,a)*a/gcd(x,a)] = num[x/gcd(x,a)]+num[a/gcd(x,a)];
*	那么只需要枚举x的每个约数，寻找最小的num[a/gcd(x,a)]即可，用优先队列维护，并用vis数组标记是否被删除
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
const int N = 1000010;
int num[N];
int vis[N];
priority_queue<PII, vector<PII>, greater<PII> > que[N];
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
    for(int i = 2; i < N; i++)
    {
        if(num[i]) continue;
        for(int j = i; j < N; j+=i)
        {
            int cnt = 0;
            int tmp = j;
            while(tmp % i == 0) cnt++, tmp /= i;
            num[j] += cnt;
        }
    }
    int n;
    int cas = 0;
    while(~scanf("%d", &n))
    {
        if(n == 0) break;
        printf("Case #%d:\n", ++cas);
        char op[2];
        for(int i = 0; i < n; i++)
        {
            int x;
            scanf("%s%d", op, &x);
            if(op[0] == 'I') {
                if(vis[x] == cas) continue;
                vis[x] = cas;
                for(int i = 1; i*i <= x; i++)
                {
                    if(x % i) continue;
                    que[i].push(PII(num[x/i], x));
                    if(i*i != x)
                        que[x/i].push(PII(num[i], x));
                }
                //s.emplace(x);
            }else if(op[0] == 'D'){
                vis[x] = 0;
            }else{
                int ans = INF;
                for(int i = 1; i*i <= x; i++)
                {
                    if(x % i) continue;
                    int pe = x/i;
                    while(!que[i].empty() && vis[que[i].top().second] != cas) que[i].pop();
                    if(!que[i].empty()) ans = min(ans, num[pe] + que[i].top().first);
                    while(!que[pe].empty()&& vis[que[pe].top().second] != cas) que[pe].pop();
                    if(!que[pe].empty()) ans = min(ans, num[i] + que[pe].top().first);
                }
                if(ans == INF) ans = -1;
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}


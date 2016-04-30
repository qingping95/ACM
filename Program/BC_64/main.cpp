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
const int N = 200020;
LL num[N];
LL pre[N];
LL tail;
LL m;
LL solve(LL n)
{
    if(n <= m) return n * (1 + n) / 2;
    LL idx = lower_bound(num, num + tail, n) - num;
    if(n == num[idx]) return pre[idx];
    idx--;
    LL ans = pre[idx];
    LL bei = n / num[idx];
    ans -= (1LL + bei) * bei / 2;
    LL res = n % num[idx];
    ans += (bei-1)*bei/2 * pre[idx - 1];
    return ans + bei * solve(res);
}
int main()
{
    //Open();
    LL n;
    while(~scanf("%I64d%I64d", &n, &m))
    {
        num[0] = m;
        pre[0] = m*(m+1)/2;
        tail = 1;
        while(num[tail-1] <= n)
        {
            num[tail] = num[tail-1] * m;
            pre[tail] = pre[tail-1] * m + num[tail-1] * pre[0];
            //cout<<num[tail]<<" "<<pre[tail]<<endl;
            tail++;
        }
//        num[tail] = num[tail-1] * m;
//        pre[tail] = pre[tail-1] * m + num[tail-1] * pre[0];
//        tail++;
        printf("%I64d\n", solve(n));
    }
    return 0;
}

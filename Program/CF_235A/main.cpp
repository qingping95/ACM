#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
#define DEBUG(x) cout<<#x<<" -> "<<x<<endl
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
const LL N = 1000010;
LL dp[N];
int main()
{
    //Open();
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 6;
    for(LL i = 4; i < N; i++)
    {
        //LL idx = lower_bound(pri, pri+pn, i) - pri - 1;
        dp[i] = dp[i-1];
        LL a = -1;
        for(LL j = i-1; j >= 1; j--)
        {
            if(__gcd(i, j) == 1){
                if(a == -1){
                    a = j;
                }else if(__gcd(j, a) == 1){
                    LL lcm = i/__gcd(i, j)*j;
                    lcm = lcm / __gcd(lcm, a) * a;
                    dp[i] = max(dp[i], lcm);
                    break;
                }
            }
        }
    }
//    cout<<"OK"<<endl;
    LL n;
    while(~scanf("%I64d", &n))
        printf("%I64d\n", dp[n]);
    return 0;
}

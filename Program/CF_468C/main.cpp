#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <climits>
#include <assert.h>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
ULL dp[111];
ULL a[1000];
const int N = 1000010;
int val[N];
int vis[N];
ULL f(ULL x)
{
    ULL t = 0;
    ULL ten = 1;
    ULL old = x;
    while(x)
    {
        a[t++] = x % 10;
        x /= 10;
        ten *= 10;
    }
    ULL res = 0;
    ten /= 10;
    for(int i = t-1; i >= 0; i--, ten /= 10)
    {
        if(i == 0){
            res += (a[i]+1)*a[i]/2;
            continue;
        }
        old -= a[i]*ten;
        res += (a[i]-1)*a[i]/2*ten + dp[i]*a[i];
        res += a[i]*(old+1);
    }
    return res;
}
ULL ff(ULL x)
{
    ULL res = 0;
    while(x)
    {
        res += x % 10;
        x /= 10;
    }
    return res;
}
int main()
{
    //Open();
    dp[0] = 0;
    for(ULL i = 1, num = 1; i < 18; i++, num*=10)
    {
        dp[i] = (dp[i-1]*10)+45*num;
//        cout<<dp[i]<<endl;
    }
    memset(vis, -1, sizeof(vis));
    val[0] = 0;
    vis[0] = 0;
    for(int i = 1; val[i-1] < N; i++)
    {
        val[i] = val[i-1] + ff(i);
        assert(val[i] == f(i));
        if(val[i] < N) vis[val[i]] = i;
    }
//    cout<<f(1728496821LL)<<endl;
    ULL a, b;
    cin >> b;
    a = 0;
    while(true){
        a += b;
        ULL lb = 0, ub = ULLONG_MAX;
        while(lb + 1 < ub)
        {
            ULL mid = lb + ub >> 1;
            if(f(mid) >= a)
                ub = mid;
            else
                lb = mid;
        }
        ULL res = f(ub);
        while(res - a < N)
        {
            if(vis[res - a] != -1 && vis[res-a]+1 <= ub){
                cout<<vis[res-a]+1<<" "<<ub<<endl;
                return 0;
            }else{
                ub++;
                res = f(ub);
            }
        }
    }
    return 0;
}

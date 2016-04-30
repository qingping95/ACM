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
LL pow_mod(LL x, LL n, LL mod)
{
    LL rnt = 1;
    while(n)
    {
        if(n & 1) rnt = rnt * x %mod;
        x = x * x % mod;
        n >>= 1;
    }
    return rnt;
}
int main()
{
    //Open();
    int n, m;
    scanf("%d%d", &n ,&m);
    cout<<pow_mod()
    return 0;
}

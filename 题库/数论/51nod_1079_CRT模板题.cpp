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
void gcd(LL a, LL b, LL& d, LL& x, LL& y)
{
    if(!b) { d = a; x = 1; y = 0; }
    else { gcd(b, a%b, d, y, x); y -= x * (a / b); }
}
LL china(LL n, LL *a, const LL *m)
{
    LL M = 1, d, y, x = 0;
    for(LL i = 0; i < n; i++) M *= m[i];
    for(LL i = 0; i < n; i++)
    {
        LL w = M / m[i];
        gcd(m[i], w, d, d, y);
        x = (x + y*w%M*a[i]%M)%M;
    }
    return (x + M) % M;
}
LL m[1111], a[1111];
int main()
{
    //Open();
    LL n;
    scanf("%I64d", &n);
    for(int i = 0; i < n; i++)
        scanf("%I64d%I64d", &m[i], &a[i]);
    printf("%I64d\n", china(n, a, m));
    return 0;
}

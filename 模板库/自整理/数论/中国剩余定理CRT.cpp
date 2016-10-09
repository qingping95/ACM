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
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f3f3f3f3fLL;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
//        freopen("/home/qingping/in.txt","r",stdin);
//        freopen("/home/qingping/out.txt","w",stdout);
//        freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const LL N = 100100;
PII p[N];
LL n, m;
void ex_gcd(LL a, LL b,LL &x, LL &y)
{
    if(b == 0){
        x = 1;y = 0;return ;
    }
    ex_gcd(b, a%b, x, y);
    LL tmp = x;
    x = y;
    y = tmp - (a/b)*y;
}
LL CRT(LL a[],LL m[],LL n)
{
    LL M = 1;
    LL ans = 0;
    for(LL i=1; i<=n; i++)
        M *= m[i];
    for(LL i=1; i<=n; i++)
    {
        LL x, y;
        LL Mi = M / m[i];
        ex_gcd(Mi, m[i], x, y);

        \\\\\\\\\这里很容易爆long long///////
        ans = (ans + Mi * x * a[i]) % M;
    }
    if(ans < 0) ans += M;
    return ans;
}
LL check(LL x, LL y)
{
    if(abs(x-y)%__gcd(2*n, 2*m)) return INF;
    LL g = __gcd(2*n, 2*m);
    LL a[] = {x, y};
    LL M[] = {2*n, 2*m};
    LL X, Y;
    ex_gcd(2*n, 2*m, X, Y);
    X *= abs(x-y)/g;
    Y *= abs(x-y)/g;

    //将X和Y放置到距离0最近的位置
    X -= 2*m/g*(X/(2*m/g));
    Y -= 2*n/g*(Y/(2*n/g));
    while(X*2*n+x<=0) X += 2*m/g;
    while(Y*2*m+y<=0) Y += 2*n/g;
    //

    LL val = min(X*2*n+x, Y*2*m+y);
    return val;
}
LL solve(LL x, LL y)
{
    LL val = check(x, y);
    val = min(val, check(2*n-x, 2*m-y));
    val = min(val, check(2*n-x, y));
    val = min(val, check(x, 2*m-y));
    return val;
}
int main(){

//    Open();
    LL k;
    scanf("%I64d%I64d%I64d", &n, &m, &k);
    LL mit = solve(0, m);
    mit = min(mit, solve(n, 0));
    mit = min(mit, solve(n, m));
//    cout<<mit<<endl;
    for(LL i = 0; i < k; i++)
    {
        LL x, y;
        scanf("%I64d%I64d", &x, &y);
        if(n == m)
        {
            if(x == y) printf("%I64d\n", x);
            else printf("-1\n");
            continue;
        }
        LL val = solve(x, y);
        if(val >= mit) val = -1;
        printf("%I64d\n", val);
    }

    return 0;
}

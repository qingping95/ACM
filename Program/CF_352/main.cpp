//#include <iostream>
//#include <cstdio>
//#include <stack>
//#include <cstring>
//#include <queue>
//#include <algorithm>
//#include <cmath>
////#define lson x<<1
////#define rson x<<1|1
////#define mid ((lt[x].l+lt[x].r)/2)
////#define ID(x, y) ((x)*m+(y))
////#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
//using namespace std;
//typedef long long LL;
//typedef pair<LL,LL> PII;
//const LL INF=0x3f3f3f3f;
//void Open()
//{
//    #ifndef ONLINE_JUDGE
//        freopen("F:/in.txt","r",stdin);
//        //freopen("F:/my.txt","w",stdout);
//    #endif // ONLINE_JUDGE
//}
//#define D(x) ((x)*(x))
//LL c[500050];
//LL b[500050];
//int main()
//{
//    Open();
//    LL n, k;
//    scanf("%I64d%I64d", &n, &k);
//    LL sum = 0;
//    for(LL i = 0; i < n; i++)
//        scanf("%I64d", &c[i]), sum += c[i];
//    sort(c, c+n);
//    LL base = sum / n;
//    LL off = sum % n;
//    LL op = 0;
//    for(LL i = 0; i < n; i++)
//    {
//        if(i < n - off) b[i] = base;
//        else b[i] = base+1;
//        op += abs(b[i] - c[i]);
//    }
//    if(k >= op / 2 || n == 1) printf("%I64d\n", (LL)(off > 0));
//    else{
//        LL ma = c[n-1], mi = c[0];
//        LL curv = 1;
//        LL tk = k;
//        for(LL i = n-2; i >= 0 && tk > 0; i--)
//        {
//            if(tk < curv * (c[i+1] - c[i])){
//                LL ba = tk / curv;
//                LL of = tk % curv;
//                ma = c[i+1]-ba;
//                break;
//            }else{
//                tk -= curv*(c[i+1] - c[i]);
//                curv++;
//            }
//        }
//        curv = 1;
//        tk = k;
//        for(LL i = 1; i < n && tk > 0; i++)
//        {
//            if(tk < curv * (c[i] - c[i-1])) {
//                LL ba = tk / curv;
//                LL of = tk % curv;
//                mi = c[i-1]+ba;
//                break;
//            } else{
//                tk -= curv * (c[i] - c[i-1]);
//                curv ++;
//            }
//        }
//        printf("%I64d\n", ma - mi);
//    }
//    return 0;
//}
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
#define D(x) ((x)*(x))
const long double eps = 1e-10;
struct point
{
    LL x, y;
    long double value;
    long double dist(LL cx, LL cy)
    {
        return sqrt(D(cx-x) + D(cy-y));
    }
}p[100010];
struct info{
    long double d;
    LL id;
    bool operator<(const info &o) const
    {
        return d > o.d;
    }
}a[100010], b[100010];
LL ax, ay, bx, by, tx, ty, n;

int main()
{
//    Open();
    scanf("%I64d%I64d%I64d%I64d%I64d%I64d%I64d", &ax, &ay, &bx, &by, &tx, &ty, &n);
    long double sum = 0;
    for(LL i = 0; i < n; i++)
    {
        scanf("%I64d%I64d", &p[i].x, &p[i].y);
        p[i].value = p[i].dist(tx, ty);
        sum += 2.0*p[i].value;
    }
    for(LL i = 0; i < n; i++)
    {
        a[i] = (info){max((long double)0.0, p[i].value - p[i].dist(ax, ay)), i};
        b[i] = (info){max((long double)0.0, p[i].value - p[i].dist(bx, by)), i};
    }
    sort(a, a+n);
    sort(b, b+n);
//    long double res = 0;
    long double res = max(a[0].d, b[0].d);
    if(a[0].id != b[0].id) res = max(res, a[0].d+b[0].d);
    if(n > 1 && a[1].id != b[0].id) res = max(res, a[1].d+b[0].d);
    if(n > 1 && a[0].id != b[1].id) res = max(res, a[0].d+b[1].d);
    if(n > 1 && a[1].id != b[1].id) res = max(res, a[1].d+b[1].d);

    printf("%.12f\n", (double)(sum - res));
    return 0;
}

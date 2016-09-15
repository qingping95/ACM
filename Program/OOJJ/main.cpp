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
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f3f3f3f3fLL;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const LL N = 500010;
struct Point{
    LL x, y;
    Point(LL x = 0, LL y = 0) : x(x), y(y) {}
    bool operator<(const Point& o) const{
        return x < o.x || (x == o.x && y < o.y);
    }
}p[N], pc[N], que[N], pd[N];
typedef Point Vector;
Vector operator-(Point A, Point B)
{
    return Vector(A.x-B.x, A.y-B.y);
}
LL Cross(Vector A, Vector B)
{
    return A.x*B.y-A.y*B.x;
}
LL getConUp(Point *p, LL n, Point *ch)
{
    sort(p, p+n);
    LL m = 0;
    for(LL i = 0; i < n; i++)
    {
        while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) < 0) m--;
        ch[m++] = p[i];
    }
    return m;
}
LL getConDn(Point *p, LL n, Point *ch)
{
    sort(p, p+n);
    LL m = 0;
    for(LL i = n-1; i >= 0; i--)
    {
        while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) < 0) m--;
        ch[m++] = p[i];
    }
    return m;
}
LL cal(LL a, LL b, LL c, LL d)
{
    return a * c + b * d;
}
int main()
{
//    Open();
//    cout<<INF<<endl;
    LL n;
    scanf("%I64d", &n);
    for(LL i = 0; i < n; i++)
    {
        LL x, y;
        scanf("%I64d%I64d", &x, &y);
        que[i] = Point(x, y);
    }
    LL m;
    scanf("%I64d", &m);
    LL mc = INF, mcy, md = INF, mdx;
    for(LL i= 0;i < m; i++)
    {
        LL x, y;
        scanf("%I64d%I64d", &x, &y);
        p[i] = Point(x, y);
        if(mc > x) mc = x, mcy = y;
        if(md > y) md = y, mdx = x;
    }
    LL t = getConUp(p, m, pc);
    LL xt = getConDn(p, m, pd);
    for(LL i = 0; i < n; i++)
    {
        LL x = que[i].x;
        LL y = que[i].y;
        Point o(-y, x);
        LL lb = 0, ub = t;
        while(lb + 1 < ub)
        {
            LL mid = lb + ub >> 1;
//            LL x2 = pc[mid].x, x1 = pc[mid-1].x;
//            LL y2 = pc[mid].y, y1 = pc[mid-1].y;
//            if(y*(y2-y1) <= -x*(x2-x1)) ub = mid;
            if(Cross(pc[mid]-pc[mid-1], o) > 0) ub = mid;
            else lb = mid;
        }
        LL ans = INF;
        int up = min(ub+350, t-1);
        for(LL j = max(0LL, lb-350); j <= up; j++)
        {
            ans = min(ans, cal(x, y, pc[j].x, pc[j].y));
        }

        lb = 0, ub = xt;
        while(lb + 1 < ub)
        {
            LL mid = lb + ub >> 1;
//            LL x2 = pd[mid].x, x1 = pd[mid-1].x;
//            LL y2 = pd[mid].y, y1 = pd[mid-1].y;
//            if(y*(y2-y1) <= -x*(x2-x1)) lb = mid;
            if(Cross(pc[mid]-pc[mid-1], o) > 0) ub = mid;
            else lb = mid;
        }
        up = min(ub+350, xt-1);
        for(LL j = max(0LL, lb-350); j <= up; j++)
        {
            ans = min(ans, cal(x, y, pd[j].x, pd[j].y));
        }
        ans = min(ans, cal(x, y, mc, mcy));
        ans = min(ans, cal(x, y, mdx, md));
        printf("%I64d%c", ans, " \n"[i == n-1]);
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <iomanip>
//#include <unordered_map>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<int,string> PIS;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 200010;
struct Point
{
    long double x, y;
};
#define D(x) ((x)*(x))
long double dist(Point a, Point b)
{
    return sqrt(D(a.x - b.x) + D(a.y - b.y));
}
const long double eps = 1e-13;
const long double PI = acos(-1.0);
int dcmp(long double x)
{
    return (x > 0) - (x < 0);
}
long double solve(Point c1, long double r1, Point c2, long double r2)
{
    long double a = dist(c1, c2), b = r1, c = r2;
    if(dcmp(a - r1 - r2) >= 0) return 0;
    if(dcmp(a + r1 - r2) <= 0) return r1*r1*PI;
    if(dcmp(a + r2 - r1) <= 0) return r2*r2*PI;

    long double cta1 = acos((a*a+b*b-c*c)/2/(a*b));
    long double cta2 = acos((a*a+c*c-b*b)/2/(a*c));
    long double s1 = r1*r1*cta1 - r1*r1*sin(cta1)*(a*a+b*b-c*c)/2/(a*b);
    long double s2 = r2*r2*cta2 - r2*r2*sin(cta2)*(a*a+c*c-b*b)/2/(a*c);
    return s1 + s2;
}
int main()
{
    //Open();
    int x1, y1, x2, y2, r1, r2;
    scanf("%d%d%d%d%d%d", &x1, &y1, &r1, &x2, &y2, &r2);
//    std::setprecision(10);
    cout<<setprecision(15)<<solve((Point){x1, y1}, r1, (Point){x2, y2}, r2)<<endl;
    //printf("%.12Lg\n", solve((Point){x1, y1}, r1, (Point){x2, y2}, r2));
    return 0;
}

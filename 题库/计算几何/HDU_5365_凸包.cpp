#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 30
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
const double eps = 1e-8;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
struct Point
{
    int x, y;
    Point(){}
    Point(int x, int y):x(x), y(y){}
    bool operator<(const Point& o)const{return (x<o.x || (x == o.x && y < o.y));}
}pp[N], p1[N], pn[N];
typedef Point Vector;
int n;
Point operator-(Point A,Point B){return Point(A.x-B.x, A.y-B.y);}
int Cross(Point A, Point B){return A.x*B.y-A.y*B.x;}
double Dot(Vector A, Vector B){return A.x*B.x+A.y*B.y;}
double Length(Vector A){return sqrt(Dot(A,A));}
double Angle(Vector A,Vector B){return acos(Dot(A,B)/Length(A)/Length(B));}
int dcmp(double x)
{
    if(fabs(x) < eps) return 0;
    else return 1;
}
int convexHull(Point *p, int n, Point* ch){
    sort(p, p+n);
    int m = 0;
    for(int i=0;i<n;i++)
    {
        while(m > 1 && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2;i>=0;i--)
    {
        while(m > k && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    if(n) m--;
    return m;
}
bool judge(int s)
{
    int tail = 0;
    for(int i=0;i<n;i++){
        if(s & (1 << i)){
            p1[tail++] = pp[i];
        }
    }
    if(tail != convexHull(p1, tail, pn)) return false;
    Vector tmp = pn[1] - pn[0];
    double rnt = Dot(tmp, tmp);
    double ang = Angle(pn[1] - pn[0], pn[tail-1] - pn[0]);
    for(int i=1;i<tail;i++)
    {
        int nxt = (i+1)%tail;
        tmp = pn[nxt] - pn[i];
        if(dcmp(Dot(tmp, tmp) - rnt) != 0) return false;
    }
    for(int i=1; i < tail;i++)
    {
        int nxt = (i+1)%tail, pre = i-1;
        Vector v = pn[nxt] - pn[i];
        Vector w = pn[pre] - pn[i];
        if(dcmp(ang - Angle(v, w)) != 0) return false;
    }
    return true;
}
int main()
{
    Open();
    while(~scanf("%d", &n))
    {
        for(int i=0;i<n;i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            pp[i] = Point(x, y);
        }
        int limit = 1 << n;
        int ans = 0;
        for(int i = 1;i<limit;i++)
        {
            if(__builtin_popcount(i) <= 6 && __builtin_popcount(i) >= 3) ans += judge(i);
        }
        printf("%d\n", ans);
    }
    return 0;
}
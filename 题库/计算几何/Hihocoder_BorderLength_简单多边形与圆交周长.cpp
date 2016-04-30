/*
* 求出圆与多边形的所有交点，对于圆弧来说，假设这段圆弧在多边形中，那么一定是边界，需要加上
* 对于多边形来说，如果这一线段在圆中，那么也需要加上去。
* 于是就取中点，判断是否在另一图形中，两部分答案加起来即可
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 10100
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
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
struct Point
{
    double x,y;
    double ang;
    Point(double x = 0, double y = 0):x(x),y(y){ang =0;}
    void updateAng(Point c)
    {
        ang = atan2(y - c.y, x - c.x);
    }
    bool operator<(const Point& o)const{
        return ang < o.ang;
    }
}pa[N],pb[N];

typedef Point Vector;
const double eps = 1e-10;
const double PI = acos(-1.0);
int dcmp(double x){if(fabs(x) < eps) return 0;else return x<0?-1:1;}
Vector operator+(Vector A,Vector B){return Vector(A.x+B.x, A.y+B.y);}
Vector operator-(Point A,Point B){return Vector(A.x-B.x, A.y-B.y);}
Vector operator*(Vector A, double p){return Vector(A.x*p, A.y*p);}
Vector operator/(Vector A, double p){return Vector(A.x/p, A.y/p);}
//bool operator<(const Point& a, const Point& b){return a.x<b.x || (a.x == b.x && a.y < b.y);}
bool operator==(const Point& a, const Point& b){return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;}
double angle(Vector A){return atan2(A.y,A.x);}
double Dot(Vector A, Vector B){return A.x*B.x+A.y*B.y;}
double Length(Vector A){return sqrt(Dot(A,A));}
double Angle(Vector A,Vector B){return acos(Dot(A,B)/Length(A)/Length(B));}
double Cross(Vector A, Vector B){return A.x*B.y-A.y*B.x;}
Vector Rotata(Vector A,double rad){return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));}
double torad(double ang){return ang / 180 * PI;}
Vector Normal(Vector A){double L = Length(A); return Vector(-A.y/L, A.x/L);}//需要确保A不是0向量
//bool OnSegment(Point p, Point a1, Point a2){return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;}
bool OnSegment(Point p, Point a, Point b) { return dcmp(Length(p - a) + Length(p - b) - Length(a - b)) == 0; }//精度也很高的！
struct Circle
{
    Point c;
    double r;
    Circle(){}
    Circle(Point c, double r):c(c),r(r){}
    Point point(double a)
    {
        return Point(c.x + cos(a)*r, c.y+sin(a)*r);
    }
}c;
struct Line{
    Point p,v;
    double a,b,c;//得到一般式的参数
    Line(Point p = Point(0,0), Vector v = Vector(0,0)):p(p),v(v){a = v.y - p.y; b = p.x - v.x; c = p.y*v.x - v.y*p.x;}
    Point point(double t){return p + v*t;}//只能在点斜式中用
    bool operator < (const Line& L)const{
        return angle(v) < angle(L.v);
    }
}L[N];
double DistanceToSegment(Point P, Point A, Point B)
{
    if(A==B) return Length(P-A);
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
    else if(dcmp(Dot(v1, v3)) > 0) return Length(Length(v3));
    else return fabs(Cross(v1, v2)) / Length(v1);
}
//判断点是否在多边形（可以是凹多边形）的内部
int isPointInPolygon(Point p, Point* poly, int n)
{
    int wn = 0;
    for(int i = 0; i<n; i++)
    {
        if(OnSegment(p, poly[i], poly[(i+1)%n])) return -1;//边界
        int k = dcmp(Cross(poly[(i+1)%n]-poly[i], p-poly[i]));
        int d1 = dcmp(poly[i].y - p.y);
        int d2 = dcmp(poly[(i+1)%n].y - p.y);
        if(k>0 && d1 <= 0 && d2 > 0) wn++;
        if(k<0 && d2 <= 0 && d1 > 0) wn--;
    }
    if(wn != 0) return 1;//内部
    return 0;//外部
}
double DistanceToLine(Point P, Point A, Point B)
{
    Vector v1 = B-A,v2 = P-A;
    return fabs(Cross(v1,v2)) / Length(v1);
}
//直线与圆相交,直线必须是点斜式
int getLineCircleIntersection(Line L, Circle C, vector<Point >& sol)
{
    double a = L.v.x, b = L.p.x - C.c.x, c = L.v.y, d = L.p.y - C.c.y;
    double e = a*a + c*c, f = 2.0*(a * b + c * d), g = b*b+d*d-C.r*C.r;
    double delta = f*f - 4.0*e*g;
    double dist = DistanceToLine(C.c, L.p, L.p + L.v);
    double t1,t2;
    if(dcmp(dist - C.r) > 0) return 0;
    if(dcmp(dist - C.r) == 0) {
        t1 = t2 = -f / (2*e);
        if(dcmp(t1) >= 0 && dcmp(t1-1) <= 0)sol.push_back(L.point(t1));
        return 1;
    }
    t1 = (-f - sqrt(delta)) / (2.0*e);
    if(dcmp(t1) >= 0 && dcmp(t1-1) <= 0)sol.push_back(L.point(t1));
    t2 = (-f + sqrt(delta)) / (2.0*e);
    if(dcmp(t2) >= 0 && dcmp(t2-1) <= 0)sol.push_back(L.point(t2));
    return 2;
}
double segmentInCircle(Point* p, int n, Circle cir)
{
    int tail = 0;
    for(int i = 0; i < n; i++)
    {
        pb[tail++] = p[i];
        int nxt = i+1;
        if(nxt >= n) nxt -= n;
        vector<Point> sol;sol.clear();
        getLineCircleIntersection(Line(p[i], p[nxt] - p[i]), cir, sol);
        for(int j = 0; j <sol.size(); j++)
            pb[tail++] = sol[j];
    }
    double res = 0;
    for(int i = 0; i < tail; i++)
    {
        int nxt = i+1;
        if(nxt >= tail) nxt -= tail;
        Point mid = (pb[i] + pb[nxt])/2.0;
        if(dcmp(Dot(mid - cir.c, mid - cir.c) - cir.r*cir.r) <= 0){
            res += Length(pb[i] - pb[nxt]);
        }
    }
    return res;
}
double CircleInPolygon(Point* p, int n, Circle cir)
{
    int tail = 0;
    for(int i = 0; i < n; i++)
    {
        int nxt = i+1;
        if(nxt >= n) nxt -= n;
        vector<Point> sol;sol.clear();
        getLineCircleIntersection(Line(p[i], p[nxt] - p[i]), cir, sol);
        for(int j = 0; j <sol.size(); j++)
            pb[tail++] = sol[j];
    }
    if(tail == 0){
        if(isPointInPolygon(cir.point(0), p, n) == 1){
            return 2 * PI * cir.r;
        }
    }
    for(int i = 0; i < tail; i++) pb[i].updateAng(cir.c);
    sort(pb, pb+tail);
    double res = 0;
    for(int i = 0; i < tail; i++)
    {
        int nxt = i+1;
        if(nxt >= tail) nxt -= tail;
        double ang = pb[nxt].ang - pb[i].ang;
        if(dcmp(ang) <= 0) ang += 2 * PI;
        Point mid = cir.c + Rotata(pb[i]-cir.c, ang/2);
        if(isPointInPolygon(mid, p, n) == 1)
            res += ang * cir.r;
    }
    return res;
}
int main()
{
//    Open();
    int n;
    while(scanf("%d", &n), n){
        for(int i = 0 ; i < n; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            pa[i] = Point(x, y);
        }
        int rx, ry, r;
        scanf("%d%d%d", &rx, &ry, &r);
        c = Circle(Point(rx, ry), r);

        double ans = segmentInCircle(pa, n, c) + CircleInPolygon(pa, n, c);
        printf("%.0f\n", ans);
//        printf("%I64d\n", (LL)round(ans));
    }
    return 0;
}
/*
5
0 0
1 1
3 1
4 0
2 -2
2 0 1


4
0 0
2 2
4 0
2 -2
2 0 3

4
0 0
2 2
4 0
2 -2
2 0 1

3
1 1
1 -1
0 0
2 0 3

3
1 1
1 -1
0 0
2 0 1


5
0 1
1 0
2 1
2 -1
0 -1
1 0 1

4
-10 -10
-10 10
10 10
10 -10
-10 -10 20
4
-10 -10
-10 10
10 10
10 -10
-10 -10 4
4
-10 -10
-10 10
10 10
10 -10
0 0 10
4
-40 -40
-40 40
40 40
40 -40
0 0 50

4
-10 -10
-10 10
10 10
10 -10
-10 -10 20
4
-10 -10
-10 10
10 10
10 -10
-10 -10 4
4
-10 -10
-10 10
10 10
10 -10
0 0 10
4
-40 -40
-40 40
40 40
40 -40
0 0 50
0

6.2831853072
11.3137084990
6.2831853072
4.8284271247
0.0000000000
6.7123889804
71.4159265359
14.2831853072
62.8318530718
296.7588218417
71.4159265359
14.2831853072
62.8318530718
296.7588218417

*/

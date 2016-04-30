/*
* 多边形与圆交面积模板中，每次加上去的都是有向面积，这样的话，多的面积会被容斥掉。对于此题来说，要求的是周长
* 由于遍历顺序为多边形的点序，那么多边形上的周长是不可能容斥出去的，而是全部都会被当做正值加到最终答案中。
* 而对于一段圆弧来说，根据遍历顺序是能够将多余的部分减去的，所以这里仍然采用之前的方法--加上有向周长。
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 100010
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
    Point(double x = 0, double y = 0):x(x),y(y){}
}pa[N],pb[N];

typedef Point Vector;
const double eps = 1e-10;
const double PI = acos(-1.0);
int dcmp(double x){if(fabs(x) < eps) return 0;else return x<0?-1:1;}
Vector operator+(Vector A,Vector B){return Vector(A.x+B.x, A.y+B.y);}
Vector operator-(Point A,Point B){return Vector(A.x-B.x, A.y-B.y);}
Vector operator*(Vector A, double p){return Vector(A.x*p, A.y*p);}
Vector operator/(Vector A, double p){return Vector(A.x/p, A.y/p);}
bool operator<(const Point& a, const Point& b){return a.x<b.x || (a.x == b.x && a.y < b.y);}
bool operator==(const Point& a, const Point& b){return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;}
double angle(Vector A){return atan2(A.y,A.x);}
double Dot(Vector A, Vector B){return A.x*B.x+A.y*B.y;}
double Length(Vector A){return sqrt(Dot(A,A));}
double Angle(Vector A,Vector B){return acos(Dot(A,B)/Length(A)/Length(B));}
double Cross(Vector A, Vector B){return A.x*B.y-A.y*B.x;}
Vector Rotata(Vector A,double rad){return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));}
double torad(double ang){return ang / 180 * PI;}
Vector Normal(Vector A){double L = Length(A); return Vector(-A.y/L, A.x/L);}//需要确保A不是0向量
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
};
struct Line{
    Point p,v;
    double a,b,c;//得到一般式的参数
    Line(Point p = Point(0,0), Vector v = Vector(0,0)):p(p),v(v){a = v.y - p.y; b = p.x - v.x; c = p.y*v.x - v.y*p.x;}
    Point point(double t){return p + v*t;}//只能在点斜式中用
    bool operator < (const Line& L)const{
        return angle(v) < angle(L.v);
    }
}L[N];
double DistanceToLine(Point P, Point A, Point B)
{
    Vector v1 = B-A,v2 = P-A;
    return fabs(Cross(v1,v2)) / Length(v1);
}
//直线与圆相交,直线必须是点斜式
int getLineCircleIntersection(Line L, Circle C, vector<Point >& sol)
{
    double a = L.v.x, b = L.p.x - C.c.x, c = L.v.y, d = L.p.y - C.c.y;
    double e = a*a + c*c, f = 2*(a * b + c * d), g = b*b+d*d-C.r*C.r;
    double delta = f*f - 4*e*g;
    double dist = DistanceToLine(C.c, L.p, L.p + L.v);
    double t1,t2;
    if(dcmp(dist - C.r) > 0) return 0;
    if(dcmp(dist - C.r) == 0) {
        t1 = t2 = -f / (2*e);
        if(dcmp(t1)>= 0 && dcmp(1-t1)>=0)sol.push_back(L.point(t1));
        return 1;
    }
    t1 = (-f - sqrt(delta)) / (2*e);
    if(dcmp(t1)>= 0 && dcmp(1-t1)>=0) sol.push_back(L.point(t1));
    t2 = (-f + sqrt(delta)) / (2*e);
    if(dcmp(t2)>= 0 && dcmp(1-t2)>=0) sol.push_back(L.point(t2));
    return 2;
}
struct CPIArea
{
    Circle cir;
    double Scir;

    Point p[N];
    int tail;
    CPIArea() { tail=0; }
    CPIArea(Circle cir):cir(cir) { Scir = PI*cir.r*cir.r; tail=0; }
    //tp[]是多边形的点集，n是点的个数。tp[]必须满足点是按顺时针或者逆时针排序的
    double solve(Point tp[],int n)
    {
		tail = 0;
        for(int i=0; i<n; i++)
        {
            p[tail++]=tp[i];//p[]是囊括了圆和多边形交点的点集，也是按顺时针或者逆时针排序的
            Line line = Line(tp[i],tp[(i+1)%n] - tp[i]);
            vector<Point > sol;
            sol.clear();
            getLineCircleIntersection(line, cir, sol);

            for(int j=0; j<sol.size(); j++)
            {
                p[tail++]=sol[j];
            }
        }
        double Cirres = 0;
        double polyres = 0;
        for(int i=0; i<tail; i++)
        {
            Point O = cir.c;
            if(dcmp(Cross( p[i]-O , p[(i+1)%tail]-O)) == 0)
            {
                Point mid = (p[i]+p[(i+1)%tail])/2;
                if(dcmp(Length(mid - O) - cir.r) < 0){
                    polyres += Length(p[i] - p[(i+1)%tail]);
                }
                continue;
            }
            double ang = Angle(p[(i+1)%tail]-O , p[i]-O);
            if( dcmp(Cross( p[i]-O , p[(i+1)%tail]-O)) > 0 ) ang*=1;
            else ang*=-1;
            double Sshan = ang/(2*PI)*Scir;
            double Strian = Cross(p[i] - O, p[(i+1)%tail] - O) * 0.5;
            //Area(O , p[i] ,p[(i+1)%tail] );
            if(dcmp( abs(Sshan) - abs(Strian)) <=0  )
            {
                Cirres += ang * cir.r;
            }
            else polyres += abs(Length(p[i] - p[(i+1)%tail]));
        }
        return abs(Cirres) + polyres;
    }
};
int main()
{
    //Open();
    int n;
    while(scanf("%d", &n), n){
        for(int i = 0 ; i < n; i++)
        {
            scanf("%lf%lf", &pa[i].x, &pa[i].y);
        }
        double rx, ry, r;
        scanf("%lf%lf%lf", &rx, &ry, &r);
        Circle c(Point(rx, ry), r);
        CPIArea solver(c);
        double ans = solver.solve(pa, n);
        printf("%.0f\n", ans);
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

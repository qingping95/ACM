
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <assert.h>
//#include <unordered_map>
#define N 3030
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
const double eps = 1e-8;
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

struct Poly
{
    Point p[N];
    int num;
    Poly(){}
    Poly(int _n){num = _n;}
    double Len()
    {
        double res = 0;
        for(int i = 0; i < num; i++)
        {
            int nxt = i + 1;
            if(nxt == num)nxt = 0;
            res += Length(p[nxt] - p[i]);
        }
        return res;
    }
};
vector<Poly> allP;
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
    double Len()
    {
        return 2 * PI * r;
    }
}Cir[N];
struct Line
{
    Point p;
    Vector v;
    double ang;
    Line(){}
    Line(Point p, Vector v):p(p), v(v){ang = atan2(v.y, v.x);}
    Line(double a, double b, double c)
    {
        v = Vector(b, -a);
        if(b != 0) p = Point(0, -c/b);
        else p = Point(-c/a, 0);
        Vector nor = Normal(v);
        Point tmp = nor + p;
        if(dcmp(a * tmp.x + b * tmp.y + c) > 0){
            v = v*-1;
        }
        ang = atan2(v.y, v.x);
    }
    Point point(double t){return p + v*t;}//只能在点斜式中用
    bool operator<(const Line &o)const{
        return ang < o.ang;
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
#define D(x) ((x)*(x))
struct CPIArea
{
    Circle cir;
    double Scir;
    Point p[N];
    int tail;
    CPIArea() { tail=0; }
    CPIArea(Circle cir):cir(cir) { Scir = PI*cir.r*cir.r; tail=0; }
    //tp[]是多边形的点集，n是点的个数。tp[]必须满足点是按顺时针或者逆时针排序的
    double solvePoly(Point tp[],int n)
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
        double polyres = 0;
        for(int i=0; i<tail; i++)
        {
            Point O = cir.c;
            Point mid = (p[i]+p[(i+1)%tail])/2;
            if(dcmp(Length(mid - O) - cir.r) < 0){
                polyres += Length(p[i] - p[(i+1)%tail]);
            }
        }
        return polyres;
    }
    double solveCircle(Circle tc)
    {
        double d = Length(tc.c - cir.c), r1 = tc.r, r2 = cir.r;
        if(dcmp(d - r1 - r2) >= 0) return 0;
        if(tc.c == cir.c){
            if(dcmp(r2 - r1) >= 0) return 2 * PI * tc.r;
            return 0;
        }
        if(dcmp(r2 - d - r1) >= 0) return 2 * PI * r1;
        if(dcmp(r1 - d - r1) >= 0) return 0;
        double w = (D(r1)+D(d)-D(r2)) / (2.0 * r1 * d);
        w = min(w, 1.0);
        double ang = acos(w);
        return 2 * ang * r1;
    }
};
int ctail;
double cx, cy;
double calc(double r)
{
    CPIArea fuck(Circle(Point(cx, cy), r));
    double res = 0;
    for(int i = 0; i < ctail; i++)
    {
        res += fuck.solveCircle(Cir[i]);
    }
    for(int i = 0; i < allP.size(); i++)
    {
        res += fuck.solvePoly(allP[i].p, allP[i].num);
    }
    return res;
}
int main()
{
    int T;scanf("%d", &T);
    int cas = 1;
    while(T--)
    {
        int n;
        double len;
        scanf("%d%lf", &n, &len);
        allP.clear();
        double alllen = 0;
        char ty[3];
        ctail = 0;
        for(int i = 0; i < n; i++){
            scanf("%s", ty);
            if(ty[0] == 'C'){
                double x, y, r;
                scanf("%lf%lf%lf", &x, &y, &r);
                Cir[ctail++] = Circle(Point(x, y), r);
                alllen += Cir[ctail-1].Len();
            }else{
                int np;
                scanf("%d", &np);
                int id = allP.size();
                allP.push_back(Poly(np));
                for(int j = 0; j < np; j++)
                {
                    double x, y;
                    scanf("%lf%lf", &x, &y);
                    allP[id].p[j] = Point(x, y);
                }
                alllen += allP[id].Len();
            }
        }
        printf("Case #%d: ", cas++);
        scanf("%lf%lf", &cx, &cy);
        if(dcmp(len - alllen) == 0) {
            printf("inestimable\n");
            continue;
        }
        double lb = 0, ub = 100000;
        double ans = -1;
        int cnt = 100;//浮点二分一定要用次数控制！100次，
        while(cnt--)
        {
            double mid = (lb + ub) / 2;
            double res = calc( mid);
            if(dcmp(res - len) > 0) ub = mid;
            else if(dcmp(res - len) == 0) lb = ans = mid;//这里答案如果为一个区间的话，这里需要特别注意
            else lb = mid;
        }
        if(ans == -1){
            printf("impossible\n");
            continue;
        }
        printf("%.2f\n", ans);
    }
    return 0;
}

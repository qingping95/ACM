#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 1110
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
const double eps = 1e-12;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
struct Point
{
    double x, y;
    Point(){}
    Point(double x, double y):x(x), y(y){}
}pn[N], pa[N];
typedef Point Vector;
int dcmp(double x) {
    if(x < -eps) return -1;
    return x > eps;
}
Vector operator+(Vector A,Vector B){return Vector(A.x+B.x, A.y+B.y);}
Vector operator-(Point A,Point B){return Vector(A.x-B.x, A.y-B.y);}
Vector operator*(Vector A, double p){return Vector(A.x*p, A.y*p);}
Vector operator/(Vector A, double p){return Vector(A.x/p, A.y/p);}
bool operator<(const Point& a, const Point& b){return a.x<b.x || (a.x == b.x && a.y < b.y);}
bool operator==(const Point& a, const Point& b){return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;}

double Dot(Vector A, Vector B){return A.x*B.x+A.y*B.y;}
double Length(Vector A){return sqrt(Dot(A,A));}
double Cross(Vector A, Vector B){return A.x*B.y-A.y*B.x;}
Vector Normal(Vector A){double L = Length(A); return Vector(-A.y/L, A.x/L);}//需要确保A不是0向量
struct Line
{
    Point P;
    Vector v;
    double ang;
    Line(){}
    Line(Point P, Vector v):P(P), v(v){ang = atan2(v.y, v.x);}
    Line(double a, double b, double c)
    {
        v = Vector(b, -a);
        if(b != 0) P = Point(0, -c/b);
        else P = Point(-c/a, 0);
        ang = atan2(v.y, v.x);
    }
    void changeV(Point a) //将方向向量改变方向使得点a在方向向量的左边
    {
        if(dcmp(Cross(v, a - P)) < 0){
            v = v * -1;
        }
    }
    bool operator<(const Line &o)const{
        return ang < o.ang;
    }
}L[N];
bool OnLeft(Line L, Point P)
{
    return dcmp(Cross(L.v, P - L.P)) > 0;
}
Point GetIntersection(Line a, Line b)
{
    Vector u = a.P - b.P;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.P + a.v*t;
}
double DistanceToLine(Point P, Point A, Point B)
{
    Vector v1 = B-A, v2 = P - A;
    return fabs(Cross(v1, v2)) / Length(v1);
}
int HalfPlaneIntersection(Line* L, int n, Point* poly)
{
    sort(L, L+n);
    int first, last;
    Point *p = new Point[n];
    Line *q = new Line[n];
    q[first = last = 0] = L[0];
    for(int i = 1; i < n ;i++)
    {
        while(first < last && !OnLeft(L[i], p[last - 1])) last--;
        while(first < last && !OnLeft(L[i], p[first])) first++;
        q[++last] = L[i];
        if(fabs(Cross(q[last].v, q[last-1].v)) < eps){
            last--;
            if(OnLeft(q[last], L[i].P)) q[last] = L[i];
        }
        if(first < last) p[last - 1] = GetIntersection(q[last - 1], q[last]);
    }
    while(first < last && !OnLeft(q[first], p[last - 1])) last -- ;
    if(last - first <= 1) return 0;
    p[last] = GetIntersection(q[last], q[first]);
    int m = 0;
    for(int i = first; i <= last; i++) poly[m++] = p[i];
    return m;
}
double PolygonArea(Point* p, int n)
{
    double res = 0;
    for(int i = 1; i < n-1; i++)
        res += Cross(p[i] - p[0], p[i+1] - p[0]);
    return fabs(res/2);
}
double f(Point a)
{
    return 2 - a.x - a.y;
}
int main()
{
//    Open();
    int T;scanf("%I64d", &T);
    int cas = 1;
    while(T--)
    {
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
        {
            double x, y;
            scanf("%lf%lf",&x, &y);
            pn[i] = Point(x, y);
        }
        printf("Case #%d:\n", cas++);
        if(n == 1){
            printf("1.000000\n");
            continue;
        }
        for(int i = 0; i < n; i++)
        {
            double res = 0;
            int tail = 0;
            L[tail++] = Line(Point(0, 0), Vector(1, 0));
            L[tail++] = Line(Point(1, 0), Vector(0, 1));
            L[tail++] = Line(Point(1, 1), Vector(-1, 0));
            L[tail++] = Line(Point(0, 1), Vector(0, -1));
            for(int j = 0; j < n; j++)
            {
                if(i == j) continue;
                L[tail++] = Line((pn[i] + pn[j])/2, Normal(pn[j] - pn[i]));
            }
            for(int j = 0; j < tail; j++) L[j].changeV(pn[i]);
            int num = HalfPlaneIntersection(L, tail, pa);
            double H = INF; int idx;
            for(int j = 0; j < num; j++)
            {
                if(dcmp(f(pa[j]) - H) < 0){
                    H = f(pa[j]);
                    idx = j;
                }
            }
            res += PolygonArea(pa, num) * H;
            for(int j = idx + 1; ; j++){
                j %= num;
                int nxt = (j + 1)%num;
                if(nxt == idx) break;
                double h1 = f(pa[j]) - H, h2 = f(pa[nxt]) - H;
                double S = Length(pa[j] - pa[nxt]) * (h1 + h2) / 2;
                res += DistanceToLine(pa[idx], pa[j], pa[nxt])* S /3;
            }
            printf("%.6f\n", res);
        }
    }
    return 0;
}

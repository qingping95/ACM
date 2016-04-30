#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 111
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
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
    double x, y;
    Point(){}
    Point(double x, double y):x(x), y(y){}
}pn[N*N];
typedef Point Vector;
LL dcmp(double x) {
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
struct line
{
    Point P;
    Vector v;
    double ang;
    line(){}
    line(Point P, Vector v):P(P), v(v){ang = atan2(v.y, v.x);}
    line(double a, double b, double c)
    {
        v = Vector(b, -a);
        if(b != 0) P = Point(0, -c/b);
        else P = Point(-c/a, 0);
        Vector nor = Normal(v);
        Point tmp = nor + P;
        if(dcmp(a * tmp.x + b * tmp.y + c) > 0){
            v = v*-1;
        }
        ang = atan2(v.y, v.x);
    }
    bool operator<(const line &o)const{
        return ang < o.ang;
    }
}L[111];
bool OnLeft(line L, Point P)
{
    return Cross(L.v, P - L.P) > 0;
}
Point GetIntersection(line a, line b)
{
    Vector u = a.P - b.P;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.P + a.v*t;
}
LL HalfPlaneIntersection(line* L, LL n, Point* poly)
{
    sort(L, L+n);
    LL first, last;
    Point *p = new Point[n];
    line *q = new line[n];
    q[first = last = 0] = L[0];
    for(LL i = 1; i < n ;i++)
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
    LL m = 0;
    for(LL i = first; i <= last; i++) poly[m++] = p[i];
    return m;
}
double PolygonArea(Point* p, LL n)
{
    double res = 0;
    for(LL i = 1; i < n-1; i++)
        res += Cross(p[i] - p[0], p[i+1] - p[0]);
    return res/2;
}
LL X[111], Y[111];
LL X2[111], Y2[111];
int main()
{
    Open();
    LL T;scanf("%I64d", &T);
    LL cas = 1;
    while(T--)
    {
        LL n, m;
        scanf("%I64d%I64d", &n, &m);
        memset(X, 0, sizeof(X));
        memset(Y, 0, sizeof(Y));
        memset(X2, 0, sizeof(X2));
        memset(Y2, 0, sizeof(Y2));
        for(LL i = 1; i <= n; i++){
            for(LL j = 1 ;j <= m; j++){
                LL x, y;
                scanf("%I64d%I64d", &x, &y);
                X2[i] += x * x;
                Y2[i] += y * y;
                X[i] += x;
                Y[i] += y;
            }
        }
        printf("Case #%I64d:", cas++);
        for(LL i = 1; i <= n; i++){
            L[0] = line(Point(0, 0), Vector(4095, 0));
            L[1] = line(Point(0, 0), Vector(0, -4095));
            L[2] = line(Point(4095, 0), Vector(0, 4095));
            L[3] = line(Point(0, 4095), Vector(-4095, 0));
            LL tail = 4;
            for(LL j = 1; j <= n; j++){
                if(i == j) continue;
                LL a = 2 * (X[j] - X[i]);
                LL b = 2 * (Y[j] - Y[i]);
                LL c = X2[i] - X2[j] + Y2[i] - Y2[j];
                L[tail++] = line(a, b, c);
            }
            LL cnt = HalfPlaneIntersection(L, tail, pn);
            printf(" %.0f", PolygonArea(pn, cnt) + eps);
        }
        cout<<endl;
    }
    return 0;
}

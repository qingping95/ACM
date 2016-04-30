#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <assert.h>
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
typedef pair<LL,LL> PII;
typedef pair<double, double> PDD;
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
//        freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
struct Point
{
    double x,y;
    Point(double x = 0, double y = 0):x(x),y(y){}
    void read()
    {
        scanf("%lf%lf", &x, &y);
    }
}pa[N],pb[N];
const double eps = 1e-10;
const double PI = acos(-1.0);
typedef Point Vector;
int dcmp(double x){if(fabs(x) < eps) return 0;else return x<0?-1:1;}
Vector operator+(Vector A,Vector B){return Vector(A.x+B.x, A.y+B.y);}
Vector operator-(Point A,Point B){return Vector(A.x-B.x, A.y-B.y);}
Vector operator*(Vector A, double p){return Vector(A.x*p, A.y*p);}
Vector operator/(Vector A, double p){return Vector(A.x/p, A.y/p);}
bool operator<(const Point& a, const Point& b){return a.x<b.x || (a.x == b.x && a.y < b.y);}
bool operator==(const Point& a, const Point& b){return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;}
double angle(Vector A){return atan2(A.y,A.x);}//返回A向量的极角
double Dot(Vector A, Vector B){return A.x*B.x+A.y*B.y;}
double Length(Vector A){return sqrt(Dot(A,A));}
double Angle(Vector A,Vector B)
{
    double d=Dot(A,B)/Length(A)/Length(B);
    if(dcmp(d-1)==0) return 0;
    if(dcmp(d+1)==0) return PI;
    return acos(d);
}//A到B的逆时针转的角
double Cross(Vector A, Vector B){return A.x*B.y-A.y*B.x;}
Vector Rotata(Vector A,double rad){return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));}//A逆时针转ang弧度
double torad(double ang){return ang / 180 * PI;}
Vector Normal(Vector A){double L = Length(A); return Vector(-A.y/L, A.x/L);}//需要确保A不是0向量，左转90度
//非规范相交，端点上视为在线段上
bool OnSegment(Point p, Point a, Point b) { return dcmp(Length(p - a) + Length(p - b) - Length(a - b)) == 0; }//精度也很高的！

Point MassCenter(Point a[] , int n){
    Point ans = Point(0,0);
    double area = 0;
    a[n] = a[0];
    for(int i=0;i<n;i++) ans = ans+(a[i] + a[i+1])*Cross(a[i] , a[i+1]), area += Cross(a[i], a[i+1]);
    if(dcmp(area) == 0) return Point(0, 0);
    return ans / (area * 3.0);
}
Point O, S;
double solve(Point st, double len, double UP)
{
    double oldl = Length(S - st);
    double lb = 0, ub = UP, ans = 0;
    int cnt = 50;
    while(cnt--)
    {
        double mid = (lb + ub) * 0.5;
        double newl = Length(S - (Rotata(st - O, -mid) + O));
        if(dcmp(newl - oldl - len) >= 0) ub = mid;
        else lb = mid;
    }
    return (ub+lb)*0.5;
}
double solve2(double a, double b, double c)
{
    double delta = b*b - 4.0 * a * c;
    return (-b + sqrt(delta)) / (2.0 * a);
}
Point getP(Point p, Vector v, Point C, double r)
{
    double a = v.x, b = p.x - C.x, c = v.y, d = p.y - C.y;
    double e = a*a + c*c, f = 2*(a*b+c*d), g = b*b+d*d-r*r;
    double delta = f*f - 4*e*g;
    return p + v * (-f + sqrt(delta)) / (2*e);
}
struct info{
    double len, ang;
    Point cur;
}preinfo[N];
int getid(int UP, double l)
{
    int lb = -1, ub = UP;
    while(lb + 1 < ub)
    {
        int mid = (ub + lb) >> 1;
        if(dcmp(l - preinfo[mid].len) == 0) return mid;
        if(mid+1 < UP &&dcmp(l - preinfo[mid].len)*dcmp(l - preinfo[mid+1].len) < 0) return mid;
        if(dcmp(l - preinfo[mid].len) > 0) lb = mid;
        else ub = mid;
    }
    return ub + lb >> 1;
}
int main()
{
    Open();
//    cout<<cos(111)<<endl;
    int T;scanf("%d", &T);
    int cas = 1;
    while(T--)
    {
        printf("Case #%d:\n", cas++);
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
            pa[i].read();
        pa[n] = pa[0];
        double sx, sy;
        scanf("%lf%lf", &sx, &sy);
        S = Point(sx, sy);
        O = MassCenter(pa, n);
        double a = Length(S - O);
        double alllen = 0;
        for(int i = 0; i < n; i++)
            alllen += Length(pa[i] - pa[(i+1)%n]);
        int st;
        double ang = -INF;
        for(int i = 0; i < n; i++)
        {
            if(dcmp(angle(pa[i] - S) - ang) > 0){
                ang = angle(pa[i] - S);
                st = i;
            }
        }
        Point las = S, cur;
        preinfo[0].cur = S;
        for(int i = st, k = 0; k < n; k++)
        {
            int id = (i + k) % n;
            cur = getP(pa[id], pa[id+1] - pa[id], O, a);
            preinfo[k+1].len = preinfo[k].len + Length(cur - pa[id]) - Length(las - pa[id]);
            preinfo[k+1].ang = preinfo[k].ang + Angle(las - O, cur - O);
            preinfo[k+1].cur = cur;
            las = cur;
        }
        int m;
        scanf("%d", &m);
        while(m--)
        {
            double l;
            double ans = 0;
            scanf("%lf", &l);
            LL num = floor(l / alllen) + eps;
            l -= num * alllen;
            ans += 360LL * num;
            double tmpans = 0;
            if(dcmp(l)>0)
            {
                int idx = getid(n+1, l);
//                int idx = lower_bound(preinfo, preinfo+tail, PDD(l, -INF)) - preinfo - 1;
                tmpans = preinfo[idx].ang;
                cur = preinfo[idx].cur;
                l -= preinfo[idx].len;
                if(dcmp(l) > 0){
                    idx = (st+idx)%n;
                    double OP = Length(O - pa[idx]);
                    l += Length(pa[idx]-cur);
                    ang = (OP*OP + a*a - l*l)/(2.0*OP*a);
                    ang = max(-1.0, min(ang, 1.0));
                    ang = acos(ang);
                    ang -= abs(Angle(pa[idx] - O, cur - O));
                    tmpans += ang;
                }
            }
            printf("%.3f\n", ans + (tmpans) / PI * 180);
        }
    }
    return 0;
}

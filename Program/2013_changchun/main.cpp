#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 1010
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const double INF=1e20;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
struct Point
{
    double x, y;
    Point(double x = 0, double y = 0):x(x), y(y){}
    void read()
    {
        scanf("%lf%lf", &x, &y);
    }
}pa[N], pb[N];
const double eps = 1e-8;
const double PI = acos(-1.0);
typedef Point Vector;
int dcmp(double x){return (x > eps) - (x < -eps);}
Vector operator+(Vector A, Vector B) {return Vector(A.x+B.x, A.y+B.y);}
Vector operator-(Vector A, Vector B) {return Vector(A.x-B.x, A.y-B.y);}
Vector operator*(Vector A, double p) {return Vector(A.x*p, A.y*p);}
Vector operator/(Vector A, double p) {return Vector(A.x/p, A.y/p);}
bool operator<(const Point& a, const Point& b){return a.x < b.x || (a.x == b.x && a.y < b.y);}
bool operator==(const Point& a, const Point& b){return dcmp(a.x - b.x) == 0 && dcmp(a.y-b.y) == 0;}
double angle(Vector A){return atan2(A.y, A.x);}
double Dot(Vector A, Vector B){return A.x*B.x+A.y*B.y;}
double Length(Vector A){return sqrt(Dot(A,A));}
double Cross(Vector A, Vector B){return A.x*B.y-A.y*B.x;}
double NormalAng(double x)//将弧度x通过+-2*PI的方式约束到[-PI,PI];
{
    if(x > 0){
        while(x > PI) x -= 2.0 * PI;
    }else{
        while(x < -PI) x += 2.0 * PI;
    }
    return x;
}
struct Circle{
    double r;
    double low, up;
    bool use;
    Point c;
    Circle(){}
    Circle(Point c, double r):c(c), r(r){
        use = true;
        low = -INF, up = INF;
    }
    Point point(double a)
    {
        return Point(c.x + cos(a)*r, c.y + sin(a)*r);
    }
}c[N];
int getCCInter(Circle C1, Circle C2, double& low, double& up)
{
    double d = Length(C1.c - C2.c);
    if(dcmp(d) == 0)
    {
        if(dcmp(C1.r - C2.r) == 0) return -1;
        return 0;
    }
    if(dcmp(C1.r+C2.r-d) < 0) return -2;
    if(dcmp(fabs(C1.r - C2.r) - d) > 0) return 0;
    double a = angle(C2.c - C1.c);
    double da = acos((C1.r*C1.r + d*d - C2.r*C2.r) / (2*C1.r*d));
    low = NormalAng(a - da), up = NormalAng(a + da);
//    if(up + eps < low) up += 2*PI;
    return 2;
}
int Conv(Point* p, int n, Point *ch)
{
    sort(p, p+n);
    n = unique(p, p+n) - p;
    int m = 0;
    for(int i = 0; i < n; i++)
    {
        while(m > 1 && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2; i >=0; i--)
    {
        while(m > k && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    if(n > 1) m--;
    return m;
}
bool change(double& low, double& up, double cl, double cu)
{
    if(dcmp(up - INF) == 0 || dcmp(low + INF) == 0){
        up = min(up, cu), low = max(low, cl);
        return true;
    }
    if(dcmp(up - low) > 0){
        if(dcmp(cu - cl) > 0){
            up = min(up, cu);
            low = max(low, cl);
            if(dcmp(up - low) < 0) return false;
            return true;
        }else{
            if(dcmp(up - cl) > 0){
                low = max(cl, low);
                return true;
            }
            if(dcmp(cu - low) > 0){
                up = min(up, cu);
                return true;
            }
        }
    }else{
        if(dcmp(cu - cl) > 0){
            if(dcmp(cu - low) > 0){
                low = max(low, cl);
                up = cu;
                return true;
            }
            if(dcmp(up - cl) > 0){
                low = cl;
                up = min(up, cu);
                return true;
            }
        }else{
            low = max(low, cl);
            up = min(up, cu);
            return true;
        }
    }
    return false;
}
int main()
{
//    cout<<dcmp(111)<<endl;
//    cout<<dcmp(eps)<<endl;
//    cout<<dcmp(eps/2)<<endl;
//    cout<<dcmp(-111)<<endl;
    Open();
    double sx, sy, d;
    while(~scanf("%lf%lf%lf", &sx, &sy, &d))
    {
        Point O(sx, sy);
        int n;
        scanf("%d", &n);
        for(int i = 0 ; i < n; i++){
            pa[i].read();
            pb[i] = pa[i];
        }
        sort(pb, pb+n);
        n = unique(pb, pb+n) - pb;
//        n = Conv(pa, n, pb);
        for(int i = 0; i < n; i++)
        {
            c[i] = Circle(pb[i], d);
        }
        bool isac = true;
        for(int i = 0; i < n && isac; i++)
        {
            for(int j = 0; j < n && isac && c[i].use; j++)
            {
                if(i == j) continue;
                double cl, cu;
                int res = getCCInter(c[i], c[j], cl, cu);
                if(res == -2) {isac = false;continue;}
                if(res != 2) while(1);
                c[i].use = change(c[i].low, c[i].up, cl, cu);
//                c[i].low = max(c[i].low, cl);
//                c[i].up = min(c[i].up, cu);
            }
        }
        if(!isac)
        {
            printf("X\n");
            continue;
        }
        for(int i = 0; i < n && isac; i++)
        {
            isac = (dcmp(Length(O - pb[i]) - d) <= 0);
        }
        if(isac)
        {
            printf("0.00\n");
            continue;
        }
        double ans = INF;
        double ang;
        Point a, b;
        for(int i = 0; i < n; i++)
        {
            if(c[i].use == false) continue;
//            if(dcmp(c[i].low - c[i].up) > 0) continue;
            if(dcmp(c[i].low + INF) == 0 || dcmp(c[i].up - INF) == 0) continue;
//            if(dcmp(Length(c[i].c - O) - c[i].r) < 0) continue;
            ans = min(ans, Length(O - c[i].point(c[i].low)));
            ans = min(ans, Length(O - c[i].point(c[i].up)));
            ang = angle(O - c[i].c);
            if(dcmp(Length(O - c[i].c)-c[i].r) < 0) continue;
            if(dcmp(c[i].up - c[i].low) > 0){
                if(dcmp(c[i].up - ang) > 0 && dcmp(ang - c[i].low) > 0)
                    ans = min(ans, Length(O - c[i].c)-c[i].r);
            }else{
                if(dcmp(c[i].up - ang) > 0 || dcmp(ang - c[i].low) > 0)
                    ans = min(ans, Length(O - c[i].c)-c[i].r);
            }
        }
        if(ans + eps >= 1e15){
            printf("X\n");
        }else
            printf("%.2f\n", ans);
    }
    return 0;
}


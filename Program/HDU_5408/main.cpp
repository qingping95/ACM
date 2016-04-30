#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <assert.h>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 200010
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
    int id;
    Point(double x = 0, double y = 0):x(x),y(y){}
}pa[N],pk[N], ch[N];
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
double Angle(Vector A,Vector B){return acos(Dot(A,B)/Length(A)/Length(B));}
double Cross(Vector A, Vector B){return A.x*B.y-A.y*B.x;}
Vector Rotata(Vector A,double rad){return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));}
double torad(double ang){return ang / 180 * PI;}
Vector Normal(Vector A){double L = Length(A); return Vector(-A.y/L, A.x/L);}//需要确保A不是0向量
//非规范相交，端点上视为在线段上
bool OnSegment(Point p, Point a, Point b) { return dcmp(Length(p - a) + Length(p - b) - Length(a - b)) == 0; }//精度也很高的！

int Convex(Point *p, int n, Point *ch)
{
    sort(p, p+n);
    int m = 0;
    for(int i = 0; i < n; i++) {
        while(m > 1 && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-1; i >= 0; i --) {
        while(m > k && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    if(n > 1) m--;
    return m;
}
bool isPointInConvexPolygon(Point p, Point* poly, int n)
{
    for(int i=0;i<n;i++)
        if(dcmp(Cross(poly[(i+1)%n] - poly[i], p - poly[i])) <= 0) return 0;
    return 1;
}
double sta[N];
int ans[N*2];
int main()
{
//    Open();
    int T;scanf("%d", &T);
    while(T--)
    {
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
        {
            double x, y;scanf("%lf%lf", &x, &y); pa[i] = Point(x, y);
            pa[i].id = i;
        }
        int m;
        scanf("%d", &m);
        for(int i = 0; i < m; i++)
        {
            double x, y;scanf("%lf%lf", &x, &y); pk[i] = Point(x, y);
        }
        m = Convex(pk, m, ch);
        double ang = Angle(ch[2] - ch[1], ch[0] - ch[1]) / 2;
        Point O = ch[1] + Rotata(ch[2] - ch[1], ang) * 0.5;
//        assert(isPointInConvexPolygon(O, ch, m));
        int tail = 0;
        for(int i = 0; i < m; i++)
        {
            sta[tail++] = angle(ch[i] - O);
        }
        int anst = 0;
        sort(sta, sta+tail);
        for(int i = 0; i < n; i++)
        {
            int nxt = (i+1)%n;
            double ast = angle(pa[i] - O), aed = angle(pa[nxt] - O);
            if(dcmp(aed - ast) > 0)
            {
                int idx = lower_bound(sta, sta+tail, ast-eps) - sta;
                if(dcmp(aed - sta[idx]) >= 0){
                    ans[anst++] = pa[i].id;
                    ans[anst++] = pa[nxt].id;
                }
            }else{
                int idx1 = lower_bound(sta, sta+tail, ast-eps) - sta;
                int idx2 = upper_bound(sta, sta+tail, aed+eps) - sta;
                if(idx1 != tail || idx2 > 0){
                    ans[anst++] = pa[i].id;
                    ans[anst++] = pa[nxt].id;
                }
            }
        }
        sort(ans, ans+anst);
        anst = unique(ans, ans+anst) - ans;
        if(anst < 3){
            printf("No\n");
        }else{
            printf("Yes\n%d\n", anst);
            for(int i = 0; i < anst; i++)
                printf("%d%c", ans[i]+1, " \n"[i == anst-1]);
        }
    }
    return 0;
}

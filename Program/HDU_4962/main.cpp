#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 10010
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<double,int> PDI;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int useless[N];
PDI sta[N];
int tail;
struct Point
{
    double x,y;
    Point(double x = 0, double y = 0):x(x),y(y){}
}pa[N],pb[N];
const double eps = 1e-10;
const double PI = acos(-1.0);
const int offset = 2000;
typedef Point Vector;
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
void getIntersection(Point a, Point b)
{
    if(dcmp(a.y) == 0 && dcmp(b.y) == 0){
        int st = a.x + offset + 0.1, ed = b.x + 0.1 + offset;
        useless[st] = 1, useless[ed] = -1;
        return ;
    }
    if(dcmp(b.y) == 0){
        int mul = 1;
        if(dcmp(a.y) < 0) mul = -1;
        sta[tail++] = PDI(b.x, mul);
        return;
    }
    if(dcmp(a.y) == 0) {
        int mul = 1;
        if(dcmp(b.y) > 0) mul = -1;
        if(tail && sta[tail-1].second == mul) mul = 0;
        sta[tail++] = PDI(a.x, mul);
        return ;
    }
    if(dcmp(a.y) * dcmp(b.y) < 0)
    {
        int mul = 1;
        if(dcmp(a.y) < 0) mul = -1;
        Vector v = b - a;
        double curx = a.x - v.x*a.y/v.y;
        sta[tail++] = PDI(curx, mul);
        return ;
    }
}
int main()
{
//    Open();
    int T;scanf("%d", &T);
    while(T--)
    {
        memset(useless, 0, sizeof(useless));
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
        {
            double x, y;
            scanf("%lf%lf", &x, &y);
            pa[i] = Point(x, y);
        }
        tail = 0;
        for(int i = 0; i < n; i++)
        {
            int nxt = i + 1;
            nxt %= n;
            getIntersection(pa[i], pa[nxt]);
        }
        if(dcmp(pa[1].y) != 0 && dcmp(pa[0].y) == 0 && sta[0].second == sta[tail-1].second) sta[0].second = 0;
        for(int i = 1; i < offset + 1111; i++)
            useless[i] += useless[i-1];
        int ans = 0;
        sort(sta, sta+tail);
        int pre = 0;
        for(int i = 0; i < tail - 1; i++)
        {
            pre += sta[i].second;
            if(dcmp(sta[i+1].first - sta[i].first) == 0) continue;
            int id = (int)floor(sta[i].first + eps + offset);
            if(useless[id]) continue;
            ans = max(ans, pre);
        }
        printf("%d\n", ans);
    }
    return 0;
}

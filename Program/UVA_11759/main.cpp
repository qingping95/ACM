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
const int INF=0x3f3f3f3f;
const double eps = 1e-12;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("E:/in.txt","r",stdin);
        //freopen("E:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
struct Point {
    double x, y;
    Point(){}
    Point(double _x, double _y){
        x = _x, y = _y;
    }
    void input()
    {
        scanf("%lf%lf", &x,&y);
    }
};
typedef Point Vector;
int dcmp(double x){
    return x < -eps ? -1 : x > eps;
}
Vector operator+(Vector A,Vector B){return Vector(A.x+B.x, A.y+B.y);}
Vector operator-(Point A,Point B){return Vector(A.x-B.x, A.y-B.y);}
Vector operator*(Vector A, double p){return Vector(A.x*p, A.y*p);}
Vector operator/(Vector A, double p){return Vector(A.x/p, A.y/p);}
bool operator<(const Point& a, const Point& b){return a.x<b.x || (a.x == b.x && a.y < b.y);}
bool operator==(const Point& a, const Point& b){return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;}
double Dot(Point A, Point B){return A.x*B.x+A.y*B.y;}
double Length(Vector A){return sqrt(Dot(A, A));}
double Cross(Point A, Point B){return A.x*B.y-A.y*B.x;}
struct Poly{
    Point p[N];
    int num;
    Poly(){}
    void input()
    {
        scanf("%d", &num);
        for(int i = 0; i < num; i++)
            p[i].input();
    }
    bool isInPoly(Point a)
    {
        for(int i = 0; i < num; i++)
            if(dcmp(Cross(p[(i+1)%num] - p[i], a - p[i])) <= 0) return 0;
        return 1;
    }
    double len()
    {
        double res = 0;
        for(int i = 0; i < num; i++)
        {
            res += Length(p[(i+1)%num] - p[i]);
        }
        return res;
    }
}poly[N];
double ans[2];
int main()
{
//    Open();
    int n;
    int cas = 1;
    while(~scanf("%d", &n), n)
    {
        ans[0] = ans[1] = 0;
        for(int i = 0; i < n; i++)
        {
            poly[i].input();
        }
        int comnum = 0;
        for(int i = 0; i < n; i++)
        {
            int res = 0;
            for(int j = 0; j < n; j++)
            {
                if(i == j) continue;
                res += poly[j].isInPoly(poly[i].p[0]);
            }
            comnum += (res == 0);
            ans[res & 1] += poly[i].len();
        }
        ans[0] *= 0.0001;
        ans[1] *= 0.00005;
        printf("Case %d:\n", cas++);
        printf("Total Number of Communities %d\n", comnum);
        printf("Total Cost:\n");
        printf("Steel Fence: %.8f Million Yuan\n", ans[0]);
        printf("Wooden Fence: %.8f Million Yuan\n\n", ans[1]);
    }
    return 0;
}

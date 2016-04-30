/*
* Problem Description
* Coach Zhang has an infinite ranch with N alpacas on it. The alpacas are so lazy that they never move. The i-th (1≤i≤N) alpaca is located at the point (Xi,Yi).
* Coach Zhang wants to monitor all the alpacas. He found M points where cameras can be placed in his ranch. Coach Zhang only needs to place one camera at a point if he thinks it necessary. An alpaca is monitored when it is on one of the cameras, on the segment between two cameras, or in the triangle formed by three cameras.
* Now Coach Zhang wants to know the minimum number of cameras required to monitor all the alpacas.
* 
* Input
* The first line of input contains an integer T, which represents the number of test cases (T≤20).
* Each test case starts with a line containing N and M (1≤N≤100000,1≤M≤500).
* Each of the next N+M lines contains two integers X and Y (|X|,|Y|≤109). The first N lines represent the alpacas’ positions and the last M lines indicate the points that cameras can be placed.
* 
* Output
* For each test case, output a single line consisting of “Case #X: Y”. X is the test case number starting from 1. Y is the minimum number of cameras required to monitor all the alpacas. If it is impossible to monitor all the alpacas, you should output -1 instead.
* 
* 题意：有n头羊，m个监视器，给出监视器的位置，希望用最少的监视器监视到所有的羊，也就是所有羊都在
* 		监视器所组成的多边形内。
* 做法：先对n头羊做一个凸包，然后对监视器i，j，如果线段ij在凸包的右边且不与多边形相交，那么建边
*		i->j,最后跑一边最小环即可。
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
    LL x,y;
    Point(LL x = 0, LL y = 0):x(x),y(y){}
}pa[N],pb[N];
typedef Point Vector;
LL dcmp(double x){if(fabs(x) < eps) return 0;else return x<0?-1:1;}
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
LL Cross(Vector A, Vector B){return A.x*B.y-A.y*B.x;}
Vector Rotata(Vector A,double rad){return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));}
Vector Normal(Vector A){double L = Length(A); return Vector(-A.y/L, A.x/L);}//需要确保A不是0向量
bool OnSegment(Point p, Point a, Point b) { return dcmp(Length(p - a) + Length(p - b) - Length(a - b)) == 0; }//精度也很高的！
struct Line{
    Point p,v;
    double a,b,c,ang;//得到一般式的参数
    Line(Point p = Point(0,0), Vector v = Vector(0,0)):p(p),v(v){ang = angle(v);}
    Point point(double t){return p + v*t;}//只能在点斜式中用
    bool operator < (const Line& L)const{
        return ang < L.ang;
    }
}L[N];
LL ConvexHull(Point* p, LL n, Point* ch)
{
    sort(p, p+n);
    LL m = 0;
    for(LL i = 0; i < n; i++)
    {
        while(m > 1 && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    LL k = m;
    for(LL i = n - 2; i >= 0; i--)
    {
        while(m > k && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    if(n > 1) m--;
    return m;
}
bool mp[505][505];
LL d[505];
LL n, m;
LL dij(LL s)
{
    memset(d, 0x3f, sizeof(d));
    priority_queue<PII, vector<PII >, greater<PII> > que;
    que.push(PII(0, s));
    d[s] = 0;
    while(!que.empty())
    {
        LL dis = que.top().first, u = que.top().second;
        que.pop();
        if(mp[u][s]) return dis + 1;
        if(dis > d[u]) continue;
        for(LL v = 0; v < m; v++){
            if(mp[u][v] && dis + 1 < d[v]){
                d[v] = dis + 1;
                que.push(PII(d[v], v));
            }
        }
    }
    return INF;
}
int main()
{
//    Open();
    LL T;scanf("%I64d", &T);
    LL cas = 1;
    while(T--)
    {
        scanf("%I64d%I64d", &n, &m);
        memset(mp, 0, sizeof(mp));
        for(LL i = 0 ; i < n; i++)
        {
            LL x, y;
            scanf("%I64d%I64d", &x, &y);
            pa[i] = Point(x, y);
        }
        LL convn = ConvexHull(pa, n, pb);
        for(LL i = 0; i < convn; i++){
            L[i] = Line(pb[i], pb[i+1]-pb[i]);
        }
        sort(L, L + convn);
        bool flag = false;
        for(LL i = 0 ; i < m; i++)
        {
            LL x, y;
            scanf("%I64d%I64d", &x, &y);
            pa[i] = Point(x, y);
            if(flag == false && pa[i] == pb[0]) flag = true;
        }
        printf("Case #%I64d: ", cas++);
        if(convn == 1 && flag){
            printf("1\n");
            continue;
        }
        flag = false;
        for(LL i = 0; i < m; i++)
            for(LL j = 0; j < m; j++)
            {
                if(i == j) continue;
                if(n == 1 && flag == false && OnSegment(pb[0], pa[i], pa[j])) flag = true;
                if(n == 2 && flag == false
                && (OnSegment(pb[0], pa[i], pa[j]) || pb[0] == pa[i] || pb[0] == pa[j])
                && (OnSegment(pb[1], pa[i], pa[j]) || pb[1] == pa[i] || pb[1] == pa[j]))
                    flag = true;
                Vector v = pa[j] - pa[i];
                LL idx = upper_bound(L, L+convn, Line(Point(0, 0), v)) - L - 1;
                idx = (idx + convn) % convn;
                if(Cross(v, L[idx].p - pa[i]) >= 0 && Cross(v, L[idx].p + L[idx].v - pa[i]) >= 0){
                    if(n <= 2 && v == L[idx].v && (OnSegment(L[idx].p, pa[i], pa[j]) || L[idx].p == pa[i] || L[idx].p == pa[j]));
                    else
                        mp[i][j] = 1;
                }
            }
        if(flag){
            printf("2\n");
            continue;
        }
        LL ans = INF;
        for(LL i = 0; i < m; i++)
        {
            ans = min(ans, dij(i));
        }
        if(ans == INF) ans = -1;
        printf("%I64d\n", ans);
    }
    return 0;
}

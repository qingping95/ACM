/*
*	����n���㣬��pair(x, y)�����x����͵�y�����ֱ����ԭ�������С��d��pair����
*	
*	���ȶ���Բ�ڵĵ���˵�����������е���ɵĵ�Զ������������ģ���ô������Բ��ĵ㡣
*	����Բ��һ���ض��㣬��Բ���������ߣ���õ�һ��Բ�����䡣��ô���Է����ó����ǣ�
*	����ֱ�߾���Բ����Ҫ�����ǣ��������Ӧ��Բ������Ҫô������Ҫô���룬��ô����һ������˵������ֻ��Ҫ�ֱ�ͳ��
*	������������룬������������������ĸ����������������ɡ�������ҪС�ĵ���������˫���ϵ������ͳ������2���ɡ�
*	���ǣ���������ת��Ϊ������ʽ���Ϳ�������״�����һ������
*	��Ȼ���ٵ����⻹�У���Ҫ��Բ�ܶϿ���Ϊһ�������Ͽ��ĵط����������串�ǡ���������ѡ�񼫽���Ϊ����������ô����
*	���ֿ���˵�����䣬����ֻ��Ҫ��������ȡ�����ɣ������ǲ�Ӱ�����ս���ģ���һ��򵥻�ͼ��֪��
*
*	���ˣ�ֵ��ע����ǣ�����Ҫ����Ǿ���С��d�ģ����ڵ�Ҳ�ǲ��еģ�
*	���⣬Ϊ�˷�ֹ�������⣬������д����ɢ�����ֲ���...(����������˵����sort->unique->lower_bound,�������ﲻ����)
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
//#include <unordered_map>
#define N 600010
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
}Cir;
const double eps = 1e-9;
const double PI = acos(-1.0);
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
Vector Normal(Vector A){double L = Length(A); return Vector(-A.y/L, A.x/L);}//��Ҫȷ��A����0����
bool OnSegment(Point p, Point a, Point b) { return dcmp(Length(p - a) + Length(p - b) - Length(a - b)) == 0; }//����Ҳ�ܸߵģ�
struct Line{
    Point p,v;
    double a,b,c;//�õ�һ��ʽ�Ĳ���
	Line(){}
    Line(Point p = Point(0,0), Vector v = Vector(0,0)):p(p),v(v){a = v.y - p.y; b = p.x - v.x; c = p.y*v.x - v.y*p.x;}
    Point point(double t){return p + v*t;}//ֻ���ڵ�бʽ����
    bool operator < (const Line& L)const{
        return angle(v) < angle(L.v);
    }
};
//����P��ԲC������
double getTangents(Point P, Circle C)
{
    Vector u = C.c - P;
    double dist = Length(u);
    if(dcmp(dist - C.r) < 0) return -1;
    if(dcmp(dist - C.r) == 0) {
        return 0;
    }
    double ang = acos(C.r/dist);
//    v[0] = Rotata(u, -ang);
//    v[1] = Rotata(u, ang);
    return ang;
}
double NormalAng(double x)
{
    if(x > 0){
        while(x > PI) x -= 2.0 * PI;
    }else{
        while(x < -PI) x += 2.0 * PI;
    }
    return x;
}
int n, d;
struct S{
    double tst, ted;
    int st, ed;
    S(){}
    void upd()
    {
        if(st > ed) swap(st, ed);
    }
    bool operator<(const S& o)const{
        return ed < o.ed;
    }
}seg[N];
double tmp[N];
double sta[N];
int binaryS(double x, int tail)
{
    int res = tail;
    int lb = -1, ub = tail;
    while(lb + 1 < ub)
    {
        int mid = ub+lb >> 1;
        if(dcmp(sta[mid] - x) >= 0) ub = res = mid;
        else lb = mid;
    }
    return res;
}
int L[N], R[N];
int limit;
void add(int c[], int x, int val)
{
    if(x == 0) return ;
    for(int i = x; i < limit + 10; i += i & (-i)) c[i] += val;
}
int getsum(int c[], int x)
{
    int res = 0;
    for(int i = x; i ; i -= i & (-i)) res += c[i];
    return res;
}
int main()
{
//    Open();
    while(~scanf("%d%d", &n, &d))
    {
        for(int i = 0; i < n; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            pa[i] = Point(x, y);
//            scanf("%lf%lf", &pa[i].x, &pa[i].y);
        }
        Cir = Circle(Point(0, 0), d);
        int num0 = 0;
        int tailn = 0, tailtmp = 0;
        for(int i = 0 ; i < n; i++)
        {
            double ang = getTangents(pa[i], Cir);
            if(dcmp(ang) == -1) num0 ++;
            else{
                seg[tailn].tst = NormalAng(angle(pa[i]) - ang);
                seg[tailn++].ted = NormalAng(angle(pa[i]) + ang);
                tmp[tailtmp++] = seg[tailn-1].tst;
                tmp[tailtmp++] = seg[tailn-1].ted;
            }
        }
        sort(tmp, tmp+tailtmp);
        int tailsta = 0;
        for(int i = 0; i < tailtmp; i++)
        {
            if(i == tailtmp-1 || dcmp(tmp[i+1] - tmp[i]) != 0){
                sta[tailsta++] = tmp[i];
            }
        }
        for(int i = 0; i < tailn; i++)
        {
            seg[i].st = binaryS(seg[i].tst, tailsta) + 1;
            seg[i].ed = binaryS(seg[i].ted, tailsta) + 1;
            seg[i].upd();
        }
        sort(seg, seg+tailn);
        limit = seg[tailn-1].ed;
        if(limit > N) while(1);
        for(int i = 0; i < limit + 10; i++) L[i] = R[i] = 0;
        LL ans2 = 0, ans = 0;
        for(int i = 0; i < tailn; i++){
            ans2 += getsum(R, seg[i].st-1);
            ans += getsum(L, seg[i].ed - 1) - getsum(L, seg[i].st);
            add(R, seg[i].ed, 1);
            add(L, seg[i].st, 1);
        }
        for(int i = 0; i < limit + 10; i++) L[i] = 0;
        for(int i = tailn-1; i >= 0;i --)
        {
            ans2 += getsum(L, limit) - getsum(L, seg[i].ed);
            add(L, seg[i].st, 1);
        }
        ans += (LL)num0 * (n - num0);
        ans2 += (LL)num0 * (num0 - 1);
        if(ans2 < 0 || ans < 0) while(1);
        printf("%lld\n", ans2/2 + ans);
    }
    return 0;
}

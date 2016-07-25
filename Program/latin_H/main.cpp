#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<double, double> PDD;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
//        freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 20010;
struct Point{
    double x, y;
    Point(double x = 0, double y = 0):x(x), y(y){}
    void read()
    {
        scanf("%lf%lf", &x, &y);
    }
}pa[N];
map<PDD, int> mp;
map<PDD, int>::iterator it1, it2, tit;
const double eps = 1e-11;
const double PI = acos(-1.0);
typedef Point Vector;
int dcmp(double x)
{
    return (x>eps)-(x<-eps);
}
Vector operator+(Vector A,Vector B){return Vector(A.x+B.x, A.y+B.y);}
Vector operator-(Point A,Point B){return Vector(A.x-B.x, A.y-B.y);}
Vector operator*(Vector A, double p){return Vector(A.x*p, A.y*p);}
Vector operator/(Vector A, double p){return Vector(A.x/p, A.y/p);}
bool operator<(const Point& a, const Point& b){return a.x<b.x || (a.x == b.x && a.y < b.y);}
bool operator==(const Point& a, const Point& b){return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;}
double angle(Vector A){return atan2((double)A.y,(double)A.x);}//返回A向量的极角atan2(y,x)所表达的意思是坐标原点为起点，指向(x,y)的射线在坐标平面上与x轴正方向之间的角的角度。范围是(-pi,pi];
double Dot(Vector A, Vector B){return (double)A.x*B.x+(double)A.y*B.y;}
double Cross(Vector A, Vector B){return (double)A.x*B.y-(double)A.y*B.x;}
double Length(Vector A){return sqrt(Dot(A,A));}
Point GetLineIntersection(Point P,Vector v, Point Q, Vector w)
{
    Vector u = P-Q;
    double t = Cross(w,u) / Cross(v,w);
    return P+v*t;
}
Vector getVFromAngle(double ang)
{
    Vector V;
    if(dcmp(ang - PI/2) == 0) V = Vector(1, 1);
    else if(dcmp(ang + PI/2) == 0) V = Vector(1, -1);
    else{
        V = Vector(1, tan(ang));
    }
    return V;
}
struct Line{
    Point s;
    Point t;
    double distFromP(Point a, double ang)
    {
        Vector V = getVFromAngle(ang);
        Point res = GetLineIntersection(a, V, s, t-s);
        return Length(a - res);
    }
}line[N];
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2)
{
    double c1 = Cross(a2-a1, b1-a1), c2 = Cross(a2-a1, b2-a1);
    double c3 = Cross(b2-b1, a1-b1), c4 = Cross(b2-b1, a2-b1);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}
int tid[N];
void printfMap(map<PDD, int> m)
{
    cout<<endl;
    for(it1 = m.begin(); it1 != m.end(); it1++)
    {
        cout<<it1->first.first<<" "<<it1->first.second<<" -> "<<it1->second<<endl;
    }
    cout<<endl;
}
void conpressMap()
{
    if(tit != mp.begin()) tit--;
    if(it2 != mp.end()) it2++;
    while(tit != it2)
    {
        it1 = tit++;
        if(tit == mp.end()) break;
        if(it1->second == tit->second)
        {
//            (*tit).first.first = (*it1).first.first;
            pair<PDD, int> tmp = *tit;
            tmp.first.first = (*it1).first.first;
            mp.erase(it1);
            mp.erase(tit);
            tit = mp.insert(tmp).first;
        }
    }
}
void updateMap(double st, double ed, int pid, int lid)
{
    it1 = mp.upper_bound(PDD(st, INF));
    it1--;
    it2 = mp.upper_bound(PDD(ed, INF));
    it2--;


    double S = (*it1).first.first;
    double T = (*it2).first.second;
    int sid = (*it1).second;
    int tid = (*it2).second;

//    if(dcmp(st - S) < 0 || dcmp(st - (*it1).first.second) > 0) sid /= 0;
//    if(dcmp(ed - (*it2).first.first) < 0 || dcmp(st - T) > 0) sid /= 0;

    if(dcmp(st - S) != 0)
    {
        mp.emplace(PDD(S, st), sid);
        pair<PDD, int> tmp = (*it1);
        mp.erase(it1);
        tmp.first.first = st;
        it1 = mp.insert(tmp).first;
    }
    if(dcmp(T - ed) != 0)
    {
        mp.emplace(PDD(ed, T), tid);
        pair<PDD, int> tmp = (*it2);
        mp.erase(it2);
        tmp.first.second = ed;
        it2 = mp.insert(tmp).first;
    }
    tit = it1, it2++;

//    cout<<it1->first.first<<" "<<it1->first.second<<" -> "<<it1->second<<endl;
//    cout<<it2->first.first<<" "<<it2->first.second<<" -> "<<it2->second<<endl;

    while(it1 != it2)
    {
        int cid = it1->second;
        S = it1->first.first;
        T = it1->first.second;
        if(cid != -1) {
            if(dcmp(min(line[lid].distFromP(pa[pid], S), line[lid].distFromP(pa[pid], T)) -
               min(line[cid].distFromP(pa[pid], S), line[cid].distFromP(pa[pid], T))) <= 0)
                it1 -> second = lid;
        }else{
            it1->second = lid;
        }
//        if(cid == -1 || dcmp(line[lid].distFromP(pa[pid]) - line[cid].distFromP(pa[pid])) < 0)
//            it1->second = lid;
        it1++;
    }
    conpressMap();
//    mp.erase(it1, tit);

//    if(dcmp(st - S) != 0)
//        mp.emplace(PDD(S, st), sid);
//    mp.emplace(PDD(st, ed), idx);
//    if(dcmp(T - ed) != 0)
//        mp.emplace(PDD(ed, T), tid);
//    printfMap(mp);
}
int main()
{
//    Open();
    int s, n, m;
    while(~scanf("%d%d%d", &s, &n, &m))
    {
        for(int i = 0; i < n; i++)
            pa[i].read();
        for(int i = 0; i < m; i++)
        {
            line[i].s.read();
            line[i].t.read();
        }
        for(int i = 0; i < s; i++)
        {
            mp.clear();
            mp.emplace(PDD(-PI, PI), -1);
//            curs = i;
//            for(int j = 0; j < m; j++)
//                tid[j] = j;
//            sort(tid, tid+m, cmp);
            for(int j = 0; j < m; j++)
            {
                int id = j;
                double st = angle(line[id].s - pa[i]);
                double ed = angle(line[id].t - pa[i]);
                if(st > ed) swap(st, ed);
                if(dcmp(ed - st - PI) > 0){
                    swap(st, ed);
                    updateMap(-PI, ed, i, id);
                    updateMap(st, PI, i, id);
                }else{
                    updateMap(st, ed, i, id);
                }
            }
            int res = 0;
            for(int j = 0; j < n; j++)
            {
                if(i == j) continue;
                double ang = angle(pa[j] - pa[i]);
                it1 = mp.upper_bound(PDD(ang, INF));
                it1--;
                int lid = (*it1).second;
                if(lid == -1 || !SegmentProperIntersection(pa[i], pa[j], line[lid].s, line[lid].t)) res++;
            }
            printf("%d\n", res);
        }
    }
    return 0;
}

/*
* 给出n棵树，每棵树有一个种类Ai，再给出m个点，需要在这m个点中选出若干个点，
* 使得这个多边形包含所有类型的树
*
* 所以还是智商题，Orz。。。
* 首先这个多边形一定是凸的，如果是凹的，一定有对应的凸多边形更优。
* 那么既然是凸多边形，这个多边形一定能分解为若干三角形链！。。于是就类似路径，所以建边，
* 然后跑一边最短路(优先队列BFS)差不多就行了
*
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 333
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<double,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int id[41][41][41];//
int s[41*41*41];//
double idw[41*41*41];//
struct node{
    int v, s;
    double w;
    node(){}
    node(int _v, int _s, double _w){
        v = _v, s = _s, w = _w;
    }
    bool operator<(const node& o)const{
        return w > o.w;
    }
};
vector<node> G[41*41*41];//
int kind[N];//
int n, m, k;//
struct Point
{
    double x, y;
    Point(double x = 0, double y = 0):x(x), y(y){}
}pa[N], pb[N];//
const double eps = 1e-10;
typedef Point Vector;
int dcmp(double x){if(x < -eps) return -1;return x > eps;}
Vector operator+(Vector A,Vector B){return Vector(A.x+B.x, A.y+B.y);}
Vector operator-(Point A,Point B){return Vector(A.x-B.x, A.y-B.y);}
Vector operator*(Vector A, double p){return Vector(A.x*p, A.y*p);}
Vector operator/(Vector A, double p){return Vector(A.x/p, A.y/p);}
bool operator<(const Point& a, const Point& b){return a.x<b.x || (a.x == b.x && a.y < b.y);}
bool operator==(const Point& a, const Point& b){return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;}
double angle(Vector A){return atan2(A.y,A.x);}//返回A向量的极角
double Dot(Vector A, Vector B){return A.x*B.x+A.y*B.y;}
double Length(Vector A){return sqrt(Dot(A,A));}
double Cross(Vector A, Vector B){return A.x*B.y-A.y*B.x;}
bool isPointInTriangle(Point P, Point A, Point B, Point C)
{
    if(dcmp(Cross(B - A, P - A)) == dcmp(Cross(C - B, P - B))
       && dcmp(Cross(C - B, P - B)) == dcmp(Cross(A - C, P - C))) return true;
    return false;
}
int getid(int a, int b, int c)
{
    if(a > b) swap(a, b);
    if(a > c) swap(a, c);
    return id[a][min(b, c)][max(b, c)];
}
int limit;//
double dp[41*41*41][(1 << 6)+10];//
double BFS(int s)
{
    priority_queue<node> que;
    que.push(node(0, 0, 0));
    dp[0][0] = 0;
    while(!que.empty())
    {
        node cur = que.top();que.pop();
        int u = cur.v, s = cur.s;
        double w = cur.w;
        if(s == limit-1) return w;
        for(int i = 0; i < G[u].size(); i++)
        {
            int nxts = G[u][i].s | s;
            int v = G[u][i].v;
            double nxtw = G[u][i].w;
            if(dp[v][nxts] > nxtw + w + eps){
                dp[v][nxts] = nxtw + w;
                que.push(node(v, nxts, dp[v][nxts]));
            }
        }
    }
    return -1;
}
double getlen(Point A, Point B, Point C){
    return Length(A-B)+Length(A-C)+Length(B-C);
}
int main()
{
//    Open();
    while(~scanf("%d%d%d", &n, &m, &k)){
        for(int i = 0; i < n; i++)
        {
            double x, y;scanf("%lf%lf", &x, &y);pa[i] = Point(x, y);
        }
        for(int i = 0; i < n; i++){
            scanf("%d", &kind[i]);kind[i]--;
        }
        for(int i = 0; i < m; i++)
        {
            double x, y;scanf("%lf%lf", &x, &y);pb[i] = Point(x, y);
        }
        limit = 1 << k;
        int tot = 0;
        for(int A = 0; A < m; A++)
            for(int B = A+1; B < m; B++)
                for(int C = B+1; C < m; C++){
                    id[A][B][C] = ++tot;
                    s[tot] = 0;
                    for(int i = 0; i < n; i++)
                    {
                        if(isPointInTriangle(pa[i], pb[A], pb[B], pb[C])){
                            s[tot] |= (1 << kind[i]);
                        }
                    }
                    idw[tot] = getlen(pb[A], pb[B], pb[C]);
                }
        for(int i = 0; i <= tot; i++) {G[i].clear(); if(i) G[0].push_back(node(i, s[i], idw[i]));}
        for(int A = 0; A < m; A++)
            for(int B = A+1; B < m; B++)
                for(int C = B+1; C < m; C++)
                    for(int i = 0; i < m; i++)
                    {
                        if(i == A || i == B || i == C) continue;
                        int curid = id[A][B][C];
                        double AB = Length(pb[A] - pb[B]);
                        double BC = Length(pb[C] - pb[B]);
                        double AC = Length(pb[A] - pb[C]);
                        double Ai = Length(pb[A] - pb[i]);
                        double Bi = Length(pb[B] - pb[i]);
                        double Ci = Length(pb[C] - pb[i]);
                        double oriw = AB+BC+AC, neww;
                        int t1 = dcmp(Cross(pb[A] - pb[C], pb[i] - pb[C]));
                        int t2 = dcmp(Cross(pb[A] - pb[C], pb[B] - pb[C]));
                        if(t1 * t2 < 0)
                        {
                            int v = getid(i, A, C);
                            G[curid].push_back(node(v, s[v], Ai + Ci - AC));
                        }
                        t1 = dcmp(Cross(pb[B] - pb[C], pb[i] - pb[C]));
                        t2 = dcmp(Cross(pb[B] - pb[C], pb[A] - pb[C]));
                        if(t1 * t2 < 0)
                        {
                            int v = getid(i, B, C);
                            G[curid].push_back(node(v, s[v], Bi + Ci - BC));
                        }
                        t1 = dcmp(Cross(pb[A] - pb[B], pb[i] - pb[B]));
                        t2 = dcmp(Cross(pb[A] - pb[B], pb[C] - pb[B]));
                        if(t1 * t2 < 0)
                        {
                            int v = getid(i, A, B);
                            G[curid].push_back(node(v, s[v], Ai + Bi - AB));
                        }
                    }
        for(int i = 0; i <= tot; i++)
            for(int j = 0; j < limit; j++) dp[i][j] = INF;
        double ans = BFS(0);
        if(dcmp(ans) < 0) printf("Impossible\n");
        else printf("%.12f\n", ans);
    }
    return 0;
}

/*
* HDU_5473 ����n���㣬ѡ��k����ʹ���γ�͹����������
* ��mΪn����͹���ϵ�ĸ�����
* 1. ��k >= mʱ���𰸺������ʾ���͹�����
* 2. ��k < m ʱ��ѡ�������k����һ����͹���ϵĵ㡣��ô����ö��n���㣬ʹ��͹��������Ͽ��γ�����
*    dp[i][j]��ʾǰi������ѡ����j������i+1 ~ m�����е㶼��ѡ�е���������ת��ֻ��Ҫö��ǰһ��ѡ�еĵ�i'���ɡ�
*    ��һ�����Ӷ�ΪO(n^3),�ټ���һ��ʼö�ٵ���㣬��ô���Ӷ�ΪO(n^4).����ע�⵽ö�ٵ����ֻҪ�����Ž�㼯�еĻ���
*    ���������ȷ�𰸣����ﲢ����Ҫö�����е㡣��ֻ��Ҫ���ö��c*(n/k)���㣬�����𰸴���ĸ���Ϊ(1-k/n)^(c*(n/k))
*    �����e^(-c)����������Ƿǳ�С�ġ�
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <time.h>
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
Vector operator+(Vector A,Vector B){return Vector(A.x+B.x, A.y+B.y);}
Vector operator-(Point A,Point B){return Vector(A.x-B.x, A.y-B.y);}
Vector operator*(Vector A, double p){return Vector(A.x*p, A.y*p);}
Vector operator/(Vector A, double p){return Vector(A.x/p, A.y/p);}
bool operator<(const Point& a, const Point& b){return a.x<b.x || (a.x == b.x && a.y < b.y);}
bool operator==(const Point& a, const Point& b){return (a.x-b.x) == 0 && (a.y-b.y) == 0;}
double angle(Vector A){return atan2(A.y,A.x);}
double Dot(Vector A, Vector B){return A.x*B.x+A.y*B.y;}
double Length(Vector A){return sqrt(Dot(A,A));}
double Angle(Vector A,Vector B){return acos(Dot(A,B)/Length(A)/Length(B));}
LL Cross(Vector A, Vector B){return A.x*B.y-A.y*B.x;}
Vector Rotata(Vector A,double rad){return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));}
Vector Normal(Vector A){double L = Length(A); return Vector(-A.y/L, A.x/L);}//��Ҫȷ��A����0����
LL ConvexHull(Point* p, LL n, Point* ch)
{
    sort(p, p+n);
    LL m = 0;
    for(LL i=0;i<n;i++){
        while(m > 1 && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    LL k=m;
    for(LL i=n-2;i>=0;i--){
        while(m>k && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    if(n>1) m--;
    return m;
}
LL PolygonArea(Point* p, LL n)
{
    LL area = 0;
    for(LL i=1;i<n-1;i++) area += Cross(p[i]-p[0], p[i+1]-p[0]);
    return abs(area);
}
bool vis[111];
LL dp[111][111];
int main()
{
//    Open();
    srand((int)time(NULL));
    LL T;scanf("%I64d", &T);
    LL cas = 1;
    while(T--)
    {
        memset(vis, 0, sizeof(vis));
        LL n, K;
        scanf("%I64d%I64d", &n, &K);
        for(LL i = 0; i < n; i++)
        {
            LL x, y;
            scanf("%I64d%I64d", &x, &y);
            pa[i] = Point(x, y);
        }
        LL m = ConvexHull(pa, n, pb);
        LL res = 0;
        if(K >= m) res = PolygonArea(pb, m);
        else{
            LL TIMES = min(m, 10LL);
            LL allarea = PolygonArea(pb, m);
            while(TIMES--){
                LL st = rand() % m;
                while(vis[st]) st = rand()%m;
                vis[st] = 1;
                memset(dp, 0, sizeof(dp));
                dp[0][0] = allarea;

                for(LL i = 1; i <= m; i++)
                {
                    LL curidx = st + i;
                    if(curidx >= m) curidx -= m;
                    LL tmparea = 0;
                    for(LL k = i-1; k >= 0; k--)
                    {
                        LL nxtidx = st + k;
                        if(nxtidx >= m) nxtidx -= m;
                        LL preidx = nxtidx + 1;
                        if(preidx >= m) preidx -= m;
                        tmparea += abs(Cross(pb[preidx] - pb[curidx], pb[nxtidx] - pb[curidx]));
                        for(LL j = K; j > 0; j--)
                        {
                            dp[i][j] = max(dp[i][j], dp[k][j-1] - tmparea);
                        }
                    }
                }
                res = max(res, dp[m][K]);
            }
        }
        printf("Case #%I64d: %I64d\n", cas++, res);
    }
    return 0;
}
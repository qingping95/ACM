#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 1111
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f3f3f3f3fLL;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
struct Point{
    LL x, y;
    Point(){}
    Point(LL _x, LL _y){
        x = _x, y = _y;
    }
    void input()
    {
        scanf("%I64d%I64d", &x, &y);
    }
}pa[N], pb[N];
#define D(x) ((x)*(x))
double dist(Point a, Point b)
{
    return sqrt((double)D(a.x-b.x)+(double)D(a.y-b.y));
}
typedef double w_type;
w_type w[N][N], lx[N], ly[N], slack[N];//
LL linky[N], linkx[N];//
bool visx[N], visy[N];//
LL nx, ny;
bool find(LL x)
{
    visx[x] = true;
    for(LL y = 1; y <= ny; y++)
    {
        if(visy[y]) continue;
        w_type t = lx[x] + ly[y] - w[x][y];
        if(fabs(t) <= 1e-8)
        {
            visy[y] = true;
            if(linky[y] == -1||find(linky[y]))
            {
                linky[y] = x;
                linkx[x] = y;
                return true;
            }
        }else slack[y] = min(t, slack[y]);
    }
    return false;
}
void KM()
{
    LL i, j;
    memset(linky, -1, sizeof(linky));
    memset(linkx, -1, sizeof(linkx));
    memset(ly, 0, sizeof(ly));
    for(i = 1; i <= nx; i++)
        for(j = 1, lx[i] = -INF; j <= ny; j++)
            lx[i] = max(w[i][j], lx[i]);
    for(LL x = 1; x <= nx; x++)
    {
        for(i = 1; i <= ny; i++) slack[i] = INF;
        while(true)
        {
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));
            if(find(x)) break;
            w_type d = INF;
            for(i = 1; i <= ny; i++)
                if(!visy[i]) d = min(d, slack[i]);
            for(i = 1; i <= nx; i++)
                if(visx[i]) lx[i] -= d;
            for(i = 1; i <= ny; i++)
                if(visy[i]) ly[i] += d;
        }
    }
}
int main()
{
//    Open();
    LL n;
    while(~scanf("%I64d", &n))
    {
        nx = ny = n;
        for(LL i = 1; i <= nx; i++)pa[i].input();
        for(LL i = 1; i <= ny; i++)pb[i].input();
        for(LL i = 1; i <= nx; i++)
            for(LL j = 1; j <= ny; j++)
                w[i][j] = -dist(pa[i], pb[j]);
        KM();
        for(LL i = 1; i <= nx; i++)
        {
            printf("%I64d\n", linkx[i]);
            if(linkx[i] == -1) while(1);
        }
    }
    return 0;
}

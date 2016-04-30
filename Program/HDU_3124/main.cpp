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
typedef pair<int,int> PII;
const LL INF=0x3f3f3f3f3f3f3f3fLL;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
struct Circle{
    LL x, y, r;
    Circle(){}
    void input()
    {
        scanf("%I64d%I64d%I64d",&x, &y, &r);
    }
    bool operator<(const Circle& o)const{
        return x - r < o.x - o.r;
    }
}c[N];
#define D(x) ((x)*(x))
double dist(LL x1, LL y1, LL x2, LL y2){
    return sqrt((double)D(x1-x2)+D(y1-y2));
}
int main()
{
//    Open();
    LL T;scanf("%I64d", &T);
    while(T--)
    {
        LL n;
        scanf("%I64d", &n);
        for(LL i = 0; i < n; i++) c[i].input();
        sort(c, c+n);
        LL UP = 100000000 / n;
        double ans = INF;
        for(LL i = 0; i < n; i++)
        {
            for(LL j = i + 1; j < n && j - i < UP; j++)
            {
                ans = min(ans, dist(c[i].x, c[i].y, c[j].x, c[j].y) - c[i].r - c[j].r);
            }
        }
        printf("%.6f\n", ans);
    }
    return 0;
}

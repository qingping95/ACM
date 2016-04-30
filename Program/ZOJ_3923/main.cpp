#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
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
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const double PI = acos(-1.0);
int main()
{
    //Open();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        double R, H, V, x0, dx, dy, dz;
        scanf("%lf%lf%lf%lf%lf%lf%lf", &R, &H, &V, &x0, &dx, &dy, &dz);
        double t = x0 / V;
        dx -= V;
        printf("%.10f\n", (PI*R*R*-dz + 2*R*H*sqrt(dx*dx+dy*dy))*t);
    }
    return 0;
}

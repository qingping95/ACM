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
LL t1, t2, X1, X2, t0;
LL cmp(LL ay1, LL ay2, LL by1, LL by2)
{
    if((ay1*t1 + ay2*t2)*(by1+by2) < (by1*t1+by2*t2)*(ay1+ay2)) return -1;
    if((ay1*t1 + ay2*t2)*(by1+by2) == (by1*t1+by2*t2)*(ay1+ay2)) return 0;
    return 1;
}
int main()
{
    //Open();
    scanf("%I64d%I64d%I64d%I64d%I64d", &t1, &t2, &X1, &X2, &t0);
    if(t0 == t2 && t1 == t0) {printf("%I64d %I64d\n", X1, X2);return 0;}
    if(t1 == t0) {printf("%I64d %I64d\n", X1, 0LL);return 0;}
    if(t0 == t2) {printf("%I64d %I64d\n", 0LL, X2);return 0;}
    LL y1 = 0, y2 = X2;
    for(LL i = 0; i <= X1; i++)
    {
        double cur = (double)(t1 - t0) / (t0 - t2) * i;
        LL cy2 = ceil(cur);
        if(cy2 <= X2 && (t1*i+t2*cy2) >= (i+cy2)*t0 && cmp(i, cy2, y1, y2) <= 0) {
            if(cmp(i, cy2, y1, y2) == 0 && i + cy2 > y1 + y2){
                y1 = i, y2 = cy2;
            }else if(cmp(i, cy2, y1, y2) == -1){
                y1 = i, y2 = cy2;
            }
        }
    }
    printf("%I64d %I64d\n", y1, y2);
    return 0;
}

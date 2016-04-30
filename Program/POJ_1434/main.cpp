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
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
PII r[N];
int main()
{
//    Open();
    int T;scanf("%d", &T);
    while(T--)
    {
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
        {
            int b, h, w, d;
            scanf("%d%d%d%d", &b, &h, &w, &d);
            r[i*2] = PII(b, w * d);
            r[i*2+1] = PII(b+h, -w*d);
        }
        int V;scanf("%d", &V);
        sort(r, r+2*n);
        int curs = r[0].second;
        int i;
        bool flag = true;
        for(i = 1; i < 2 * n; i++)
        {
            LL curV = (LL)curs * (r[i].first - r[i-1].first);
            if(curV >= V){
                flag = false;
                break;
            }
            V -= curV;
            curs += r[i].second;
        }
        if(flag){
            printf("OVERFLOW\n");
            continue;
        }
        printf("%.2f\n", r[i-1].first*1.0 + V*1.0 / curs);
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
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
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
LL n, a[200020];

int main()
{
    //Open();
    scanf("%I64d", &n);
    for(LL i = 0 ; i < n; i++)
        scanf("%I64d", &a[i]);
    LL l = 0, d = INF, idx = INF;
    LL ans = 1;
    for(LL i = 0; i < n; i++)
    {
        if(a[i] == -1){
            if(d != INF && d < 0 && a[idx] + d*(i-idx) <= 0){
                ans++;
                l = i;
                idx = INF;
                d = INF;
            }
        }else if(idx == INF){
            idx = i;
        }else if(d == INF){
            LL diff = a[i] - a[idx];
            if(diff % (i - idx)){
                ans++;
                idx = l = i;
                d = INF;
            }else{
                d = diff / (i - idx);
                if(a[l] == -1){
                    if(d > 0 && a[idx] - d * (idx - l) <= 0)
                    {
                        ans++;
                        l = idx = i;
                        d = INF;
                    }
                }
            }
        }else{
            LL diff = a[i] - a[idx];
            if(diff % (i - idx) || diff/(i - idx) != d){
                ans ++;
                idx = l = i;
                d = INF;
            }
        }
    }
    printf("%I64d\n", ans);
    return 0;
}

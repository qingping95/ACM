#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 1000010
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f3f3f3f3fLL;
const double eps = 1e-8;
void Open()
{
#ifndef ONLINE_JUDGE
    freopen("/home/qingping/in.txt","r",stdin);
    //freopen("D:/my.txt","w",stdout);
#endif // ONLINE_JUDGE
}
LL w[N];
LL ans[N];
LL maxnum[N];
#define pb push_back
int main()
{
//    Open();
    LL T;
    scanf("%lld",&T);
    LL n,q;
    LL Cas = 1;
    while(T--)
    {
        memset(ans, 0, sizeof(ans));
        printf("Case #%lld: ",Cas++);
        scanf("%lld", &n);
        memset(w, 0, sizeof(w));
        LL ma = 0;
        for(LL i = 0; i < n; i++)
        {
            LL x, y;
            scanf("%lld%lld", &x, &y);
            w[x] += y;
            ma = max(x, ma);
        }
        maxnum[0] = w[0];
        for(LL i = 0; i <= ma; i++)
        {
            maxnum[i+1] = w[i+1] + maxnum[i] / 2;
        }
        bool flag = true;
        LL idx, tmpres;
        for(LL i = ma ; i>= 0 && flag; i--)
        {
            if((w[i] & 1) == 0) continue;
            LL res = 1;
            w[i] = 0;
            for(LL j = i-1; j >= 0 && flag; j--)
            {
                res *= 2;
                if(res > maxnum[j]){
                    flag = false;
                    tmpres = res;
                    idx = j;
                    break;
                }
                if(res <= w[j])
                {
                    w[j] -= res;
                    maxnum[j] -= res;
                    break;
                }
                else
                {
                    res -= w[j];
                    w[j] = 0;
                }
                if(j == 0) flag = false, tmpres = res, idx = j;
            }
        }
        if(flag)
        {
            printf("0\n");
            continue;
        }
        LL wma = -1;
        for(LL i = 0; ; i++)
        {
            w[i+1] += w[i]/2;
            w[i] = w[i] & 1;
            if(w[i])wma = max(wma, i);
            if(i > ma && w[i+1] == 0) break;
        }
        LL first = -1;
        LL pre = -1;
        for(LL i = idx; ; i++)
        {
            if(tmpres==0) break;
            ans[i] = tmpres & 1;
            tmpres >>= 1;
            if(ans[i] && first == -1)
            {
                first = i;
            }
            if(ans[i]) pre = i;
        }
        if(wma == -1)
        {
            for(LL i = pre; i >= 0; i--)
            {
                printf("%lld", ans[i]);
            }
            printf("\n");
            continue;
        }
        ans[first] = 0;
        bool tmpflag = true;
        LL id = 0;
        while(id < first && w[id] == 0) ans[id] = 0, id++;
        ans[id] = 1;
        for(id++; id < first; id++)
        {
            ans[id] = w[id] ^ 1;
        }
        LL tpre = pre;
        pre = -1;
        for(LL i = 0; i <= tpre; i++)
        {
            if(ans[i]) pre = i;
        }
        for(LL i = pre; i >= 0; i--)
        {
            printf("%lld", ans[i]);
        }
        printf("\n");
    }
    return 0;
}

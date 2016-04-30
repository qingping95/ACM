/*
* 题意：题意如上。。
* 
* 做法：对于数组的与和来说，固定起点的话，不同的值只可能有log个，那么只需要维护固定起点之后，这个
*		数组有多少个j满足i-j区间的异或和等于一个定值即可。由于异或的特殊性质，可以先重做数组为了求
*		异或和，具体代码中有
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <ctime>
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
//    freopen("D:/in.txt","r",stdin);
    freopen("hack.in","r",stdin);
    freopen("hack.out","w",stdout);
}

LL sta[N];
LL a[N];
LL f[N];
LL pre[44];
vector<LL> id[N];
set<PII>::iterator sit;
LL n;
int main()
{
    Open();
    while(~scanf("%I64d", &n))
    {
        LL tail = 0;
        sta[tail++] = f[n-1] = 0;
        for(LL i = 0; i < n; i ++) scanf("%I64d", &a[i]);
        for(LL i = n - 2; i >= 0; i--) f[i] = f[i+1] ^ a[i + 1], sta[tail++] = f[i];
        sort(sta, sta+tail);
        tail = unique(sta, sta+tail) - sta;
        for(LL i = 0; i <= tail; i ++) id[i].clear();
        for(LL i = 0; i < n; i++)
        {
            f[i] = lower_bound(sta, sta + tail, f[i]) - sta;
            id[f[i]].push_back(i);
        }
        for(LL i = 0; i < 31; i ++) pre[i] = n;
        LL ans = 0;
        LL X = 0;
        for(LL i = n - 1; i >= 0; i--)
        {
            X ^= a[i];
            set<PII > S;
            for(LL j = 0; j < 31; j++)
            {
                if(!(a[i] & (1 << j)))
                    pre[j] = min(i, pre[j]);
                if(pre[j] < n) S.insert(PII(pre[j], j));
            }
            S.insert(PII(n, 0));
            LL val = (1LL << 31) - 1;
            LL preidx = i;
            for(sit = S.begin(); sit != S.end(); sit++)
            {
                LL curidx = (*sit).first, dig = (*sit).second;
                if(curidx != preidx)
                {
                    LL findidx = lower_bound(sta, sta+tail, val ^ X) - sta;
                    if(sta[findidx] == (val ^ X))
                    {
                        LL r = upper_bound(id[findidx].begin(), id[findidx].end(), curidx - 1) - id[findidx].begin() - 1;
                        LL l = lower_bound(id[findidx].begin(), id[findidx].end(), preidx) - id[findidx].begin();
                        ans += max(0LL, (r - l + 1));
                    }
                }
                preidx = curidx;
                val ^= (1LL << dig);
            }
        }
        printf("%I64d\n", ans);
    }
    return 0;
}


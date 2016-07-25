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
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
LL li[500010];
LL mi[500010];
LL sum[500010];
LL sta[500010];
LL tn;
int main()
{
    //Open();
    memset(mi, 0x3f, sizeof(mi));
    for(LL i = 0; i < 500010; i++)
        li[i] = i*i*i;
    LL m;
    scanf("%I64d", &m);
    mi[0] = 0;
    for(LL i = 1; i <= 7; i++)
    {
        mi[i] = i;
        sum[i] = sum[i-1]+1;
    }
    mi[8] = 7+8;
    mi[9] = mi[8]+8;
    LL tn = 9;
    LL threshold = mi[9];
    for(LL i = 3; threshold <= m ; i++)
    {
        LL curli = li[i];
        if(i >= 500003) break;
        for(LL idx = tn; idx >= 0; idx--)
        {
            if(li[i+1] - mi[idx] > curli)
            {
                LL num = (li[i+1] - mi[idx]) / curli;
                LL tmps = mi[idx] + curli * num;
                if(mi[num+idx] > tmps)
                    mi[num+idx] = tmps, mi[num+idx] = tmps;
                threshold = max(threshold, mi[num+idx]);
                tn = max(tn, num+idx);
                break;
            }
        }
    }
//    for(int i = 0 ; i < tn; i++)
//        cout<<i<<" -> "<< mi[i]<<endl;
    LL idx = upper_bound(mi, mi+tn+1, m) - mi;
    idx--;
    LL tmp = mi[idx];
    LL curtn = 0;
    while(tmp > 0)
    {
        LL liidx = upper_bound(li, li+500010, tmp) - li - 1;
        sta[curtn++] = liidx;
        tmp -= li[liidx];
    }

    LL Ls = mi[idx], Rs = 0, ans = 0;
    for(LL i = 0; i < curtn; i++)
    {
        Ls -= li[sta[i]];
        LL dif = m - Ls;
        LL low = 0x3f3f3f3f3f3f3f3fLL;
//        if(i != 0) low = li[sta[i]+1] - Ls;
        LL liidx = upper_bound(li, li+500010, min(dif, low)) - li - 1;
        while(liidx > sta[i] && li[liidx] + Ls >= li[liidx+1]) liidx--;
        if(liidx > sta[i])
            sta[i] = liidx;
        m -= li[liidx];
    }
    for(LL i = 0; i < curtn; i++)
        ans += li[sta[i]];
    printf("%I64d %I64d\n", curtn, ans);
    return 0;
}

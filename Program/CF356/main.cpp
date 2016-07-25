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
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int li[500010];
int mi[500010];
int sum[500010];
int sta[500010];
int tn;
int main()
{
    //Open();
    memset(mi, 0x3f, sizeof(mi));
    for(int i = 0; i < 500010; i++)
        li[i] = i*i*i;
    int m;
    scanf("%d", &m);
    mi[0] = 0;
    for(int i = 1; i <= 7; i++)
    {
        mi[i] = i;
        sum[i] = sum[i-1]+1;
    }
    mi[8] = 7+8;
    mi[9] = mi[8]+8;
    int tn = 9;
    int threshold = mi[9];
    for(int i = 3; threshold <= m; i++)
    {
        int curli = li[i];
        for(int idx = tn; idx >= 0; idx--)
        {
            if(li[i+1] - mi[idx] > curli)
            {
                int num = (li[i+1] - mi[idx]) / curli;
                int tmps = mi[idx] + curli * num;
                if(mi[num+idx] > tmps)
                    mi[num+idx] = tmps, mi[num+idx] = tmps;
                threshold = max(threshold, mi[num+idx]);
                tn = max(tn, num+idx);
                break;
            }
        }
    }
    int idx = upper_bound(mi, mi+tn+1, m) - mi;
    idx--;
    int tmp = mi[idx];
    int curtn = 0;
    while(tmp > 0)
    {
        int liidx = upper_bound(li, li+500010, tmp) - li - 1;
        sta[curtn++] = liidx;
        tmp -= li[liidx];
    }

    int Ls = mi[idx], Rs = 0, ans = 0;
    for(int i = curtn-1; i >= 0; i--)
    {
        int dif = m - Ls - li[sta[i]];
        int liidx = upper_bound(li, li+500010, dif) - li - 1;
        if(liidx < 0 || i == curtn-1 || Ls - li[sta[i]] + li[liidx] >= li[sta[i+1]]) continue;
        sta[i] = liidx;
        m -= li[liidx];
    }
    for(int i = 0; i < curtn; i++)
        ans += li[sta[i]];
    printf("%d %d\n", curtn, ans);
    return 0;
}

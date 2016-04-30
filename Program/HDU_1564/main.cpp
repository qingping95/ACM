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
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
LL n, m;
LL a[22];

LL f[12]={0, 2, 1, 5, 4, 3, 6, 8, 7, 10, 9, 11};
LL dp[16][(1<<4)+1][(1<<15)+1];
PII xy[16];
bool in[13][2];
bool out[13][2];
LL ans;
LL rli, mli, cnt, tail;
LL getsta(LL i, LL s1, LL j, LL val)
{
    LL x = xy[i].first, y = xy[i].second;
    LL res = s1;
    if(res & (1 << y)) res ^= (1 << y);
    if(res & (1 << y+1)) res ^= (1 << y+1);
    bool iscon = (in[j][0] && (s1 & (1 << y))) || (in[j][1] && (s1 & (1 << y+1))) || (i == 1);
    if(iscon){
        if(i == cnt)
            ans += val;
        if(out[j][0]) res ^= (1 << y);
        if(out[j][1]) res ^= (1 << y+1);
    }
    if(y == m-1) res = (res << 1)&(mli-1);
    return res;
}
void change()
{
    swap(n, m);
    for(LL i = 0; i < tail; i++) a[i] = f[a[i]];
}
int main()
{
    Open();
    in[1][1] = out[1][0] = in[2][0] = out[2][1] = in[3][1] = out[3][1] = out[4][0] = out[4][1] = in[5][0] = out[5][0] = in[6][0] = in[6][1] = 1;
    in[7][1] = out[7][0] = out[7][1] = in[8][0] = out[8][0] = out[8][1] = in[9][0] = in[9][1] = out[9][0] = in[10][0] = in[10][1] = out[10][1] = 1;
    in[11][0] = in[11][1] = out[11][0] = out[11][1] = 1;
    scanf("%lld%lld", &n, &m);
    tail = 0;
    for(LL i = 0; i < 12; i++)
    {
        LL x;
        scanf("%lld", &x);
        while(x--) a[tail++] = i;
    }
    if(n < m) change();
    cnt = 0;
    for(LL i = 0; i < n; i++)
        for(LL j = 0; j < m; j++)
            xy[++cnt] = PII(i, j);
    rli = 1 << tail;
    mli = 1 << m+1;
    dp[0][3][rli-1] = 1;
    ans = 0;
    for(LL i = 0; i < cnt ; i++)
    {
        for(LL s1 = 0; s1 < mli; s1++)
        {
            for(LL s2 = 0; s2 < rli; s2++)
            {
                if(dp[i][s1][s2] == 0) continue;
                LL pre = -1;
                for(LL j = 0; j < tail; j++)
                {
                    if(s2 & (1 << j)){
                        if(a[j] == pre) continue;
                        pre = a[j];
                        LL nxts1 = getsta(i+1, s1, a[j], dp[i][s1][s2]);
                        dp[i+1][nxts1][s2 ^ (1 << j)] += dp[i][s1][s2];
                    }
                }
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}

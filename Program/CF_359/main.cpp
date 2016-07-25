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
LL n, m;
LL a[111];
LL ta;
LL tb;
LL b[111];
bool vis[111];
LL C[12][12];
LL F[12];
void getC()
{
    F[0] = 1;
    for(LL i = 1; i < 12; i++)
        F[i] = i * F[i-1];
    for(LL i = 0; i < 12; i++)
        C[i][0] = C[i][i] = 1;
    for(LL i = 1; i < 12; i++)
        for(LL j = 1; j < i; j++)
            C[i][j] = C[i-1][j] + C[i-1][j-1];
}
void get7(LL x, LL A[], LL &t)
{
    t = 0;
    while(x)
    {
        A[t++] = x % 7;
        x /= 7;
    }
    if(t == 0) A[t] = 0;
}
LL get10(LL A[], LL t)
{
    LL res = 0;
    for(LL i = 0; i < t; i++)
        res = res * 7LL + A[i];
    return res;
}
LL dp[111];
LL dfs(LL idx, LL num)
{
//    if(idx == -1) return 1;
////    if(limit == 0 && dp[idx] != -1) return dp[idx];
//    LL up = limit?b[idx]:7;
//    LL res = 0;
//    for(LL i = 0; i < up; i++)
//    {
//        if(vis[i]) continue;
//        vis[i] = 1;
//        res += dfs(idx-1, limit & (i == up));
//        vis[i] = 0;
//    }
////    if(limit == 0) dp[idx] = res;
//    return res;
    bool tvis[111];
    memcpy(tvis, vis, sizeof(vis));
    LL res = 0;
    for(LL i = idx; i >= 0; i--)
    {
        LL tmp = 0;
        for(LL j = 0; j < b[i]; j++)
            tmp += (tvis[j] == 0);
        if(num + 1 <= 7 && 7-num-1 >= i) res += tmp * C[7-num-1][i]*F[i];
        if(tvis[b[i]] == 1) break;
        tvis[b[i]] = 1;
        num++;
        if(i == 0) res++;
    }
    return res;
}
LL sta[21];
LL tmp[21];
LL ans;
void select(LL dep, LL limit, LL pos)
{
    if(dep == limit)
    {
        LL num = 0;
        memcpy(tmp, sta, sizeof(sta));
        sort(tmp, tmp+limit);
        do{
            if(get10(tmp, limit) < n) num++;
        }while(next_permutation(tmp, tmp+limit));
        memset(dp, -1, sizeof(dp));
        ans += num*dfs(tb-1, limit);
        return ;
    }
    for(LL i = pos; i < 7; i++)
    {
        sta[dep] = i;
        vis[i] = 1;
        select(dep+1, limit, i+1);
        vis[i] = 0;
    }
}
int main()
{
    //Open();
    getC();
    scanf("%I64d%I64d", &n, &m);
    get7(n-1, a, ta);
    ta = max(1LL, ta);
    get7(m-1, b, tb);
    tb = max(1LL, tb);
//    cout<<"ta -> "<<ta<<endl;
//    cout<<"tb -> "<<tb<<endl;

    ans = 0;
    select(0, ta, 0);
    printf("%I64d\n", ans);
    return 0;
}

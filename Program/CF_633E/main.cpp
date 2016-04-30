#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
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
typedef long double LD;
const int N = 1000010;
int mi[N][22], ma[N][22], mm[N];
int v[N], c[N];
int p[N];
int f[N];
int sta[N];
int num[N];
LD C[N];
void makermqmi(int n,int b[],int dp[][22])
{
    int i,j;
    mm[0] = -1;
    for(i=0;i<n;i++)
        mm[i+1] = ((i&(i+1)) == 0)?mm[i]+1:mm[i], dp[i][0]=b[i];
    for(j=1;(1<<j)<=n;j++)
        for(i=0;i+(1<<j)-1<n;i++)
            dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
}
void makermqma(int n,int b[],int dp[][22])
{
    int i,j;
    for(i=0;i<n;i++)
        dp[i][0]=b[i];
    for(j=1;(1<<j)<=n;j++)
        for(i=0;i+(1<<j)-1<n;i++)
            dp[i][j]=max(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
}
int rmqmi(int s,int v,int dp[][22])
{
    int k= mm[v-s+1];
    return min(dp[s][k],dp[v-(1<<k)+1][k]);
}
int rmqma(int s,int v,int dp[][22])
{
    int k= mm[v-s+1];
    return max(dp[s][k],dp[v-(1<<k)+1][k]);
}

int calc(int l, int r)
{
    return min(rmqma(l, r, ma), rmqmi(l, r, mi));
}
int main()
{
    //Open();
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++)
        scanf("%d", &v[i]), v[i] *= 100;
    for(int i = 0; i < n; i++)
        scanf("%d", &c[i]);
    makermqma(n, v, ma);
    makermqmi(n, c, mi);
    int tail = 0;
    for(int i = 0; i < n; i++)
    {
        int lb = i-1, ub = n;
        while(lb + 1 < ub)
        {
            int mid = lb+ub >> 1;
            if(rmqma(i, mid, ma) < rmqmi(i, mid, mi)) lb = mid;
            else ub = mid;
        }
        p[i] = max(calc(i, lb), calc(i, ub));
        sta[tail++] = p[i];
    }
//    for(int i = 0; i < n; i++)
//        printf("%d ", p[i]);
    sort(sta, sta+tail);
    double ans = 0.0;
    double prob = 1.0;
    for (int i = 0; i <= n - k; i++) {
        if(prob < 1e-20) break;
        double q = k * 1.0 / (n - i);
        ans += prob * q * sta[i];
        prob *= (1.0 - q);
    }
//    tail = unique(sta, sta+tail) - sta;
//    for(int i = 0; i < n; i++)
//        num[lower_bound(sta, sta+tail, p[i]) - sta]++;
//    num[tail] = 0;
//    for(int i = tail-1; i >= 0; i--)
//        num[i] += num[i+1];
//
//    for(int i = 0; i < k; i++)
//        C[i] = 0;
//    C[k] = 1;
//    int cur = n-k+1;
//    for(int i = 1; i <= k; i++)
//    {
//        C[k] *= i;
//        while(C[k] > 1e9 && cur <= n) C[k]/=cur, cur++;
//    }
//    while(cur <= n) C[k] /= cur, cur++;
//    for(int i = k+1; i <= n; i++)
//    {
//        C[i] = C[i-1] * (LD)i/(i-k);
//    }
//    LD ans = 0;
//    for(int i = 0; i < tail; i++)
//    {
//        if(num[i] < k) break;
//        int xy = num[i], y = num[i+1];
//        ans += (C[xy] - C[y]) * sta[i];
//    }
    printf("%.7f\n", (double)ans);
    return 0;
}

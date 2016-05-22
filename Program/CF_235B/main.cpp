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
const int N = 100010;
double dp[N];
double s[N];
double p[N];
const double eps = 1e-9;
int sign(double x)
{
    return (x>eps)-(x<-eps);
}
int main()
{
    //Open();
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%lf", &p[i]);
    int num = 0;
    dp[0] = p[0];
    num++;
    if(sign(p[0]) == 0) num = 0;
    double cp = p[0];
    for(int i = 1; i < n; i++)
    {
        dp[i] = p[i]*(dp[i-1] + num*(num+1) + num+1)*cp;
        dp[i] += (1-p[i])*dp[i-1];
        cp = (cp+1)*p[i];
        num++;
        if(sign(p[0]) == 0) num = 0;
    }
    printf("%.12f\n", dp[n-1]);
    return 0;
}

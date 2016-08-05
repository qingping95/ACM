#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#define ls (x<<1)
//#define rs (x<<1|1)
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<LL,LL> PII;
const LL INF=(1LL<<62)-10;
//const LL INF=0x3f3f3f3f3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
//        freopen("F:/test.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int mod = 1000000007;;
const int N = 1000010;
PII pre[N];
void check(LL n)
{
    LL ans = INF;
    PII L, R;
    LL up = sqrt(n)+10;
    while(up*up > n) up--;
    for(LL i = up;i>0&& i>up-10000000; i--)
    {
        LL P = n - i * i;
        LL j = P / i + i;
        LL s = P % i;
        if(s == 0) j--, s = n-i*j;
        if(i*j+s != n || s >= N || pre[s].first == INF) continue;
        PII Left = pre[s];
        PII Right = PII(i, j);
        if(ans > Left.first+Left.second+Right.first+Right.second)
        {
            ans = Left.first+Left.second+Right.first+Right.second;
            L = Left;
            R = Right;
        }
    }

    printf("%lld\n", ans*2);
    printf("%lld %lld\n", L.first, L.second);
    printf("%lld %lld\n", R.first, R.second);
}
int main()
{
//    Open();
    for(int i = 0; i < N; i++)
        pre[i] = PII(INF, INF);
    for(int i = 1; i < N; i++)
        for(int j = i; (LL)i*j < N; j++)
            if(pre[i*j].first+pre[i*j].second > i+j)
                pre[i*j] = PII(i, j);
    LL n;
    scanf("%lld", &n);
    check(n);
    return 0;
}

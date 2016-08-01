#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
#include <assert.h>
#include <unordered_map>
//#define ls (x<<1)
//#define rs (x<<1|1)
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<LL,LL> PII;
//const LL INF=1LL<<62;
const LL INF=0x3f3f3f3f3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
//        freopen("F:/test.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int mod = 1000000007;
int L1 = 309090906, R1 = 323529415;
int L2 = 31455947, R2 = 31790491;
int L3 = 315126158, R3 = 317333225;
const int N = 1000010;
PII pre[N];
unordered_map<LL, PII> mp;
PII getpair(LL x, LL limit)
{
    if(x < N && pre[x].first != INF) return pre[x];
    if(mp.find(x) != mp.end()) return mp[x];
    LL ans = INF;
    int a = -1;
    int low = 1;
//    low = sqrt(x)-5000000;
//    low = max(1, low);
    for(int i = sqrt(x)+1e-8; i>=low; i--)
    {
//        if(i*i + x >= limit*i) return PII(INF/2+1, INF/2+1);
        if(double(i + 1.0*x/i) > limit) return PII(INF/2+1, INF/2+1);
        if(x % i == 0){
            ans = i+x/i;
            a = i;
            break;
        }
    }
    if(a == -1) return PII(INF/2+1, INF/2+1);
    if(x < N) pre[x] = PII(a, x/a);
    else mp[x] = PII(a, x/a);
    return PII(a, x/a);
}
void check(LL n)
{
    LL ans = INF;
    PII L, R;
    LL up = sqrt(n)+10;
    while(up*up > n) up--;
    for(LL i = up;i>0&& i>up-10000000; i--)
    {
        LL p = n-i*i;
        LL j = p/i+i;
        LL s = p%i;
        //LL j = n/i;
//        if(i == 316102090){
//            cout<<p<<endl;
//            cout<<j<<endl;
//            cout<<s<<endl;
//        }
        if(i*j+s != n || s >= N || pre[s].first == INF) continue;
        PII Left = pre[s];
        PII Right = PII(i, j);
        if(ans > (ULL)Left.first+Left.second+Right.first+Right.second)
        {
            ans = Left.first+Left.second+Right.first+Right.second;
            L = Left;
            R = Right;
        }
    }
//    for(int i = 1; i+i<=n && i <= 300; i++)
//    {
//        PII Left = pre[i];
//        LL limit = ans - Left.first-Left.second;
//        if(2.0*sqrt(n-i) > limit) continue;
//        PII Right = getpair(n-i, limit);
//        if(ans > Left.first+Left.second+Right.first+Right.second)
//        {
//            ans = Left.first+Left.second+Right.first+Right.second;
//            L = Left;
//            R = Right;
//        }
//    }
    for (int a = 1 ; a <= 50 ; ++ a)
        for (int b = a ; b <= 50 ; ++ b)
            for (int c = 1 ; c <= 50 ; ++ c)
                for (int d = c ; d <= 50 ; ++ d) {
                {
                    if(a*b + c*d != n) continue;
                    if(ans > a+b+c+d)
                    {
                        ans = a+b+c+d;
                        L = PII(a, b);
                        R = PII(c, d);
                    }
                }
            }
    printf("%I64d\n", ans*2);
    printf("%I64d %I64d\n", L.first, L.second);
    printf("%I64d %I64d\n", R.first, R.second);
    //printf("%I64d: %I64d (%I64d %I64d %I64d %I64d)\n", n, ans, L.first, L.second, R.first, R.second);
}
int main()
{
//    Open();
//    cout<<(LL)L1*R1<<endl;
//    cout<<(1LL<<62)<<endl;
//    cout<<INF<<endl;
    //memset(pre, 0x3f, sizeof pre);
    for(int i = 0; i < N; i++)
        pre[i] = PII(INF, INF);
//    for(int i = 1; i < N; i++)
//        pre[i] = getpair(i, INF);
    for(int i = 1; i < N; i++)
        for(int j = i; (LL)i*j < N; j++)
            if((ULL)pre[i*j].first+pre[i*j].second > i+j)
                pre[i*j] = PII(i, j);
//    cout<<"FUCK!"<<endl;
    LL n;
//    scanf("%I64d", &n);
    cin >> n;
    check(n);
//    for(int i = 2; i < 100; i++)
//        check(i);
    return 0;
}

/*
* 凸包面积为多边形中各个矢量三角形的面积之和
* 而面积之和可转化为三角形的两向量的叉积，也就是说凸包上的每一条边对总面积都有贡献，那么只需要枚举点集中的所有边，
* 再计算出这条边在凸包中的概率，即可得出该边对答案的贡献。
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
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
const LL INF = 0x3f3f3f3f;
const LL mod = 1000000007;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
LL x[N], y[N];
int main()
{
//    Open();
    LL T;scanf("%I64d", &T);
    while(T--)
    {
        LL n;
        scanf("%I64d", &n);
        for(LL i = 0; i < n; i++) scanf("%I64d%I64d", &x[i], &y[i]);
        LL px = 0, py = 0, mul = 1, pxx = 0, pyy = 0;
        for(LL i = n - 2; i >= 1; i--){
            mul = mul * 2 % mod;
            px = (px + x[i]) % mod;
            py = (py + y[i]) % mod;
            pxx = (pxx + x[i] * mul % mod) % mod;
            pyy = (pyy + y[i] * mul % mod) % mod;
        }

        LL tail = n-1;
        LL head = 1;
        LL ans = 0;
        for(LL i = 0; i < n; i++)
        {
            ans = (ans + x[i] * (pyy - py) % mod) %mod;
            ans = (ans - y[i] * (pxx - px) % mod) %mod;
            pyy = (pyy - y[head] * mul % mod) %mod;
            py = (py - y[head]) % mod;
            pyy = pyy * 2 %mod + y[tail]*2;
            py = (py + y[tail]);

            pxx = (pxx - x[head] * mul % mod) %mod;
            px = (px - x[head]) % mod;
            pxx = pxx * 2 %mod + x[tail]*2;
            px = (px + x[tail]);
            head++, tail++;
            head %= n, tail %= n;
        }
        printf("%I64d\n", (ans + mod)%mod);
    }
    return 0;
}
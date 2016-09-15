/*
*	用dp[i][j]表示抽了i张a卡，j张b卡的概率，那么只能从还能继续抽牌的状态转移过来，转移方程见代码
*	考虑如何计算答案，这里只需要在每一个结束状态(再也不能抽牌(j == i+1))计算当前的有多少种方式伤害超过P点
*	需要注意的是，当b卡全部抽完之后，还剩很多A卡也是一个结束状态。这里被坑了很久
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <climits>
#include <bitset>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PII;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
const LL mod = 1e9+7.5;
const LL N = 50010;

struct fs{
    LL num;
    LL den;
    fs(LL num = 0, LL den = 1){
        if(den < 0)
        {
            num = -num;
            den = -den;
        }
        LL g = __gcd(abs(num), den);
        this->num = num/g;
        this->den = den/g;
    }
    fs operator+(const fs& o)const{
        return fs(num*o.den+den*o.num, den*o.den);
    }
    fs operator-(const fs& o)const{
        return fs(num*o.den-den*o.num, den*o.den);
    }
    fs operator*(const fs& o)const{
        return fs(num*o.num, den*o.den);
    }
    fs operator/(const fs& o)const{
        return fs(num*o.den, den*o.num);
    }
};
fs dp[22][22];
LL dp2[22];
LL c[22][22];
LL x[22];
LL p, n, m;
fs getP(LL b)
{
    return fs(dp2[b], c[m][b]);
}
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
    for(LL i = 0; i <= 20; i++)
        c[i][i] = c[i][0] = 1;
    for(LL i = 1; i <= 20; i++)
        for(LL j = 1; j < i; j++)
        {
            c[i][j] = c[i-1][j-1]+c[i-1][j];
        }

    LL T;
    scanf("%I64d", &T);
    while(T--)
    {
        scanf("%I64d%I64d%I64d", &p, &n, &m);
        for(LL i = 0; i < m; i++)
            scanf("%I64d", &x[i]);
        memset(dp2, 0, sizeof(dp2));
        LL limit = 1 << m;
        for(LL s = 0; s < limit; s++)
        {
            LL res = 0;
            for(LL i = 0; i < m; i++)
            {
                if(s & (1<<i)) res += x[i];
            }
            if(res >= p) dp2[__builtin_popcount(s)]++;
        }

        fs ans = fs(0, 1);
        for(LL i = 0; i <= n; i++)
            for(LL j = 0; j <= m; j++)
                dp[i][j] = fs(0, 1);
        dp[0][0] = fs(1, 1);
        fs all;
        for(LL i = 0; i <= n; i++)
            for(LL j = 0; j <= min(m, i+1); j++)
            {
                //if(i || j) dp[i][j] = fs(0, 1);
                if(j-1 >= 0 && j-1 <= i) dp[i][j] = dp[i][j-1] * fs(m-j+1, n+m-i-j+1);
                if(i-1 >= 0 && j <= i-1) dp[i][j] = dp[i][j] + dp[i-1][j] * fs(n-i+1, n+m-i-j+1);
                if(j == i+1)
                    ans = ans + dp[i][j]*getP(j);
            }
        if(m < n+1)ans = ans + dp[n][m] * getP(m);
        printf("%I64d/%I64d\n", ans.num, ans.den);
    }

    return 0;
}


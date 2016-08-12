/*
*	把公式化一下，c(k1,k2) = c(k1, k1-k2),然后就会发现式子变成了n个不同的小球放在m个不同的盒子中，允许为空的方案数
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
const int INF = 0x3f3f3f3f;
const int N = 100010;
const int mod = 1000000007;
LL pow_mod(LL x,LL k)
{
    LL res = 1;
    while(k)
    {
        if(k & 1) res = res * x % mod;
        x = x * x %mod;
        k >>= 1;
    }
    return res;
}
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
    int T;
    scanf("%d", &T);
    while(T--)
    {
        LL n, m;
        scanf("%I64d%I64d", &n, &m);
        printf("%I64d\n", (pow_mod(m, n+1)-1)*pow_mod(m-1, mod-2)%mod);
    }

    return 0;
}

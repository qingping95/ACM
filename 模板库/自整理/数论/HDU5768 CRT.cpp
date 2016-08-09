#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <bitset>
#include <list>
#include <climits>

using namespace std;

#define MAXN 20
typedef unsigned long long ULL;
typedef long long LL;
long long p[MAXN];
long long a[MAXN];
long long tp[MAXN] = {7};
long long ta[MAXN];

LL mul(LL a, LL b, LL c)
{
    if(a < 0) a+= c;
    if(b < 0) b+= c;
    LL ans = 0;
    while(b)
    {
        if(b&1) ans = (ans+a)%c;
        a = a*2%c;
        b >>= 1;
    }
    return ans;
}
long long extend_gcd(long long a, long long b, long long& x, long long& y)
{
    if(!b)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long r = extend_gcd(b, a%b, y, x);
    y -= x * (a / b);
    return r;
}

long long M;

long long crt(long long n, long long* a, long long* m)
{
    long long ret=0, x, y, tm, i;
    for(i=0, M=1; i<n; i++)
        M *= m[i];
    for(i=0; i<n; i++)
    {
        tm = M / m[i];
        extend_gcd(tm, m[i], x, y);
        ret = (ret + mul(a[i], mul(tm, x%M, M), M))%M;
        //ret = (ret + tm*x%M*a[i]%M)%M;
    }
    return (ret + M) % M;
}

int main()
{
    //cout<<tp[0]<<endl;
//    freopen("/home/qingping/in.txt", "r", stdin);
//    cout<<LLONG_MAX<<endl;
//    cout<<(long long)1e18<<endl;
    long long T, t, n, i, j, cnt, ans;
    long long x, y, r;
    scanf("%I64d", &T);
    for(t=1; t<=T; t++)
    {
        scanf("%I64d%I64d%I64d", &n, &x, &y);
        for(i=0; i<n; i++)
            scanf("%I64d%I64d", p+i, a+i);
        for(i=ans=0; i<(1<<n); i++)
        {
            tp[0] = 7, ta[0] = 0;
            for(j=cnt=0; j<n; j++)
            {
                if(i & (1 << j))
                {
                    tp[++cnt] = p[j];
                    ta[cnt] = a[j];
                }
            }
//            printf("cnt:%I64d\n", cnt);
            r = crt(cnt + 1, ta, tp);
            if(x < r && y < r) continue;
            long long st = (x-r)%M == 0 ? (x-r)/M :  ceil((long double)(1.0*(x-r))/M);
            long long ed = (y-r)%M == 0 ? (y-r)/M : floor((long double)(1.0*(y-r))/M);
            long long sum = max(0LL, ed - st + 1);
            ans += (cnt & 1) ? -sum : sum;
        }
        printf("Case #%I64d: %I64d\n", t, ans);
    }
    return 0;
}


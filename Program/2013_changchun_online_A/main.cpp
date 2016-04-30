#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef __int64 LL;
const int maxn = 100010;

int p[maxn], vis[maxn], num[maxn];
int gcd (int a, int b)
{
    return b==0 ? a : gcd(b, a%b);
}

int main ()
{
    freopen("F:/in.txt", "r", stdin);
    freopen("F:/out.txt", "w", stdout);
    int T;
    scanf ("%d", &T);
    for (int t=1; t<=T; t++)
    {
        int n, m, cnt = 0;
        scanf ("%d %d", &n, &m);
        for (int i=1; i<=sqrt(m); i++)
        {
            if (m % i == 0)
            {
                p[cnt ++] = i;
                if (i * i != m)
                    p[cnt ++] = m / i;
            }
        }
        sort (p, p+cnt);
        int u;
        memset (vis, 0, sizeof(vis));
        memset (num, 0, sizeof(num));
        for (int i=0; i<n; i++)
        {
            scanf ("%d", &u);
            int temp = gcd (u, m);
            for (int j=0; j<cnt; j++)
            {
                if (p[j] % temp == 0)
                    vis[j] = 1;
            }
        }
        vis[cnt-1] = 0;
        LL ans = 0;
        for (int i=0; i<cnt; i++)
        {
            if (vis[i] != num[i])
            {
                LL temp = m / p[i];
                ans += temp * (temp - 1) / 2 * p[i] * (vis[i] - num[i]);
                temp = vis[i] - num[i];
                for (int j=i; j<cnt; j++)
                    if (p[j] % p[i] == 0)
                    num[j] += temp;
            }
        }
        printf ("Case #%d: %I64d\n", t, ans);
    }
    return 0;
}

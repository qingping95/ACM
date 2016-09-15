#include <stdio.h>
#include <algorithm>

using namespace std;

int main()
{
    long long n, m, a, b, g;
    while(scanf("%I64d%I64d", &n, &m) > 0 && (n | m))
    {
        a = n * (m - 1);
        b = m * m;
        g = __gcd(a, b);
        printf("%I64d/%I64d\n", a / g, b / g);
    }
    return 0;
}



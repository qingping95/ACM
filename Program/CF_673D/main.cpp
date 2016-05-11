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
int n, k, a, b, c, d;
int getnext(int x)
{
    x++;
    while(x == a || x == b || x == c || x == d) x++;
    return x;
}
int main()
{
    //Open();
    scanf("%d%d%d%d%d%d", &n, &k, &a, &b, &c, &d);
    if(k < n+1 || n == 4) printf("-1\n");
    else{
        printf("%d", a);
        printf(" %d", c);
        for(int i = 0, idx = 0; i < n - 4; i++)
            idx = getnext(idx), printf(" %d", idx);
        printf(" %d", d);
        printf(" %d\n", b);

        printf("%d", c);
        printf(" %d", a);
        for(int i = 0, idx = 0; i < n - 4; i++)
            idx = getnext(idx), printf(" %d", idx);
        printf(" %d", b);
        printf(" %d\n", d);
    }
    return 0;
}

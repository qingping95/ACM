#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
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
        //freopen("F:/in.txt","r",stdin);
        freopen("F:/regular_in.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
PII p[22];
int main()
{
    Open();
    int T = 50;
    while(T--)
    {
        int n = rand()%21;
        n >>= 2; n <<= 2;
        //printf("%d\n", n);
        int tail = 0;
        for(int i = 0; i < n / 2; i+=2)
        {
            int x = 11 - i%11;
            x = rand()%x;
            p[tail++] = PII(i%11, i%11);
            p[tail++] = PII((i+x)%11, i%11);
            p[tail++] = PII(i%11, (i+x)%11);
            p[tail++] = PII((i+x)%11, (i+x)%11);
        }
        sort(p, p+tail);
        n = unique(p, p+tail) - p;
        printf("%d\n", n);
        for(int i = 0; i < n; i++) printf("%d %d\n", p[i].first, p[i].second);
    }
    return 0;
}

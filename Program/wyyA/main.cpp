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
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
char s[2002];
unsigned int h1[2002], h2[2002], base[2002];
inline void init_hash(char *s, unsigned int *h, int l)
{
    h[0]= 0;
    for(int i = 1; i <= l;++i)
        h[i] = h[i-1] * 123 + s[i-1];
    base[0] = 1;
    for(int i = 1; i <= l; ++i)
        base[i] = base[i-1] * 123;
}
inline unsigned int string_hash(unsigned *h, int l, int r) //[0-base)
{
    return h[r] - h[l]* base[r-l];
}
int main()
{
    //Open();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%s", s);
        int n = strlen(s);
        init_hash(s, h1, n);
        reverse(s, s+n);
        init_hash(s, h2, n);
        int ans = 0;
        for(int i = 0; i < n; i++)
            for(int j = i+1; j<=n; j++)
                ans += (string_hash(h1, i, j) == string_hash(h2, n-j, n-i));
        printf("%d\n", ans);
    }
    return 0;
}

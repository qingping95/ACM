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
const int mod = 9973;
int pow_mod(int x, int k, int mod)
{
    int res = 1;
    while(k)
    {
        if(k&1) res = res * x % mod;
        x = x * x % mod;
        k >>= 1;
    }
    return res;
}
int pre[100010];
int inv[100010];
char str[100010];
int main()
{
    //Open();
    int n;
    while(~scanf("%d", &n))
    {
        scanf("%s", str);
        pre[0] = 1;
        inv[0] = pow_mod(pre[0], mod-2, mod);
        int len = strlen(str);
        for(int i = 0; i < len; i++)
        {
            pre[i+1] = pre[i]*(str[i] - 28)%mod;
            inv[i+1] = pow_mod(pre[i+1], mod-2, mod);
        }
        for(int i = 0 ; i < n; i++)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            printf("%d\n", pre[b]*inv[a-1]%mod);
        }
    }
    return 0;
}

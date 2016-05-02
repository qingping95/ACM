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
int num[1000100];
int main()
{
    //Open();
    int n;
    scanf("%d", &n);
    int ans = 0;
    for(int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        for(int j = 1; j*j <= x; j++)
        {
            if(x % j) continue;
            num[j]++;
            if(j*j != x) num[x/j]++;
            if(num[j] >= 2) ans = max(ans, j);
        }
    }
    printf("%d\n", ans);
    return 0;
}
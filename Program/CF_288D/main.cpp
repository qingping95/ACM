#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <climits>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
ULL caln2(ULL n)
{
    if(n < 2) return 0;
    return n*(n-1)/2;
}
const int N = 100010;
ULL ans;
int n;
vector<int> G[N];
int num[N];
int dfs(int u, int fa)
{
    num[u] = 1;
    ULL C = 0;
    for(int v : G[u])
    {
        if(v == fa) continue;
        dfs(v, u);
        C += num[u] * num[v];
        num[u] += num[v];
    }
    ans -= caln2(C);
    ans -= C * num[u] * (n - num[u]);
    return num[u];
}
int main()
{
//    Open();
//    cout<<(unsigned long long)caln4(80000)*6<<endl;
    scanf("%d", &n);
    ans = caln2(caln2(n));
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0);
    cout<<ans*2<<endl;
    return 0;
}

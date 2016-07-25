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
const int N = 1000010;
int c[N];
int a[N];
bool vis[N];
int sta[N];
int main()
{
    //Open();
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    int t = 0;
    for(int i = 2; i*i <= k; i++)
    {
        int tmp = 1;
        while(k % i == 0) k /= i, tmp *= i;
        if(tmp != 1) sta[t++] = tmp;
    }
    if(k != 1) sta[t++] = k;
    sort(sta, sta+t);
    int t1 = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < t; j++)
        {
            if(a[i] % sta[j] == 0) vis[j] = 1;
        }
    }
    int num = 0;
    for(int i = 0; i < t; i++)
        num += vis[i];
    if(num == t) printf("Yes\n");
    else printf("No\n");
    return 0;
}

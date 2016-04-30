#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 100010
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
        freopen("/home/qingping/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int s[N], T[N];
int sa[N], t[N], t2[N], c[N], n;
int rank[N], height[N];
void getHeight(int *s, int n)
{
    int i, k = 0;
    for(i = 0; i < n; i++) rank[sa[i]] = i;
    for(i = 0; i < n; i++)
    {
        if(k)k--;
        int j = sa[rank[i]-1];
        while(i+k<n && j+k<n && s[i+k] == s[j+k]) k++;
        height[rank[i]] = k;
    }
}
void build_sa(int *s, int n, int m)
{
    int i, *x = t, *y = t2;
    for(i = 0; i < m; i++) c[i] = 0;
    for(i = 0; i < n; i++) c[x[i] = s[i]]++;
    for(i = 1; i < m; i++) c[i] += c[i-1];
    for(i = n-1; i>=0; i--)sa[--c[x[i]]] = i;
    for(int k = 1; k <= n; k <<= 1){
        int p = 0;
        for(i = n-k; i < n; i++) y[p++] = i;
        for(i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i]-k;
        for(i = 0; i < m; i++) c[i] = 0;
        for(i = 0; i < n; i++) c[x[y[i]]]++;
        for(i = 1; i < m; i++) c[i] += c[i-1];
        for(i = n-1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
        swap(x, y);
        p = 1; x[sa[0]] = 0;
        for(i = 1; i < n; i++)
            x[sa[i]] = (y[sa[i-1]]== y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k]) ? p-1 : p++;
        if(p >= n) break;
        m = p;
    }
}
bool check(int len, int n)
{
    for(int i = 1; i < n; i++)
    {
        while(i < n && height[i] < len) i++;
        if(i >= n) break;
        int mi = sa[i-1], ma = sa[i-1];
        while(i < n && height[i] >= len){
            mi = min(mi, sa[i]);
            ma = max(ma, sa[i]);
            i++;
        }
        if(ma - mi > len) return true;
    }
    return false;
}
int main()
{
    Open();
    while(~scanf("%d", &n), n)
    {
        for(int i = 0; i < n; i++)
            scanf("%d", &T[i]);
        for(int i = 0; i < n - 1; i++)
            s[i] = T[i+1] - T[i] + 90;
        n--;
//        s[n-1] = 0;
        build_sa(s, n, 180);
        getHeight(s, n);
        int lb = 3, ub = n, ans = 3;
        while(lb + 1 < ub)
        {
            int mid = ub + lb >> 1;
            if(check(mid, n)) lb = ans = mid;
            else ub = mid;
        }
        if(ans < 4)ans = -1;
        printf("%d\n", ans+1);
    }
    return 0;
}

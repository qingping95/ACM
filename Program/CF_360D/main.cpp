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
const int N = 1010;
int pa[N];
int col[N];
int son[N];
struct edge{
    int u, v, w, id;
    bool operator<(const edge& o)const{
        return w > o.w;
    }
}e[N*N];
inline void init(int n)
{
    for(int i = 0; i <= n; i++) pa[i] = i, col[i] = 0;
}
int find(int x, int& cx)
{
    int u = x;
    while(u != pa[u])
    {
        son[pa[u]] = u;
        u = pa[u];
    }
    int res = u, uc = col[u];
    while(u != x)
    {
        u = son[u];
        pa[u] = res;
        uc ^= col[u];
        col[u] = uc ^ col[res];
    }
    cx = uc;
    return res;
}
bool unite(int u, int v)
{
    int cu, cv;
    int fu = find(u, cu), fv = find(v, cv);
    if(fu == fv)
    {
        if(cu == cv) return false;
        return true;
    }
    pa[fu] = fv;
    if(cu != cv) col[fu] ^= col[fv];
    else {
        col[fu] ^= 1;
        col[fu] ^= col[fv];
    }
    return true;
}
int main()
{
//    Open();
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        e[i] = (edge){u, v, w, i+1};
    }
    sort(e, e+m);
    while(q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        init(n);
        bool flag = true;
        for(int i = 0; i < m; i++)
        {
            if(e[i].id >= l && e[i].id <= r){
                if(!unite(e[i].u, e[i].v))
                {
                    printf("%d\n", e[i].w);
                    flag = false;
                    break;
                }
            }
        }
        if(flag)printf("-1\n");
    }
    return 0;
}

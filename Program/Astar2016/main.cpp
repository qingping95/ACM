#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#define lson x<<1
#define rson x<<1|1
#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f3f3f3f3fLL;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const LL N = 100110;
struct node{
    LL l, r, ma, flag;
}lt[N*6];
LL V[N];//
LL s[N], t[N];//
LL Tn;//
vector<LL> G[N];//
void push_up(LL x)
{
    lt[x].ma = max(lt[lson].ma, lt[rson].ma);
}
void push_down(LL x)
{
    if(lt[x].flag != 0)
    {
        lt[lson].ma += lt[x].flag;
        lt[lson].flag += lt[x].flag;
        lt[rson].ma += lt[x].flag;
        lt[rson].flag += lt[x].flag;
        lt[x].flag = 0;
    }
}
void build(LL l, LL r, LL x)
{
    lt[x].l = l;
    lt[x].r = r;
    lt[x].flag = 0;
    lt[x].ma = 0;
    if(l == r)
    {
        return ;
    }
    build(l, mid, lson);
    build(mid+1, r, rson);
    push_up(x);
}
void update(LL l, LL r, LL val, LL x)
{
    if(lt[x].l >= l && lt[x].r <= r)
    {
        lt[x].ma += val;
        lt[x].flag += val;
        return ;
    }
    push_down(x);
    if(r <= mid) update(l, r, val, lson);
    else if(l > mid) update(l, r, val, rson);
    else update(l, mid, val, lson), update(mid+1, r, val, rson);
    push_up(x);
}
LL queryma(LL l, LL r, LL x)
{
    if(lt[x].l >= l && lt[x].r <= r)
    {
        return lt[x].ma;
    }
    push_down(x);
    LL ans;
    if(r <= mid) ans = queryma(l, r, lson);
    else if(l > mid) ans = queryma(l, r, rson);
    else ans = max(queryma(l, mid, lson), queryma(mid+1, r, rson));
    push_up(x);
    return ans;
}
void dfs(LL u, LL fa)
{
    s[u] = Tn++;
    for(LL i = 0; i < G[u].size(); i++)
    {
        LL v = G[u][i];
        if(v == fa) continue;
        dfs(v, u);
    }
    t[u] = Tn-1;
}
int main()
{
//    Open();
    LL T;
    scanf("%I64d", &T);
    LL cas = 0;
    while(T--)
    {
        LL n, m;
        scanf("%I64d%I64d", &n, &m);
        Tn = 1;
        for(int i = 0; i <= n; i++)
            G[i].clear();
        for(LL i = 1; i < n; i++)
        {
            LL u, v;
            scanf("%I64d%I64d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(0, -1);
        build(1, Tn, 1);
        for(LL i = 0; i < n; i++)
        {
            LL x;
            scanf("%I64d", &x);
            V[s[i]] = x;
            update(s[i], t[i], x, 1);
        }
        printf("Case #%I64d:\n", ++cas);
        for(LL i = 0; i < m; i++)
        {
            LL op;
            LL x, y;
            scanf("%I64d", &op);
            if(op == 0)
            {
                scanf("%I64d%I64d", &x, &y);
                //LL old = queryma(s[x], s[x], 1);
                update(s[x], t[x], y - V[s[x]], 1);
                V[s[x]] = y;
            }
            else
            {
                scanf("%I64d", &x);
                printf("%I64d\n", queryma(s[x], t[x], 1));
            }
        }
    }
    return 0;
}

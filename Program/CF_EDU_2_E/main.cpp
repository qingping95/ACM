/*
 * 题意：每个点有一种颜色，为每个点定义一个val， val[v]表示以v为根的子树中，
 * 出现次数最多的颜色集的编号和。
 *
 * 启发式合并线段树：n棵节点数为n的线段树合并n-1次，复杂度为nlogn。
 * 					某节点要用的时候再new出来，和主席树一样。
 * */
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
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const LL N = 100010;
struct node
{
    LL l, r, ma, sum, num;
    LL lch, rch;
    void update(node o)
    {
        ma = o.ma, sum = o.sum;
    }
    void update(node a, node b)
    {
        if(a.ma == b.ma) ma = a.ma, sum = a.sum + b.sum;
        else{
            if(a.ma < b.ma) swap(a, b);
            ma = a.ma, sum = a.sum;
        }
    }
}pool[N*40];
LL tot = 0;
LL createNode(LL l, LL r, LL ma, LL sum)
{
    pool[tot] = (node){l, r, ma, sum, 1, -1, -1};
    return tot++;
}
void push_up(LL rt)
{
    LL lch = pool[rt].lch, rch = pool[rt].rch;

    if(lch == -1 && rch == -1) return ;
    else if(lch == -1) pool[rt].update(pool[rch]), pool[rt].num = pool[rch].num+1;
    else if(rch == -1) pool[rt].update(pool[lch]), pool[rt].num = pool[lch].num+1;
    else pool[rt].update(pool[rch], pool[lch]), pool[rt].num = pool[lch].num + pool[rch].num + 1;
}
void unite(LL a, LL b)
{
    if(pool[a].l == pool[a].r)
    {
        pool[a].ma += pool[b].ma;
        pool[a].sum = pool[a].l;
        return ;
    }
    LL l = pool[a].l, r = pool[b].r;
    LL mid = l + r >> 1;
    if(pool[b].lch != -1)
    {
        if(pool[a].lch == -1) pool[a].lch = createNode(l, mid, 0, 0);
        unite(pool[a].lch, pool[b].lch);
    }
    if(pool[b].rch != -1)
    {
        if(pool[a].rch == -1) pool[a].rch = createNode(mid+1, r, 0, 0);
        unite(pool[a].rch, pool[b].rch);
    }
    push_up(a);
}
void update(LL x, LL idx)
{
    if(pool[x].l == idx && pool[x].r == idx)
    {
        pool[x].ma++;
        pool[x].sum = idx;
        return ;
    }
    LL l = pool[x].l, r = pool[x].r;
    LL mid = l + r >> 1;
    if(idx <= mid)
    {
        if(pool[x].lch == -1) pool[x].lch = createNode(l, mid, 0, 0);
        update(pool[x].lch, idx);
    }
    else
    {
        if(pool[x].rch == -1) pool[x].rch = createNode(mid+1, r, 0, 0);
        update(pool[x].rch, idx);
    }
    push_up(x);
}
LL n;
vector<LL> G[N];
LL color[N];
LL root[N];
LL ans[N];
void dfs(LL u, LL fa)
{
    root[u] = createNode(1, n, 0, 0);
    for(LL i = 0; i < G[u].size(); i++)
    {
        LL v = G[u][i];
        if(v == fa) continue;
        dfs(v, u);
        if(pool[root[u]].num < pool[root[v]].num) swap(root[u], root[v]);
        unite(root[u], root[v]);
    }
    update(root[u], color[u]);
    ans[u] = pool[root[u]].sum;
}
int main()
{
//    Open();
    scanf("%I64d", &n);
    for(LL i = 1; i <= n; i++) scanf("%I64d", &color[i]);
    for(LL i = 1; i < n; i++)
    {
        LL u, v;scanf("%I64d%I64d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0);
    for(LL i = 1; i <= n; i++)
        printf("%I64d%c", ans[i], " \n"[i == n]);
    return 0;
}

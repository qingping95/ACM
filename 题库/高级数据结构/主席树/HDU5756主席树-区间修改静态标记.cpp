#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
#include <assert.h>
//#define ls (x<<1)
//#define rs (x<<1|1)
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
//        freopen("/home/qingping/in.txt","r",stdin);
//        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 50010;
vector<int> G[N];//
set<PII> S;//
set<PII>::iterator it1, it2, it;//
int dep[N], st[N], ed[N], id[N];//
int Tn, T[N];//
struct node{
    int l, r, ma, mi, sum, fg, ls, rs;
    node(int l = 0, int r = 0, int val = 0){
        this -> l = l, this -> r = r;
        fg = 0;
        ma = mi = sum = val;
        ls = rs = -1;
    }
    inline int len()
    {
        return r-l+1;
    }
    void update(int x)
    {
        ma += x;
        mi += x;
        sum += x*len();
        fg += x;
    }
    int res(int ty, int add)
    {
        if(ty == 0) return sum+add*len();
        if(ty == 1) return mi+add;
        if(ty == 2) return ma+add;
    }
}lt[N*50];
int tot;
void push_up(int rt)
{
    int ls = lt[rt].ls, rs = lt[rt].rs;
    lt[rt].ma = max(lt[ls].ma, lt[rs].ma) + lt[rt].fg;
    lt[rt].mi = min(lt[ls].mi, lt[rs].mi) + lt[rt].fg;
    lt[rt].sum = lt[ls].sum+lt[rs].sum + lt[rt].fg*lt[rt].len();
}
int build(int l, int r)
{
    int nr = tot++;
    lt[nr] = node(l, r);
    if(l == r)
    {
        lt[nr] = node(l, r, dep[id[l]]);
        return nr;
    }
    int mid = l + r >> 1;
    lt[nr].ls = build(l, mid);
    lt[nr].rs = build(mid+1, r);
    push_up(nr);
    return nr;
}


int update(int rt, int l, int r, int val)
{
    int nr = tot++;
    lt[nr] = lt[rt];
    if(l <= lt[rt].l && r >= lt[rt].r)
    {
        lt[nr].update(val);
        return nr;
    }
    //push_down(rt);
    //lt[nr] = lt[rt];
    int mid = lt[rt].l + lt[rt].r >> 1;
    if(r <= mid) lt[nr].ls = update(lt[rt].ls, l, r, val);
    else if(l > mid) lt[nr].rs = update(lt[rt].rs, l, r, val);
    else lt[nr].ls = update(lt[rt].ls, l, mid, val), lt[nr].rs = update(lt[rt].rs, mid+1, r, val);
    push_up(nr);
    return nr;
}
int res(int v1, int v2, int ty)
{
    if(v1 == -1) return v2;
    if(v2 == -1) return v1;
    if(ty == 0) return v1 + v2;
    if(ty == 1) return min(v1, v2);
    if(ty == 2) return max(v1, v2);
}
int query(int rt, int l, int r, int ty, int fg)
{
    if(l <= lt[rt].l && r >= lt[rt].r)
    {
        return lt[rt].res(ty, fg);
    }
//    push_down(rt);
    int mid = lt[rt].l + lt[rt].r >> 1;
    if(r <= mid) return query(lt[rt].ls, l, r, ty, fg+lt[rt].fg);
    else if(l > mid) return query(lt[rt].rs, l, r, ty, fg+lt[rt].fg);
    else return res(query(lt[rt].ls, l, mid, ty, fg+lt[rt].fg), query(lt[rt].rs, mid+1, r, ty, fg+lt[rt].fg), ty);
}
void dfs(int u, int fa, int d)
{
    dep[u] = d;
    st[u] = ++ Tn;
    id[Tn] = u;
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(v == fa) continue;
        dfs(v, u, d+1);
    }
    ed[u] = Tn;
}
void dfsSeg(int u, int fa)
{
    if(fa == -1) T[u] = build(1, Tn);
    else
    {
        T[u] = update(T[fa], st[u], ed[u], -2);
        T[u] = update(T[u], 1, Tn, 1);
    }
    assert(tot < N*40);
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(v == fa) continue;
        dfsSeg(v, u);
    }
}
int main()
{
//    Open();
    int n, q;
    int cas = 0;
    while(~scanf("%d%d", &n,&q))
    {
        cas++;
        Tn = 0;
        tot = 0;
        for(int i = 0; i <= n; i++) G[i].clear();
        for(int i = 1; i < n; i++)
        {
            int u, v;
            scanf("%d%d", &u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1, -1, 0);
        dfsSeg(1, -1);

        int last = 0;
        while(q--)
        {
            int k, p, t;
            scanf("%d%d%d", &k, &p, &t);
            t--;
            S.clear();
            p += last;
            p = p%n+1;
            for(int i = 0; i < k; i++)
            {
                int x;
                scanf("%d", &x);
                bool flag = true;
                it = it1 = S.upper_bound(PII(st[x], 0));
                it2 = S.upper_bound(PII(ed[x], 0));
                if(it != S.begin()) it--;
                else flag = false;
                S.erase(it1, it2);
                if(!flag || !(it->first <= st[x] && it -> second >= ed[x]))
                    S.emplace(st[x], ed[x]);
            }
            int pre = 1;
            int ans = -1;
            for(it1 = S.begin(); it1 != S.end(); it1++)
            {
                int l = it1->first;
                if(pre < l) ans = res(ans, query(T[p], pre, l-1, t, 0), t);//, printf("%d, %d\n", pre, l-1);
                pre = it1->second + 1;
            }
            if(pre <= Tn) ans = res(ans, query(T[p], pre, Tn, t, 0), t);//, printf("%d, %d\n", pre, Tn);
            printf("%d\n", ans);
            last = max(ans, 0);
        }
    }
    return 0;
}


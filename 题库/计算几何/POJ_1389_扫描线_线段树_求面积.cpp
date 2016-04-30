#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 10100
#define lson x<<1
#define rson x<<1|1
#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
double sty[N];
struct Node{
    LL l, r;
    LL st, ed, sum;
    LL lazy;
    Node(){}
    Node(LL _l, LL _r, LL _s ,LL _e){
        l = _l, r = _r, st = _s, ed = _e, lazy = sum = 0;
    }
    LL len()
    {
        return ed - st;
    }
}lt[N*6];
void push_up(LL x)
{
    if(lt[x].lazy > 0) lt[x].sum = lt[x].len();
    else if(lt[x].l == lt[x].r) lt[x].sum = 0;
    else lt[x].sum = lt[lson].sum + lt[rson].sum;
}
void build(LL l, LL r, LL x)
{
    lt[x] = Node(l, r, sty[l], sty[r]);
    if(l == r) return ;
    if(mid != r)build(l, mid, lson);
    if(mid != l)build(mid, r, rson);
}
void update(LL l, LL r, LL x, LL val)
{
    if(lt[x].l >= l && lt[x].r <= r)
    {
        lt[x].lazy += val;
        push_up(x);
        return;
    }
    if(r <= mid) update(l, r, lson, val);
    else if(l >= mid) update(l, r, rson, val);
    else update(l, mid, lson, val), update(mid, r, rson, val);
    push_up(x);
}
struct Rec{
    LL x, y1, y2;
    LL ly1, ly2, val;
    Rec(){}
    Rec(LL _x, LL _y1, LL _y2, LL v){
        x = _x, y1 = _y1, y2 = _y2, val = v;
    }
    bool operator<(const Rec& o)const{
        return x < o.x;
    }
}r[N];
int main()
{
//    Open();
    LL cas = 1;
    LL x1, y1, x2, y2;
    while(~scanf("%I64d%I64d%I64d%I64d", &x1, &y1, &x2, &y2), x1 != -1)
    {
        LL n = 0;
        LL tx = 0, ty = 0;
        r[n*2] = Rec(x1, y1, y2, 1);
        r[n*2+1] = Rec(x2, y1, y2, -1);
        sty[ty++] = y1, sty[ty++] = y2;
        n++;
        while(~scanf("%I64d%I64d%I64d%I64d", &x1, &y1, &x2, &y2), x1 != -1)
        {
            r[n*2] = Rec(x1, y1, y2, 1);
            r[n*2+1] = Rec(x2, y1, y2, -1);
            sty[ty++] = y1, sty[ty++] = y2;
            n++;
        }
        sort(r, r+2*n);
        sort(sty, sty+ty);
        build(0, ty-1, 1);
        LL ans = 0;
        for(LL i = 0; i < 2*n; i++)
        {
            r[i].ly1 = lower_bound(sty, sty+ty, r[i].y1) - sty;
            r[i].ly2 = lower_bound(sty, sty+ty, r[i].y2) - sty;
        }
        update(r[0].ly1, r[0].ly2, 1, r[0].val);
        for(LL i = 1; i < 2 * n; i++)
        {
            ans += lt[1].sum * (r[i].x - r[i-1].x);
            update(r[i].ly1, r[i].ly2, 1, r[i].val);
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
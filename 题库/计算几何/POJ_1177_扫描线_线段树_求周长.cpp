#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 20000
#define lson x<<1
#define rson x<<1|1
#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int sty[N], stx[N];
struct Node{
    int l, r;
    int tl, tr, sum;//tl,tr表示是否顶满左(右)区间
    int lazy;
    Node(){}
    Node(int _l, int _r){
        l = _l, r = _r, tl = tr = 0, lazy = sum = 0;
    }
}lt[N*6];
void push_up(int x)
{
    if(lt[x].lazy > 0) lt[x].sum = 2, lt[x].tl = lt[x].tr = 1;
    else if(lt[x].l == lt[x].r) lt[x].sum = 0;
    else {
        lt[x].sum = lt[lson].sum + lt[rson].sum;
        lt[x].tl = lt[lson].tl, lt[x].tr = lt[rson].tr;
        if(lt[lson].tr && lt[rson].tl) lt[x].sum -= 2;
    }
}
void build(int l, int r, int x)
{
    lt[x] = Node(l, r);
    if(l == r) return ;
    if(mid != r)build(l, mid, lson);
    if(mid != l)build(mid, r, rson);
}
void update(int l, int r, int x, int val)
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
    int x, y1, y2;
    int ly1, ly2, val;
    Rec(){}
    Rec(int _x, int _y1, int _y2, int v){
        x = _x, y1 = _y1, y2 = _y2, val = v;
    }
    bool operator<(const Rec& o)const{
        return x < o.x;
    }
}rx[N], ry[N];
int main()
{
//    Open();
    int cas = 1;
    int n;
    while(~scanf("%d", &n))
    {
        int tx = 0, ty = 0;
        for(int i = 0; i < n; i++)
        {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            rx[i*2] = Rec(x1, y1, y2, 1);
            rx[i*2+1] = Rec(x2, y1, y2, -1);
            ry[i*2] = Rec(y1, x1, x2, 1);
            ry[i*2+1] = Rec(y2, x1, x2, -1);
            sty[ty++] = y1, sty[ty++] = y2;
            stx[tx++] = x1, stx[tx++] = x2;
        }
        sort(rx, rx+2*n);
        sort(ry, ry+2*n);
        sort(sty, sty+ty);
        sort(stx, stx+tx);
        build(0, ty-1, 1);
        int ans = 0;
        for(int i = 0; i < 2*n; i++)
        {
            rx[i].ly1 = lower_bound(sty, sty+ty, rx[i].y1) - sty;
            rx[i].ly2 = lower_bound(sty, sty+ty, rx[i].y2) - sty;
            ry[i].ly1 = lower_bound(stx, stx+tx, ry[i].y1) - stx;
            ry[i].ly2 = lower_bound(stx, stx+tx, ry[i].y2) - stx;
        }
        update(rx[0].ly1, rx[0].ly2, 1, rx[0].val);
        for(int i = 1; i < 2 * n; i++)
        {
            ans += lt[1].sum * (rx[i].x - rx[i-1].x);
            update(rx[i].ly1, rx[i].ly2, 1, rx[i].val);
        }
        build(0, tx-1, 1);
        update(ry[0].ly1, ry[0].ly2, 1, ry[0].val);
        for(int i = 1; i < 2 * n; i++){
            ans += lt[1].sum * (ry[i].x - ry[i-1].x);
            update(ry[i].ly1, ry[i].ly2, 1, ry[i].val);
        }
        printf("%d\n", ans);
    }
    return 0;
}
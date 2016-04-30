#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 1010
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
double sty[N];
struct Node{
    int l, r;
    double st, ed, sum;
    int lazy;
    Node(){}
    Node(int _l, int _r, double _s ,double _e){
        l = _l, r = _r, st = _s, ed = _e, lazy = sum = 0;
    }
    double len()
    {
        return ed - st;
    }
}lt[N*6];
void push_up(int x)
{
    if(lt[x].lazy > 0) lt[x].sum = lt[x].len();
    else if(lt[x].l == lt[x].r) lt[x].sum = 0;
    else lt[x].sum = lt[lson].sum + lt[rson].sum;
}
void build(int l, int r, int x)
{
    lt[x] = Node(l, r, sty[l], sty[r]);
    if(l == r) return ;
    if(mid != r)build(l, mid, lson);//线段树中存储线段，于是这里l,mid表示开始和结束，右区间不能是mid+1，不然会丢失一段区间
    if(mid != l)build(mid, r, rson);//
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
    double x, y1, y2;
    int ly1, ly2, val;
    Rec(){}
    Rec(double _x, double _y1, double _y2, int v){
        x = _x, y1 = _y1, y2 = _y2, val = v;
    }
    bool operator<(const Rec& o)const{
        return x < o.x;
    }
}r[N];
int main()
{
//    Open();
    int cas = 1;
    int n;
    while(~scanf("%d", &n), n)
    {
        int tx = 0, ty = 0;
        for(int i = 0; i < n; i++)
        {
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            r[i*2] = Rec(x1, y1, y2, 1);
            r[i*2+1] = Rec(x2, y1, y2, -1);
            sty[ty++] = y1, sty[ty++] = y2;
        }
        sort(r, r+2*n);
        sort(sty, sty+ty);
        build(0, ty-1, 1);
        double ans = 0;
        for(int i = 0; i < 2*n; i++)
        {
            r[i].ly1 = lower_bound(sty, sty+ty, r[i].y1) - sty;
            r[i].ly2 = lower_bound(sty, sty+ty, r[i].y2) - sty;
        }
        update(r[0].ly1, r[0].ly2, 1, r[0].val);
        for(int i = 1; i < 2 * n; i++)
        {
            ans += lt[1].sum * (r[i].x - r[i-1].x);
            update(r[i].ly1, r[i].ly2, 1, r[i].val);
        }
        printf("Test case #%d\n", cas++);
        printf("Total explored area: %.2f\n\n", ans);
    }
    return 0;
}
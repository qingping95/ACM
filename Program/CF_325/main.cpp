#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 111
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
int sty[N];
struct Node{
    int l, r;
    int st, ed, sum;
    int lazy;
    Node(){}
    Node(int _l, int _r, int _s ,int _e){
        l = _l, r = _r, st = _s, ed = _e, lazy = sum = 0;
    }
    int len()
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
    int id;
    Rec(){}
    Rec(int _x, int _y1, int _y2, int v, int i){
        x = _x, y1 = _y1, y2 = _y2, val = v, id = i;
    }
    bool operator<(const Rec& o)const{
        return x < o.x;
    }
}r[N*2];
bool vis[N];
inline long long Scan()     //ÊäÈëÍâ¹Ò
{
    long long res=0,ch,flag=0;
    if((ch=getchar())=='-')
        flag=1;
    else if(ch>='0'&&ch<='9')
        res=ch-'0';
    while((ch=getchar())>='0'&&ch<='9')
        res=res*10+ch-'0';
    return flag?-res:res;
}
int main()
{
//    Open();
    int cas = 1;
    int n, q;
    while(n = Scan(), q = Scan(), n||q)
    {
        int tx = 0, ty = 0;
        for(int i = 0; i < n; i++)
        {
            int x1, y1, x2, y2;
            x1 = Scan();
            y1 = Scan();
            x2 = Scan();
            y2 = Scan();
//            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            r[i*2] = Rec(x1, y1, y2, 1, i);
            r[i*2+1] = Rec(x2, y1, y2, -1, i);
            sty[ty++] = y1, sty[ty++] = y2;
        }
        sort(r, r+2*n);
        sort(sty, sty+ty);
        ty = unique(sty, sty+ty) - sty;
        for(int i = 0; i < 2*n; i++)
        {
            r[i].ly1 = lower_bound(sty, sty+ty, r[i].y1) - sty;
            r[i].ly2 = lower_bound(sty, sty+ty, r[i].y2) - sty;
        }
        build(0, ty-1, 1);
        printf("Case %d:\n", cas++);
        int qcas = 1;
        while(q--)
        {
            int num = Scan();
//            scanf("%d", &num);
            memset(vis, 0, sizeof(vis));
            for(int i = 0; i < num ; i++)
            {
                int tmp = Scan();
//                scanf("%d", &tmp);
                vis[tmp-1] = 1;
            }
            int ans = 0;
            int cnt = 0;
            while(cnt < 2 * n && vis[r[cnt].id] == 0) cnt++;
            if(cnt < 2 * n) update(r[cnt].ly1, r[cnt].ly2, 1, r[cnt].val);
            int pre = cnt;
            for(int i = cnt+1; i < 2 * n; i++)
            {
                if(vis[r[i].id] == 0) continue;
                ans += lt[1].sum * (r[i].x - r[pre].x);
                update(r[i].ly1, r[i].ly2, 1, r[i].val);
                pre = i;
            }
            printf("Query %d: %d\n", qcas++, ans);
        }
        printf("\n");
    }
    return 0;
}

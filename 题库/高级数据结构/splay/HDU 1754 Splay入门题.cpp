#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 200010
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int a[N];
int n, m;
struct Splay
{
    int mx[N];//存储以该节点为根的子树中的最大值
    int sz[N];//存储以该结点为根的子树中的节点数
    int pre[N], ch[N][2];//该节点的儿子和父亲
    int val[N];
    int tot, root;//tot总共有多少个节点，root根节点的编号

    void init()
    {
        tot = root = 0;
    }
    int newnode(int fa, int v)
    {
        int k = ++tot;
        ch[k][0] = ch[k][1] = 0;
        pre[k] = fa;
        mx[k] = v;
        val[k] = v;
        sz[k] = 1;
        return k;
    }
    void push_up(int x)
    {
        mx[x] = max(mx[ch[x][0]], mx[ch[x][1]]);
        mx[x] = max(mx[x], val[x]);
        sz[x] = sz[ch[x][1]] + sz[ch[x][0]] + 1;
    }
    void rotate(int x)
    {
        int y = pre[x], d = (ch[y][1] == x);
		//push_down(y);push_down(x);
        ch[y][d] = ch[x][!d];
        if(ch[x][!d]) pre[ch[x][!d]] = y;
        ch[x][!d] = y;
        pre[x] = pre[y];
        pre[y] = x;
        if(pre[x]) ch[pre[x]][ch[pre[x]][1] == y] = x;
        push_up(y);
        push_up(x);
    }
    void splay(int x, int goal)//将x旋转到goal的下面
    {
        while(pre[x] != goal)
        {
            int f = pre[x], ff = pre[f];
            if(ff == goal) rotate(x);
            else if((ch[ff][1] == f) == (ch[f][1] == x))
                rotate(f), rotate(x);
            else
                rotate(x), rotate(x);
        }
        push_up(x);
        if(goal == 0) root = x;//根的父亲为null
    }
    int kth(int k)//寻找splay中的第k大的节点
    {
        int x = root;
        while(x)
        {
            if(sz[ch[x][0]] >= k) x = ch[x][0];
            else {
                k -= sz[ch[x][0]] + 1;
                if(k == 0) return x;
                x = ch[x][1];
            }
        }
        return x;
    }
    int build(int l, int r, int fa)
    {
        if(l > r) return 0;
        int mid = l + r >> 1;
        int k = newnode(fa, a[mid]);
        ch[k][0] = build(l, mid-1, k);
        ch[k][1] = build(mid+1, r, k);
        push_up(k);
        return k;
    }
}spl;
int op[11];
int main()
{
    Open();
    while(~scanf("%d%d", &n, &m))
    {
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        a[0] = a[n+1] = -INF;
        spl.init();
        spl.root = spl.build(0, n+1, 0);
        while(m--)
        {
            scanf("%s", op);
            if(op[0] == 'Q'){
                int x, y;
                scanf("%d%d", &x, &y);
                spl.splay(spl.kth(x), 0);
                spl.splay(spl.kth(y+2), spl.root);
                int idx = spl.ch[spl.root][1];
                idx = spl.ch[idx][0];
                printf("%d\n", spl.mx[idx]);
            }else {
                int x, v;
                scanf("%d%d", &x, &v);
//                spl.splay(spl.kth(x), 0);
//                spl.splay(spl.kth(x+2), spl.root);
//                int y = spl.ch[spl.root][1];
//                spl.ch[y][0] = spl.newnode(y, v);
//                spl.push_up(y);
//                spl.push_up(spl.root);
                int idx = spl.kth(x+1);
                spl.splay(idx, 0);
                spl.val[idx] = v;
                spl.push_up(idx);
            }
        }
    }
    return 0;
}
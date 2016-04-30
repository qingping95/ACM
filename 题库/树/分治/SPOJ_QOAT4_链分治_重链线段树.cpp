/*
* SPOJ Query on a tree IV
* 
* 据说这是query on a tree 1~5 中最繁琐的一道题，的确是这样！
* 
* 解法来自：分治算法在树的路径问题中的应用--漆子超
* 我将论文中我觉得没说清楚的地方说一下。
* 此题首先需要将原树轻重链剖分，然后为每一条重链都维护一棵线段树，两条重链间由一条轻边链接。
* 每条重链上需要维护这样的信息：maxl, maxr, opt; opt 就是在这条链上的答案。
* 首先对每一个点处理出这样一个量D[i], D2[i],表示这个节点向下至某个白色结点的路径中长度的最大值和次大值(路
* 径中不包含同重链的点，如果没有白色节点不存在，长度记为-INF)
* 那么线段树的某个区间[l, r]的opt的含义就是d[i]+dist[i,j]+d[j],i,j都在区间中，dist[i,j]表示第i个节点到第j
* 个节点的距离；而maxl，maxr是用来维护opt的量，maxl表示一条左端点在该区间内且还可以向左延伸，右端点为一个
* 白色节点的路径的最大长度；maxr相反。那么由这两个量父亲节点的opt可以得到维护(opt[fa] = maxr[lc]+maxl[rc]+dist[mid, mid+1])
* 于是，整棵树就被若干棵线段树得以维护。最终答案只需要用一个堆存储所有线段树的opt值即可。
* 但是其中还有一个特别重要的d[]和d2[]数组，这两个数组的维护在论文里面写的比较清楚，这里就不说了。大概就是
* 每个节点开一个堆，用来记录所有可能的d值，然后就能o(1)取出来了。
* 对于修改操作，由于一个节点到根的路径上不超过log条轻边，那么需要修改的线段树也不超过log个，修改线段树log
* 
* 复杂度为O(Qlog(n)^2)
* 
* 当然这其中包含众多下标处理...首先每条重链都有一个线段树，不可能每颗线段树都开一个数组，所以开了一个节点池
* 每个区间记录儿子所在的下标，总的节点数不超过6*N个。这里需要知道每个节点对应那颗线段树，反过来也需要知道
* 每颗线段树上的节点对应原树上的那个节点。这里的处理方法是利用重儿子将原树节点重新排列，记录每个线段树根节点
* 的下标，并记录线段树起始节点的偏移量，那么根据这些信息即可查找与反找。每个数组的意义代码中有详细注释。上面
* 的dist值也可以利用这个来维护。
*/
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
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int MAXN = 100010;
int top[MAXN];//top[v]表示v所在的重链的顶端节点
int fa[MAXN]; //父亲节点
int deep[MAXN];//深度
int sz[MAXN];//sz[v]表示以v为根的子树的节点数
int p[MAXN];//p[v]表示v与其父亲节点的连边在线段树中的位置
int fp[MAXN];//和p数组相反
int son[MAXN];//重儿子
int col[MAXN];//颜色
int val[MAXN];
int pos;
priority_queue<PII > que[N], ansque;//que:存储D(i)
struct Edge
{
    int to, w, nxt;
    Edge(){}
    Edge(int _t, int _w, int _next){
        to = _t, w = _w, nxt = _next;
    }
}e[MAXN*2];
int head[MAXN],tot;
void addedge(int u,int v, int w)
{
    e[tot] = Edge(v, w, head[u]);
    head[u] = tot++;
}

//-------segment Tree--------//
struct node{
    int l, r, maxl, maxr, opt;
    int ch[2];
    node(){}
    node(int _l, int _r, int _ml, int _mr, int _op){
        l = _l, r = _r, maxl = _ml, maxr = _mr, opt = _op;
        ch[0] = ch[1] = 0;
    }
}lt[N*8];
int nodenum = 0;
int root[N];//root[i]表示节点i(head)所在的重链表示的线段树在pool中的位置
int pn[N];//类似DFS序，相当于将节点重排，将同一条重链上的节点放到一起
int idx[N];//idx[i]表示节点i在他所在的重链线段树上的rank
int num[N];//num[i]表示节点i(head)所在的重链有多少个节点
int dis[N];//dis[i]表示节点i到对应线段树最左节点的距离
int sonw[N];

void dfs1(int u,int pre,int d) //第一遍dfs求出fa,deep,sz,son,val
{
    deep[u] = d;
    fa[u] = pre;
    sz[u] = 1;
    for(int i = head[u];i != -1; i = e[i].nxt)
    {
        int v = e[i].to;
        if(v != pre)
        {
            val[v] = e[i].w;
            dfs1(v,u,d+1);
            sz[u] += sz[v];
            if(son[u] == -1 || sz[v] > sz[son[u]])
                son[u] = v, sonw[u] = val[v];
        }
    }
}
int Tn;
int fpn[N];
void getpos(int u,int sp, int dist) //第二遍dfs求出top和p,num;
{
    pn[++Tn] = u;
    fpn[u] = Tn;
    dis[Tn] = dist;
    top[u] = sp;
    num[sp]++;
    if(son[u] != -1)
    {
        p[u] = pos++;
        fp[p[u]] = u;
        getpos(son[u],sp, dist + sonw[u]);
    }
    else
    {
        p[u] = pos++;
        fp[p[u]] = u;
        return;
    }
    for(int i = head[u] ; i != -1; i = e[i].nxt)
    {
        int v = e[i].to;
        if(v != son[u] && v != fa[u])
            getpos(v,v, 0);
    }
}

int add(int a, int b)
{
    if(a == -INF || b == -INF) return -INF;
    return a + b;
}
void push_up(int off, int rt)
{
    int lc = lt[rt].ch[0], rc = lt[rt].ch[1];
    int mid = lt[rt].l + lt[rt].r >> 1;
    lt[rt].maxl = max(lt[lc].maxl, add(lt[rc].maxl,  dis[off + mid + 1] - dis[off + lt[rt].l]));
    lt[rt].maxr = max(lt[rc].maxr, add(lt[lc].maxr,  dis[off + lt[rt].r] - dis[off + mid]));
    lt[rt].opt = max(lt[lc].opt, max(lt[rc].opt, add(add(lt[lc].maxr, lt[rc].maxl), dis[off + mid + 1] - dis[off + mid])));
}
int build(int l, int r){
    int rt = nodenum++;
    lt[rt] = node(l, r, -INF, -INF, -INF);
    if(l == r) return rt;
    int mid = l + r >> 1;
    lt[rt].ch[0] = build(l, mid);
    lt[rt].ch[1] = build(mid+1, r);
    return rt;
}
void update(int id, int x, int off, bool isrt)
{
    if(lt[x].l == id && lt[x].r == id)
    {
        int u = pn[off + id];
        int d = -INF, sond = -1, d2 = -INF;
        while(!que[u].empty())
        {
            PII pp = que[u].top();que[u].pop();
            int v = pp.second, w = pp.first;
            if(lt[root[v]].maxl + val[v] != w) continue;
            d = w;sond = v;
            break;
        }
        while(!que[u].empty()){
            PII pp = que[u].top();
            int v = pp.second, w = pp.first;
            if(v == sond || lt[root[v]].maxl + val[v] != w) {que[u].pop();continue;}
            d2 = w;
            break;
        }
        if(sond != -1) que[u].push(PII(d, sond));
        if(!col[u]) d = max(d, 0);
        if(col[u]){
            lt[x].maxl = lt[x].maxr = d;
            lt[x].opt = add(d, d2);
        }else{
            d = max(d, 0);
            lt[x].maxl = lt[x].maxr = d;
            lt[x].opt = max(d, add(d, d2));
        }
        if(isrt && lt[x].opt != -INF) ansque.push(PII(lt[x].opt, x));
        return ;
    }
    int mid = lt[x].l + lt[x].r >> 1;
    if(id <= mid) update(id, lt[x].ch[0], off, false);
    else update(id, lt[x].ch[1], off, false);
    push_up(off, x);
    if(isrt && lt[x].opt != -INF) ansque.push(PII(lt[x].opt, x));
}
int dfsFire(int u, int p, int id)
{
    idx[u] = id;
    if(id == 1) root[u] = build(1, num[u]);
    int w;
    for(int i = head[u]; ~i; i = e[i].nxt)
    {
        int v = e[i].to;
        if(v == p) continue;
        if(v == son[u]) {w = e[i].w;continue;}
        dfsFire(v, u, 1);
        que[u].push(PII(lt[root[v]].maxl+val[v], v));
    }
    update(idx[u], root[top[u]], fpn[top[u]]-1, true);
    if(son[u] != -1) dfsFire(son[u], u, id+1);
}

void init(int n)
{
    tot = 0;
    memset(head,-1,sizeof(head));
    pos = 0;
    Tn = 0;
    nodenum = 0;
    memset(son,-1,sizeof(son));
    memset(num, 0,sizeof(num));
    memset(col, 0, sizeof(col));
    while(!ansque.empty()) ansque.pop();
    for(int i = 0; i <= n; i++)
        while(!que[i].empty()) que[i].pop();
}

int main()
{
//    Open();
    int n;
    while(~scanf("%d", &n))
    {
        init(n);
        for(int i = 1; i < n; i++)
        {
            int u, v, w;scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w);
            addedge(v, u, w);
        }
        int res = n;
        dfs1(1, 0, 0);
        getpos(1, 1, 0);
        dfsFire(1, 0, 1);
        int q;scanf("%d", &q);
        while(q--)
        {
            char op[33];
            scanf("%s", op);
            if(op[0] == 'A'){
                if(res == 0){
                    puts("They have disappeared.");
                    while(!ansque.empty()) ansque.pop();
                }else if(res == 1){
                    puts("0");
                    while(!ansque.empty()) ansque.pop();
                }else{
                    bool flag = true;
                    while(!ansque.empty()){
                        PII pp = ansque.top();
                        int x = pp.second, w = pp.first;
                        if(lt[x].opt != w){
                            ansque.pop();
                            continue;
                        }
                        flag = false;
                        printf("%d\n", w);
                        break;
                    }
                    if(flag){
                        puts("They have disappeared.");
                    }
                }
            }else{
                int u;scanf("%d", &u);
                col[u] ^= 1;
                if(col[u]) res--;
                else res++;
                while(u){
                    int tp = top[u];
                    update(idx[u], root[tp], fpn[tp]-1, true);
                    if(lt[root[tp]].maxl != -INF)
                        que[fa[tp]].push(PII(lt[root[tp]].maxl + val[tp], tp));
                    u = fa[tp];
                }
            }
        }
    }
    return 0;
}
/*
5
1 2 1
1 3 2
3 4 -3
3 5 4
21
A
C 1
A
C 2
A
C 3
A
C 4
A
C 5
A
C 5
A
C 4
A
C 3
A
C 1
A
C 2
A

10
1 2 1
1 3 2
2 4 3
2 5 -8
2 6 -2
3 7 3
3 8 -2
3 9 6
3 10 10
21
A
C 1
A
C 2
A
C 3
A
C 4
A
C 5
A
C 6
A
C 7
A
C 8
A
C 9
A
C 10
A

7
1 2 1
1 3 2
2 4 3
2 5 4
3 6 5
3 7 6
15
A
C 1
A
C 2
A
C 3
A
C 4
A
C 5
A
C 6
A
C 7
A


5
1 2 1
1 3 2
3 4 3
3 5 4
11
A
C 1
A
C 2
A
C 3
A
C 4
A
C 5
A
*/
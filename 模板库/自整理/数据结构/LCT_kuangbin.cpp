//BZOJ_3669_维护最小生成树
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
struct edge{
    int u, v, a, b;
    edge(){}
    edge(int _u, int _v, int _a, int _b){
        u = _u, v = _v, a = _a, b = _b;
    }
    bool operator<(const edge& o) const{
        return a < o.a;
    }
}e[N];
int n, m;
int pa[N];
int find(int x)
{
    return pa[x] == x ? x : pa[x] = find(pa[x]);
}
void unite(int u, int v)
{
    u = find(u), v = find(v);
    if(u == v) return ;
    pa[u] = v;
}
struct LCT{
    int ch[N][2],pre[N], rev[N];//rev这个数组是不能去掉的
    int ma[N], maid[N];
    bool rt[N];
	void Treaval(int x) {
        if(x) {
            Treaval(ch[x][0]);
            printf("结点%2d:左儿子 %2d 右儿子 %2d 父结点 %2d size = %2d ,key = %2d \n",x, ch[x][0], ch[x][1], pre[x], sz[x], sum[x]);
            Treaval(ch[x][1]);
        }
    }
    void Update_Add(int r,int d)
    {
//        if(!r)return;
//        key[r] += d;
//        add[r] += d;
//        Max[r] += d;
    }
    void Update_Rev(int r)
    {
        if(!r)return;
        swap(ch[r][0],ch[r][1]);
        rev[r] ^= 1;
    }
    void push_down(int r)
    {
//        if(add[r])
//        {
//            Update_Add(ch[r][0],add[r]);
//            Update_Add(ch[r][1],add[r]);
//            add[r] = 0;
//        }
        if(rev[r])
        {
            Update_Rev(ch[r][0]);
            Update_Rev(ch[r][1]);
            rev[r] = 0;
        }
    }
    void push_up(int r)
    {
        maid[r] = r;
        if(ma[maid[r]] < ma[maid[ch[r][0]]]) maid[r] = maid[ch[r][0]];
        if(ma[maid[r]] < ma[maid[ch[r][1]]]) maid[r] = maid[ch[r][1]];
//        Max[r] = max(max(Max[ch[r][0]],Max[ch[r][1]]),key[r]);
    }
    void init(int n, int m)
    {
        for(int i = 1; i <= n; i++)
            rev[i] = pre[i] = ch[i][0] = ch[i][1] = 0, rt[i] = true, ma[i] = 0, maid[i] = i;
        for(int i = 1; i <= m; i++)
        {
            int id = i + n;
            rev[id] = pre[id] = ch[id][0] = ch[id][1] = 0;
            rt[id] = true;
            ma[id] = e[i].b;
            maid[id] = id;
        }
    }
    void Rotate(int x)
    {
        int y = pre[x], kind = ch[y][1]==x;
        ch[y][kind] = ch[x][!kind];
        pre[ch[y][kind]] = y;
        pre[x] = pre[y];
        pre[y] = x;
        ch[x][!kind] = y;
        if(rt[y])
            rt[y] = false, rt[x] = true;
        else
            ch[pre[x]][ch[pre[x]][1]==y] = x;
        push_up(y);
    }
    //P函数先将根结点到r的路径上所有的结点的标记逐级下放
    void P(int r)
    {
        if(!rt[r])P(pre[r]);
        push_down(r);
    }
    void Splay(int r)
    {
        P(r);
        while( !rt[r] )
        {
            int f = pre[r], ff = pre[f];
            if(rt[f])
                Rotate(r);
            else if( (ch[ff][1]==f)==(ch[f][1]==r) )
                Rotate(f), Rotate(r);
            else
                Rotate(r), Rotate(r);
        }
        push_up(r);
    }
    int Access(int x)
    {
        int y = 0;
        for( ; x ; x = pre[y=x])
        {
            Splay(x);
            rt[ch[x][1]] = true, rt[ch[x][1]=y] = false;
            push_up(x);
        }
        return y;
    }
    //判断是否是同根(真实的树，非splay)
    bool judge(int u,int v)
    {
        while(pre[u]) u = pre[u];
        while(pre[v]) v = pre[v];
        return u == v;
    }
    //先Access(r),形成一条路径，再使r成为它所在的树的根
    void mroot(int r)
    {
        Access(r);
        Splay(r);
        Update_Rev(r);
    }
    //调用后u是原来u和v的lca,v和ch[u][1]分别存着lca的2个儿子
    //(原来u和v所在的2颗子树)
    void lca(int &u,int &v)
    {
        Access(v), v = 0;
        while(u)
        {
            Splay(u);
            if(!pre[u])return;
            rt[ch[u][1]] = true;
            rt[ch[u][1]=v] = false;
            push_up(u);
            u = pre[v = u];
        }
    }
	int kth(int k, int root)
    {
        int x = root;
        while(x){
            push_down(x);
            push_up(x);
            if(sz[ch[x][0]] >= k) x = ch[x][0];
            else {
                k -= sz[ch[x][0]] + 1;//
                if(k == 0) return x;
                x = ch[x][1];
            }
        }
        return x;
    }
    void link(int u,int v)
    {
        if(judge(u,v))
        {
    //        puts("-1");
            return;
        }
        mroot(u);//这里的换根操作需要特别注意，有的题目不能换根
        pre[u] = v;
    }
    //先将u变为将v与他的父亲连边切断
    void cut(int x, int v)
    {
        mroot(x);//这里的换根操作需要特别注意，有的题目不能换根
        Splay(v);
        pre[ch[v][0]] = pre[v];
        pre[v] = 0;
        rt[ch[v][0]] = true;
        ch[v][0] = 0;
        push_up(v);
    }
    //------------End---------------

    int queryid(int x, int y)
    {
        mroot(x);
        Access(y);
        Splay(y);
        return maid[y];
    }
    int query(int x, int y)
    {
        return ma[queryid(x, y)];
    }
}lct;
int main()
{
//    Open();
    while(~scanf("%d%d", &n, &m))
    {
        for(int i = 0 ; i <= n; i++) pa[i] = i;
        for(int i = 1; i <= m; i++)
        {
            int u, v, a, b;scanf("%d%d%d%d", &u, &v, &a, &b);
            e[i] = edge(u, v, a, b);
        }
        sort(e+1, e+1+m);
        lct.init(n, m);
        int ans = INF;
        for(int i = 1; i <= m; i++)
        {
            int u = e[i].u, v = e[i].v, w = e[i].b;
            if(find(u) != find(v)){
                unite(u, v);
                lct.link(u, n+i);
                lct.link(v, n+i);
            }else {
                int id = lct.queryid(u, v);
                if(w < lct.ma[id]){
                    lct.cut(e[id - n].u, id);
                    lct.cut(e[id - n].v, id);
                    lct.link(u, n+i);
                    lct.link(v, n+i);
                }
            }
            if(find(1) == find(n)){
                ans = min(ans, e[i].a + lct.query(1, n));
            }
        }
        if(ans == INF) ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}

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
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
#define max8(a,b,c,d,e,f,g,h) max(a,max(b,max(c,max(d,max(e,max(f,max(g,h)))))))
vector<int> G[N];
int n, m;
struct LCT{
    int ch[N][2],pre[N], rev[N], val[N], mark[N], sz[N];//rev这个数组是不能去掉的
    int L[N], R[N], opt[N], sum[N];
    bool rt[N];
	void Treaval(int x) {
        if(x) {
            Treaval(ch[x][0]);
//            printf("结点%2d:左儿子 %2d 右儿子 %2d 父结点 %2d size = %2d ,key = %2d \n",x, ch[x][0], ch[x][1], pre[x], sz[x], opt[x]);
            Treaval(ch[x][1]);
        }
    }
    void Update_Mark(int r,int d)
    {
        if(!r)return;
        val[r] = mark[r] = d;
        opt[r] = R[r] = L[r] = max(sz[r]*d, d);
        sum[r] = sz[r] * d;
    }
    void Update_Rev(int r)
    {
        if(!r)return;
        swap(ch[r][0],ch[r][1]);
        swap(L[r], R[r]);
        rev[r] ^= 1;
    }
    void push_down(int r)
    {
        if(mark[r] != INF)
        {
            Update_Mark(ch[r][0],mark[r]);
            Update_Mark(ch[r][1],mark[r]);
            mark[r] = INF;
        }
        if(rev[r])
        {
            Update_Rev(ch[r][0]);
            Update_Rev(ch[r][1]);
            rev[r] = 0;
        }
    }
    void push_up(int r)
    {
        if(!r) return;
        int lc = ch[r][0], rc = ch[r][1];
        sz[r] = sz[lc] + sz[rc] + 1;
        sum[r] = sum[lc] + sum[rc] + val[r];
        L[r] = max(L[lc], sum[lc] + val[r] + max(0, L[rc]));
        R[r] = max(R[rc], sum[rc] + val[r] + max(0, R[lc]));
        opt[r] = max8(opt[lc], opt[rc], L[r], R[r], val[r], val[r]+L[rc]+R[lc], val[r]+L[rc], val[r]+R[lc]);
//        Max[r] = max(max(Max[ch[r][0]],Max[ch[r][1]]),key[r]);
    }
    void init(int n)
    {
        opt[0] = mark[0] = L[0] = R[0] = -INF;
        sum[0] = sz[0] = 0;
        for(int i = 1; i <= n; i++)
        {
            rev[i] = pre[i] = ch[i][0] = ch[i][1] = 0, rt[i] = true;
            L[i] = R[i] = opt[i] = -INF, mark[i] = INF;
            sz[i] = 1;
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
    //------------End---------------
    void update(int u, int v, int va)
    {
        mroot(u);
        Access(v);
        Splay(v);
        Update_Mark(v, va);
    }
    int query(int u, int v)
    {
        mroot(u);
        Access(v);
        Splay(v);
        return opt[v];
    }
}lct;
void dfs(int u, int pa)
{
    lct.pre[u] = pa;
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(v == pa) continue;
        dfs(v, u);
    }
}
int main2()
{
//    Open();
    while(~scanf("%d%d", &n, &m))
    {
        for(int i = 1; i <= n; i++)
            scanf("%d", &lct.val[i]), lct.sum[i] = lct.val[i], G[i].clear();
        lct.init(n);
        for(int i = 1; i < n; i++)
        {
            int u, v;scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1, 0);
        while(m--)
        {
            int op, a, b, c;
            scanf("%d%d%d%d", &op, &a, &b, &c);
            if(op == 1){
                lct.update(a, b, c);
            }else{
                printf("%d\n", lct.query(a, b));
            }
        }
    }
    exit(0);
}

extern int main2(void) __asm__ ("_main2");
int main()
{
    int size = 256 << 20;  // 256Mb
    char *p = (char *)malloc(size) + size;
    __asm__ __volatile__(
        "mov  %0, %%rsp\n"		//这里很多时候会报错“bad register name '%rsp'”此时只需要将rsp换成esp就行了(原理就是两个不同的寄存器，在某些平台上名字不同)
        "push $_exit\n"
        "jmp _main2\n"
        :: "r"(p));
    return 0;
}

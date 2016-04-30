/*
*Description
SC省MY市有着庞大的地下水管网络，嘟嘟是MY市的水管局长（就是管水管的啦），嘟嘟作为水管局长的工作就是：每天供水公司可能要将一定量的水从x处送往y处，嘟嘟需要为供水公司找到一条从A至B的水管的路径，接着通过信息化的控制中心通知路径上的水管进入准备送水状态，等到路径上每一条水管都准备好了，供水公司就可以开始送水了。嘟嘟一次只能处理一项送水任务，等到当前的送水任务完成了，才能处理下一项。
在处理每项送水任务之前，路径上的水管都要进行一系列的准备操作，如清洗、消毒等等。嘟嘟在控制中心一声令下，这些水管的准备操作同时开始，但由于各条管道的长度、内径不同，进行准备操作需要的时间可能不同。供水公司总是希望嘟嘟能找到这样一条送水路径，路径上的所有管道全都准备就绪所需要的时间尽量短。嘟嘟希望你能帮助他完成这样的一个选择路径的系统，以满足供水公司的要求。另外，由于MY市的水管年代久远，一些水管会不时出现故障导致不能使用，你的程序必须考虑到这一点。
不妨将MY市的水管网络看作一幅简单无向图（即没有自环或重边）：水管是图中的边，水管的连接处为图中的结点。
 
Input
输入文件第一行为3个整数：N, M, Q分别表示管道连接处（结点）的数目、目前水管（无向边）的数目，以及你的程序需要处理的任务数目（包括寻找一条满足要求的路径和接受某条水管坏掉的事实）。
以下M行，每行3个整数x, y和t，描述一条对应的水管。x和y表示水管两端结点的编号，t表示准备送水所需要的时间。我们不妨为结点从1至N编号，这样所有的x和y都在范围[1, N]内。
以下Q行，每行描述一项任务。其中第一个整数为k：若k=1则后跟两个整数A和B，表示你需要为供水公司寻找一条满足要求的从A到B的水管路径；若k=2，则后跟两个整数x和y，表示直接连接x和y的水管宣布报废（保证合法，即在此之前直接连接x和y尚未报废的水管一定存在）。
 
Output
按顺序对应输入文件中每一项k=1的任务，你需要输出一个数字和一个回车/换行符。该数字表示：你寻找到的水管路径中所有管道全都完成准备工作所需要的时间（当然要求最短）。

* 做法： 一般道路损坏的题目都是反过来，变成增加边，这个也是反过来变成加边，然后用LCT暴力搞即可
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
//#include <unordered_map>
#define N 1200010
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
    int u, v, w, useless, id;
    edge(){}
    edge(int _u, int _v, int _w, int _id){
        u = _u, v = _v, w = _w, useless = 0, id = _id;
    }
    bool operator < (const edge& o) const{
        return useless < o.useless || (useless == o.useless && w < o.w);
    }
}e[N];
struct LCT{
    int ch[N][2],pre[N], rev[N];//rev这个数组是不能去掉的
    int ma[N], maid[N];
    bool rt[N];
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
            ma[id] = e[i].w;
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
}lct;
int pa[100100];
int find(int x)
{
    return pa[x] == x ? x : pa[x] = find(pa[x]);
}
bool unite(int u, int v)
{
    u = find(u), v = find(v);
    if(u == v) return false;
    pa[u] = v;
    return true;
}
int n, m, q;
int getint()
{
    char ch = getchar();
    for ( ; ch > '9' || ch < '0'; ch = getchar());
    int tmp = 0;
    for ( ; '0' <= ch && ch <= '9'; ch = getchar())
        tmp = tmp * 10 + int(ch) - 48;
    return tmp;
}
struct QUE{
    int op, u, v, id;
    QUE(){}
    QUE(int _op, int _u, int _v, int _w){
        op = _op, u = _u, v = _v, id = _w;
    }
}que[100010];
bool cmp(const edge& a, const edge& b){
    return a.id < b.id;
}
int ans[N];
struct Item{
        LL key,val,nxt;
};
struct UMP{
        Item item[N];
        LL itnum;
        LL head[1999993];
        LL MOD;
        UMP(){
                MOD=1999993;
                clear();
        }
        void clear(){
                memset(head,-1,sizeof(head));
                itnum=0;
        }
        LL& operator[](LL x){
                LL idx=x%MOD;
                //cerr<<idx<<endl;
                for(LL i=head[idx];i!=-1;i=item[i].nxt){
                        if(item[i].key==x) return item[i].val;
                }

                item[itnum]=(Item){x,0,head[idx]};
                head[idx]=itnum;
                return item[itnum++].val;
        }
}mp;
int main()
{
//    Open();
    while(~scanf("%d%d%d", &n, &m, &q))
    {
        mp.clear();
        for(int i = 0; i <= n; i++) pa[i] = i;
        for(int i = 1; i <= m; i++)
        {
            int u = getint(), v = getint(), w = getint();
            if(v < u) swap(u, v);
            LL hs = (LL)u * 100001LL + v;
            mp[hs] = i;
            e[i] = edge(u, v, w, i);
        }
        for(int i = 0; i < q; i++)
        {
            int op = getint();
            int u = getint(), v = getint(), id = 0;
            if(op == 2){
                if(v < u) swap(u, v);
                LL hs = (LL)u * 100001LL + v;
                id = mp[hs];
                e[id].useless = 1;
            }
            que[i] = QUE(op, u, v, id);
        }
        lct.init(n, m);
        sort(e+1, e+m+1);
        for(int i = 0; i < m; i++)
        {
            if(e[i].useless == 1) break;
            if(unite(e[i].u, e[i].v)){
                lct.link(e[i].u, e[i].id + n);
                lct.link(e[i].v, e[i].id + n);
            }
        }
        sort(e+1, e+1+m, cmp);
        int tail = 0;
        for(int i = q-1; i >= 0; i--)
        {
            int u = que[i].u, v = que[i].v, id = que[i].id, op = que[i].op;
            if(op == 1){
                int idx = lct.queryid(u, v);
                ans[tail++] = lct.ma[idx];
            }else{
                int idx = lct.queryid(u, v);
                if(e[id].w < lct.ma[idx])
                {
                    lct.cut(e[idx-n].u, idx);
                    lct.cut(e[idx-n].v, idx);
                    lct.link(u, id+n);
                    lct.link(v, id+n);
                }
            }
        }
        for(int i = tail-1 ; i >= 0; i--)
            printf("%d\n", ans[i]);
    }
    return 0;
}

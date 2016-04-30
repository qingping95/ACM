/*
*Description
SCʡMY�������Ӵ�ĵ���ˮ�����磬����MY�е�ˮ�ֳܾ������ǹ�ˮ�ܵ�����������Ϊˮ�ֳܾ��Ĺ������ǣ�ÿ�칩ˮ��˾����Ҫ��һ������ˮ��x������y��������ҪΪ��ˮ��˾�ҵ�һ����A��B��ˮ�ܵ�·��������ͨ����Ϣ���Ŀ�������֪ͨ·���ϵ�ˮ�ܽ���׼����ˮ״̬���ȵ�·����ÿһ��ˮ�ܶ�׼�����ˣ���ˮ��˾�Ϳ��Կ�ʼ��ˮ�ˡ���һ��ֻ�ܴ���һ����ˮ���񣬵ȵ���ǰ����ˮ��������ˣ����ܴ�����һ�
�ڴ���ÿ����ˮ����֮ǰ��·���ϵ�ˮ�ܶ�Ҫ����һϵ�е�׼������������ϴ�������ȵȡ����ڿ�������һ�����£���Щˮ�ܵ�׼������ͬʱ��ʼ�������ڸ����ܵ��ĳ��ȡ��ھ���ͬ������׼��������Ҫ��ʱ����ܲ�ͬ����ˮ��˾����ϣ�������ҵ�����һ����ˮ·����·���ϵ����йܵ�ȫ��׼����������Ҫ��ʱ�価���̡���ϣ�����ܰ��������������һ��ѡ��·����ϵͳ�������㹩ˮ��˾��Ҫ�����⣬����MY�е�ˮ�������Զ��һЩˮ�ܻ᲻ʱ���ֹ��ϵ��²���ʹ�ã���ĳ�����뿼�ǵ���һ�㡣
������MY�е�ˮ�����翴��һ��������ͼ����û���Ի����رߣ���ˮ����ͼ�еıߣ�ˮ�ܵ����Ӵ�Ϊͼ�еĽ�㡣
 
Input
�����ļ���һ��Ϊ3��������N, M, Q�ֱ��ʾ�ܵ����Ӵ�����㣩����Ŀ��Ŀǰˮ�ܣ�����ߣ�����Ŀ���Լ���ĳ�����Ҫ�����������Ŀ������Ѱ��һ������Ҫ���·���ͽ���ĳ��ˮ�ܻ�������ʵ����
����M�У�ÿ��3������x, y��t������һ����Ӧ��ˮ�ܡ�x��y��ʾˮ�����˽��ı�ţ�t��ʾ׼����ˮ����Ҫ��ʱ�䡣���ǲ���Ϊ����1��N��ţ��������е�x��y���ڷ�Χ[1, N]�ڡ�
����Q�У�ÿ������һ���������е�һ������Ϊk����k=1������������A��B����ʾ����ҪΪ��ˮ��˾Ѱ��һ������Ҫ��Ĵ�A��B��ˮ��·������k=2��������������x��y����ʾֱ������x��y��ˮ���������ϣ���֤�Ϸ������ڴ�֮ǰֱ������x��y��δ���ϵ�ˮ��һ�����ڣ���
 
Output
��˳���Ӧ�����ļ���ÿһ��k=1����������Ҫ���һ�����ֺ�һ���س�/���з��������ֱ�ʾ����Ѱ�ҵ���ˮ��·�������йܵ�ȫ�����׼����������Ҫ��ʱ�䣨��ȻҪ����̣���

* ������ һ���·�𻵵���Ŀ���Ƿ�������������ӱߣ����Ҳ�Ƿ�������ɼӱߣ�Ȼ����LCT�����㼴��
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
    int ch[N][2],pre[N], rev[N];//rev��������ǲ���ȥ����
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
    //P�����Ƚ�����㵽r��·�������еĽ��ı�����·�
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
    //�ж��Ƿ���ͬ��(��ʵ��������splay)
    bool judge(int u,int v)
    {
        while(pre[u]) u = pre[u];
        while(pre[v]) v = pre[v];
        return u == v;
    }
    //��Access(r),�γ�һ��·������ʹr��Ϊ�����ڵ����ĸ�
    void mroot(int r)
    {
        Access(r);
        Splay(r);
        Update_Rev(r);
    }
    //���ú�u��ԭ��u��v��lca,v��ch[u][1]�ֱ����lca��2������
    //(ԭ��u��v���ڵ�2������)
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
        mroot(u);//����Ļ���������Ҫ�ر�ע�⣬�е���Ŀ���ܻ���
        pre[u] = v;
    }
    //�Ƚ�u��Ϊ��v�����ĸ��������ж�
    void cut(int x, int v)
    {
        mroot(x);//����Ļ���������Ҫ�ر�ע�⣬�е���Ŀ���ܻ���
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

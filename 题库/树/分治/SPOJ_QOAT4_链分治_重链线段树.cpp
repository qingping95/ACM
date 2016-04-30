/*
* SPOJ Query on a tree IV
* 
* ��˵����query on a tree 1~5 �������һ���⣬��ȷ��������
* 
* �ⷨ���ԣ������㷨������·�������е�Ӧ��--���ӳ�
* �ҽ��������Ҿ���û˵����ĵط�˵һ�¡�
* ����������Ҫ��ԭ���������ʷ֣�Ȼ��Ϊÿһ��������ά��һ���߶�����������������һ��������ӡ�
* ÿ����������Ҫά����������Ϣ��maxl, maxr, opt; opt �������������ϵĴ𰸡�
* ���ȶ�ÿһ���㴦�������һ����D[i], D2[i],��ʾ����ڵ�������ĳ����ɫ����·���г��ȵ����ֵ�ʹδ�ֵ(·
* ���в�����ͬ�����ĵ㣬���û�а�ɫ�ڵ㲻���ڣ����ȼ�Ϊ-INF)
* ��ô�߶�����ĳ������[l, r]��opt�ĺ������d[i]+dist[i,j]+d[j],i,j���������У�dist[i,j]��ʾ��i���ڵ㵽��j
* ���ڵ�ľ��룻��maxl��maxr������ά��opt������maxl��ʾһ����˵��ڸ��������һ������������죬�Ҷ˵�Ϊһ��
* ��ɫ�ڵ��·������󳤶ȣ�maxr�෴����ô�������������׽ڵ��opt���Եõ�ά��(opt[fa] = maxr[lc]+maxl[rc]+dist[mid, mid+1])
* ���ǣ��������ͱ����ɿ��߶�������ά�������մ�ֻ��Ҫ��һ���Ѵ洢�����߶�����optֵ���ɡ�
* �������л���һ���ر���Ҫ��d[]��d2[]���飬�����������ά������������д�ıȽ����������Ͳ�˵�ˡ���ž���
* ÿ���ڵ㿪һ���ѣ�������¼���п��ܵ�dֵ��Ȼ�����o(1)ȡ�����ˡ�
* �����޸Ĳ���������һ���ڵ㵽����·���ϲ�����log����ߣ���ô��Ҫ�޸ĵ��߶���Ҳ������log�����޸��߶���log
* 
* ���Ӷ�ΪO(Qlog(n)^2)
* 
* ��Ȼ�����а����ڶ��±괦��...����ÿ����������һ���߶�����������ÿ���߶�������һ�����飬���Կ���һ���ڵ��
* ÿ�������¼�������ڵ��±꣬�ܵĽڵ���������6*N����������Ҫ֪��ÿ���ڵ��Ӧ�ǿ��߶�����������Ҳ��Ҫ֪��
* ÿ���߶����ϵĽڵ��Ӧԭ���ϵ��Ǹ��ڵ㡣����Ĵ������������ض��ӽ�ԭ���ڵ��������У���¼ÿ���߶������ڵ�
* ���±꣬����¼�߶�����ʼ�ڵ��ƫ��������ô������Щ��Ϣ���ɲ����뷴�ҡ�ÿ��������������������ϸע�͡�����
* ��distֵҲ�������������ά����
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
int top[MAXN];//top[v]��ʾv���ڵ������Ķ��˽ڵ�
int fa[MAXN]; //���׽ڵ�
int deep[MAXN];//���
int sz[MAXN];//sz[v]��ʾ��vΪ���������Ľڵ���
int p[MAXN];//p[v]��ʾv���丸�׽ڵ���������߶����е�λ��
int fp[MAXN];//��p�����෴
int son[MAXN];//�ض���
int col[MAXN];//��ɫ
int val[MAXN];
int pos;
priority_queue<PII > que[N], ansque;//que:�洢D(i)
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
int root[N];//root[i]��ʾ�ڵ�i(head)���ڵ�������ʾ���߶�����pool�е�λ��
int pn[N];//����DFS���൱�ڽ��ڵ����ţ���ͬһ�������ϵĽڵ�ŵ�һ��
int idx[N];//idx[i]��ʾ�ڵ�i�������ڵ������߶����ϵ�rank
int num[N];//num[i]��ʾ�ڵ�i(head)���ڵ������ж��ٸ��ڵ�
int dis[N];//dis[i]��ʾ�ڵ�i����Ӧ�߶�������ڵ�ľ���
int sonw[N];

void dfs1(int u,int pre,int d) //��һ��dfs���fa,deep,sz,son,val
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
void getpos(int u,int sp, int dist) //�ڶ���dfs���top��p,num;
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
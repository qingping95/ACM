#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 100010
#define M 2500010
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

int lson[M], rson[M], ma[M], tot, lazy[M], mi[M];//ά������Ϣ
int Tn;
int dep[2][N];
int fa[2][N];
int st[N], ed[N];
vector<int> G[2][N];
int n, m;
int T[N];//�洢ÿ���ڵ���߶����ĸ��ڵ��š�
void dfsseq(int u, vector<int> G[], int d)
{
    dep[1][u] = d;
    st[u] = ++Tn;
    for(int i = 0; i < G[u].size(); i ++)
        dfsseq(G[u][i], G, d + 1);
    ed[u] = Tn;
}
void dfsdep(int u, int d)
{
    dep[0][u] = d;
    for(int i = 0; i < G[0][u].size(); i ++)
        dfsdep(G[0][u][i], d+1);
}
int build(int l, int r)
{
    int root = tot++;
    ma[root] = 0, mi[root] = 0, lazy[root] = 0;
    if(l == r) return root;
    int mid = l + r >> 1;
    lson[root] = build(l, mid);
    rson[root] = build(mid+1, r);
    return root;
}
// �е�ģ���·�����ǵ�ʱ����һ���������˵�ǰ������Ҷ����Ƿ�����ʷ�汾�� ����ǵĻ�����������ڵ㣬������Ǿ�ֱ�Ӹ��¡�
// ��ô����������Ϊ�˽�ʡ�ռ䣬�Ҹ��˲���֮�������������ò��ٿ�һ�����߶�����С��ͬ�ı�����飬��ʵ�����������ڴ��ǻ��
// ���...��һ��ʼ���������ǣ������ǲ�����ʷ�汾�� ֻҪ�������Ч���Ҿ����������½ڵ㵱�����ӡ�
// ����Ҳ���ж��ĵ����ݻ������ֲ��ӱ�ǵ�MLE�ģ�����ע��ȡ�ᡣ
void push_down(int root){
    if(lazy[root]){
        lson[tot] = lson[lson[root]];
        rson[tot] = rson[lson[root]];
        ma[tot] = max(ma[lson[root]], lazy[root]);
        mi[tot] = max(mi[lson[root]], lazy[root]);
        lazy[tot] = max(lazy[lson[root]], lazy[root]);
        lson[root] = tot++;
        lson[tot] = lson[rson[root]];
        rson[tot] = rson[rson[root]];
        ma[tot] = max(ma[rson[root]], lazy[root]);
        mi[tot] = max(mi[rson[root]], lazy[root]);
        lazy[tot] = max(lazy[rson[root]], lazy[root]);
        rson[root] = tot++;
        lazy[root] = 0;
    }
}
void push_up(int root){
    ma[root] = max(ma[lson[root]], ma[lson[root]]);
    mi[root] = min(mi[lson[root]], mi[lson[root]]);
}
int update(int root, int L, int R, int l, int r, int val)// [l, r]�޸����䣬[L�� R]��ǰ����
{
    if(mi[root] >= val) return root;
    int newroot = tot ++;
    if(L >= l && R <= r){
        lazy[newroot] = max(lazy[root], val);
        ma[newroot] = max(ma[root], val);
        mi[newroot] = max(mi[root], val);
        lson[newroot] = lson[root];
        rson[newroot] = rson[root];
        return newroot;
    }
    lazy[newroot] = ma[newroot] = 0, mi[newroot] = 0;
    push_down(root);
    int mid = L + R >> 1;
    if(r <= mid)
    {
        lson[newroot] = update(lson[root], L, mid, l, r, val);
        rson[newroot] = rson[root];
    }else if(l > mid){
        lson[newroot] = lson[root];
        rson[newroot] = update(rson[root], mid+1, R, l, r, val);
    }else{
        lson[newroot] = update(lson[root], L, mid, l, mid, val);
        rson[newroot] = update(rson[root], mid+1, R, mid+1, r, val);
    }
    push_up(newroot);
    return newroot;
}
int query(int root, int L, int R, int idx){
    if(L == R && L == idx) return ma[root];
    push_down(root);
    int mid = L + R >> 1;
    if(idx <= mid) return query(lson[root], L, mid, idx);
    else return query(rson[root], mid+1, R, idx);
}
void dfs(int u, vector<int> G[])
{
    T[u] = update(T[fa[0][u]], 1, Tn, st[u], ed[u], u);
    for(int i = 0; i < G[u].size(); i ++)
    {
        dfs(G[u][i], G);
    }
}

int main()
{
    Open();
    while(~scanf("%d%d", &n, &m)){
        Tn = 0;
        tot = 0;
        for(int i = 0; i <= n; i++) G[1][i].clear(), G[0][i].clear();
        for(int i = 2; i <= n; i++)
        {
            scanf("%d", &fa[0][i]);
            G[0][fa[0][i]].push_back(i);
        }
        for(int i = 2; i <= n; i++)
        {
            scanf("%d", &fa[1][i]);
            G[1][fa[1][i]].push_back(i);
        }
        dfsseq(1, G[1], 1);
        dfsdep(1, 1);
        fa[0][1] = n + 1;
        T[n+1] = build(1, Tn);
        dfs(1, G[0]);
        int preans = 0;
        while(m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            u += preans; u %= n; u++;
            v += preans; v %= n; v++;
            preans = query(T[u], 1, Tn, st[v]);
            printf("%d %d %d\n", preans, dep[0][u] - dep[0][preans] + 1, dep[1][v] - dep[1][preans] + 1);
        }
    }
    return 0;
}

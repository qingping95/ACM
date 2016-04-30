#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
//#include <unordered_map>
#define N 100100
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
const int mod = 530600414;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int n, m, q;
int dsufa[N];

const int MAXN = 100010;
int top[MAXN];//top[v]表示v所在的重链的顶端节点
int fa[MAXN]; //父亲节点
int deep[MAXN];//深度
int num[MAXN];//num[v]表示以v为根的子树的节点数
int p[MAXN];//p[v]表示v与其父亲节点的连边在线段树中的位置
int fp[MAXN];//和p数组相反
int son[MAXN];//重儿子
int pos;


struct Edge
{
    int to,next;
}edge[MAXN*2];
int head[MAXN],tot;
int find(int x)
{
    return dsufa[x] == x ? x : dsufa[x] = find(dsufa[x]);
}
bool unite(int u, int v)
{
    u = find(u), v = find(v);
    if(u == v) return false;
    dsufa[u] = v;
    return true;
}
void init(int V){
    tot = 0;
    memset(head,-1,sizeof(head));
    pos = 0;
    memset(son,-1,sizeof(son));
    for(int i = 0 ; i <= V; i++) dsufa[i] = i;
}

void addedge(int u,int v)
{
    edge[tot].to = v;edge[tot].next = head[u];head[u] = tot++;
}


////////////////////线段树////////////////////
/**
  根节点是1,范围下标从0开始，[0,4] means 0,1,2,3,4
*/
struct Node {
	int l,r;
	int sum;
	bool flag;
}segTree[MAXN*6];
struct Seg{
	void pushDown(int x){
		if(segTree[x].flag){
			int lson=x<<1;
			int rson=(x<<1)|1;
			segTree[lson].sum =0;
			segTree[rson].sum =0;
			segTree[lson].flag=true;
			segTree[rson].flag=true;
			segTree[x].flag=false;
		}
	}
	void pushUp(int x){
		int lson=x<<1;
		int rson=(x<<1)|1;
		segTree[x].sum = segTree[lson].sum + segTree[rson].sum;
	}
	void build(int i,int l,int r){
		segTree[i].l = l;
		segTree[i].r = r;
		segTree[i].sum = 0;
		segTree[i].flag = 0;
		if(l == r){
            segTree[i].sum = 1;
            return;
		}
		int mid = (l+r)/2;
		build(i<<1,l,mid);
		build((i<<1)|1,mid+1,r);
		pushUp(i);
	}
	int querySum(int i,int l,int r){  //查询线段树中[l,r] 的和
		if(segTree[i].l == l && segTree[i].r == r)
			return segTree[i].sum;
        pushDown(i);
		int mid = (segTree[i].l + segTree[i].r)/2;
		if(r <= mid)return querySum(i<<1,l,r);
		else if(l > mid)return querySum((i<<1)|1,l,r);
		else return querySum(i<<1,l,mid) + querySum((i<<1)|1,mid+1,r);
	}
	void updateZero(int i, int l,int r){
		if(segTree[i].l == l && segTree[i].r == r){
			segTree[i].flag=true;
			segTree[i].sum=0;
			return;
		}
		pushDown(i);
		int mid = (segTree[i].l + segTree[i].r)/2;
		if(r <= mid) updateZero(i<<1,l,r);
		else if(l > mid) updateZero((i<<1)|1,l,r);
		else  updateZero(i<<1,l,mid) , updateZero((i<<1)|1,mid+1,r);
		pushUp(i);
	}
}seg;


////////////////////树链剖分////////////////////
/**
  点的下标从1开始
  */
struct TreeLink{
	void build(){
		pos=0;
		dfs1(1,0,0);
		getpos(1,1);
	}
	int findSum(int u,int v){//查询u->v边的和
		int f1 = top[u], f2 = top[v];
		int tmp = 0;
		while(f1 != f2){
			if(deep[f1] < deep[f2]){
				swap(f1,f2);
				swap(u,v);
			}
			tmp += seg.querySum(1,p[f1],p[u]);
			u = fa[f1]; f1 = top[u];
		}
		if(u == v) return tmp;
		if(deep[u] > deep[v]) swap(u,v);
		return tmp + seg.querySum(1,p[son[u]],p[v]);
	}
	void set0(int u,int v){//置为0
		int f1 = top[u], f2 = top[v];
		while(f1 != f2){
			if(deep[f1] < deep[f2]){
				swap(f1,f2);
				swap(u,v);
			}
			seg.updateZero(1,p[f1],p[u]);
			u = fa[f1]; f1 = top[u];
		}
		if(u == v) return ;
		if(deep[u] > deep[v]) swap(u,v);
		seg.updateZero(1,p[son[u]],p[v]);
	}
	/*Useless*/
	void dfs1(int u,int pre,int d){ //第一遍dfs求出fa,deep,num,son
		deep[u] = d;
		fa[u] = pre;
		num[u] = 1;
		son[u]=0;
		for(int i = head[u];i != -1; i = edge[i].next){
			int v = edge[i].to;
			if(v != pre){
				dfs1(v,u,d+1);
				num[u] += num[v];
				if(num[v] > num[son[u]])
					son[u] = v;
			}
		}
	}
	void getpos(int u,int sp){ //第二遍dfs求出top和p
		top[u] = sp;
		if(son[u] != 0){
			p[u] = pos++;
			fp[p[u]] = u;
			getpos(son[u],sp);
		}else{
			p[u] = pos++;
			fp[p[u]] = u;
			return;
		}
		for(int i = head[u] ; i != -1; i = edge[i].next){
			int v = edge[i].to;
			if(v != son[u] && v != fa[u])
				getpos(v,v);
		}
	}
}trlnk;

PII EdgeE[N];
int vis[N];
struct query{
    int op, u, v;
    query(){}
    query(int o, int uu, int vv)
    {
        op = o, u = uu, v = vv;
    }
}que[N];

int ans[N];
map<PII, int> mp;

int main()
{
    Open();
    int T;scanf("%d", &T);
    int cas = 1;
    while(T--)
    {
        mp.clear();
        memset(vis, 0, sizeof(vis));
        scanf("%d%d%d", &n, &m, &q);
        init(n);
        for(int i = 0 ; i < m; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            EdgeE[i] = PII(u, v);
        }
        for(int i = 0 ; i < q; i++)
        {
            int op, u, v;
            scanf("%d%d%d", &op, &u, &v);
            que[i] = query(op, u, v);
            if(op == 1) mp[PII(u, v)]++, mp[PII(v, u)]++;
        }

        for(int i =0 ; i < m; i++)
        {
            int u = EdgeE[i].first, v = EdgeE[i].second;
            if(mp.find(PII(u, v)) != mp.end()) {
                vis[i] = 2;
                mp[PII(u, v)]--, mp[PII(v, u)]--;
                if(mp[PII(u, v)] == 0) mp.erase(PII(u, v)), mp.erase(PII(v, u));
                continue;
            }
            if(unite(u, v)){
                vis[i] = 1;
                addedge(u, v);
                addedge(v, u);
            }
        }

        trlnk.build();
        seg.build(1, 0, pos-1);
        for(int i = 0; i < m; i++)
        {
            if(vis[i] == 0){
                int u = EdgeE[i].first, v = EdgeE[i].second;
                trlnk.set0(u, v);
            }
        }
        int tail = 0;
        for(int i = q - 1; i >= 0 ;i--)
        {
            int op = que[i].op, u = que[i].u, v = que[i].v;
            if(op == 2){
                ans[tail ++] = trlnk.findSum(u, v);
            } else {
                trlnk.set0(u, v);
            }
        }
        printf("Case #%d:\n", cas++);
        for(int i = tail - 1; i >= 0; i--)
        {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}

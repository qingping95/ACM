#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
//#include <unordered_map>
#define lson x<<1
#define rson x<<1|1
#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f3f3f3f3fLL;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}

const int MAXN = 200010;
int top[MAXN];//top[v]表示v所在的重链的顶端节点
int fa[MAXN]; //父亲节点
int deep[MAXN];//深度
int num[MAXN];//num[v]表示以v为根的子树的节点数
int p[MAXN];//p[v]表示v与其父亲节点的连边在线段树中的位置
int fp[MAXN];//和p数组相反
int son[MAXN];//重儿子
int pos;
LL val[MAXN];
int IDX[MAXN];
struct info
{
    int v;
    LL w;
    int id;
};
vector<info > G[MAXN];
////////////////////线段树////////////////////
/**
  根节点是1,范围下标从0开始，[0,4] means 0,1,2,3,4
*/
struct Node {
	int l, r, ls, rs;
	LL v;
	int len()
	{
	    return r - l + 1;
	}
}lt[MAXN*6];
struct Seg{
	void pushUp(int x){
	    lt[x].ls = lt[lson].ls;
	    lt[x].rs = lt[rson].rs;
	    if(lt[x].ls == lt[lson].len()) lt[x].ls += lt[rson].ls;
	    if(lt[x].rs == lt[rson].len()) lt[x].rs += lt[lson].rs;
	}
	void build(int x,int l,int r){
	    lt[x] = (Node){l, r, 0, 0, 0};
		if(l == r){
		    lt[x].v = val[fp[l]];
            if(lt[x].v == 1) lt[x].ls = lt[x].rs = 1;
            return;
		}
		build(lson,l,mid);
		build(rson,mid+1,r);
		pushUp(x);
	}
	int querySum(int x,int l,int r, bool isL){  //查询线段树中[l,r] 的和
	    if(l > r) return 0;
	    if(lt[x].l == l && lt[x].r == r)
        {
            return isL ? lt[x].ls : lt[x].rs;
        }
        if(r <= mid) return querySum(lson, l, r, isL);
        else if(l > mid) return querySum(rson, l, r, isL);
        else {
            int resL = querySum(lson, l, mid, isL);
            int resR = querySum(rson, mid+1, r, isL);
            int res = isL ? resL : resR;
            if(isL && resL == (mid-l+1)) res += resR;
            if(!isL && resR == (r - mid)) res += resL;
            return res;
        }
	}
	void update(int x, int idx, LL _val)
	{
	    if(lt[x].l == lt[x].r && lt[x].l == idx)
        {
            lt[x].v = _val;
            if(lt[x].v == 1) lt[x].ls = lt[x].rs = 1;
            else lt[x].ls = lt[x].rs = 0;
            return ;
        }
        if(idx <= mid) update(lson, idx, _val);
        else update(rson, idx, _val);
        pushUp(x);
	}
}seg;


////////////////////树链剖分////////////////////
/**
  点的下标从1开始
  */
struct TreeLink{
    PII sta[MAXN];
	void build(){
		pos=0;
		dfs1(1,0,0);
		getpos(1,1);
	}
	LL findres(int u, int v, LL y){//查询u->v边的和
//	    while(!sta.empty()) sta.pop();
        int tail = 0;
		int f1 = top[u], f2 = top[v];
		bool uisu = 1;
		while(f1 != f2){
			if(deep[f1] < deep[f2]){
				swap(f1,f2);
				swap(u,v);
				uisu = !uisu;
			}
			if(uisu){
                int res = seg.querySum(1,p[f1],p[u], 0);
                res = min(res, p[u] - p[f1]);
                u = fp[p[u] - res];
                y /= val[u];
                if(y == 0) return y;
                u = fa[u];
                f1 = top[u];
                continue;
			}
//			sta.push(PII(p[f1], p[u]));
            sta[tail++] = PII(p[f1], p[u]);
			u = fa[f1]; f1 = top[u];
		}
		if(deep[u] > deep[v]) swap(u, v), uisu = !uisu;
		if(u != v)
        {
            if(uisu) sta[tail++] = PII(p[son[u]], p[v]);
//            if(uisu) sta.push(PII(p[son[u]], p[v]));
            else {
                while(v != son[u])
                {
                    if(p[son[u]] > p[v]) while(1);
                    int res = seg.querySum(1, p[son[u]], p[v], 0);
                    v = fp[p[v] - res];
                    if(v == son[u] || deep[v] < deep[son[u]]) break;
                    y /= val[v];
                    if(y == 0) return y;
                    v = fa[v];
                }
                y /= val[son[u]];
                if(y == 0) return y;
            }
        }
		while(tail)
        {
            PII pp = sta[--tail];
            u = pp.first, v = pp.second;
            while(v != u)
            {
                y /= val[fp[u]];
                if(y == 0) return y;
                u++;
                if(v == u) break;
                int res = seg.querySum(1, u, v, 1);
                res = min(res, v - u);
                u += res;
                //<<son[fp[u]]<<":"<<val[son[fp[u]]]<<endl;
            }
            y /= val[fp[v]];
            if(y == 0) return y;
            //<<fp[v]<<":"<<val[fp[v]]<<endl;
        }
        return y;
	}
	void update(int id, LL _val)
	{
	    seg.update(1, p[IDX[id]], _val);
	    val[IDX[id]] = _val;
	}
	/*Useless*/
	void dfs1(int u,int pre,int d){ //第一遍dfs求出fa,deep,num,son
		deep[u] = d;
		fa[u] = pre;
		num[u] = 1;
		son[u]=0;
		for(int i = 0; i < G[u].size(); i++){
//		for(int i = head[u];i != -1; i = edge[i].next){
			int v = G[u][i].v;
			LL w = G[u][i].w;
			int id = G[u][i].id;
			if(v != pre){
				dfs1(v,u,d+1);
                val[v] = w;
                IDX[id] = v;
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
		for(int i = 0; i < G[u].size();i++){
//		for(int i = head[u] ; i != -1; i = edge[i].next){
			int v = G[u][i].v;
			if(v != son[u] && v != fa[u])
				getpos(v,v);
		}
	}
}trlnk;

int main()
{
    Open();
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i < n; i++)
    {
        int u, v;
        LL w;
        scanf("%d%d%I64d", &u, &v, &w);
        G[u].push_back((info){v, w, i});
        G[v].push_back((info){u, w, i});
    }
    trlnk.build();
    seg.build(1, 0, pos-1);
    val[1] = 1;
    while(m--)
    {
        int ty;
        scanf("%d",&ty);
        if(ty == 1)
        {
            int u, v;
            LL y;
            scanf("%d%d%I64d", &u, &v, &y);
            printf("%I64d\n", trlnk.findres(u, v, y));
        }
        else
        {
            int p;
            LL c;
            scanf("%d%I64d", &p, &c);
            trlnk.update(p, c);
        }
    }
    return 0;
}

/*
http://codeforces.com/group/qcIqFPYhVr/contest/203881/problem/X
一棵n（n<=1e5）个点的有边权的树，q(q<=1e5)个查询（v，L），求v点周围距离他不超过L的点的个数。
利用树分治， 显然树上的任何一个点，可以达到它的重心不会超过logn个。
对于点v周围的某个距离他L远的u点而言，u的重心要么是v（距离为L），要么是包括v的某个重心x（距离为L-dist(v,x)）。
那么对于每个点v，预处理出以他为中心的子树上的所有的点到他的距离，用vector存下来并排序，同时处理出每个点被包括的所有中心。
空间复杂度为O(nlogn)，时间复杂度为O(nlognlong)。
现在考虑去重，一个点u如果在v的某个重心x上计算一次后，必然还会被包含x的重心再计算一次，所以对于每个点，还要处理出以他为重心时的每一棵子
树对他的贡献，考虑到每个点最多作为一个点的直接子树，所以空间复杂度会再多一倍。
*/
#include<bits/stdc++.h>
#define MAXN 110000
typedef long long LL;
struct edge{
    int to,next,cost;
}E[MAXN*2];
struct Node{
	int root,subtree;
	LL dis;
	Node(int _root = 0, int _subtree = 0,LL _dis = 0){
		root = _root;
		subtree = _subtree;
		dis = _dis;
	}
};
std::vector<Node>vec[MAXN];
std::vector<LL> vs[MAXN<<1];
bool vis[MAXN];
int fa[MAXN],sz[MAXN],que[MAXN],head[MAXN],si,cnt=0,id[MAXN];
LL dist[MAXN];
void add_edge(int u,int v,int w)
{
    E[si].to=v;
    E[si].next=head[u];
    E[si].cost=w;
    head[u]=si++;
}
int getroot(int root)
{
    int l=0,r=0;fa[root]=0;
    for(que[r++]=root;l<r;l++){
        int v=que[l];
        for(int i=head[v];~i;i=E[i].next){
            int u=E[i].to;
            if(u==fa[v]||vis[u])continue;
            fa[u]=v;
            que[r++]=u;
        }
    }
    int res=MAXN;
    for(;r;r--){
        int v=que[r-1];
        sz[v]=1;
        int m=0;
        for(int i=head[v];~i;i=E[i].next){
            int u=E[i].to;
            if(u==fa[v]||vis[u])continue;
            sz[v]+=sz[u];
            m=std::max(sz[u],m);
        }
        m=std::max(m,l-sz[v]);
        if(m<res){
            res=m;
            root=v;
        }
    }
    return root;
}
void go(int v,int root,int w,int subtree)
{
    int l=0,r=0;fa[v]=root;dist[v]=w;
    vs[subtree].clear();
    for(que[r++]=v;l<r;l++){
        int u=que[l];
        vs[subtree].push_back(dist[u]);
        vs[id[root]].push_back(dist[u]);
        vec[u].push_back(Node(id[root],subtree,dist[u]));
        for(int i=head[u];~i;i=E[i].next){
            int to=E[i].to;
            if(to==fa[u]||vis[to])continue;
            dist[to]=dist[u]+E[i].cost;
            fa[to]=u;
            que[r++]=to;
        }
    }
}
void solve(int root)
{
    root=getroot(root);
    id[root]=++cnt;
    dist[root]=0;fa[root]=0;
    vis[root]=true;
    vec[root].push_back(Node(id[root],-1,0));
    vs[id[root]].clear();
    vs[id[root]].push_back(0);
    for(int i=head[root];~i;i=E[i].next){
        int u=E[i].to;
        if(vis[u])continue;
        go(u,root,E[i].cost,++cnt);
    }
    for(int i=head[root];~i;i=E[i].next){
        int u=E[i].to;
        if(vis[u])continue;
        solve(u);
    }
}
int query(int v,LL x)
{
    if(x<0)return 0;
    return std::upper_bound(vs[v].begin(),vs[v].end(),x)-vs[v].begin();
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    memset(head,-1,sizeof head);si=cnt=0;
    for(int i=1,u,v,w;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    solve(getroot(1));
    for(int i=1;i<=cnt;i++){
        std::sort(vs[i].begin(),vs[i].end());
    }
    LL L;
    for(int i=0,v;i<q;i++){
        scanf("%d%I64d",&v,&L);
        int ans=0;
        for(int j=0;j<vec[v].size();j++){
            Node tmp=vec[v][j];
            ans+=query(tmp.root,L-tmp.dis);
            if(~tmp.subtree)ans-=query(tmp.subtree,L-tmp.dis);
        }
        printf("%d\n",ans);
    }
	return 0;
}

#include<bits/stdc++.h>
#define MAXN 110000
using namespace std;
int head[MAXN],si,sz[MAXN],id[MAXN],W[MAXN],que[MAXN],fa[MAXN],cnt,vis[MAXN],dir[MAXN],N,dist[MAXN];
struct edge{
    int to,next;
}E[MAXN*2];
struct node{
    int root,dis,subtree,dir;
    node(int _root=0,int _dis=0,int _subtree=0,int _dir=0){
        root=_root;
        dis=_dis;
        subtree=_subtree;
        dir=_dir;
    }
};
vector<node>vec[MAXN];
struct BIT{
    vector<int> bit[3];
    void init()
    {
        memset(bit,0,sizeof bit);
    }
    void add(int dir,int v)
    {
        bit[dir].push_back(v);
    }
    int query(int v,int dir)
    {
        if(!bit[dir].size()||v<bit[dir][0])return 0;
        return upper_bound(bit[dir].begin(),bit[dir].end(),v)-bit[dir].begin();
    }
}Q[MAXN*3];
void add_edge(int u,int v)
{
    E[si].to=v;
    E[si].next=head[u];
    head[u]=si++;
}
int get_root(int root,int &tot)
{
    int res=N+1;
    int l=0,r=0;
    fa[root]=0;
    for(que[r++]=root;l<r;l++){
        int v=que[l];
        for(int i=head[v];~i;i=E[i].next){
            int u=E[i].to;
            if(vis[u]||fa[v]==u)continue;
            fa[u]=v;
            que[r++]=u;
        }
    }
    tot=r;
    for(;l;l--){
        int v=que[l-1],m=0;
        sz[v]=1;
        for(int i=head[v];~i;i=E[i].next){
            int u=E[i].to;
            if(fa[v]==u||vis[u])continue;
            sz[v]+=sz[u];
            m=max(m,sz[u]);
        }
        m=max(m,r-sz[v]);
        if(m<res){
            res=m;
            root=v;
        }
    }
    return root;
}
void go(int now,int root,int subtree)
{
    dist[now]=1;fa[now]=root;
    dir[now]=0;
    if(W[now]>W[root])dir[now]=1;
    else if(W[now]<W[root])dir[now]=2;
    int l=0,r=0;
    for(que[r++]=now;l<r;l++){
        int v=que[l];
        vec[v].push_back(node(id[root],dist[v],subtree,dir[v]));
        for(int i=head[v];~i;i=E[i].next){
            int u=E[i].to;
            if(vis[u]||fa[v]==u)continue;
            fa[u]=v;
            dist[u]=dist[v]+1;
            if(dir[v]==0){
                if(W[u]>W[v]){
                    dir[u]=1;
                }
                else if(W[u]<W[v]){
                    dir[u]=2;
                }
                else dir[u]=0;
                que[r++]=u;
            }
            else if(dir[v]==1&&W[u]>=W[v]){
                dir[u]=1;
                que[r++]=u;
            }
            else if(dir[v]==2&&W[u]<=W[v]){
                dir[u]=2;
                que[r++]=u;
            }
        }
    }
    Q[subtree].init();
  //  printf("go(%d,%d,%d):\n",now,root,subtree);
    for(int i=0;i<r;i++){
        int v=que[i];
     //   printf("add(%d:%d,%d)\n",v,dist[v],dir[v]);
        Q[id[root]].add(dir[v],dist[v]);
        Q[subtree].add(dir[v],dist[v]);
    }
}
void solve(int now)
{
    int tot=0;
    int root=get_root(now,tot);
    vis[root]=true;
    id[root]=cnt++;
 //   printf("solve(%d):%d__%d\n",now,root,tot);
    Q[id[root]].init();
    Q[id[root]].add(0,0);
   // Q[id[root]].add(1,0);
   // Q[id[root]].add(2,0);
    vec[root].push_back(node(id[root],0,-1,0));
    for(int i=head[root];~i;i=E[i].next){
        int u=E[i].to;
        if(vis[u])continue;
        go(u,root,cnt);
        cnt++;
    }
    for(int i=head[root];~i;i=E[i].next){
        int u=E[i].to;
        if(vis[u])continue;
        solve(u);
    }
}
int main()
{
   // freopen("in.txt","r",stdin);
 //   freopen("test.txt","w",stdout);
    int T,q;scanf("%d",&T);
    while(T--){
        memset(head,-1,sizeof head);si=0;
        memset(vis,0,sizeof vis);cnt=0;
        memset(vec,0,sizeof vec);
        scanf("%d%d",&N,&q);
        for(int i=1;i<=N;i++)scanf("%d",&W[i]);
        for(int i=1,u,v;i<N;i++){
            scanf("%d%d",&u,&v);
            add_edge(u,v);
            add_edge(v,u);
        }
        solve(1);
        for(int i=0;i<cnt;i++){
            for(int j=0;j<3;j++){
           //     printf("Q[%d][%d].size()=%d\n",i,j,Q[i].bit[j].size());
                sort(Q[i].bit[j].begin(),Q[i].bit[j].end());
            }
        }
        for(int i=0,v,L;i<q;i++){
            scanf("%d%d",&v,&L);
            int ans=0;
            for(int j=0;j<vec[v].size();j++){
                node tmp=vec[v][j];
             //   printf("%d___%d__%d\n",tmp.root,tmp.dis,tmp.dir);
                if(tmp.dir!=2){
                    ans+=Q[tmp.root].query(L-tmp.dis,2);
                    if(~tmp.subtree){
                        ans-=Q[tmp.subtree].query(L-tmp.dis,2);
                    }
                }
                if(tmp.dir!=1){
                    ans+=Q[tmp.root].query(L-tmp.dis,1);
                    if(~tmp.subtree){
                        ans-=Q[tmp.subtree].query(L-tmp.dis,1);
                    }
                }
                ans+=Q[tmp.root].query(L-tmp.dis,0);
                if(~tmp.subtree){
                    ans-=Q[tmp.subtree].query(L-tmp.dis,0);
                }
            }
            printf("%d\n",ans);
        }
    }
}

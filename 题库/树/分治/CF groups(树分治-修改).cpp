#include<bits/stdc++.h>
#define MAXN 200005
using namespace std;
typedef long long LL;
const LL mod = 1000000007;
LL cc[MAXN*60];
LL *cc_tail;
struct BIT{
    LL *bit;
    int n;
    void init(int _n)
    {
        n=_n+1;
        bit=cc_tail;
        cc_tail=cc_tail+_n+2;
        memset(bit,0,sizeof(LL)*(n+2));
    }
    void add(int v,int x)
    {
        while(v<=n){
            bit[v]+=x;
            bit[v]%=mod;
            v+=v&-v;
        }
    }
    LL query(int v)
    {
        LL ans=0;
        while(v){
            ans+=bit[v];
            v-=v&-v;
        }
        return ans%mod;
    }
}A[MAXN*3];
struct edge{
    int to,next;
}E[MAXN*2];
struct Node{
    int root,dis,subtree;
    Node(int _root=0,int _dis=0,int _subtree=0){
        root=_root,dis=_dis,subtree=_subtree;
    }
};
vector<Node> vec[MAXN];
int head[MAXN],id[MAXN],si,N,que[MAXN],vis[MAXN],sz[MAXN],cnt,dist[MAXN],fa[MAXN];
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
void go(int v,int root,int subtree)
{
    fa[v]=root;
    dist[v]=1;
    int l=0,r=0;
    for(que[r++]=v;l<r;l++){
        int u=que[l];
        for(int i=head[u];~i;i=E[i].next){
            if(vis[E[i].to]||fa[u]==E[i].to)continue;
            dist[E[i].to]=dist[u]+1;
            fa[E[i].to]=u;
            que[r++]=E[i].to;
        }
    }
    A[subtree].init(r+1);
    for(int i=0;i<l;i++){
        int u=que[i];
        vec[u].push_back(Node(id[root],dist[u],subtree));
    }
}
void solve(int root)
{
    int tot=0;
    root=get_root(root,tot);
    vis[root]=true;
    id[root]=++cnt;
    vec[root].push_back(Node(id[root],0,-1));
    A[id[root]].init(tot+1);
    for(int i=head[root];~i;i=E[i].next){
        int u=E[i].to;
        if(vis[u])continue;
        ++cnt;
        go(u,root,cnt);
    }
    for(int i=head[root];~i;i=E[i].next){
        int u=E[i].to;
        if(vis[u])continue;
        solve(u);
    }
}
int main()
{
    int q;
    scanf("%d%d",&N,&q);
    memset(head,-1,sizeof head);si=0;cnt=0;
    cc_tail=cc;
    for(int i=1,v,u;i<N;i++){
        scanf("%d%d",&u,&v);
        add_edge(u,v);
        add_edge(v,u);
    }
    solve(1);
    for(int i=0,v,d,p;i<q;i++){
        scanf("%d%d%d",&v,&d,&p);
        for(int j=0;j<vec[v].size();j++){
            Node tmp=vec[v][j];
            if(d<tmp.dis)continue;
            A[tmp.root].add(1,p);
            A[tmp.root].add(d-tmp.dis+2,-p);
            if(~tmp.subtree){
                A[tmp.subtree].add(1,p);
                A[tmp.subtree].add(d-tmp.dis+2,-p);
            }
        }
    }
   // printf("__end\n");
    for(int i=1;i<=N;i++){
        LL ans=0;
       // printf("%d___\n",i);
        for(int j=0;j<vec[i].size();j++){
            Node tmp=vec[i][j];
          //  printf("%d____%d\n",tmp.root,tmp.dis);
            ans+=A[tmp.root].query(tmp.dis+1);
            if(~tmp.subtree){
                ans-=A[tmp.subtree].query(tmp.dis+1);
            }
            ans=(ans%mod+mod)%mod;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

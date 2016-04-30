//最小生成树

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#define N 111
using namespace std;
const int INF=0x3f3f3f3f;
int last[N];//
struct edge
{
    int u,v,w,nxt;
    edge(){}
    edge(int uu,int vv,int ww,int n):u(uu),v(vv),w(ww),nxt(n){}
}e[N*N];
typedef pair<int,int> PII;
int ans,n,m;//
bool vis[N];//
int prim(int s)
{
    priority_queue<PII,vector<PII>,greater<PII> > que;
    ans=0;

    que.push(PII(0,s));
    int prev=0;
    int num=0;
    while(!que.empty())
    {
        int u=que.top().second;
        int w=que.top().first;
        que.pop();
        if(vis[u]) continue;
        ans+=w;
        vis[u]=true;
        num++;
        if(num==n) return ans;
        for(int i=last[u];~i;i=e[i].nxt)
        {
            int v=e[i].v;
            w=e[i].w;
            if(vis[v]) continue;
            que.push(PII(w,v));
        }
    }
    if(num!=n) return -1;
}
//////////

//次小生成树
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#define N 111
using namespace std;
const int INF=0x3f3f3f3f;
int last[N];//
struct edge
{
    int u,v,w,nxt;
    edge(){}
    edge(int uu,int vv,int ww,int n):u(uu),v(vv),w(ww),nxt(n){}
}e[N*N*2];
typedef pair<int,pair<int,int> >  PII;//三元组
int ans,n,m;//
bool vis[N];//
int pre[N];//
int eMax[N][N];//最小生成树中u,v路径上的最大边
int prim(int s)
{
    priority_queue<PII,vector<PII>,greater<PII> > que;
    ans=0;

    que.push(PII(0,pair<int,int>(0,s)));
    int num=0;
    while(!que.empty())
    {
        int prev=que.top().second.first;
        int u=que.top().second.second;
        int w=que.top().first;
        que.pop();
        if(vis[u]) continue;
        ans+=w;
        vis[u]=true;
        num++;
        pre[u]=prev;
        for(int i=1;i<=n;i++)
        {
            if(vis[i] && i!=u )
            {
                eMax[i][u]=eMax[u][i]=max(eMax[i][pre[u]],w);
            }
        }
        if(num==n) return ans;
        for(int i=last[u];i!=-1;i=e[i].nxt)
        {
            int v=e[i].v;
            w=e[i].w;
            if(vis[v]) continue;
            que.push(PII(w,pair<int,int>(u,v)));
        }
    }
    if(num!=n) return -1;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        memset(last,-1,sizeof(last));
        memset(vis,0,sizeof(vis));
        memset(eMax,0,sizeof(eMax));
        memset(pre,0,sizeof(pre));
        ans=0;
        int edgeNum=0;

        scanf("%d%d",&n,&m);
        for(int i=0;i<m;i++)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            e[edgeNum]=edge(u,v,w,last[u]),last[u]=edgeNum++;
            e[edgeNum]=edge(v,u,w,last[v]),last[v]=edgeNum++;
        }
        ans=prim(1);
        if(ans==-1)
        {
            printf("0\n");
            continue;
        }
        bool flag=true;
        for(int i=0;i<edgeNum && flag;i+=2)
        {
            int u=e[i].u,v=e[i].v,w=e[i].w;
            if(pre[u]==v || pre[v]==u)
                continue;
            if(w==eMax[u][v]) flag=false;
        }
        if(!flag)
            printf("Not Unique!\n");
        else
            printf("%d\n",ans);
    }
    return 0;
}

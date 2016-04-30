#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
//const long long INF=0x7fffffffffffffffL;
#define N 100010
struct edge
{
    int v,w,nxt;
}e[N],reve[N];
int last[1010];
int revlast[1010];
typedef pair<int,int> PII;
int V;
int d[1010];
priority_queue<PII,vector<PII>,greater<PII> > que;
void dijkstra(int s)
{
    memset(d,0x3f,sizeof(d));
    //fill(d+1,d+V+1,INF);
    d[s]=0;
    que.push(PII(0,s));
    while(!que.empty())
    {
        PII pp=que.top();que.pop();
        int u=pp.second;
        if(d[u]<pp.first) continue;
        for(int i=revlast[u];i!=-1;i=reve[i].nxt){
            int v=reve[i].v,w=reve[i].w;
            if(d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                que.push(PII(d[v],v));
            }
        }
    }
}
struct A
{
    int u,g,f;
    bool operator< (const A& a) const
    {
        return f > a.f;
    }
    A(int uu=0,int gg=0,int hh=0){u=uu,g=gg,f=hh;}
};
int cnt[1010];
int Astar(int s,int t,int k)
{
    if(s==t) k++;
    priority_queue<A> Aque;
    Aque.push(A(s,0,0));
    while(!Aque.empty())
    {
        A tmp=Aque.top();Aque.pop();
        int u=tmp.u,g=tmp.g,f=tmp.f;
        cnt[u]++;
        if(cnt[u]==k && u==t) return f;
        for(int i=last[u];i!=-1;i=e[i].nxt)
        {
            int v=e[i].v,w=e[i].w;
            if(cnt[v]<k)
                Aque.push(A(v,g+w,g+w+d[v]));
        }
    }
    return -1;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    memset(last,-1,sizeof(last));
    memset(revlast,-1,sizeof(revlast));
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        e[i].v=v,e[i].w=w,e[i].nxt=last[u],last[u]=i;
        reve[i].v=u,reve[i].w=w,reve[i].nxt=revlast[v],revlast[v]=i;
    }
    int s,t,k;
    scanf("%d%d%d",&s,&t,&k);
    dijkstra(t);
    printf("%d\n",Astar(s,t,k));
    return 0;
}
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#define N 50050
using namespace std;
const int INF=0x3f3f3f3f3f3f3f3fL;
int c[N];
int last[N];
struct edge
{
    int v,w,nxt;
    edge(){}
    edge(int vv,int ww,int n):v(vv),w(ww),nxt(n){}
}e[N*2];
typedef pair<int,int> PII;
int ans,n,m;
int d[N];
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
        for(int i=last[u];i!=-1;i=e[i].nxt){
            int v=e[i].v,w=e[i].w;
            if(d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                que.push(PII(d[v],v));
            }
        }
    }
}
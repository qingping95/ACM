#include <iostream>  
#include <cstdio>  
#include <cmath>  
#include <cstring>  
#include <queue>  
#define N 400100  
using namespace std;  
struct edge  
{  
    int from,to,c,nxt;  
}e[N];  
int head[N];  
int d[N];  
int s;  
bool vis[N];  
int n,m;
void spfa(int s)  
{  
    queue<int> q;  
    memset(d,0x3f,sizeof(d));  
    d[s]=0;  
    memset(vis,0,sizeof(vis));  
  
    q.push(s);  
    vis[s]=1;  
    while(!q.empty())  
    {  
        int x=q.front();  
        q.pop();  
        vis[x]=0;  
        for(int k=head[x];k!=-1;k=e[k].nxt)  
        {  
            if(d[e[k].to]>d[e[k].from]+e[k].c)  
            {  
                d[e[k].to]=d[e[k].from]+e[k].c;  
                if(!vis[e[k].to])  
                {  
                    vis[e[k].to]=1;  
                    q.push(e[k].to);  
                }  
            }  
        }  
    }  
  
}  

//DFS版SPFA(判断正/负环非常快)伪代码
Void SPFA(Node) { 
    Instack[Node]=true; 
    For (Node,v) ∈E 
        If dis[Node]+edge(Node,v)<dis[v] then { 
			dis[v]=dis[Node]+edge(Node,v); 
			If not Instack[v] then 
				SPFA(v); 
			Else{ 
				Contain an negative cycle. 
				Halt; 
			} 
		} 
    Instack [Node] =false; 
} 

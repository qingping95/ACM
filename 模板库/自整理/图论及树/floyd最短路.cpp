
int d[N][N];
int n;

void floyd(int d[][N])
{
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
}


////floyd 快速幂求解恰好有N条边的最短路
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define N 222
int v[1111];
int tmp[N][N];
int n,t,s,e;
int d[N][N];
int ans[N][N];
int V;

void floyd(int target[][N],int a[][N],int b[][N])
{
    memset(tmp,0x3f,sizeof(tmp));
    for(int k=0;k<V;k++)
        for(int i=0;i<V;i++)
            for(int j=0;j<V;j++)
                 tmp[i][j]=min((long long)tmp[i][j],(long long)a[i][k]+b[k][j]);
    for(int i=0;i<V;i++)
        for(int j=0;j<V;j++)
            target[i][j]=tmp[i][j];
}

void quickfloyd(int n)
{
    while(n)
    {
        if(n&1)
        {
            floyd(ans,ans,d);
        }
        floyd(d,d,d);
        n>>=1;
    }
}

int main()
{
    memset(v,-1,sizeof(v));
    memset(d,0x3f,sizeof(d));
    scanf("%d%d%d%d",&n,&t,&s,&e);
    V=0;
    for(int i=0;i<t;i++)
    {
        int a,b,l;
        scanf("%d%d%d",&l,&a,&b);
        if(v[a]==-1) v[a]=V++;
        if(v[b]==-1) v[b]=V++;
        d[v[a]][v[b]]=l;
        d[v[b]][v[a]]=l;
    }
    memset(ans,0x3f,sizeof(ans));
    for(int i=0;i<V;i++)
        ans[i][i]=0;
    quickfloyd(n);
    printf("%d\n",ans[v[s]][v[e]]);
    return 0;
}
/////
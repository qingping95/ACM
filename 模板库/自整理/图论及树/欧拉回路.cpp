#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define N 55
using namespace std;
int du[N];
int par[N];
int eNum[N][N];
int Find(int x)
{
    return par[x]==x?x:(par[x]=Find(par[x]));
}
bool connectable(int u)
{
    for(int i=1;i<N;i++)
        if(du[i] && (Find(i)!=Find(u) || (du[i] & 1)))
            return false;
    return true;
}
int dfs(int u)
{
    for(int i=1;i<N;i++)
    {
        if(eNum[u][i])
        {
            eNum[i][u]--;
            eNum[u][i]--;
            dfs(i);
            printf("%d %d\n",i,u);
        }
    }
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int t,cas=1;
    scanf("%d",&t);
    while(t--)
    {
        printf("Case #%d\n",cas++);
        memset(du,0,sizeof(du));
        memset(eNum,0,sizeof(eNum));
        for(int i=1;i<N;i++)
            par[i]=i;
        int n;
        int V=0;
        scanf("%d",&n);
        int pre;
        for(int i=0;i<n;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            pre=u;
            du[u]++,du[v]++;
            eNum[u][v]++;
            eNum[v][u]++;
            if(Find(u)!=Find(v))	//判断联通性
                par[Find(u)]=Find(v);
        }
        if(!connectable(pre))//判断联通性！
		{
            printf("some beads may be lost\n");
            if(t) printf("\n");
            continue;
        }
        dfs(pre);
        if(t) printf("\n");
    }
    return 0;
}
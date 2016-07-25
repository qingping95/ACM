/*
*Rainto96
*Beijing University of Posts and Telecommunications School of Software Engineering
*http://blog.csdn.net/u011775691
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <climits>
using namespace std;
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define VINT vector<ll>
#define PII pair<ll,ll>
#define MP(x,y) make_pair((x),(y))
#define ll long long
#define ull unsigned long long
#define MEM0(x)  memset(x,0,sizeof(x))
#define MEM(x,val) memset((x),val,sizeof(x))
#define scan(x) scanf("%d",&(x))
#define scan2(x,y) scanf("%d%d",&(x),&(y))
#define scan3(x,y,z) scanf("%d%d%d",&(x),&(y),&(z))
#define scan4(x,y,z,k) scanf("%d%d%d%d",&(x),&(y),&(z),&(k))
#define Max(a,b) a=max(a,b)
#define Min(a,b) a=min(a,b)
#define fuck(x) cout<<#x<<" - "<<x<<endl
int n,K;
struct Edge{
    int u,v,w;
};
vector<Edge > G[101111];
int C[13][13];
int fae[101111];
int S[101111][13];
int plusOneTree(int u,int q,int k,int euq){
    int sum=0;
    int euqs=1;
    for(int i=0;i<=k;i++){
        sum += C[k][i] * S[q][k-i] * euqs;
        euqs *= euq;
    }
    return sum;
}
int dfs0(int now,int fa, int fae_val){
    if(fa!=-1){
        fae[now] = fae_val;
    }
    int u = 1;
    for(int i=0;i<G[now].size();i++){
        int to = G[now][i].v;
        int w = G[now][i].w;
        if(to == fa)continue;
        u+=dfs0(to,now,w);
    }
    S[now][0] = max(1,u-1);
    return u;
}
void dfs1(int now, int fa){
    for(int i=0;i<G[now].size();i++){
        int to = G[now][i].v;
        int w = G[now][i].w;
        if(to == fa)continue;
        dfs1(to,now);
        for(int k=1;k<=K;k++){
            S[now][k] += plusOneTree(now,to,k,w);
        }
    }
}
int ans;
void dfs2(int now,int fa){
    if(fa != -1){
        S[now][0] += S[fa][0] + 1;
        for(int k=1;k<=K;k++){
            S[now][k] += plusOneTree(now,fa,k,fae[now]);
        }
        ans = min(ans, S[now][K]);
    }
    for(int i=0;i<G[now].size();i++){
        int to = G[now][i].v;
        int w = G[now][i].w;
        if(to == fa)continue;

        S[now][0] -= S[to][0] + 1;
        for(int k=1;k<=K;k++){
            S[now][k] -= plusOneTree(now,to,k,w);
        }

        dfs2(to,now);

        S[now][0] += S[to][0] + 1;
        for(int k=1;k<=K;k++){
            S[now][k] += plusOneTree(now,to,k,w);
        }
    }
    if(fa != -1){
        S[now][0] -= S[fa][0] + 1;
        for(int k=1;k<=K;k++){
            S[now][k] -= plusOneTree(now,fa,k,fae[now]);
        }
        ans = min(ans, S[now][K]);
    }
}
int main(){
    freopen("F:/in.txt","r",stdin);
    C[0][0]=1;
    for(int i=1;i<13;i++){
        C[i][0] = C[i][i] = 1;
        for(int j=1;j+j<=i;j++){
            C[i][i-j] = C[i][j] = C[i-1][j] + C[i-1][j-1];
        }
    }
    while(scan2(n,K) == 2){
        memset(S,0,sizeof(S));
        ans = 0x3f3f3f3f;///mind!!!
        for(int i=0;i<=n;i++) G[i].clear();
        for(int i=0;i<n-1;i++){
            int u,v,w;
            scan3(u,v,w);
            u++;v++;
            G[u].pb((Edge){u,v,w});
            G[v].pb((Edge){v,u,w});
        }
        dfs0(1,-1,-1);
        dfs1(1,-1);
        ans = min(ans, S[1][K]);
        cout<<ans<<endl;
        dfs2(1,-1);
        printf("%d\n",ans);
    }
    return 0;
}

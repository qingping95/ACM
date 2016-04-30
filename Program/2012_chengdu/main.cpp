#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 100010
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int INF=0x3f3f3f3f;
const double eps = 1e-10;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
        //freopen("/home/qingping/out.txt","w",stdout);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
template<class T>
inline bool read(T &n){
    T x = 0, tmp = 1; char c = getchar();
    while((c < '0' || c > '9') && c != '-' && c != EOF) c = getchar();
    if(c == EOF) return false;
    if(c == '-') c = getchar(), tmp = -1;
    while(c >= '0' && c <= '9') x *= 10, x += (c - '0'), c = getchar();
    n = x * tmp;
    return true;
}
template <class T>
inline void write(T n){
    if(n < 0){
        putchar('-');
        n = -n;
    }
    int len = 0, data[20];
    while(n){
        data[len++] = n%10;
        n/=10;
    }
    if(!len) data[len++] = 0;
    while(len--) putchar(data[len] + 48);
}

const int MAXN = 100010;
int n,m;
int deg[MAXN];//
bool weight[MAXN];//
int col[MAXN];//
LL w[MAXN][2];//
vector<PII > vc[MAXN];//
struct Edge{
    int v,w,nxt;
};
//vector<Edge> G[MAXN];//
int head[MAXN];
Edge ed[MAXN*2];
int tot;
inline void addEdge(int u,int v,int W){
    ed[tot] = (Edge){v,W,head[u]};
    head[u] = tot++;
}
struct ED{
    int u,v,w;
    bool operator<(const ED& e) const{
        return u==e.u? v<e.v : u<e.u;
    }
}que[MAXN];

#define TO first
#define WT second
int main()
{
    Open();
    int Cas = 1;
    int zzz=1;
    zzz--;
    while(scanf("%d%d",&n,&m) == 2){
        if(Cas>=10) n/=zzz;
        printf("Case %d:\n",Cas++);
        tot=0;
        for(int i=0;i<=n+5;i++)
            vc[i].clear();

        memset(w,0,sizeof(w));
        memset(deg,0,sizeof(deg));
        memset(weight,0,sizeof(weight));
        memset(head,-1,sizeof(head));
        LL Ans10=0 , Ans11=0, Ans00=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&col[i]);
            //read(col[i]);
        }
        vector<ED> ved;
        for(int i=0;i<m;i++){
            int u,v,W;
            scanf("%d%d%d",&u,&v,&W);
            if(u>v) swap(u,v);
            ved.push_back((ED){u,v,W});
            //read(u);read(v);read(W);
            //cerr<<u<<" "<<v<<" "<<w<<endl;
            //G[u].push_back((Edge){v,W});
            //G[v].push_back((Edge){u,W});

        }
        sort(ved.begin(),ved.end());
        int tao = 0;
        que[tao++]=(ED){ved[0].u,ved[0].v,ved[0].w};
        for(int i=1;i<m;i++){
            if(ved[i].u == ved[i-1].u && ved[i].v == ved[i-1].v) {

            }else que[tao++] = ved[i];
        }
        int SQRT=sqrt(2*m);
        for(int i=1;i<=n;i++) if(deg[i]>=SQRT) weight[i] = true;
        for(int i=1;i<=n;i++) if(weight[i]){
            for(int j=head[i];j!=-1;j=ed[j].nxt){
                int to = ed[j].v;
                if(weight[to]) vc[i].push_back(make_pair(to,ed[j].w));
                w[i][col[to]] += ed[j].w;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=head[i];j!=-1;j=ed[j].nxt){
                int to = ed[j].v;
                if(col[i]^col[to]) Ans10 += ed[j].w;
                else if(col[i] == 0) Ans00 += ed[j].w;
                else Ans11 += ed[j].w;
            }
        }
        Ans11/=2 , Ans10/=2 , Ans00/=2;
        //cerr<<Ans11<<" "<<Ans10<<" "<<Ans00<<endl;
        int Q;scanf("%d",&Q);
        char op[111];
        while(Q--)
        {
            scanf("%s",op);
            if(op[0]=='A'){
                int t1,t2;
                scanf("%d%d",&t1,&t2);
                //read(t1);read(t2);
                if(t1<t2) swap(t1,t2);
                LL ans;
                if(t1==0 && t2==0) ans = Ans00;
                else if(t1==1 && t2 ==0 ) ans = Ans10;
                else ans = Ans11;
                printf("%lld\n",ans);
                //write(ans);
                //putchar('\n');
            }else{
                int u;
                scanf("%d",&u);
                //read(u);
                if(weight[u]){
                    if(col[u]==1){
                        col[u] = 0;
                        Ans11 -= w[u][1];
                        Ans10 = Ans10 - w[u][0] + w[u][1];
                        Ans00 += w[u][0];
                        for(int i=0;i<vc[u].size();i++){
                            int v= vc[u][i].TO;
                            w[v][1] -= vc[u][i].WT;
                            w[v][0] += vc[u][i].WT;
                        }
                    }else{
                        col[u] = 1;
                        Ans11 += w[u][1];
                        Ans10 = Ans10 - w[u][1] + w[u][0];
                        Ans00 -= w[u][0];
                        for(int i=0;i<vc[u].size();i++){
                            int v= vc[u][i].TO;
                            w[v][0] -= vc[u][i].WT;
                            w[v][1] += vc[u][i].WT;
                        }
                    }
                }else{
                    if(col[u]==1){
                        col[u] = 0;
                        for(int i=head[u];i!=-1;i=ed[i].nxt){
                            int v = ed[i].v;
                            int W = ed[i].w;
                            if(weight[v])
                                w[v][1] -= W, w[v][0] += W;
                            if(col[v]==0) Ans10 -= W, Ans00 += W;
                            else Ans11 -= W, Ans10 += W;
                        }
                    }else{
                        col[u] = 1;
                        for(int i=head[u];i!=-1;i=ed[i].nxt){
                            int v = ed[i].v;
                            int W = ed[i].w;
                            if(weight[v])
                                w[v][0] -= W, w[v][1] += W;
                            if(col[v]==0) Ans10 += W, Ans00 -= W;
                            else Ans11 += W, Ans10 -= W;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
/*
4 3
0 0 0 0
1 2 1
2 3 2
3 4 3
4
Asksum 0 0
Change 2
Asksum 0 0
Asksum 0 1

4 3
0 1 0 0
1 2 1
2 3 2
3 4 3
4
Asksum 0 0
Change 3
Asksum 0 0
Asksum 0 1
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <ctime>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef pair<int, int> PII;
const int INF=0x3f3f3f3f;
const double eps = 1e-10;
typedef long long LL;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int f[1111];
int a[1111];
int v[1111];
int n,L;
LL dp[2][4044][2][2];
//#define Max(a,b) a = max(a,b)
#define Max(a,b) (a) = (a)>(b)?(a):(b)

template<class T>
inline bool read(T &n){
    T x=0, tmp=1; char c=getchar();
    while((c < '0' || c > '9') && c != '-' && c != EOF) c=getchar();
    if(c == EOF) return false;
    if(c == '-') c=  getchar() , tmp=-1;
    while(c >= '0' && c <= '9') x *= 10, x+= (c - '0') , c= getchar();
    n = x * tmp;
    return true;
}
struct PIII{
    int j;
    int k,q;
    PIII(int j,int k,int q):j(j),k(k),q(q){}
};
int que[2][111111];
int tail[2];
int vis[11111];
int VP = 1;
int main()
{
    freopen("/home/qingping/in2.txt","r",stdin);
    //freopen("/home/qingping/outTrue2.txt","w",stdout);
    int T;scanf("%d",&T);
    for(int Cas = 1; Cas <= T;Cas++){
        printf("Case #%d: ",Cas);
        //scanf("%d%d",&n,&L);
        read(n);read(L);
        memset(dp,0,sizeof(dp));
        memset(tail,0,sizeof(tail));
        L*=2;
        for(int i=0;i<n;i++){
            //scanf("%d%d",&a[i] , &v[i]);
            read(a[i]); read(v[i]);
            a[i]*=2;
        }
        int cur = 1;
        que[cur][tail[cur]++] = 0;
        for(int i=0;i<n;i++){
            int nxt = cur ^ 1;
            memcpy(dp[nxt],dp[cur],sizeof(dp[cur]));
            for(int J=0;J<tail[cur];J++){
                int j = que[cur][J];
                for(int k=0;k<2;k++){
                    for(int q=0;q<2;q++){
                        if(j>=a[i]) {
                            if(dp[nxt][j-a[i]][k][q] < dp[cur][j][k][q] + v[i]){
                                dp[nxt][j-a[i]][k][q] = dp[cur][j][k][q] + v[i];
                                if(vis[j-a[i]]!=VP){
                                    vis[j-a[i]] = VP++;
                                    que[nxt][tail[nxt]++] = j-a[i];
                                }
                            }
                        }
                        if(k==0 && j>=(a[i]>>1)) {
                            if(dp[nxt][j-(a[i]>>1)][1][q] < dp[cur][j][k][q] + v[i]){
                                dp[nxt][j-(a[i]>>1)][1][q] = dp[cur][j][k][q] + v[i];
                                if(vis[j-(a[i]>>1)]!=VP){
                                    vis[j-(a[i]>>1)] = VP++;
                                    que[nxt][tail[nxt]++] = j-(a[i]>>1);
                                }
                            }
                        }
                        if(q==0 && j>=(a[i]>>1)) {
                            if(dp[nxt][j-(a[i]>>1)][k][1] < dp[cur][j][k][q] + v[i]){
                                dp[nxt][j-(a[i]>>1)][k][1] = dp[cur][j][k][q] + v[i];
                                if(vis[j-(a[i]>>1)]!=VP){
                                    vis[j-(a[i]>>1)] = VP++;
                                    que[nxt][tail[nxt]++] = j-(a[i]>>1);
                                }
                            }
                        }
                        //Max(dp[nxt][j][k][q] , dp[cur][j][k][q]);
                    }
                }
            }
            memset(dp[cur],0,sizeof(dp[cur]));
            tail[cur] = 0;
            cur^=1;
            VP++;
        }
        //LL maxn = *max_element(v,v+n);
        LL maxn = 0;
        for(int i=0;i<n;i++) maxn = max(maxn , (LL)v[i]);
        for(int i=0;i<=L;i++) for(int k=0;k<2;k++) for(int q=0;q<2;q++){
            maxn = max(maxn , dp[cur][i][k][q]);
        }
        printf("%lld\n",maxn);
    }
    return 0;
}


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
#define VINT vector<int>
#define PII pair<int,int>
#define MP(x,y) make_pair((x),(y))
#define ll long long
#define ull unsigned ll
#define MEM0(x)  memset(x,0,sizeof(x))
#define MEM(x,val) memset((x),val,sizeof(x))
#define scan(x) scanf("%d",&(x))
#define scan2(x,y) scanf("%d%d",&(x),&(y))
#define scan3(x,y,z) scanf("%d%d%d",&(x),&(y),&(z))
#define scan4(x,y,z,k) scanf("%d%d%d%d",&(x),&(y),&(z),&(k))
#define Max(a,b) a=max(a,b)
#define Min(a,b) a=min(a,b)
using namespace std;
const int MAXN=1022;
VINT G[MAXN];//
bool pr[MAXN][MAXN];//
int up[MAXN][MAXN];//
int dfs(int now, int fa){

        int ans=0;
        int s[11] , sum=0;
        for(int i=0;i<G[now].size();i++){
                int to = G[now][i];
                if(to == fa) continue;
                ans+=dfs(to,now);//子树的答案
                s[sum++] = to;
        }
        //cerr<<"Now:"<<now<<endl;
        //cerr<<"SonDfs : "<<ans<<endl;
        for(int i=0;i<sum;i++){
                for(int j=1;j<=up[s[i]][0];j++){
                        if(pr[up[s[i]][j]][now]){
                                //cerr<<"Son: "<<up[s[i]][j]<<" To Now:"<<now<<endl;
                                ans++ , up[s[i]][0] = 0;//子树中的点到当前根节点的答案
                                break;
                        }
                }
        }
        //cerr<<"SonToNow : "<<ans<<endl;
        int link[11][11]={0};
        for(int i=0;i<sum;i++){
                for(int j=i+1;j<sum;j++){
                        int son1 = s[i] , son2 = s[j];
                        bool goon=true;
                        for(int p1=1;p1<=up[son1][0] && goon;p1++){
                                for(int p2=1;p2<=up[son2][0] && goon;p2++){
                                        if(pr[ up[son1][p1] ][ up[son2][p2] ] ){
                                                link[i][j]=link[j][i]=true;
                                                //cerr<<"Son1:"<<i <<"<->"<<"Son2 :"<<j<<endl;
                                                goon=false;
                                                break;
                                        }
                                }
                        }
                }
        }

        int mark[1111]={0};
        for(int i=1;i<(1<<sum);i++){
                int a = i&-i;
                mark[i] = mark[i-a];
                int cnt=0;
                int tmpa=a;
                while(tmpa) tmpa>>=1 ,cnt++;
                for(int j= cnt ;j < sum;j++ ){
                        //cerr<<"JudgeLink:"<<j<<" "<<cnt-1<<endl;
                        //cerr<<"JudgeLink:"<<(i&(1<<j))<<endl;

                        if( (i&(1<<j)) && link[j][cnt-1]){
                                //cerr<<j<<" "<<cnt-1<<" son2son"<<endl;
                                mark[i] = max(mark[i] , mark[i-a-(1<<j)] + 1 );
                        }
                }
        }

        up[now][0]=0;
        up[now][++up[now][0]] = now;
        int mm=(1<<sum)-1;
        ans += mark[mm];//子树点经过当前根节点到另一子树的方案数
        //cerr<<"SonToSon : "<<ans<<endl;
        for(int i=0;i<sum;i++){
                if(mark[mm] == mark[mm-(1<<i)] ){//说明这里的点都可以上来
                        for(int j=1;j<=up[s[i]][0];j++){
                                up[now][ ++up[now][0] ] = up[s[i]][j];//维护可上来的点给上面用
                        }
                }
        }
        return ans;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("C:/OJ/in.txt","r",stdin);
	#endif
	int T;scan(T);
	while(T--){
                int n;scan(n);
                MEM0(pr);
                for(int i=0;i<MAXN;i++) up[i][0]=0;
                for(int i=0;i<=n;i++) G[i].clear();

                for(int i=0;i<n-1;i++){
                        int u,v;scan2(u,v);
                        G[u].pb(v);
                        G[v].pb(u);
                }
                int m;scan(m);
                for(int i=0;i<m;i++){
                        int q1,q2;scan2(q1,q2);
                        pr[q2][q1]=pr[q1][q2]=true;
                        //cerr<<q1<<" "<<q2<<endl;
                }
                int res = dfs(1,-1);
                printf("%d\n",res);
	}
        return 0;
}

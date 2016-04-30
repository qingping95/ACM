/*
这份代码计算
一个图中有多少条边必在MST上
也等价于，将图中某一条边更改后，用O（1）的复杂度在线回答新的图的MST数值。查询之前需要O（n^2）（n为点数）的时间来预处理。
*/
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;
#define scan(x) scanf("%d",&(x))
#define scan2(x,y) scanf("%d%d",&(x),&(y))
#define scan3(x,y,z) scanf("%d%d%d",&(x),&(y),&(z))
#define scan4(x,y,z,k) scanf("%d%d%d%d",&(x),&(y),&(z),&(k))
const int maxn = 3003;
const int maxm = maxn * maxn;
const int inf = 1000000000;

int n, m;
__int64 mst;
int map[maxn][maxn];
int dp[maxn][maxn], best[maxn][maxn];
int dis[maxn], pre[maxn];
bool vis[maxn];
vector<int> edge[maxn];
#include<iostream>
int minz(int a, int b)
{
    return a < b ? a : b;
}
void init()
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            map[i][j] = dp[i][j] = inf;
        edge[i].clear();
        vis[i] = 0;
        pre[i] = -1;
        dis[i] = inf;
    }
}
void input()
{
//cerr<<"st"<<endl;
//    int x, y, z;
//    while(m--)
//    {
//        scanf("%d%d%d", &x, &y, &z);
//        cerr<<x<<" "<<y<<" "<<z<<endl;
//        map[x][y] = map[y][x] = z;
//    }

        for(int i=0;i<n;i++){
                for(int j=i+1;j<n;j++){
                        int w;scan(w);
                        map[i][j] = map[j][i] = w;
                        //cerr<<i<<" "<<j<<" "<<w<<endl;
                }
        }
}

void prim()
{
    int i, j, k;
    for(i = 1; i < n; i++)
    {
        dis[i] = map[0][i];
        pre[i] = 0;
    }
    dis[0] = inf;
    vis[0] = 1;
    pre[0] = -1;
    mst = 0;

    for(i = 0; i < n-1; i++)
    {
        k = 0;
        for(j = 1; j < n; j++)
            if(!vis[j] && dis[k] > dis[j])
                k = j;

        vis[k] = 1;
        mst += dis[k];
       //建最小生成树
        if(pre[k] != -1)
            edge[k].push_back(pre[k]),
            edge[pre[k]].push_back(k);

        for(j = 1; j < n; j++)
            if(!vis[j] && dis[j] > map[k][j] )
                dis[j] = map[k][j], pre[j] = k;
    }
}

int dfs1(int u, int fa, int rt) // 求 点rt 到 以u为根的数及其子树的最小距离
{
    int i;
    for(i = 0; i < edge[u].size(); i++)
    {
        int v = edge[u][i];
        if(v == fa) continue;
        dp[rt][u] = minz(dp[rt][u], dfs1(v, u, rt));
    }
    if(fa != rt) dp[rt][u] = minz(dp[rt][u], map[rt][u]);
    return dp[rt][u];
}

int dfs2(int u, int fa, int rt) // 求 以rt为根的数及其子树 到 以u为根的数及其子树的最小距离
{
    int i;
    int ans = dp[u][rt];
    for(i = 0; i < edge[u].size(); i++)
    {
        int v = edge[u][i];
        if(v == fa) continue;
        ans = minz(ans, dfs2(v, u, rt));
    }
    return ans;
}

void solve()
{
    int i,j;
    for(i = 0; i < n; i++)
        dfs1(i, -1, i);
    for(i = 0; i < n; i++)
        for(j = 0; j < edge[i].size(); j++)
        {
            int v = edge[i][j];
            best[i][v] = best[v][i] = dfs2(v, i, i);
        }
}

void query()
{
//    int x, y, z;
//    double sum = 0;
//    scanf("%d", &m);
//    x=1,y=3,z=10;
//        if(pre[x] != y && pre[y] != x)
//            sum += mst * 1.0;
//        else
//            sum += mst * 1.0 - map[x][y] + minz(best[x][y], z);
//    printf("%.4f\n", sum/1);

    int ans =0 ;
    for(int i=0;i<n;i++){
        int x=i;
        for(int j=0;j<edge[i].size() ; j++){
                int y=edge[i][j];
                if(x<y) continue;
                int sum = mst - map[x][y] + best[x][y];
                //cerr<<"best:"<<best[x][y]<<endl;
                if(sum != mst){
                        ans++;
                }
        }
    }
    printf("%d\n",ans);
}

//int main()
//{
//freopen("C:/OJ/in.txt","r",stdin);
//    while( ~scanf("%d%d", &n, &m) && n + m)
//    {
//        init();
//        input();
//        prim();
//        solve();
//        query();
//    }
//    return 0;
//}

int main(){
    #ifndef ONLINE_JUDGE
		freopen("C:/OJ/in.txt","r",stdin);
	#endif
	int T;scan(T);
	while(T--){
                scan(n);
                m=n-1;
                init();
                input();
               // cerr<<"start:"<<map[0][1]<<endl;
                prim();
                //std::cerr<<mst<<std::endl;
                solve();
                query();
               // cerr<<"end:"<<map[0][1]<<endl;
	}
}
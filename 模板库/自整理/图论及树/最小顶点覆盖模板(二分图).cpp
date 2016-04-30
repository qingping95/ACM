const int MAXN=;//$
////////////////最小顶点覆盖/二分图最大匹配///////////////////
//下标从0开始
struct BPM{
    int n,m;
    vector<int > G[MAXN];
    int left[MAXN];
    bool T[MAXN];

    int right[MAXN];
    bool S[MAXN];

    void init(int n,int m){
        this -> n = n;
        this -> m = m;
        for(int i = 0;i < MAXN;i++) G[i].clear();
    }

    void add_edge(int u,int v){
        G[u].push_back(v);
    }

    bool match(int u){
        S[u] = true;
        for(int i = 0;i < G[u].size();i++){
            int v = G[u][i];
            if(!T[v]){
                T[v] = true;
                if(left[v] == -1 || match(left[v])){
                    left[v] = u;
                    right[u] = v;
                    return true;
                }
            }
        }
        return false;
    }
	//最大匹配数
    int solve(){
        memset(left,-1,sizeof(left));
        memset(right,-1,sizeof(right));
        int ans = 0;
        for(int u = 0;u < n;u++){
            memset(S,0,sizeof(S));
            memset(T,0,sizeof(T));
            if(match(u))    ans++;
        }
        return ans;
    }
    //计算最小顶点覆盖，返回点数，覆盖哪些点分别在X，Y中
    int mincover(vector<int>& X,vector<int>& Y){
        int ans = solve();
        memset(S,0,sizeof(S));
        memset(T,0,sizeof(T));
        for(int u = 0;u < n;u++)
            if(right[u] == -1)  match(u);
        for(int u = 0;u < n;u++)
            if(!S[u])   X.push_back(u);
        for(int v = 0;v < m;v++)
            if(T[v])   Y.push_back(v);
        return  ans;
    }
}solver;
/*how to use
solver.init(m,n);//左边m个点，右边n个点
...solver.AddEdge(u,v)  //下标从0开始
vector<int > X,Y;
int point_num=solver.mincover(X,Y);//最小覆盖点数，也是最大匹配数
//输出覆盖了哪些点
for(int i = 0;i < X.size();i++)
    printf(" r%d",X[i]);
for(int j = 0;j < Y.size();j++)
    printf(" c%d",Y[j]);
*/
////////////////最小顶点覆盖///////////////////



const int maxn = 1000 + 5;

struct BPM{
    int n,m;
    vector<int > G[maxn];
    int left[maxn];
    bool T[maxn];

    int right[maxn];
    bool S[maxn];

    void init(int n,int m){
        this -> n = n;
        this -> m = m;
        for(int i = 0;i < maxn;i++) G[i].clear();
    }

    void AddEdge(int u,int v){
        G[u].push_back(v);
    }

    bool match(int u){
        S[u] = true;
        for(int i = 0;i < G[u].size();i++){
            int v = G[u][i];
            if(!T[v]){
                T[v] = true;
                if(left[v] == -1 || match(left[v])){
                    left[v] = u;
                    right[u] = v;
                    return true;
                }
            }
        }
        return false;
    }

    int solve(){
        memset(left,-1,sizeof(left));
        memset(right,-1,sizeof(right));
        int ans = 0;
        for(int u = 0;u < n;u++){
            memset(S,0,sizeof(S));
            memset(T,0,sizeof(T));
            if(match(u))    ans++;
        }
        return ans;
    }

    int mincover(vector<int>& X,vector<int>& Y){
        int ans = solve();
        memset(S,0,sizeof(S));
        memset(T,0,sizeof(T));
        for(int u = 0;u < n;u++)
            if(right[u] == -1)  match(u);
        for(int u = 0;u < n;u++)
            if(!S[u])   X.push_back(u);
        for(int v = 0;v < n;v++)
            if(T[v])   Y.push_back(v);
        return  ans;
    }
};

BPM solver;

int main(){
    int n,r,c;

    while(scanf("%d%d%d",&r,&c,&n)){
        if(r == 0 && c == 0 && n == 0)  break;
        solver.init(r,c);
        while(n--){
            int x,y;
            scanf("%d%d",&x,&y);x--;y--;//模版中编号是从0开始的
            solver.AddEdge(x,y);
        }
        vector<int> X,Y;
        printf("%d",solver.mincover(X,Y));
        for(int i = 0;i < X.size();i++)
            printf(" r%d",X[i]+1);//最后别忘了加回来
        for(int j = 0;j < Y.size();j++)
            printf(" c%d",Y[j]+1);
        printf("\n");
    }
    return 0;
}




//如今的版本：
/*
	此版本可处理重边。
	st: 某节点的dfs序
	bccno: 某条边属于的分量编号
	Tn: time_stamp
	b_cnt: 分量编号标记
	G: 图
	iscut：标记某个点是否割点
*/

int st[N], bccno[N*10], Tn, b_cnt;
vector<PII > G[N];
stack<int> S;
int iscut[N];
int dfs(int u, int fa)
{
    int lowu = st[u] = ++Tn;
    int child = 0;
    bool flag = true;
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i].first;
        int No = G[u][i].second;
        if(!st[v]){
            S.push(No);
            child++;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if(lowv >= st[u]){
                iscut[u] = 1;
                b_cnt++;
                while(true)
                {
                    int curNo = S.top();S.pop();
                    bccno[curNo] = b_cnt;
                    if(curNo == No) break;
                }
            }
        }else if(st[v] < st[u]){
            if(v == fa && flag) {flag = false; continue;}
            S.push(No);
            lowu = min(lowu, st[v]);
        }
    }
    if(fa < 0 && child == 1) iscut[u] = 0;
    return lowu;
}
void find_bcc(int n)
{
    memset(st, 0, sizeof(st));
    memset(iscut, 0, sizeof(iscut));
    memset(bccno, 0, sizeof(bccno));

    Tn = b_cnt = 0;
    for(int i = 1; i <= n; i++)
        if(!st[i]) dfs(i, -1);
}



typedef pair<int,int> edge;

int pre[N],iscut[N],bccno[N],dfs_clock,bcc_cnt;
vector<int> G[N],bcc[N];

stack<edge> S;

/*
	点-双联通
    G[],上述数组中唯一需要初始化的数组
    dfs_clock 时钟标记，记录访问路径中这个点的访问下标
    bcc_cnt 双联通分量的数量
    bccno[] 数组表示每个点属于的双联通分量，有的点可能属于多个分量
    iscut[] 标记该点是否为割顶
    pre[] 每个点的时钟标记
    bcc[] 每个双联通分量中有哪些点
*/

int dfs(int u,int fa)
{
    int lowu=pre[u] = ++dfs_clock;
    int child=0;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        edge e=edge(u,v);
        if(!pre[v])
        {
            S.push(e);
            child++;
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);  //用后代的low函数更新u的low函数
            if(lowv>=pre[u])
            {
                iscut[u]=true;
                bcc_cnt++;bcc[bcc_cnt].clear(); 	// bcc从1开始编号
                for(;;)
                {
                    edge x = S.top();S.pop();
                    if(bccno[x.first]!=bcc_cnt){
                        bcc[bcc_cnt].push_back(x.first);
                        bccno[x.first]=bcc_cnt;
                    }
                    if(bccno[x.second]!=bcc_cnt){
                        bcc[bcc_cnt].push_back(x.second);
                        bccno[x.second]=bcc_cnt;
                    }
                    if(x.first == u && x.second == v) break;
                }
            }
        }else if(pre[v] < pre[u] && v != fa){
            //用反向边更新u的low函数
            S.push(e);
            lowu=min(lowu,pre[v]);
        }
    }
    if(fa < 0 && child ==1) iscut[u]=0; 
    return lowu;
}

//函数顶点编号从0~n-1
void find_bcc(int n)
{
    //调用结束之后S都为空，不需要清空
    memset(pre,0,sizeof(pre));
    memset(iscut,0,sizeof(iscut));
    memset(bccno,0,sizeof(bccno));

    dfs_clock=bcc_cnt=0;
    for(int i=0;i<n;i++)//遍历每个点
        if(!pre[i]) dfs(i,-1);
}


/*模型一：两者（A，B）不能同时取
　　那么选择了A就只能选择B’，选择了B就只能选择A’
　　连边A→B’，B→A’

模型二：两者（A，B）不能同时不取
　　那么选择了A’就只能选择B，选择了B’就只能选择A
　　连边A’→B，B’→A

模型三：两者（A，B）要么都取，要么都不取
　　那么选择了A，就只能选择B，选择了B就只能选择A，选择了A’就只能选择B’，选择了B’就只能选择A’
　　连边A→B，B→A，A’→B’，B’→A’

模型四：两者（A，A’）必取A
　　那么，那么，该怎么说呢？先说连边吧。
　　连边A’→A

AND 结果为1：建边 ~x->x,~y->y （两个数必须全为1）
AND 结果为0：建边 y->~x,x->~y （两个数至少有一个为0）
OR 结果为1：建边 ~x->y,~y->x （两个数至少有一个为1）
OR 结果为0：建边 x->~x,y->~y （两个数必须全为0）
XOR 结果为1：建边 x->~y,y->~x,~y->x,~x->y （两个数必须不同）
XOR 结果为0：建边 x->y,y->x,~x->~y,~y->~x （两个数必须相同）*/
////vector邻接表
/*
hints:
	·构造一组由‘且’链接起来的二元布尔式子。对每一个式子建边。
	·需要初始化的有g[],rg[],
	·每次需要对V重新赋值
	·建边过程中只需要利用冲突的条件来建边，而满足的情况不需要在意。（有待确定）
	·（如：x与y冲突，则构造出(x且y=0)来建边）
*/
int n;
int V;
vector<int> g[N];
vector<int> rg[N];
vector<int> vs;
bool used[N];
int cmp[N];
//0~n-1 true,n~2n-1 false
void init(int n)
{
    for(int i=0;i<n*2;i++)
        g[i].clear(),rg[i].clear();
}
void add_edge(int from,int to)
{
    g[from].push_back(to);
    rg[to].push_back(from);
}
void dfs(int v)
{
    used[v]=1;
    for(int i=0;i<g[v].size();i++)
        if(!used[g[v][i]]) dfs(g[v][i]);
    vs.push_back(v);
}
void rdfs(int v,int k)
{
    used[v]=1;
    cmp[v]=k;
    for(int i=0;i<rg[v].size();i++)
        if(!used[rg[v][i]]) rdfs(rg[v][i],k);
}
int scc()
{
    memset(used,0,sizeof(used));
    vs.clear();
    for(int v=0;v<V;v++)
        if(!used[v]) dfs(v);
    memset(used,0,sizeof(used));
    int k=0;
    for(int i=vs.size()-1;i>=0;i--)
        if(!used[vs[i]])
            rdfs(vs[i],k++);
    return k;
}
int main()
{
	/*add_edge*/
	V=n*2;
	scc();
	bool flag=true;
        for(int i=0;i<n && flag;i++)
            if(cmp[i] == cmp[i+n])
                flag=false;
            else
                ans.push_back(Output[age[i]>=x][cmp[i]>cmp[i+n]]);//cmp[i]>cmp[i+n]说明i项应该为true；
}


//vector邻接表


////////////
//用之前需要用init函数
//////////
struct Twosat{
    int n;
    vector<int> G[N*2];
    bool mark[N*2];
    int S[N*2],c;
    void init(int n)
    {
        this->n=n;
        for(int i=0;i<n*2;i++)
            G[i].clear();
        memset(mark,0,sizeof(mark));
    }
    bool dfs(int x)
    {
        if(mark[x^1]) return false;
        if(mark[x]) return true;
        mark[x]=true;
        S[c++]=x;
        for(int i=0;i<G[x].size();i++)
            if(!dfs(G[x][i])) return false;
        return true;
    }
    void add_edge(int x,int xval,int y,int yval)
    {
        x=x*2+xval;
        y=y*2+yval;
        G[x^1].push_back(y);
        G[y^1].push_back(x);
    }
    bool solve()
    {
        for(int i=0;i<n*2;i+=2)
        {
            if(!mark[i] && !mark[i+1])
            {
                c=0;
                if(!dfs(i))
                {
                    while(c>0) mark[S[--c]]=false;
                    if(!dfs(i+1)) return false;
                }
            }
        }
        return true;
    }
};

/////


//邻接矩阵
int m[MAXN][MAXN];  
int id[MAXN];  
  
  
int find_components(int n,int mat[][MAXN],int* id){  
    int ret=0,a[MAXN],b[MAXN],c[MAXN],d[MAXN],i,j,k,t;  
    for (k=0;k<n;id[k++]=0);  
    for (k=0;k<n;k++)  
        if (!id[k]){  
            for (i=0;i<n;i++)  
                a[i]=b[i]=c[i]=d[i]=0;  
            a[k]=b[k]=1;  
            for (t=1;t;)  
                for (t=i=0;i<n;i++){  
                    if (a[i]&&!c[i])  
                        for (c[i]=t=1,j=0;j<n;j++)  
                            if (mat[i][j]&&!a[j])  
                                a[j]=1;  
                    if (b[i]&&!d[i])  
                        for (d[i]=t=1,j=0;j<n;j++)  
                            if (mat[j][i]&&!b[j])  
                                b[j]=1;  
                }  
            for (ret++,i=0;i<n;i++)  
                if (a[i]&b[i])  
                    id[i]=ret;  
        }  
    return ret;  
} 

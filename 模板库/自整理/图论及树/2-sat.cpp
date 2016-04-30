/*ģ��һ�����ߣ�A��B������ͬʱȡ
������ôѡ����A��ֻ��ѡ��B����ѡ����B��ֻ��ѡ��A��
��������A��B����B��A��

ģ�Ͷ������ߣ�A��B������ͬʱ��ȡ
������ôѡ����A����ֻ��ѡ��B��ѡ����B����ֻ��ѡ��A
��������A����B��B����A

ģ���������ߣ�A��B��Ҫô��ȡ��Ҫô����ȡ
������ôѡ����A����ֻ��ѡ��B��ѡ����B��ֻ��ѡ��A��ѡ����A����ֻ��ѡ��B����ѡ����B����ֻ��ѡ��A��
��������A��B��B��A��A����B����B����A��

ģ���ģ����ߣ�A��A������ȡA
������ô����ô������ô˵�أ���˵���߰ɡ�
��������A����A

AND ���Ϊ1������ ~x->x,~y->y ������������ȫΪ1��
AND ���Ϊ0������ y->~x,x->~y ��������������һ��Ϊ0��
OR ���Ϊ1������ ~x->y,~y->x ��������������һ��Ϊ1��
OR ���Ϊ0������ x->~x,y->~y ������������ȫΪ0��
XOR ���Ϊ1������ x->~y,y->~x,~y->x,~x->y �����������벻ͬ��
XOR ���Ϊ0������ x->y,y->x,~x->~y,~y->~x ��������������ͬ��*/
////vector�ڽӱ�
/*
hints:
	������һ���ɡ��ҡ����������Ķ�Ԫ����ʽ�ӡ���ÿһ��ʽ�ӽ��ߡ�
	����Ҫ��ʼ������g[],rg[],
	��ÿ����Ҫ��V���¸�ֵ
	�����߹�����ֻ��Ҫ���ó�ͻ�����������ߣ���������������Ҫ���⡣���д�ȷ����
	�����磺x��y��ͻ�������(x��y=0)�����ߣ�
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
                ans.push_back(Output[age[i]>=x][cmp[i]>cmp[i+n]]);//cmp[i]>cmp[i+n]˵��i��Ӧ��Ϊtrue��
}


//vector�ڽӱ�


////////////
//��֮ǰ��Ҫ��init����
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


//�ڽӾ���
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

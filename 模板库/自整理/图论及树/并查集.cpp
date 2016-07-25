//以下是并查集的函数
void init(int n)
{
	for(int i=0;i<n;i++)
	{
		par[i]=i;
		rank[i]=0;
	}
}
int find(int x)
{
	if(par[x]==x)
		return x;
	else 
		return par[x]=find(par[x]);
}
void unite(int x,int y)
{
	x=find(x);
	y=find(y);
	if(x==y) return ;
	if(rank[x]<rank[y])
		par[x]=y;
	else 
	{
		par[y]=x;
		if(rank[x]==rank[y]) rank[x]++;
	}
}
bool same(int x,int y)
{
	return find(x)==find(y);
}
//并查集

//构筑二分图的并查集， col[u]数组记录的节点颜色的信息，如果u为根(并查集的根)则表示自身颜色，否则表示与父亲颜色是否相同。
int pa[N];
int col[N];
int son[N];
inline void init(int n)
{
    for(int i = 0; i <= n; i++) pa[i] = i, col[i] = 0;
}
//非递归的find，能够维护col数组，以及得到x节点的真实颜色
int find(int x, int& cx)
{
    int u = x;
    while(u != pa[u])
    {
        son[pa[u]] = u;
        u = pa[u];
    }
    int res = u, uc = col[u];
    while(u != x)
    {
        u = son[u];
        pa[u] = res;
        uc ^= col[u];
        col[u] = uc ^ col[res];
    }
    cx = uc;
    return res;
}
bool unite(int u, int v)
{
    int cu, cv;
    int fu = find(u, cu), fv = find(v, cv);
    if(fu == fv)
    {
        if(cu == cv) return false;
        return true;
    }
    pa[fu] = fv;
    if(cu != cv) col[fu] ^= col[fv];
    else {
        col[fu] ^= 1;
        col[fu] ^= col[fv];
    }
    return true;
}
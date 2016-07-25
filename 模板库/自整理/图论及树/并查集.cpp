//�����ǲ��鼯�ĺ���
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
//���鼯

//��������ͼ�Ĳ��鼯�� col[u]�����¼�Ľڵ���ɫ����Ϣ�����uΪ��(���鼯�ĸ�)���ʾ������ɫ�������ʾ�븸����ɫ�Ƿ���ͬ��
int pa[N];
int col[N];
int son[N];
inline void init(int n)
{
    for(int i = 0; i <= n; i++) pa[i] = i, col[i] = 0;
}
//�ǵݹ��find���ܹ�ά��col���飬�Լ��õ�x�ڵ����ʵ��ɫ
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
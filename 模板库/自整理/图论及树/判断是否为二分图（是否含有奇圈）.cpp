int color[N];

//�жϱ��Ϊb��˫��ͨ�����Ƿ�Ϊ����ͼ
bool bipartite(int u)
{
    for(int i=0;i<G[u].size();i++)
    {
        int v = G[u][i];
        if(color[v]== color[u]) return false;
        if(!color[v]){
            color[v]=3-color[u];
            if(!bipartite(v,b)) return false;
        }
    }
    return true;
}

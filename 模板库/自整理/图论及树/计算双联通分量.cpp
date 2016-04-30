
//���İ汾��
/*
	�˰汾�ɴ����رߡ�
	st: ĳ�ڵ��dfs��
	bccno: ĳ�������ڵķ������
	Tn: time_stamp
	b_cnt: ������ű��
	G: ͼ
	iscut�����ĳ�����Ƿ���
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
	��-˫��ͨ
    G[],����������Ψһ��Ҫ��ʼ��������
    dfs_clock ʱ�ӱ�ǣ���¼����·���������ķ����±�
    bcc_cnt ˫��ͨ����������
    bccno[] �����ʾÿ�������ڵ�˫��ͨ�������еĵ�������ڶ������
    iscut[] ��Ǹõ��Ƿ�Ϊ�
    pre[] ÿ�����ʱ�ӱ��
    bcc[] ÿ��˫��ͨ����������Щ��
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
            lowu=min(lowu,lowv);  //�ú����low��������u��low����
            if(lowv>=pre[u])
            {
                iscut[u]=true;
                bcc_cnt++;bcc[bcc_cnt].clear(); 	// bcc��1��ʼ���
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
            //�÷���߸���u��low����
            S.push(e);
            lowu=min(lowu,pre[v]);
        }
    }
    if(fa < 0 && child ==1) iscut[u]=0; 
    return lowu;
}

//���������Ŵ�0~n-1
void find_bcc(int n)
{
    //���ý���֮��S��Ϊ�գ�����Ҫ���
    memset(pre,0,sizeof(pre));
    memset(iscut,0,sizeof(iscut));
    memset(bccno,0,sizeof(bccno));

    dfs_clock=bcc_cnt=0;
    for(int i=0;i<n;i++)//����ÿ����
        if(!pre[i]) dfs(i,-1);
}


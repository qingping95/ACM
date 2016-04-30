#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 1000;
vector<int > G[N];
int color[N];
int n, m;

//���u�ڵ�ĵ�ǰ��ɫ�Ƿ������ڽڵ��ͻ
bool check(int u)
{
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(color[v] == color[u]) return false;
    }
    return true;
}
//knumΪ��ǰ����״̬����ɫ����
bool dfs(int u, int knum)
{
    //����������ɫ���鿴����ɫ�Ƿ����
    for(int i = 1; i <= knum; i++)
    {
        color[u] = i;//���ýڵ����ɫ����Ϊi���������ɫ���м������������ڵ�
        if(check(u))
        {
            bool flag = true;
            for(int j = 0; j < G[u].size(); j++)
            {
                int v = G[u][j];
                if(color[v] != 0) continue;
                //������ڽڵ���ɫ�ѱ�ã�����Ҫ������
                if(!dfs(v, knum))
                {
                    //�÷���ƥ��ʧ�ܣ�����
                    flag = false;
                    break;
                }
            }
            //���ڷ������У�����true
            if(flag) return true;
        }
    }
    //���з������Ƿ��������޸���һ�ڵ��
    color[u] = 0;
    return false;
}
int main()
{
    //Open();

    //��ʼ��
    memset(G, 0, sizeof(G));
    memset(color, 0, sizeof(color));
    cout<<"������ͼ�ڵ���������Լ��ߵ�����"<<endl;
    scanf("%d%d", &n, &m);
    cout<<"���������бߣ�(��ʽ��u v  ��ʾ�ڵ�u�ͽڵ�v֮����һ����)"<<endl;
    for(int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
        //����vector���ڽӱ�ķ�ʽ�洢ͼ������˫���
    }
    int lb = 0, ub = n+1;
    int ans ;
    //���ö��ַ���Ѱ�����Ž��
    while(lb + 1 < ub)
    {
        //��ʼ����ɫ����
        memset(color, 0, sizeof(color));
        int mid = ub + lb >> 1;
        //flag��ǵ�ǰ����ֵ�Ƿ����
        bool flag = true;
        //����ѭ���������Ƿ�ֹͼ����ͨ������£��еĵ����û�б���ɫ
        //���������У����flag�ѱ���Ϊfalse������Ҫ�ټ���������ȥ����������������
        for(int i = 1; i <= n && flag; i++)
        {
            //��ǰ�ڵ�δ��ɫ�ŶԸõ��������
            if(color[i] == 0)
                flag = dfs(i, mid);
        }
        if(flag) ub = ans = mid;
        else lb = mid;
    }
    //�ó���֮������һ�������ó��𰸡�
    memset(color, 0, sizeof(color));
    bool flag = true;
    for(int i = 1; i <= n && flag; i++)
    {
        if(color[i] == 0)
            flag = dfs(i, ans);
    }
    //������
    cout<<"����ʹ�õ���ɫΪ��"<< ans << endl;
    for(int i = 1; i <= n; i++) cout<<color[i]<<endl;
    return 0;
}

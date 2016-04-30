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
bool check(int u, int k)
{
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(color[v] == k) return false;
    }
    return true;
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
    color[1] = 1;
    int num = 1;
    int k = 0;
    while(num < n){
        k++;
        for(int i = 2; i <= n; i++)
        {
            if(color[i]) continue;
            if(check(i, k))
            {
                color[i] = k;
                num++;
            }
        }
    }
    cout<<"ʹ��̰�ķ��õ��Ľ�Ϊ��"<<k<<endl;
    cout<<"��ɫ���Ϊ��"<<endl;
    for(int i = 1; i <= n; i++)
        cout<<i<<":"<<color[i]<<endl;
    return 0;
}
/*
7 10
1 2
2 3
3 4
4 5
5 6
6 7
3 7
4 6
1 5
1 4
*/

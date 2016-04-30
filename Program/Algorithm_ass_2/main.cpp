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
const int N = 3000;
int w[N], v[N];
int suf[N];
int n,m;
int ans;
void dfs(int idx, int cw, int cv)
{
    //�����ǰ�����Ѿ����ڱ�����������ֱ�ӷ���
    if(cw > m) return ;
    //�����ǰ�ļ�ֵ���Ϻ������еļ�ֵ�������ڵ�ǰ�Ľ����ʱ��ֱ�ӷ���
    if(ans > suf[idx] + cv) return ;
    if(idx == n)
    {
        ans = max(ans, cv);
        return ;
    }
    dfs(idx+1, cw + w[idx], cv + v[idx]);
    dfs(idx+1, cw, cv);
}
int main()
{
    //Open();
    cout<<"��������Ʒ������,�Լ�����������"<<endl;
    scanf("%d%d", &n, &m);
    cout<<"�����������Ʒ���������ÿո�������س�����"<<endl;

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &w[i]);
    }
    cout<<"�����������Ʒ�ļ�ֵ���ÿո�������س�����"<<endl;
    for(int i =0 ; i < n;i++)
    {
        scanf("%d", &v[i]);
    }
    suf[n] = 0;
    for(int i = n-1; i >= 0; i--) suf[i] = suf[i+1] + v[i];
    ans = 0;//��ʼ��ansΪ��Сֵ
    dfs(0, 0, 0);
    cout<<"���ļ�ֵΪ��"<<ans<<endl;
    return 0;
}

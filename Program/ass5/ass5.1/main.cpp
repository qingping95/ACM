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
const int N = 100100;
struct item
{
    int w, v;
    bool operator<(const item& o)const{
        return v*o.w > o.v*w;
    }
}Item[N];
int main()
{
    //Open();
    int n, m;
    cout<<"��������Ʒ������,�Լ�����������"<<endl;
    scanf("%d%d", &n, &m);
    cout<<"�����������Ʒ���������ÿո�������س�����"<<endl;

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &Item[i].w);
    }
    cout<<"�����������Ʒ�ļ�ֵ���ÿո�������س�����"<<endl;
    for(int i =0 ; i < n;i++)
    {
        scanf("%d", &Item[i].v);
    }
    sort(Item, Item+n);
    int ans = 0, curw = 0;
    for(int i = 0; i < n; i++)
    {
        if(curw + Item[i].w > m) continue;
        curw += Item[i].w;
        ans += Item[i].v;
    }
    cout<<"���ļ�ֵΪ��"<<ans<<endl;
    return 0;
}
/*
5 10
3 5 7 8 2
1 9 7 8 1
*/

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
const int N = 100010;
int a[N];
int n, d;
int main()
{
    //Open();
    cout<<"������������������ʱ���ܹ���ʻ�ľ��룺";
    cin >> d;
    cout<<"���������վ�ĸ�����";
    cin >> n;
    cout<<"��ӽ���Զ����������������վ֮��ľ���(�Կո����)��"<<endl;
    for(int i = 1; i < n; i++)
        cin >> a[i];

    int cur = d;
    int ans = 0;
    for(int i = 1; i < n; i++)
    {
        if(cur < a[i])
        {
            cur = d;
            ans ++;
        }
        cur -= a[i];
        if(cur < 0){
            printf("�����޷������յ�!!\n");
            return 0;
        }
    }
    cout<<"����̰�ķ��������ټ��ʹ���Ϊ��"<<ans<<endl;
    return 0;
}
/*
10 5
5 5 5 5
*/

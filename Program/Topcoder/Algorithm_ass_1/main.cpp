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
const int N = 30;
int w[N], v[N];
int n,m;
int main()
{
    //Open();
    cout<<"请输入物品的数量,以及背包的容量"<<endl;
    scanf("%d%d", &n, &m);
    cout<<"请输入各个物品的重量，用空格隔开，回车结束"<<endl;

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &w[i]);
    }
    cout<<"请输入各个物品的价值，用空格隔开，回车结束"<<endl;
    for(int i =0 ; i < n;i++)
    {
        scanf("%d", &v[i]);
    }
    int ans = 0;
    int limit = 1 << n;
    for(int i = 1; i < limit; i++)
    {
        int weightsum = 0;
        int valuesum = 0;
        for(int j = 0; j < n;j++)
        {
            if(i & (1 << j))
            {
                weightsum += w[j];
                valuesum += v[j];
            }
        }
        if(weightsum <= m)
            ans = max(ans, valuesum);
    }
    cout<<"最大的价值为："<<ans<<endl;
    return 0;
}

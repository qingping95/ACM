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
    //如果当前重量已经大于背包容量，则直接返回
    if(cw > m) return ;
    //如果当前的价值加上后面所有的价值都不大于当前的结果的时候，直接返回
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
    suf[n] = 0;
    for(int i = n-1; i >= 0; i--) suf[i] = suf[i+1] + v[i];
    ans = 0;//初始化ans为最小值
    dfs(0, 0, 0);
    cout<<"最大的价值为："<<ans<<endl;
    return 0;
}

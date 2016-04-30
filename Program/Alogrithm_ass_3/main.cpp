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
struct item
{
    int w, v;
    bool operator<(const item& o)const{
        return v*o.w > o.v*w;
    }
}s[N];
int n,m;
int lb;
void dfs(int idx, int cw, int cv)
{
    if(cw > m) return ;
    lb = max(cv, lb);
    if(idx == n) return ;
    int ub = cv + (m - cw) * (s[idx].v * 1.0 / s[idx].w);
    if(ub <= lb) return ;
    dfs(idx+1, cw + s[idx].w, cv + s[idx].v);
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
        scanf("%d", &s[i].w);
    }
    cout<<"请输入各个物品的价值，用空格隔开，回车结束"<<endl;
    for(int i =0 ; i < n;i++)
    {
        scanf("%d", &s[i].v);
    }
    sort(s, s+n);
    lb = s[0].v;
    dfs(0, 0, 0);
    cout<<"最大的价值为："<<lb<<endl;
    return 0;
}
/*
5 10
3 5 7 8 2
1 9 7 8 1
*/

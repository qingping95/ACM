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

//检测u节点的当前标色是否与相邻节点冲突
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
    //初始化
    memset(G, 0, sizeof(G));
    memset(color, 0, sizeof(color));
    cout<<"请输入图节点的数量，以及边的数量"<<endl;
    scanf("%d%d", &n, &m);
    cout<<"请输入所有边：(格式：u v  表示节点u和节点v之间有一条边)"<<endl;
    for(int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
        //利用vector以邻接表的方式存储图，建立双向边
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
    cout<<"使用贪心法得到的解为："<<k<<endl;
    cout<<"着色情况为；"<<endl;
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

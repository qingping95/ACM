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
bool check(int u)
{
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(color[v] == color[u]) return false;
    }
    return true;
}
//knum为当前搜索状态的颜色总数
bool dfs(int u, int knum)
{
    //遍历所有颜色，查看该颜色是否可行
    for(int i = 1; i <= knum; i++)
    {
        color[u] = i;//将该节点的颜色设置为i，如果该颜色可行继续再搜索相邻点
        if(check(u))
        {
            bool flag = true;
            for(int j = 0; j < G[u].size(); j++)
            {
                int v = G[u][j];
                if(color[v] != 0) continue;
                //如果相邻节点颜色已标好，则不需要往下搜
                if(!dfs(v, knum))
                {
                    //该方案匹配失败，跳出
                    flag = false;
                    break;
                }
            }
            //存在方案可行，返回true
            if(flag) return true;
        }
    }
    //所有方案都非法，回溯修改上一节点的
    color[u] = 0;
    return false;
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
    int lb = 0, ub = n+1;
    int ans ;
    //利用二分法来寻找最优结果
    while(lb + 1 < ub)
    {
        //初始化颜色数组
        memset(color, 0, sizeof(color));
        int mid = ub + lb >> 1;
        //flag标记当前测试值是否可行
        bool flag = true;
        //利用循环的意义是防止图不连通的情况下，有的点可能没有被着色
        //跳出条件中，如果flag已被置为false，则不需要再继续搜索下去，整个方案不可行
        for(int i = 1; i <= n && flag; i++)
        {
            //当前节点未标色才对该点进行搜索
            if(color[i] == 0)
                flag = dfs(i, mid);
        }
        if(flag) ub = ans = mid;
        else lb = mid;
    }
    //得出答案之后，再做一遍搜索得出答案。
    memset(color, 0, sizeof(color));
    bool flag = true;
    for(int i = 1; i <= n && flag; i++)
    {
        if(color[i] == 0)
            flag = dfs(i, ans);
    }
    //输出结果
    cout<<"最少使用的颜色为："<< ans << endl;
    for(int i = 1; i <= n; i++) cout<<color[i]<<endl;
    return 0;
}

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
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<n)
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
struct node
{
    int x, y, g, h;
    //重写比较函数，使得估价最小的一个先弹出队列。
    bool operator<(const node& o)const{
        return g+h > o.g+o.h;
    }
};
const int N = 1010;
char maze[N][N];//迷宫地图
bool vis[N][N];//记忆化搜索数组
int n;
int dir[4][2] = {0,1,0,-1,1,0,-1,0};//方向数组
//利用曼哈顿距离当做估价函数
int dist(int sx, int sy, int tx, int ty)
{
    return abs(sx-tx)+abs(sy-ty);
}
void A_star(int sx, int sy, int tx, int ty)
{
    memset(vis, 0, sizeof(vis));
    priority_queue<node> que;//利用优先队列存储
    int ans = 0;
    int stats = 0;
    que.push((node){sx, sy, 0, dist(sx, sy, tx, ty)});
    stats++;
    vis[sx][sy] = 1;
    while(!que.empty())
    {
        node cur = que.top();
        que.pop();
        sx = cur.x, sy = cur.y;
        if(sx == tx && sy == ty)
        {
            ans = cur.g;
            break;
        }
        //往四个方向扩展
        for(int i = 0; i < 4; i++)
        {
            int cx = sx+dir[i][0];
            int cy = sy+dir[i][1];
            //检测合法性
            if(!CHECK(cx, cy)) continue;
            if(maze[cx][cy] == '#') continue;
            if(vis[cx][cy]) continue;
            vis[cx][cy] = 1;
            que.push((node){cx, cy, cur.g+1, dist(cx, cy, tx, ty)});
            stats++;//记录状态的多少
        }
    }
    printf("从起点到终点至少要走%d步\n", ans);
    printf("整个搜索过程搜索了%d个状态\n", stats);
}
int main()
{
    Open();
    if(~scanf("%d\n", &n))
    {
        for(int i = 0 ;i < n; i++)
            scanf("%s", maze[i]);
    }else{
        n = 5;
        strcpy(maze[0], ".....");
        strcpy(maze[1], ".....");
        strcpy(maze[2], "..S..");
        strcpy(maze[3], ".....");
        strcpy(maze[4], "...T.");
    }
    cout<<"数据如下："<<endl;
    printf("迷宫大小%d X %d\n", n, n);
    for(int i = 0; i < n; i++)
        cout<<maze[i]<<endl;
    cout<<endl;
    int sx, sy, tx, ty;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            if(maze[i][j] == 'S')
            {
                sx = i, sy = j;
            }
            if(maze[i][j] == 'T')
            {
                tx = i, ty = j;
            }
        }
    A_star(sx, sy, tx, ty);
    return 0;
}
/*
测试样例
5
.....
.....
..S..
.....
...T.
*/

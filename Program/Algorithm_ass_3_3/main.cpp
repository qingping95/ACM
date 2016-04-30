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
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
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
    int x, y, cost;
    bool operator<(const node& o)const{
        return cost>o.cost;
    }
};
const int N = 1000;
bool vis[N][N];
int n, m;
int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};//方向数组，用于四向搜寻
char mark[N][N];
int BFS(int sx, int sy, int ex, int ey)
{
    int ans = INF;
    memset(vis, 0, sizeof(vis));
    priority_queue<node> que;
    que.push((node){sx, sy, 0});
    vis[sx][sy] = 1;
    while(!que.empty())
    {
        int cx = que.top().x, cy = que.top().y, cost = que.top().cost;
        que.pop();
        if(cx == ex && cy == ey)
        {
            ans = min(ans, cost);
            continue;
        }
        if(cost + abs(cx - ex) + abs(cy - ey) >= ans) continue;
        for(int i = 0 ; i < 4; i++)
        {
            int nx = cx + dir[i][0];
            int ny = cy + dir[i][1];
            if(!CHECK(nx, ny)) continue;
            if(mark[nx][ny] == '*') continue;
            if(vis[nx][ny]) continue;
            vis[nx][ny] = 1;
            que.push((node){nx, ny, cost+1});
        }
    }
    return ans;
}
int main()
{
//    Open();
    cout<<"请输入n（布线区域的大小n*n）"<<endl;
    scanf("%d", &n);
    m = n;
    cout<<"请输入布线区域的构造，n*n的方阵， .代表可到区域，*代表不可到区域，a代表起点，b代表终点"<<endl;
    for(int i = 0; i < n; i++)
        scanf("%s", mark[i]);
    int sx, sy;
    int ex, ey;
    for(int i = 0; i < n; i++)
        for(int j = 0 ; j < n; j++)
        {
            if(mark[i][j] == 'a')
            {
                sx = i, sy = j;
            }
            if(mark[i][j] == 'b')
            {
                ex = i, ey = j;
            }
        }
    cout<<"答案为："<<BFS(sx, sy, ex, ey)<<endl;
    return 0;
}
/*
7
..*....
..**...
.a..*..
...**b.
*...*..
***....
***....
*/

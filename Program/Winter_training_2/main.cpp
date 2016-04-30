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
const int N = 30003;
int n, m, k;
char mark[22][22];
PII black[22];
bool vis[15][15][1<<15];
int index[15][15];
int num[15][15][1<<15];
int dir[8][2] = {2, 1, -2, 1, 2, -1, -2, -1, 1, 2, -1, 2, 1, -2, -1, -2};
int kdir[8][2] = {0, 1, 1, 0, 0, -1, -1, 0, 1, 1, -1, 1, 1, -1, -1, -1};
void solveK(int x, int y, int s, int add)
{
    for(int i = 0; i < 8; i++)
    {
        int cx = x + dir[i][0], cy = y + dir[i][1];
        if(!CHECK(cx, cy)) continue;
        num[cx][cy][s]+=add;
    }
}
void solveB(int x, int y, int s, int add)
{
    int cx = x, cy = y;
    while(CHECK(cx, cy)) {num[cx][cy][s]+=add; if((x != cx || y != cy) && mark[cx][cy] != '.' && (s & (1 << index[cx][cy]))) break; cx++, cy++;}

    cx = x, cy = y;
    while(CHECK(cx, cy)) {num[cx][cy][s]+=add; if((x != cx || y != cy) && mark[cx][cy] != '.' && (s & (1 << index[cx][cy]))) break; cx--, cy++; }

    cx = x, cy = y;
    while(CHECK(cx, cy)) {num[cx][cy][s]+=add; if((x != cx || y != cy) && mark[cx][cy] != '.' && (s & (1 << index[cx][cy]))) break; cx++, cy--; }

    cx = x, cy = y;
    while(CHECK(cx, cy)) {num[cx][cy][s]+=add; if((x != cx || y != cy) && mark[cx][cy] != '.' && (s & (1 << index[cx][cy]))) break; cx--, cy--; }

    num[x][y][s] -= add*4;
}
void solveR(int x, int y, int s, int add)
{
    int cx = x, cy = y;
    while(CHECK(cx, cy)) {num[cx][cy][s]+=add; if((x != cx || y != cy) && mark[cx][cy] != '.' && (s & (1 << index[cx][cy]))) break; cx++; }

    cx = x, cy = y;
    while(CHECK(cx, cy)) {num[cx][cy][s]+=add; if((x != cx || y != cy) && mark[cx][cy] != '.' && (s & (1 << index[cx][cy]))) break; cx--; }

    cx = x, cy = y;
    while(CHECK(cx, cy)) {num[cx][cy][s]+=add; if((x != cx || y != cy) && mark[cx][cy] != '.' && (s & (1 << index[cx][cy]))) break; cy++; }

    cx = x, cy = y;
    while(CHECK(cx, cy)) {num[cx][cy][s]+=add; if((x != cx || y != cy) && mark[cx][cy] != '.' && (s & (1 << index[cx][cy]))) break; cy--; }

    num[x][y][s]-=add*4;
}
struct node
{
    int x, y, s, step;
};
int bfs(int sx, int sy)
{
    queue<node> que;
    que.push((node){sx, sy, (1<<k)-1, 0});
    vis[sx][sy][(1<<k)-1] = 1;
    while(!que.empty())
    {
        node on = que.front();que.pop();
        int x = on.x, y = on.y, s = on.s, step = on.step;
        if(s == 0) return step;
        for(int i = 0; i < 8; i ++)
        {
            int cx = x+kdir[i][0], cy = y+kdir[i][1];
            if(!CHECK(cx, cy)) continue;
            if(num[cx][cy][s] != 0) continue;
            if(mark[cx][cy] != '.'){
                int idx = index[cx][cy];
                if(s & (1 << idx)){
                    int cs = s ^ (1 << idx);
                    if(vis[cx][cy][cs] == 0)
                    {
                        vis[cx][cy][cs] = 1;
                        que.push((node){cx, cy, cs, step+1});
                    }
                }else if(vis[cx][cy][s] == 0){
                    vis[cx][cy][s] = 1;
                    que.push((node){cx, cy, s, step+1});
                }
            }else if(vis[cx][cy][s] == 0){
                vis[cx][cy][s] = 1;
                que.push((node){cx, cy, s, step+1});
            }
        }
    }
    return -1;
}
int main()
{
//    Open();
    scanf("%d%d", &n, &m);
    int sx, sy;
    k = 0;
    for(int i = 0; i < n; i++)
        scanf("%s", mark[i]);
    for(int i= 0; i < n; i++)
        for(int j = 0; j < m; j++)
        {
            if(mark[i][j] == '*') sx = i, sy = j, mark[i][j] = '.';
            if(mark[i][j] == 'K') black[k++] = PII(i, j), index[i][j] = k-1;
            if(mark[i][j] == 'B') black[k++] = PII(i, j), index[i][j] = k-1;
            if(mark[i][j] == 'R') black[k++] = PII(i, j), index[i][j] = k-1;
        }
    for(int s = 0; s < (1<<k); s++)
    {
        for(int j = 0; j < k; j++)
        {
            if(s & (1 << j))
            {
                if(mark[black[j].first][black[j].second] == 'K')
                    solveK(black[j].first, black[j].second, s, 1);
                if(mark[black[j].first][black[j].second] == 'B')
                    solveB(black[j].first, black[j].second, s, 1);
                if(mark[black[j].first][black[j].second] == 'R')
                    solveR(black[j].first, black[j].second, s, 1);
            }
        }
    }
    int ans = bfs(sx, sy);
    printf("%d\n", ans);
    return 0;
}

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
typedef pair<int, int> PII;
const int INF=0x3f3f3f3f;
const double eps = 1e-10;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
bool vis[1010][55][55][10];//
int f[333];//
bool G[55][55][10];//
int n, X0, Y0, t, alls;
int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};

int T[1010];
struct info
{
    int s, x, y, di;
    info(){}
    info(int _s, int _x, int _y, int _dir)
    {
        s = _s, x = _x, y = _y, di = _dir;
    }
};
bool ans[55][55];//
void solve()
{
    memset(ans, 0, sizeof(ans));
    memset(vis, 0, sizeof(vis));
    queue<info> que;
    for(int i = 0;i < 4;i++)
        que.push(info(0, X0, Y0, i)), vis[0][X0][Y0][i] = 1;
    while(!que.empty())
    {
        info pp = que.front();
        que.pop();
        int cx = pp.x, cy = pp.y, s = pp.s, di = pp.di;
        for(int i = 0; i < 4; i++)
        {
            if(max(di, i) - min(di, i) == 2) continue;
            if(G[cx][cy][i])
            {
                int nx = cx + dir[i][0];
                int ny = cy + dir[i][1];
                if(T[s] == -1 || di == T[s] || i == T[s])
                {
                    if(vis[s+1][nx][ny][i] == 0)
                    {
                        vis[s+1][nx][ny][i] = 1;
                        if(s < alls)que.push(info(s+1, nx, ny, i));
                        else{
                            ans[cx][cy] = 1;
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i <= 51; i ++)
        for(int j = 0;j <= 51; j++)
        {
            if(ans[i][j])
                printf("%d %d\n", i, j);
        }
//    puts("");
}
int main()
{
//    Open();
    f['N'] = 0, f['E'] = 1, f['S'] = 2, f['W']  = 3;
    while(scanf("%d%d%d%d",&n,&X0,&Y0,&t) == 4)
    {
//        for(int i = 0; i <= 50; i++)
//            for(int j = 0; j <=50; j++ )
//                G[i][j].clear();
//
        memset(G, 0, sizeof(G));
        memset(T, -1, sizeof(T));
        for(int i = 0; i < n; i++)
        {
            int xs, ys, xe, ye;
            scanf("%d%d%d%d", &xs, &ys, &xe, &ye);
            if(xs == xe)
            {
                if(ys > ye) swap(xs, xe), swap(ys, ye);
                G[xs][ys][0] = 1;
                for(int y = ys+1; y < ye; y++)
                {
                    G[xs][y][0] = G[xs][y][2] = 1;
                }
                G[xs][ye][2] = 1;
            }
            else
            {
                if(xs > xe) swap(xs, xe), swap(ys, ye);
                G[xs][ys][1] = 1;
                for(int x = xs + 1; x < xe; x++)
                {
                    G[x][ys][1] = G[x][ys][3] = 1;
                }
                G[xe][ys][3] = 1;
            }
        }
        alls = 0;
        for(int i = 0; i < t; i++)
        {
            char op[3];
            int d;
            scanf("%d%s", &d, op);
            alls += d;
            T[alls] = f[op[0]];
        }
        solve();
    }
    return 0;
}

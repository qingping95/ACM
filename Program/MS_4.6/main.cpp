#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
LL n, m;
bool vis[111][111][111];
bool exi[111][111][111];
struct node
{
    int x, y, z;
//    node()
//    {
//        x = y = z = 0;
//    }
//    int dist()
//    {
//        return 11 - x + 11 - y + 11 - z;
//    }
    bool operator<(const node& o) const{
        int xx = 11 - x + 11 - y + 11 - z;
        int yy = 11 - o.x + 11 - o.y + 11 - o.z;
        return xx > yy ;
    }
};
int dir[][3] = {1, 0, 0, -1, 0, 0,
                0, 1, 0, 0, -1, 0,
                0, 0, 1, 0, 0, -1};
bool BFS(int x, int y, int z)
{
    memset(vis, 0, sizeof(vis));
    priority_queue<node> que;
    que.push((node){x, y, z});
    vis[x][y][z] = 1;
    while(!que.empty())
    {
        node cur = que.top();
        que.pop();
        x = cur.x, y = cur.y, z = cur.z;
        if(x > 10 || y > 10 || z > 10) return true;
        for(int i = 0; i < 6; i++)
        {
            int cx = x + dir[i][0];
            int cy = y + dir[i][1];
            int cz = z + dir[i][2];
            if(cx < 0 || cy < 0 || cz < 0) continue;
            if(vis[cx][cy][cz] || exi[cx][cy][cz]) continue;
            vis[cx][cy][cz] = 1;
            que.push((node){cx, cy, cz});
        }
    }
    return false;
}
int main()
{
//    Open();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        memset(exi, 0, sizeof(exi));
        scanf("%d", &n);
        for(int i = 0; i <= 10; i++)
            for(int j = 0; j <= 10; j++)
                exi[i][j][0] = 1;
        bool flag = true;
        for(int i = 0; i < n; i++)
        {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            if(!flag) continue;
            if(exi[x][y][z]){
                flag = false;
                continue;
            }
            if(exi[x-1][y][z] || exi[x+1][y][z]
            || exi[x][y-1][z] || exi[x][y+1][z]
            || exi[x][y][z-1] || exi[x][y][z+1])
            {
                if(BFS(x, y, z)) continue;
                flag = false;
            }else{
                flag = false;
            }
        }
        if(flag) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

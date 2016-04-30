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
const int N = 1010;
int dir[4][2] = {0, 0, 1, 0, 0, 1, 1, 1};
int off[4][2] = {-1, -1, 0, -1, -1, 0, 0, 0};
int board[N][N];
int Lcnt;
void divide(int x, int y, int n, int a, int b)
{
    if(n == 1) return ;
    Lcnt++;
    int tmp = Lcnt;
    for(int i = 0; i < 4; i++)
    {
        int lx = x + dir[i][0]*n/2, ly = y + dir[i][1]*n/2;
        int ux = lx + n/2 - 1, uy = ly + n/2 - 1;
        if(a >= lx && a <= ux && b >= ly && b <= uy)
        {
            divide(lx, ly, n/2, a, b);
            for(int j = 0; j < 4; j++)
            {
                if(j == i) continue;
                int cx = x+n/2+off[j][0], cy = y+n/2+off[j][1];
                int sx = x + dir[j][0]*n/2, sy = y + dir[j][1]*n/2;
                board[cx][cy] = tmp;
                divide(sx, sy, n/2, cx, cy);
            }
        }
    }
}
int main()
{
    //Open();
    int n, cx, cy;
    cout<<"请输入棋盘的大小，以及特殊方格的坐标(三个数，用空格隔开，请保证第一个数为2的幂)"<<endl;
    cin >> n >> cx >> cy;
    board[cx][cy] = 0;
    Lcnt = 0;
    divide(1, 1, n, cx, cy);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            printf("%2d%c", board[i][j], " \n"[j == n]);
        }
    return 0;
}

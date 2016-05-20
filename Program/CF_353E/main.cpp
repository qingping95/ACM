#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 2002;
int N, M, d[maxn][maxn], state, maxv, fx, fy;
short int dx[maxn][maxn], dy[maxn][maxn];
bool ins[maxn][maxn], vis[maxn][maxn];
char s[maxn][maxn];
int dfs(short int x, short int y) {
    if (ins[x][y]) {
//        printf ("-1\n");
//        exit(0);
        return -1;
    }
    if (vis[x][y]) {
        return 0;
    }
    dx[x][y] = x;
    dy[x][y] = y;
    vis[x][y] = 1;
    ins[x][y] = 1;
    if (s[x][y]!='#') {
        if(s[x][y]=='^'&&x-1>=1)
        {
            if (s[x-1][y]=='#') {
                d[x][y] = 1;
                ins[x][y] = 0;
                return 0;
            }
            if (ins[x-1][y]) {
//                printf ("-1\n");
                //exit(0);
                return -1;
            }
            if (!vis[x-1][y]) {
                dfs(x-1, y);
            }
            d[x][y] = d[x-1][y] + 1;
            if (d[x][y]!=1) {
                dx[x][y] = dx[x-1][y];
                dy[x][y] = dy[x-1][y];
            }
        }
        else if (s[x][y]=='<'&&y-1>=1)
        {
            if (s[x][y-1]=='#') {
                d[x][y] = 1;
                ins[x][y] = 0;
                return 0;
            }
            if (ins[x][y-1]) {
//                printf ("-1\n");
//                exit(0);
                return -1;
            }
            if (!vis[x][y-1]) {
                dfs(x, y-1);
            }
            d[x][y] = d[x][y-1] + 1;
            if (d[x][y]!=1) {
                dx[x][y] = dx[x][y-1];
                dy[x][y] = dy[x][y-1];
            }
        } else if (s[x][y]=='>'&&y+1<=M) {
            if (s[x][y+1]=='#') {
                d[x][y] = 1;
                ins[x][y] = 0;
                return 0;
            }
            if (ins[x][y+1]) {
                //                printf ("-1\n");
//                exit(0);
                return -1;
            }
            if (!vis[x][y+1]) {
                dfs(x, y+1);
            }
            d[x][y] = d[x][y+1] + 1;
            if (d[x][y]!=1) {
                dx[x][y] = dx[x][y+1];
                dy[x][y] = dy[x][y+1];
            }
        } else if(x+1<=N){
            if (s[x+1][y]=='#') {
                d[x][y] = 1;
                ins[x][y] = 0;
                return 0;
            }
            if (ins[x+1][y]) {
                //                printf ("-1\n");
//                exit(0);
                return -1;
            }
            if (!vis[x+1][y]) {
                dfs(x+1, y);
            }
            d[x][y] = d[x+1][y] + 1;
            if (d[x][y]!=1) {
                dx[x][y] = dx[x+1][y];
                dy[x][y] = dy[x+1][y];
            }
        }
    }
    ins[x][y] = 0;
    return 0;
}
int main()
{
    scanf ("%d%d", &N, &M);
    for (int i=1; i<=N; ++i) {
        scanf ("%s", &s[i][1]);
    }
    for (int i=1;i<=N;i++) {
        for (int j=1;j<=M;j++) {
            if (s[i][j]!='#') {
                if (!vis[i][j]) {
                    if(dfs(i, j) == -1){
                        printf("-1\n");
                        return 0;
                    }
                }
                int x = d[i][j];
                if (x>maxv) {
                    state = 0;
                    maxv = x;
                    fx = dx[i][j];
                    fy = dy[i][j];
                } else if (x==maxv && (fx!=dx[i][j] || fy!=dy[i][j])) {
                    state = 1;
                }
            }
        }
    }
    if (state) {
        printf ("%d\n", maxv*2);
    } else {
        if (maxv==0) {
            printf ("0\n");
        } else {
            printf ("%d\n", maxv*2-1);
        }
    }
    return 0;
}

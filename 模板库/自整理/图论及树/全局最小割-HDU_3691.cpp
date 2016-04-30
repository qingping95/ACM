#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 310;

LL mat[MAXN][MAXN];
LL weight[MAXN];
bool del[MAXN], vis[MAXN];;
int n, m, st;

void init() {
    memset(mat, 0, sizeof(mat));
    memset(del, 0, sizeof(del));
}

LL StoerWagner(int &s, int &t, int cnt) {
    memset(weight, 0, sizeof(weight));
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= n; ++i)
        if(!del[i]) {t = i; break; }
    while(--cnt) {
        vis[s = t] = true;
        for(int i = 1; i <= n; ++i) if(!del[i] && !vis[i]) {
            weight[i] += mat[s][i];
        }
        t = 0;
        for(int i = 1; i <= n; ++i) if(!del[i] && !vis[i]) {
            if(weight[i] >= weight[t]) t = i;
        }
    }
    return weight[t];
}

void merge(int s, int t) {
    for(int i = 1; i <= n; ++i) {
        mat[s][i] += mat[t][i];
        mat[i][s] += mat[i][t];
    }
    del[t] = true;
}

LL solve() {
    LL ret = -1;
    int s, t;
    for(int i = n; i > 1; --i) {
        if(ret == -1) ret = StoerWagner(s, t, i);
        else ret = min(ret, StoerWagner(s, t, i));
        merge(s, t);
    }
    return ret;
}

int main() {
    while(scanf("%d%d%d", &n, &m, &st) != EOF) {
        if(n == 0 && m == 0 && st == 0) break;
        init();
        while(m--) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            mat[x][y] += z;
            mat[y][x] += z;
        }
        cout<<solve()<<endl;
    }
}
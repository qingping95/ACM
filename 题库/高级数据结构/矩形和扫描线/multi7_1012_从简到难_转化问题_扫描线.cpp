/*
*	还是要从简单情况考虑。。。
*	对于一个点(x,y)来说，别的点要到达该点，只能通过与该点最近的同行或者同列的点过来，该点四个方向的最近点构成
*	一个矩形，该矩形内的点全都无法到达该点。于是就变成了一个扫描线的裸题
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <climits>
#include <bitset>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int INF = 0x3f3f3f3f;
const int mod = 1e9+7.5;
const int N = 500010;
const int M = 50050;
struct node{
    int x, y1, y2, ty, id;
    node(int x = 0, int y1 = 0, int y2 = 0, int ty = 0, int id = 0):x(x), y1(y1), y2(y2), ty(ty), id(id){
    }
    bool operator<(const node& o) const{
        return x == o.x ? (ty < o.ty) : x < o.x;
    }
}que[N*3];//
PII p[N];//
int col[M];//
int c[M];//
int L[N], R[N], U[N], D[N];//
int ans[N];
void add(int x, int v)
{
    if(x == 0) return;
    for(int i = x; i < M; i += i & -i)
        c[i] += v;
}
int getsum(int x)
{
    int res = 0;
    for(int i = x; i; i -= i & -i)
        res += c[i];
    return res;
}
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);

    int n;
    int cas = 0;
    while(~scanf("%d", &n))
    {
        memset(col, 0, sizeof(col));
        memset(c, 0, sizeof(c));
        if(n == 0) break;
        for(int i = 0; i < n; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            p[i] = PII(x, y);
        }
        sort(p, p+n);
        n = unique(p, p+n)-p;
        int ly = 0;
        for(int i = 0; i < n; i++)
        {
            if(i == 0 || p[i].first != p[i-1].first)
                ly = 0;
            int x = p[i].first, y = p[i].second;
            L[i] = ly;
            U[i] = col[y];
            ly = y;
            col[y] = x;
        }
        ly = 50001;
        for(int i = 0; i < M; i++)
            col[i] = ly;
        int t = 0;
        for(int i = n-1; i >= 0; i --)
        {
            if(i == n-1 || p[i].first != p[i+1].first)
                ly = 50001;
            int x = p[i].first, y = p[i].second;
            R[i] = ly;
            D[i] = col[y];
            ly = y;
            col[y] = x;
            int x1 = U[i]+1, x2 = D[i]-1, y1 = L[i]+1, y2 = R[i]-1;
//            cout<<U[i]<<" "<<L[i]<<" "<<D[i]<<" "<<R[i]<<endl;
//            cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
            if(x1 <= x2 && y1 <= y2)
            {
                que[t++] = node(x1, y1, y2, 0, i);
                que[t++] = node(x2, y1, y2, 2, i);
            }
            que[t++] = node(x, y, y, 1, i);
        }

        sort(que, que+t);
        bool flag = true;
        for(int i = 0; i < t && flag; i++)
        {
            if(que[i].ty == 1){
                add(que[i].y1, 1);
            }else if(que[i].ty == 0){
                ans[que[i].id] = getsum(que[i].y2) - getsum(que[i].y1-1);
            }else{
                ans[que[i].id] = getsum(que[i].y2) - getsum(que[i].y1-1) - ans[que[i].id];
                if(ans[que[i].id] != 1)
                    flag = false;
            }
        }
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}


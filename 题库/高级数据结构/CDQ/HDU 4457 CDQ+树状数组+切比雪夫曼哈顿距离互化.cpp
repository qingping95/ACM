/*
* 首先得将曼哈顿距离转化为切比雪夫距离，(x, y) --> (x - y, x + y)，由于可能有负坐标，所以得加20000修正；
* 转化之后呢，这个问题就变为一个非常常见的二维区间和的问题啦。二维树状数组水之~
* 然而数组大小40000*40000，这怎么能开下呢！摔！（据说现场赛能开下。。hhh），想过一下离散化，但是发现离散化
* 非常难处理，感觉略复杂，于是果断上了CDQ！CDQ的话，这个题也很好做，每个大区间中考虑左区间的全部修改操作，
* 去更新右区间的所有查询操作。这里更新的话只需要将所有操作按照x坐标排序，存下y坐标
* 即可(不好讲。。具体看代码就知道了)
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 100010
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
        freopen("D:/in.txt","r",stdin);
//        freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int n, m;
struct query{
    int op, x, val, id;
    int y1, y2;
    query(){}
    query(int o, int xx, int yy1, int yy2, int v, int i){
        op = o, x = xx, y1 = yy1, y2 = yy2, val = v, id = i;
    }

    bool operator< (const query& o) const{
        return x < o.x || (x == o.x && op < o.op);
    }
}qlist[N], que[N];
int ans[N];
int c[N];
int tmp[N];
int changetoX(int x, int y)
{
    return x - y + 20010;
}
int changetoY(int x, int y)
{
    return x + y + 20010;
}
void add(int x, int val)
{
    for(int i = x; i <= N; i += (-i) & i) c[i] += val;
}
int getsum(int x)
{
    int res = 0;
    for(int i = x; i > 0 ; i -= (-i) & i) res += c[i];
    return res;
}
void divide(int l, int r){
    if(l >= r) return ;
    int mid = l + r >> 1;
    int tail = 0;
    for(int i = l; i <= mid; i++){
        if(qlist[i].op == 1){
            que[tail++] = query(1, qlist[i].x, qlist[i].y1, qlist[i].y1, qlist[i].val, qlist[i].id);
        }
    }
    for(int i = mid + 1; i <= r; i++) {
        if(qlist[i].op != 1){
            int val = qlist[i].val;
            que[tail++] = query(2, qlist[i].x - val - 1, qlist[i].y1 - val, qlist[i].y2 + val, qlist[i].val, qlist[i].id);
            que[tail++] = query(3, qlist[i].x + val, qlist[i].y1 - val, qlist[i].y2 + val, qlist[i].val, qlist[i].id);
        }
    }
    sort(que, que + tail);
    for(int i = 0 ; i < tail ; i++)
    {
        if(que[i].op == 1){
            add(que[i].y1, que[i].val);
        } else if(que[i].op == 2){
            tmp[que[i].id] = getsum(que[i].y2) - getsum(que[i].y1 - 1);
        } else {
            ans[que[i].id] += getsum(que[i].y2) - getsum(que[i].y1 - 1) - tmp[que[i].id];
        }
    }
    for(int i = 0; i < tail; i++)
        if(que[i].op == 1) add(que[i].y1, -que[i].val);
    divide(l, mid);
    divide(mid+1, r);
}
int main()
{
//    Open();
    while(scanf("%d",&n)==1 && n){
        scanf("%d", &m);
        int qtail = 1;
        for(int i = 1 ; i <= m; i++)
        {
            ans[i] = 0;
            int op, x, y, val;
            scanf("%d%d%d%d", &op, &x, &y, &val);
            int curx = changetoX(x, y);
            int cury = changetoY(x, y);
            qlist[i] = query(op, curx, cury, cury, val, i);
        }
        divide(1, m);
        for(int i = 1; i <= m; i++)
        {
            if(qlist[i].op == 2){
                printf("%d\n", ans[i]);
            }
        }
    }
    return 0;
}
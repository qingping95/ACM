/*
* Problem Description
She says that any Pavarotti among the nightingales will serenade his mate while she sits on her eggs.
She says that any excited database can answer the queries efficiently.

You are given the two dimensional database as a matrix A with n rows and n columns. In the beginning, A[i][j]=0 for all 1≤i,j≤n.
Then q operations or queries will be given in turn.

You should maintain the database for two type of operations:
1 L R: for each element A[i][j] which satisfy L≤i+j≤R, increase the value to A[i][j]+1, where 2≤L≤R≤2n.
2 L R: for each element A[i][j] which satisfy L≤i−j≤R, increase the value to A[i][j]+1, where 1−n≤L≤R≤n−1.
Meanwhile, you should answer the queries:
3 x1 x2 y1 y2: count the value of elements A[i][j] which satisfy x1≤i≤x2 and y1≤j≤y2, where 1≤x1<x2≤n and 1≤y1<y2≤n.
 

Input
The input contains several test cases. The first line of the input is a single integer t which is the number of test cases. Then t test cases follow.

Each test case contains several lines. The first line contains the integer n and q.
The i-th line of the next q lines contains an operation ‘‘1 L R" or ‘‘2 L R", or a query ‘‘3 x1 x2 y1 y2".

The sum of n for all test cases would not be larger than 200000 and the sum of q would not be larger than 50000.
*
* 做法：这个题稍加分析就会发现，每一次改变值都是正副对角线方向上的所有数加值，那么我们可以用两棵线段
*		树去分别维护正副对角线上的a[i]*i和a[i]的区间和，以此来计算所求矩形的和。
*
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 200010
#define lson x<<1
#define rson x<<1|1
#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
struct node
{
    LL l, r, sumi, sum, lazy;
    node(){}
    node(LL _l, LL _r, LL _sumi, LL _sum, LL _lazy)
    {
        l = _l, r = _r, sumi = _sumi, sum = _sum, lazy = _lazy;
    }
    LL len()
    {
        return r - l + 1;
    }
}lt1[N*6], lt2[N*6];
void build(LL l, LL r, LL x, node lt[])
{
    lt[x] = node(l, r, 0, 0, 0);
    if(l == r) return ;
    build(l, mid, lson, lt);
    build(mid+1, r, rson, lt);
}
void push_down(LL x, node lt[])
{
    if(lt[x].lazy)
    {
        lt[lson].sum += lt[x].lazy * lt[lson].len();
        lt[lson].sumi += lt[x].lazy * lt[lson].len() * (mid + lt[x].l) / 2;
        lt[lson].lazy += lt[x].lazy;
        lt[rson].sum += lt[x].lazy * lt[rson].len();
        lt[rson].sumi += lt[x].lazy * lt[rson].len() * (mid+1+lt[x].r) / 2;
        lt[rson].lazy += lt[x].lazy;
        lt[x].lazy = 0;
    }
}
void push_up(LL x, node lt[])
{
    lt[x].sumi = lt[lson].sumi + lt[rson].sumi;
    lt[x].sum = lt[lson].sum + lt[rson].sum;
}
void update(LL l, LL r, LL x, node lt[])
{
    if(lt[x].l >= l && lt[x].r <= r)
    {
        lt[x].sum += lt[x].len();
        lt[x].sumi += (r + l) * lt[x].len() / 2;
        lt[x].lazy ++;
        return ;
    }
    push_down(x, lt);
    if(r <= mid) update(l, r, lson, lt);
    else if(l > mid) update(l, r, rson, lt);
    else update(l, mid, lson, lt), update(mid+1, r, rson, lt);
    push_up(x, lt);
}
PII query(LL l, LL r, LL x, node lt[])
{
    if(lt[x].l >= l && lt[x].r <= r)
    {
        return PII(lt[x].sumi, lt[x].sum);
    }
    push_down(x, lt);
    if(r <= mid) return query(l, r, lson, lt);
    else if(l > mid)return query(l, r, rson, lt);
    else {
        PII p1 = query(l, mid, lson, lt);
        PII p2 = query(mid+1, r, rson, lt);
        return PII(p1.first + p2.first, p2.second + p1.second);
    }
}
LL getans(LL l, LL r, LL x, node lt[])
{
    PII res = query(l, r, x, lt);
    return res.first - (l - 1) * res.second;
}
int main()
{
    Open();
    LL T;scanf("%I64d", &T);
    LL cas = 1;
    while(T--)
    {
        LL n, q;
        scanf("%I64d%I64d", &n, &q);
        LL offset = n;
        printf("Case #%I64d:\n", cas++);
        build(1, 2*n, 1, lt1);
        build(1, 2*n, 1, lt2);
        while(q--)
        {
            LL op;
            scanf("%I64d", &op);
            if(op == 1) {
                LL l, r;
                scanf("%I64d%I64d", &l, &r);
                update(l, r, 1, lt1);
            }else if(op == 2){
                LL l, r;
                scanf("%I64d%I64d", &l, &r);
                update(l + offset, r + offset, 1, lt2);
            }else {
                LL x1, y1, x2, y2;
                scanf("%I64d%I64d%I64d%I64d", &x1, &x2, &y1, &y2);
                LL res = getans(x1+y1, x2+y2, 1, lt1);
                if(x1 + y2 + 1 <= x2 + y2)res -= getans(x1+y2+1, x2+y2, 1, lt1);
                if(x2 + y1 + 1 <= x2 + y2)res -= getans(x2+1+y1, x2+y2, 1, lt1);
                res += getans(x1 - y2 + offset, x2 - y1 + offset, 1, lt2);
                if(x1 - (y1 - 1) <= x2 - y1) res -= getans(x1 - (y1 - 1) + offset, x2 - y1 + offset, 1, lt2);
                if(x2 + 1 - y2 <= x2 - y1) res -= getans(x2 + 1 - y2 + offset, x2 - y1 + offset, 1, lt2);
                printf("%I64d\n", res);
            }
        }
    }
    return 0;
}

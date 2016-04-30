/*
* Problem Description
* A connected, undirected graph of N vertices and M edges is given to CRB.
* A pair of vertices (u, v) (u < v) is called critical for edge e if and only 
* if u and v become disconnected by removing e.
* CRB’s task is to find a critical pair for each of M edges. Help him!
*
* Input
* There are multiple test cases. The first line of input contains an integer T, indicating 
* the number of test cases. For each test case:
* The first line contains two integers N, M denoting the number of vertices and the number of edges.
* Each of the next M lines contains a pair of integers a and b, denoting an undirected edge
* between a and b.
* 1 ≤ T ≤ 12
* 1 ≤ N, M ≤ 105
* 1 ≤ a, b ≤ N
* All given graphs are connected.
* There are neither multiple edges nor self loops, i.e. the graph is simple.
*
* Output
* For each test case, output M lines, i-th of them should contain two integers u and v, 
* denoting a critical pair (u, v) for the i-th edge in the input.
* If no critical pair exists, output "0 0" for that edge.
* If multiple critical pairs exist, output the pair with largest u. If still ambiguous, 
* output the pair with smallest v.
*
* 题意：给出一个简单图(无重边，无自环)，要求输出每条边e的"至关重要对"，也就是如果删除e这条边，
* 		这两个点就不连通。
*
* 做法：这里用可回滚并查集(就是暴力回滚而已)+CDQ，并查集合并方式必须是启发式合并，而不能有路径压缩，
* 		CDQ分治边表，到CDQ的每一层[l,r]时，并查集中的状态都是[1,l-1]与[r+1,m]中的全部边合并之后的状态
*		那么当分治到长度为1的时候，此时并查集的状态即为整个图中不包含这条边的状态。函数返回上一层的时
*		候，回滚即可。回滚这一步的复杂度与合并是一样的。
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
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int rk[N], pa[N], ma[N];
struct node{
    int u, pa, rk, ma;
}sta[N*2];
struct edge{
    int u, v;
}e[N];
int tail  = 0;
int n, m;
PII ans[N];
int find(int x)
{
    while(x != pa[x]) x = pa[x];
    return x;
}
void unite(int u, int v){
    u = find(u), v = find(v);
    if(u == v) return ;
    sta[tail++] = (node){u, u, rk[u], ma[u]};
    sta[tail++] = (node){v, v, rk[v], ma[v]};
    if(rk[u] > rk[v]){
        swap(u, v);
    }
    pa[u] = v;
    if(rk[u] == rk[v]) rk[v]++;
    ma[v] = max(ma[v], ma[u]);
}
void rollback(int tmp)
{
    while(tail > tmp){
        tail--;
        int u = sta[tail].u;
        pa[u] = sta[tail].pa;
        rk[u] = sta[tail].rk;
        ma[u] = sta[tail].ma;
    }
}
void UnionAll(int l, int r)
{
    for(int i = l; i <= r; i++)
    {
        unite(e[i].u, e[i].v);
    }
}
void divide(int l, int r)
{
    if(l == r){
        int u = find(e[l].u), v = find(e[l].v);
        if(u == v) ans[l] = PII(0, 0);
        else{
            int tmp = min(ma[u], ma[v]);
            ans[l] = PII(tmp, tmp+1);
        }
        return ;
    }
    int mid = l + r >> 1;
    int tmp = tail;
    UnionAll(mid+1, r);
    divide(l, mid);
    rollback(tmp);

    UnionAll(l, mid);
    divide(mid+1, r);
    rollback(tmp);
}
char *ch, buf[40*1024000+5];

template <class T>
void read(T &x) {
	for (++ch; *ch <= 32; ++ch);
	for (x = 0; '0' <= *ch; ch++)	x = x * 10 + *ch - '0';
}

int main()
{
    Open();
    ch = buf - 1;
    fread(buf, 1, 1000*35*1024, stdin);
    int T;
    read(T);
//    scanf("%d",&T);
    while(T--)
    {
//        scanf("%d%d", &n, &m);
        read(n);read(m);
        tail = 0;
        for(int i = 1; i <= n; i++)
            pa[i] = i, rk[i] = 1, ma[i] = i;
        for(int i = 1; i <= m; i++)
        {
            read(e[i].u);read(e[i].v);
//            scanf("%d%d", &e[i].u, &e[i].v);
        }
        divide(1, m);
        for(int i = 1; i <= m; i++)
        {
            printf("%d %d\n", ans[i].first, ans[i].second);
        }
    }
    return 0;
}

/*
* Problem Description
* soda has a undirected graph with n vertices and m edges. He wants to make the graph become a bipartite graph by deleting only one vertex. You need to tell him which vertex can be deleted.
* 
* Input
* There are multiple test cases. The first line of input contains an integer T, indicating the number of test cases. For each test case:
* 
* The first contains two integer n and m (1≤n,m≤105), the number of vertices and the number of edges.
* Next m lines contain two integers each, ui and vi (1≤ui,vi≤n,ui≠vi) , indicating there is an edge between vertices ui and vi.
* 
* Output
* For each test case, output binary string of length n. The i-th character is '1' if soda can delete i-th vertex to make the graph become a bipartite graph, otherwise the i-th character is '0'.
* 
* 题意：给出一个二分图，n个点，m条边，需要输出每个点是否能通过删除该点，使得原图成为一个二分图
*		
* 做法：首先二分图的话，我们需要对每个节点标记颜色，同一条边上的两个点颜色不能相同。
* 这一题是并查集+cdq分治，这里并查集需要回滚，所以不能使用压缩路径，而需要用启发式合并的方法，
* 保证每次寻找fa都为logn，首先说整体思路，也就是分治过程，我们先处理(l, mid)区间， 那么需要
* 将(mid+1,r)区间内的点的边全部合并，这里不包括与左区间相连的点，看右边区间组成的图能不能构成二分图。
* 处理完左区间之后需要回滚到合并右区间之前的状态，然后对右区间做相同的操作。一直递归即可。
* 对于如何利用并查集判断是否二分图的话，我们可以用一个color数组记录，color[v]如果v节点为并查集根，
* 那么表示的即为这个根的颜色，否则的话表示与他的父亲（注意这里不是根）的颜色相不相同，为1表示
* 不相同，0表示相同，color的初始值可以随便设置。（当然这里不一样的话，合并的时候考虑的转换会不一样。）
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#pragma comment(linker, "/STACK:102400000,102400000")
#define N 100010
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
#define mid ((l + r) >> 1)
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

vector<int > G[N];
int n, m;
int pa[N], rk[N], color[N];
int ans[N];

struct node
{
    int u, pa, rk, col;
    node(){}
    node(int u, int pa, int rk, int col):u(u), pa(pa), rk(rk), col(col){}
}sta[N*2];

int tail;
int find(int x)
{
    while(pa[x] != x) x = pa[x];
    return x;
}
int findcol(int x)
{
    if(pa[x] == x) return color[x];
    else if(color[x]) return !findcol(pa[x]);
    return findcol(pa[x]);
}
bool unite(int u, int v)
{
    int colu = findcol(u), colv = findcol(v);
    u = find(u), v = find(v);
    if(u == v){
        if(colu == colv) return false;
        return true;
    }
    if(rk[u] < rk[v]) swap(u, v), swap(colu, colv);
    sta[tail++] = node(u, pa[u], rk[u], color[u]);
    sta[tail++] = node(v, pa[v], rk[v], color[v]);
    pa[v] = u;

    if(colu == colv && color[v] == 0){
        color[v] = 1;
    }
    if(colu != colv && color[v] == 1){
        color[v] = 0;
    }

    if(rk[u] == rk[v]) rk[u] ++;
    return true;
}
bool uniteSeg(int l, int r, int a, int b)
{
    for(int u = l; u <= r; u++)
        for(int i=0;i<G[u].size();i++){
            int v = G[u][i];
            if(v >= a && v <= b) continue;
            if(!unite(u, v)) return false;
        }
    return true;
}
void rollback(int mark)
{
    while(tail != mark)
    {
        tail--;
        int u = sta[tail].u, ufa = sta[tail].pa, urk = sta[tail].rk, ucol = sta[tail].col;
        pa[u] = ufa, rk[u] = urk, color[u] = ucol;
    }
}
void divide(int l, int r)
{
    if(l == r){
        printf("1");
        return ;
    }
    int mark = tail;
    bool flag = uniteSeg(mid+1, r, l, mid);
    if(flag) divide(l, mid);
    else for(int i=l;i<=mid;i++) printf("0");
    rollback(mark);
    flag = uniteSeg(l, mid, mid+1, r);
    if(flag) divide(mid+1, r);
    else for(int i=mid+1;i<=r;i++) printf("0");
    rollback(mark);
}
int main()
{
    Open();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        for(int i=0;i<=n;i++) G[i].clear(), pa[i] = i, color[i] = rk[i] = 1;
        tail = 0;
        int u, v;
        for(int i=0;i<m;i++)
        {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        divide(1, n);
        printf("\n");
    }
    return 0;
}
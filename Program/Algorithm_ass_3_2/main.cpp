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
const int N = 20;
int G[N][N];
int n, m;
int ans;
struct node
{
    int u, s, v;
    bool operator<(const node& o)const{
        return v > o.v;
    }
};
int value[N][1<<N];
int UP;
int BFS(int st)
{
    ans = INF;
    priority_queue<node> que;
    que.push((node){st, 1<<st, 0});
    memset(value, 0x3f, sizeof(value));
    value[st][1<<st] = 0;
    while(!que.empty())
    {
        node cur = que.top();
        que.pop();
        int u = cur.u, s = cur.s, v = cur.v;
        //cout<<u<<" "<<v<<endl;
        if(v > value[u][s]) continue;
        if(v > ans) continue;
        if(s == ((1 << n) - 1))
        {
            ans = min(ans, v + G[u][st]);
            UP = ans;
            continue;
        }
        int tmpans = v;
        for(int i = 0; i < n; i++)
        {
            if(s & (1 << i)) continue;
            tmpans += *(min_element(G[i], G[i] + n));
        }
        if(tmpans >= UP) continue;
        for(int i = 0; i < n; i++)
        {
            if(s & (1 << i)) continue;
            if(G[u][i] == INF) continue;
            if(value[i][s | (1 << i)] < v + G[u][i]) continue;
            value[i][s|(1<<i)] = v + G[u][i];
            que.push((node){i, s|(1<<i), v + G[u][i]});
        }
    }
    return ans;
}
int main()
{
    //Open();
    memset(G, 0x3f, sizeof(G));
    cout<<"请输入图中的节点数以及边数"<<endl;
    scanf("%d%d", &n, &m);
    cout<<"接下来m行，每行3个整数u,v,w,表示节点u与节点v之间有一条权值为m的边"<<endl;
    for(int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--, v--;
        G[u][v] = min(G[u][v], w);
        G[v][u] = min(G[v][u], w);
    }
    UP = 0;
    for(int i = 0; i < n - 1; i++){
        if(G[i][i+1] == INF) UP = INF;
        else UP += G[i][i+1];
        if(UP == INF) break;
    }
    if(G[n-1][0] == INF || UP == INF) UP = INF;
    else UP += G[n-1][0];
    cout<<"本图的结果为："<<BFS(0)<<endl;
    return 0;
}
/*
5 10
1 2 3
1 3 1
1 4 5
1 5 8
2 3 6
2 4 7
2 5 9
3 4 4
3 5 2
4 5 3
*/

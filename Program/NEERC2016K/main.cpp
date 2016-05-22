#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
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
    freopen("king.in","r",stdin);
    freopen("king.out","w",stdout);
    #ifndef ONLINE_JUDGE
//        freopen("F:/046","r",stdin);
//        freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 200020;
int vin[N], vout[N];
int in[N], out[N];
PII edge[N];
PII rem[N];
int n, m;
int rn, sn;
int UP;
int pa[N];
int num[N];
int rk[N];
struct node{
    int u, pa, num, rk;
}sta[N];
int tail = 0;
void init(int n)
{
    for(int i = 0; i <= n; i++) pa[i] = i, num[i] = 1, rk[i] = 1;
}
int find(int x) {
    while(pa[x] != x) x = pa[x];
    return x;
    //return x == pa[x] ? x : pa[x] = find(pa[x]);
}
bool unite(int u, int v)
{
    u = find(u), v = find(v);
    if(u == v) return false;
    sta[tail++] = (node){u, pa[u], num[u], rk[u]};
    sta[tail++] = (node){v, pa[v], num[v], rk[v]};
    if(rk[v] > rk[u])
        swap(u, v);
    num[u] += num[v];
    pa[v] = u;
    if(rk[u] == rk[v]) rk[u]++;
    return true;
}
void rollback(int limit)
{
    while(tail > limit)
    {
        tail--;
        int u = sta[tail].u;
        num[u] = sta[tail].num;
        pa[u] = sta[tail].pa;
        rk[u] = sta[tail].rk;
    }
}
bool dfs(int pos)
{
    if(sn == n)
    {
        return  num[find(1)] == n;
    }
    for(int i = pos; i < rn; i++)
    {
        int u = rem[i].first;
        int v = rem[i].second;
        if(vin[v] != -1 || vout[u] != -1) continue;
        int limit = tail;
        unite(u, v);
        vin[v] = u, vout[u] = v;
        sn++;
        if(dfs(i+1)) return true;
        rollback(limit);
        sn--;
        vin[v] = -1, vout[u] = -1;
    }
    return false;
}
int main()
{
    Open();
    memset(vin, -1, sizeof(vin));
    memset(vout, -1, sizeof(vout));
    scanf("%d%d", &n, &m);
    init(n);
    for(int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        edge[i] = PII(u, v);
        if(u == v) continue;
        in[v]++;
        out[u]++;
    }
    rn = 0;
    sn = 0;
    bool flag = true;
    for(int i = 0; i < m; i++)
    {
        int u = edge[i].first, v = edge[i].second;
        if(u == v) continue;
        if(out[u] == 1 || in[v] == 1) {
            if(vin[v] != -1 || vout[u] != -1) flag = false;
            vin[v] = u, vout[u] = v;
            sn++;
            unite(u, v);
        }
    }
    for(int i = 0; i < m; i++)
    {
        int u = edge[i].first, v = edge[i].second;
        if(u == v) continue;
        if(out[u] == 1 || in[v] == 1) ;
        else if(vin[v] == -1 && vout[u] == -1){
            rem[rn++] = edge[i];
        }
    }
    UP = 0;
    for(int i = 1; i <= n && flag; i++)
        flag = (in[i]>0&&out[i]>0);

    if(flag && dfs(0)){
        printf("1");
        int st = vout[1];
        while(true)
        {
            printf(" %d", st);
            if(st == 1) break;
            st = vout[st];
        }
        printf("\n");
    }else{
        printf("There is no route, Karl!\n");
    }
    return 0;
}

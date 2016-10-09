#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
#include <climits>
#include <assert.h>
#include <bitset>
using namespace std;
typedef long long LL;
const int INF = 2e9+10;
//const int INF = 0x3f3f3f3f;
typedef pair<int, int> PII;
const int N = 60032;
struct edge{
    int u, v, w, id;
}e[60040];
vector<edge> G[N];
int Tn;
int pre[N], iscut[N];
//fa初始值为-1
int dfs(int u, int fa, int id, int xid)
{
    int lowu = pre[u] = ++Tn;
    int child = 0;
    bool egfa = true;
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i].v, sid = G[u][i].id;
        //if(sid == xid) continue;//本题的特殊需求，不用在意，
        if(sid == id) {egfa = false;continue;}///这里是如果允许重边的情况
//        if(v == fa && egfa){egfa = false;continue;}
        if(!pre[v]){
            child++;
            int lowv = dfs(v, u, sid, xid);
            lowu = min(lowu, lowv);
            //割顶的判断
//            if(lowv >= pre[u] && fa >= 0){
//                iscut[u] = true;
//            }
        }else if(pre[v] < pre[u]) {
            lowu = min(lowu, pre[v]);
        }
    }
    //桥的判断，id是fa->u边的编号
    if(lowu >= pre[u]) iscut[id] = 1;
    //if(fa < 0 && child == 1) iscut[u] = 0;
    return lowu;
}
int path[N];
bool vis[N];
bool dfspath(int u, int t, int xid)
{
    if(u == t) return true;
    vis[u] = 1;
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i].v;
        int id = G[u][i].id;
        if(id == xid) continue;
        if(vis[v]) continue;
        if(dfspath(v, t, xid)){
            path[G[u][i].id] = 1;
            return true;
        }
    }
    return false;
}
int sta[N];
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
    Tn = 0;
    int n, m;
    int s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for(int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        e[i] = (edge){u,v,w,i};
        G[u].push_back((edge){u,v,w,i});
        G[v].push_back((edge){v,u,w,i});
    }
    dfs(s, -1, -1, -1);
//    for(int i = 0; i < m; i++)
//        if(iscut[i]) cout<<i<<" : "<<e[i].u<<" -> "<<e[i].v<<" : "<<e[i].w<<endl;
    if(dfspath(s, t, -1) == false)
    {
        printf("0\n0\n");
        return 0;
    }
    int ans = INF, c, a[2];
    int st = 0;
    for(int i = 0; i < m; i++)
    {
        if(path[i]) sta[st++] = i;
//        if(path[i]) cout<<i<<" : "<<e[i].u<<" -> "<<e[i].v<<" : "<<e[i].w<<endl;
//        if(iscut[i]) cout<<i<<" : "<<e[i].u<<" -> "<<e[i].v<<" : "<<e[i].w<<endl;
        if(path[i] && iscut[i])
        {
            if(ans > e[i].w)
            {
                ans = e[i].w;
                c = 1;
                a[0] = i;
            }
        }
    }
    for(int i = 0; i < st; i++)
    {
        int idx = sta[i];
        Tn = 0;
        memset(path, 0, sizeof(path));
        memset(iscut, 0, sizeof(iscut));
        memset(pre, 0, sizeof(pre));
        memset(vis, 0, sizeof(vis));
        dfs(s, -1, -1, idx);
        dfspath(s, t, idx);
        for(int j = 0; j < m; j++)
        {
            //if(idx == 23 && path[j]) cout<<j<<" : "<<e[j].u<<" -> "<<e[j].v<<" : "<<e[j].w<<endl;
//            if(iscut[j]) cout<<"cut : "<<j<<" : "<<e[j].u<<" -> "<<e[j].v<<" : "<<e[j].w<<endl;
            if(path[j] && iscut[j])
            {
                if(ans > e[j].w + e[idx].w)
                {
                    ans = e[j].w + e[idx].w;
                    c = 2;
                    a[0] = j, a[1] = idx;
                }
            }
        }
    }
    if(ans == INF)
    {
        printf("-1\n");
        return 0;
    }
    printf("%d\n%d\n", ans, c);
    for(int i = 0; i < c; i++)
        printf("%d%c", a[i]+1, " \n"[i == c-1]);
    return 0;
}


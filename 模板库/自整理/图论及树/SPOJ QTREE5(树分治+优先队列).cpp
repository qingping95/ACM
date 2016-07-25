#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 200010
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int > PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
struct Reader{
    static const int MSIZE = 1000 * 8 * 1024;
    char buf[MSIZE], *pt = buf, *o = buf;
    void init(){
        fread(buf, 1, MSIZE, stdin);
    }
    char getch()
    {
        char ch;
        while((*pt < 'A' || *pt > 'Z') && (*pt < 'a' || *pt > 'z')) pt++;
        ch = *pt;pt++;
        return ch;
    }
    int getint()
    {
        int f = 1, x = 0;
        while(*pt != '-' && !isdigit(*pt)) pt++;
        if(*pt == '-') f = -1, pt++;
        else x = *pt++ - 48;
        while(isdigit(*pt)) x = x * 10 + *pt++ - 48;
        return x * f;
    }
}frd;
struct edge{
    int to, nxt;
    edge(){}
    edge(int _t, int _n)
    {
        to = _t, nxt = _n;
    }
}e[N*2];
int head[N], eN = 0;
void addedge(int u, int v)
{
    e[eN] = edge(v, head[u]);
    head[u] = eN++;
}
priority_queue<PII, vector<PII>, greater<PII > > que[N];
vector<PII > wV[N];
int col[N];
//得到树的重心
int root, s[N], f[N];
bool vis[N];
int n;
int maxn;
int getroot(int now, int fa, int sz)
{
    int cnt=1;
    int mx=0;
    for(int i=head[now]; i!=-1; i=e[i].nxt)
    {
        int to=e[i].to;
        if(to==fa || vis[to]) continue;
        f[to]=getroot(to,now,sz);
        mx = max(mx,f[to]);
        cnt+=f[to];
    }
    mx = max(mx,sz-cnt);
    if(mx<maxn)
    {
        maxn=mx, root=now;
        for(int i = head[now]; i != -1; i = e[i].nxt)
        {
            int to = e[i].to;
            if(vis[to]) continue;
            if(to == fa)
            {
                s[to] = sz - cnt;
                continue;
            }
            s[to] = f[to];
        }
    }
    return cnt;
}
void dfsgao(int u, int fa, int rt, int dis)
{
    wV[u].push_back(PII(dis, rt));
    for(int i = head[u]; ~i ; i = e[i].nxt)
    {
        int v = e[i].to;
        if(vis[v] || v == fa) continue;
        dfsgao(v, u, rt, dis+1);
    }
}
//在调用dfs之前一定要记得将s[u]赋好值
void dfs(int u)
{
    maxn = INF;
    getroot(u, 0, s[u]);
    int trt = root;
    vis[trt] = 1;
    dfsgao(trt, 0, trt, 0);
    for(int i = head[trt]; ~i ; i = e[i].nxt)
    {
        int v = e[i].to;
        if(vis[v]) continue;
        dfs(v);
    }
}
bool pvvis[N];
int main()
{
//    Open();
    frd.init();
    memset(head, -1, sizeof(head));
    n = frd.getint();
//    scanf("%d", &n);
    for(int i = 1; i < n; i++){
        int x, y;
        x = frd.getint();
        y = frd.getint();
//        scanf("%d%d", &x, &y);
        addedge(x, y);
        addedge(y, x);
    }
    s[1] = n;
    dfs(1);
    int q;
    q = frd.getint();
    int ndnum = 0;
//    scanf("%d", &q);
    while(q--){
        int op, u;
        op = frd.getint();
        u  = frd.getint();
//        scanf("%d%d", &op, &u);
        if(op == 0){
            col[u] ^= 1;
            if(col[u]) ndnum++;
            else ndnum--;
            if(col[u]){
                //pvvis[u] = 1;
                for(int i = 0; i < wV[u].size(); i ++)
                {
                    int v = wV[u][i].second;
                    int dis = wV[u][i].first;
                    que[v].push(PII(dis, u));
                }
            }
        }else{
            if(ndnum == 0){
                puts("-1");
                continue;
            }
            int ans = INF;
            for(int i = 0; i < wV[u].size(); i ++){
                int v = wV[u][i].second;
                int dis = wV[u][i].first;
                while(!que[v].empty()){
                    PII pp = que[v].top();
                    int curv = pp.second, dist = pp.first;
                    if(!col[curv]) {que[v].pop(); continue;}
                    ans = min(ans, dist+dis);
                    break;
                }
            }
            if(ans == INF) ans = -1;
            if(ans == -1) while(1);
            printf("%d\n", ans);
        }
    }
    return 0;
}
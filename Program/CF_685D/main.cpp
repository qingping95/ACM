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
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 1011;
queue<int> que;//
vector<PII > G[N];//
bool ans[200020];//
struct Q{
    int l, r, t, id;
    Q(int _l, int _r, int _t, int _id){
        l = _l, r = _r, t = _t, id = _id;
    }
    bool operator<(const Q& o){
        return l > o.l;
    }
};
vector<Q> query[200020];
int d[N];//
int inq[N];//
void spfa()
{
    while(!que.empty())
    {
        int u = que.front();
        que.pop();
        inq[u] = 0;
        for(int i = 0; i < G[u].size(); i++)
        {
            int v = G[u][i].second;
            int w = G[u][i].first;
            if(d[u] <= w && d[v] > w) {
                d[v] = w;
                if(inq[v] == 0){
                    inq[v] = 1;
                    que.push(v);
                }
            }
        }
    }
}
int main()
{
    //Open();
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(PII(i, v));
        G[v].push_back(PII(i, u));
    }
    for(int i = 0; i < q; i++)
    {
        int l, r, s, t;
        scanf("%d%d%d%d", &l, &r, &s, &t);
        query[s].emplace_back(l, r, t, i);
    }
    for(int i = 1; i <= n; i++)
    {
        sort(query[i].begin(), query[i].end());
        sort(G[i].begin(), G[i].end());
    }
    for(int i = 1; i <= n; i++)
    {
        memset(d, 0x3f, sizeof(d));
        while(!que.empty()) que.pop();
        d[i] = 0;
        vector<PII > tmp(G[i].size());
        for(int j = 0; j < G[i].size(); j++)
        {
            tmp.emplace_back(G[i][j]);
        }
        for(int j = 0; j < query[i].size(); j++)
        {
            while(tmp.size() > 0 && tmp[tmp.size()-1].first >= query[i][j].l)
            {
                int v = tmp[tmp.size()-1].second;
                int w = tmp[tmp.size()-1].first;
                tmp.pop_back();
                d[v] = min(d[v], w);
                if(inq[v] == 0){
                    que.push(v);
                    inq[v] = 1;
                }
            }
            spfa();
            ans[query[i][j].id] = (d[query[i][j].t] != INF);
        }
    }
    for(int i = 0; i < q; i++)
    {
        printf("%s\n", ans[i] ? "Yes" : "No");
    }
    return 0;
}

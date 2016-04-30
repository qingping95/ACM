#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
//#include <unordered_map>
#define N 500010
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
vector<int> G[N];
vector<vector<int > > deplist;
vector<vector<int > > depch;
int st[N];
int ed[N];
char num[N];
int Tn = 0;
int mad;
int n, m;
char str[N];
void dfs(int u, int d)
{
    st[u] = ++Tn;
    num[Tn] = str[u];
    if(d == deplist.size())
        deplist.push_back(vector<int>());
    deplist[d].push_back(st[u]);
    mad = max(mad, d);
    for(int i = 0;i<G[u].size();i++)
    {
        int v = G[u][i];
        dfs(v, d+1);
    }
    ed[u] = Tn;
}
int main()
{
    Open();
    scanf("%d%d", &n, &m);
    for(int i=2;i<=n;i++){
        int x;
        scanf("%d", &x), G[x].push_back(i);
    }
    scanf("%s", str+1);
    mad = -1;
    dfs(1, 0);
    for(int i = 0; i <= mad; i++)
    {
        for(int j = 0; j<deplist[i].size(); j++)
        {
            int u = num[deplist[i][j]] - 'a';
            if(j == 0) depch.push_back(vector<int>());

            depch[i].push_back((1<<u));
        }
        for(int j=1;j<depch[i].size();j++)
            depch[i][j] = depch[i][j] ^ depch[i][j-1];
    }
    for(int i=0;i<m;i++)
    {
        int v, h;
        scanf("%d%d", &v, &h);
        h--;
        if(h > mad) {
            printf("Yes\n");
            continue;
        }
        int l = lower_bound(deplist[h].begin(), deplist[h].end(), st[v]) - deplist[h].begin();
        int r = upper_bound(deplist[h].begin(), deplist[h].end(), ed[v]) - deplist[h].begin();
        r--;
        if(l == deplist[h].size() || r == deplist[h].size() || l > r)
        {
            printf("Yes\n");
            continue;
        }
        int cnt = 0;
        if(l == 0) cnt = depch[h][r];
        else cnt = depch[h][r] ^ depch[h][l-1];

        if(__builtin_popcount(cnt) > 1){
            printf("No\n");
        }else {
            printf("Yes\n");
        }
    }
    return 0;
}

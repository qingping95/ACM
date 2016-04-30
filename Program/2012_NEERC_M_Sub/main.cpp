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
typedef pair<double ,int> PDI;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int n, k;
int dp[N];
struct people
{
    int id, p;
    char s[11];
    people(){}
    people(int _id, int _p)
    {
        id = _id, p = _p;
        for(int i = 0; i < k; i++) s[i] = 0;
    }
    bool operator<(const people& o)const{
        return p > o.p;
    }
}peo[N];
char st[11];
struct query{
    int id;
    int ren;
    int sta;
    query(){}
    query(int _id, int _r){
        id = _id, ren = _r;
        for(int i = 0; i < k; i++) st[i] = 2;
    }
};
vector<query> lis[10010];
int getnum(char s[])
{
    int res = 0;
    for(int i = 0; i < k ;i++)
        res = res * 3 + s[i];
    return res;
}
int ans[N];
int main()
{
//    Open();
    while(~scanf("%d%d", &n, &k)){
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= n; i++)
        {
            int p, num;
            scanf("%d%d", &p, &num);
            peo[i] = people(i, p);
            while(num--)
            {
                int x;scanf("%d", &x);peo[i].s[x-1]=1;
            }
            lis[i].clear();
        }
        int m;
        scanf("%d", &m);
        for(int i = 0; i < m; i++)
        {
            int pe, num;
            scanf("%d%d", &pe, &num);
            query tmp(i, pe);
            while(num--)
            {
                int x;scanf("%d", &x);st[x-1] = peo[pe].s[x-1];
            }
            tmp.sta = getnum(st);
            lis[pe].push_back(tmp);
        }
        sort(peo+1, peo+n+1);
        int cnt = 1;
        while(cnt <= n && peo[cnt].p == peo[1].p){
            int pe = peo[cnt].id;
            for(int i = 0; i < lis[pe].size(); i++)
            {
//                cerr << lis[pe][i].id<<endl;
                ans[lis[pe][i].id] = 1;
            }
            cnt++;
        }
        int limit = 1 << k;
        for(int i = 1; i <= n; i++)
        {
            for(int j = 0; j < limit; j++)
            {
                for(int sid = 0; sid < k; sid++)
                {
                    st[sid] = (j & (1 << sid)) ? 2 : peo[i].s[sid];
                }
                int sta = getnum(st);
                dp[sta]++;
            }
            if(i==n || i < cnt-1) continue;
            int nxt = peo[i+1].p;
            if(peo[i].p == nxt) continue;
            for(int j = i+1; j <= n && peo[j].p == nxt; j++){
                int pe = peo[j].id;
                for(int l = 0; l < lis[pe].size(); l++)
                {
//                    cerr<<lis[pe][l].id<<" "<< lis[pe][l].sta<<endl;
                    ans[lis[pe][l].id] = dp[lis[pe][l].sta] + 1;
                }
            }
        }
        for(int i = 0; i < m; i++)
            printf("%d\n", ans[i]);
    }
    return 0;
}

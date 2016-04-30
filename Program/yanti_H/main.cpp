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
const int N = 20020;
const int mod = 1000000007;
int nxt[66];//
int a[N];//
vector<PII> P[66];//
double cmp[N];//
LL ans[N];//
PII sta[66];//
int ma[66];//
void init()
{
    for(int i = 2; i <= 60; i++)
    {
        int tmp = i;
        for(int j = 2; j <= i; j++)
        {
            int t = 0;
            while(tmp % j == 0) tmp /= j, t++;
            if(t != 0)P[i].push_back(PII(j, t));
        }
    }
}

int main()
{
    //Open();
    init();
    int n, m;
    while(~scanf("%d%d", &n, &m))
    {
        for(int i = 0; i <= n; i++) cmp[i] = INF;
        memset(nxt, 0x3f, sizeof(nxt));

        for(int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        for(int i = n-1; i >= 0; i--)
        {
            memset(ma, 0, sizeof(ma));
            nxt[a[i]] = i;
            double curcmp = 0;
            LL curans = 1;
            int t = 0;
            for(int j = 1; j <= 60; j++)
            {
                if(nxt[j] == INF) continue;
                sta[t++] = PII(nxt[j], j);
            }
            sort(sta, sta+t);
            for(int j = 0; j < t; j++)
            {
                int len;
                if(j < t-1) len = sta[j+1].first - i;
                else len = n - i;
                int tmp = sta[j].second;
                for(int k = 0; k < P[tmp].size(); k++)
                {
                    int p = P[tmp][k].first, mi = P[tmp][k].second;
                    if(mi > ma[p])
                    {
                        curcmp += log(p)*(mi - ma[p]);
                        int num = mi - ma[p];
                        ma[p] = mi;
                        while(num--)
                        {
                            curans = curans * p % mod;
                        }
                    }
                }
                if(cmp[len] > curcmp)
                {
                    cmp[len] = curcmp;
                    ans[len] = curans;
                }
            }
        }
        for(int i = n; i > 1; i--)
        {
            if(cmp[i-1] > cmp[i])
            {
                cmp[i-1] = cmp[i];
                ans[i-1] = ans[i];
            }
        }
        while(m--)
        {
            int x;
            scanf("%d", &x);
            printf("%d\n", ans[x]);
        }
    }
    return 0;
}

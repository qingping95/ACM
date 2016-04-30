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
        freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int phi(int n)
{
    int res = n, a = n;
    for(int i = 2; i*i <= a; i++)
    {
        if(a % i == 0){
            res = res / i *(i-1);
            while(a%i == 0) a /= i;
        }
    }
    if(a > 1) res = res / a * (a-1);
    return res;
}
vector<int> fac;
bool vis[100100];
void getFac(int n)
{
    fac.clear();
    for(int i = 2; i*i <= n; i++)
    {
        if(n % i == 0){
            fac.push_back(i);
            if(i*i != n) fac.push_back(n/i);
        }
    }
    sort(fac.begin(), fac.end());
}

int main()
{
//    Open();
    int T;scanf("%d", &T);
    int cas = 1;
    while(T--)
    {
        memset(vis, 0, sizeof(vis));
        int n, m;
        scanf("%d%d", &n, &m);
        getFac(m);
        bool flag = true;
        for(int i = 0; i < n; i++)
        {
            int x;scanf("%d", &x);
            int g = __gcd(x, m);
            if(g == 1)
            {
                flag = false;
            }
            int idx = lower_bound(fac.begin(), fac.end(), g) - fac.begin();
            vis[idx] = 1;
        }
        if(!flag)
        {
            printf("Case #%d: %I64d\n", cas++, (LL)(m-1)*m/2);
            continue;
        }
        LL sum = 0;
        for(int i = 0; i < fac.size(); i++)
        {
            for(int j = 0; j < i && !vis[i]; j++)
            {
                if(fac[i]%fac[j] == 0)
                    vis[i] |= vis[j];
            }

            if(vis[i])
            {
                int tmp = m / fac[i];
                sum += (LL)fac[i]*(((LL)tmp * phi(tmp))/2);
            }
        }
        printf("Case #%d: %I64d\n", cas++, sum);
    }
    return 0;
}

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
const int N = 1000020;
int cma[N], cmi[N];
int a[300030], b[300030], L[300030], R[300030];
LL sum[300030];
int n, ma;

inline void insma(int x, int v)
{
    for(int i = x; i <= ma; i+= i & -i)
       cma[i] = max(cma[i], v);
}
inline int getma(int x)
{
    int rns = 0;
    for(int i = x; i; i -= i & -i)
        rns = max(rns, cma[i]);
    return rns;
}
inline void resetma(int x)
{
    for(int i = x; i <= ma; i+= i & -i)
       cma[i] = 0;
}
inline void insmi(int x, int v)
{
    for(int i = x; i <= ma; i+= i & -i)
       cmi[i] = min(cmi[i], v);
}
inline int getmi(int x)
{
    int rns = INF;
    for(int i = x; i; i -= i & -i)
        rns = min(rns, cmi[i]);
    return rns;
}
inline void resetmi(int x)
{
    for(int i = x; i <= ma; i+= i & -i)
       cmi[i] = INF;
}
int main1()
{
    Open();
    LL T;
    scanf("%I64d", &T);
    while(T--)
    {
        memset(cmi, 0x3f, sizeof(cmi));
        memset(cma, 0, sizeof(cma));
        scanf("%d", &n);
        ma = 0;
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]), ma = max(a[i], ma);
        LL ans = 0;
        for(int k = 1; k <= n; k++)
        {
            int tail = 0;
            int sk = sqrt(k);
            for(int l = k; l <= n; l+=k) b[++tail] = a[l];
            sum[0] = 0;
            sum[1] = b[1];
            for(int i = 2; i <= tail; i++) sum[i] = sum[i-1] + b[i];
            for(int i = 1; i <= tail; i++)
            {
                L[i] = getma(b[i]-1);
                insma(b[i], i);
            }
            for(int i = tail; i > 0; i--)
            {
                R[i] = getmi(b[i]-1);
                insmi(b[i], i);
            }
            for(int i = 1; i <= tail; i++)
            {
                int st = L[i], ed = R[i];
                if(ed == INF) ed = tail+1;
                ans = max(ans, (sum[ed-1] - sum[st]) * b[i] * sk);
            }
            for(int i = 1; i <= tail; i++)
            {
                resetma(b[i]);
                resetmi(b[i]);
            }
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
int main()
{
    freopen("F:/in.txt","w",stdout);
    int T = 1;
    cout<<T<<endl;
    while(T--)
    {
        int n = 300000;
        cout<<n<<endl;
        for(int i = 0; i < n; i++)
        {
            cout<<rand()+1;
            if(i == n-1) cout<<endl;
            else cout<<" ";
        }
    }
}

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
const int N = 300030;
int cma[N], cmi[N];
int a[N], b[N], c[N], L[N], R[N], f[N];
int sta[N];
LL sum[N];
int n, ma;

inline void insma(int x, int v)
{
    if(x == 0) return;
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
inline void reset(int x)
{
    if(x == 0) return;
    for(int i = x; i <= ma; i += i & -i)
       cma[i] = 0, cmi[i] = INF;
}
inline void insmi(int x, int v)
{
    if(x == 0) return;
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
template<class T>
inline bool read(T &n){
    T x = 0, tmp = 1; char c = getchar();
    while ((c < '0' || c > '9') && c != '-' && c != EOF) c = getchar();
    if (c == EOF) return false;
    if (c == '-') c = getchar(), tmp = -1;
    while (c >= '0' && c <= '9') x *= 10, x += (c - '0'), c = getchar();
    n = x*tmp;
    return true;
}

template <class T>
inline void write(T n) {
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    int len = 0, data[20];
    while (n) {
        data[len++] = n % 10;
        n /= 10;
    }
    if (!len) data[len++] = 0;
    while (len--) putchar(data[len] + 48);
}

int main()
{
//    Open();
//    init();
    int T;
    memset(cmi, 0x3f, sizeof(cmi));
    memset(cma, 0, sizeof(cma));
    getmi(0);
    read(T);
//    T = getint();
//    scanf("%I64d", &T);
    while(T--)
    {
        read(n);
//        n = getint();
//        scanf("%d", &n);
        ma = 0;
        for(int i = 1; i <= n; i++)
//            scanf("%d", &a[i]), ma = max(a[i], ma);
//            a[i] = getint(), ma = max(a[i], ma);
            read(a[i]), sta[i-1] = a[i];
        sort(sta, sta+n);
        int ST = unique(sta, sta+n) - sta;
        for(int i = 1; i <= n; i++)
            f[i] = lower_bound(sta, sta+ST, a[i]) - sta + 1;
        LL ans = 0;
        for(int k = 1; k <= n; k++)
        {
            ma = 0;
            int tail = 0;
            int sk = sqrt((double)k);
            for(int l = k; l <= n; l+=k){
                b[++tail] = a[l];
                c[tail] = f[l];
                ma = max(ma, f[l]);
            }
            sum[1] = b[1];
            for(int i = 2; i <= tail; i++) sum[i] = sum[i-1] + b[i];
            for(int i = 1; i <= tail; i++)
            {
                L[i] = getma(c[i]-1);
                insma(c[i], i);
            }
            for(int i = tail; i > 0; i--)
            {
                R[i] = getmi(c[i]-1);
                insmi(c[i], i);
            }
            for(int i = 1; i <= tail; i++)
            {
                int st = L[i], ed = R[i];
                if(ed == INF) ed = tail+1;
                ans = max(ans, (sum[ed-1] - sum[st]) * b[i] * sk);
            }
            for(int i = 1; i <= tail; i++)
            {
                reset(c[i]);
            }
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
//int main1()
//{
//    freopen("F:/in.txt","w",stdout);
//    int T = 1;
//    cout<<T<<endl;
//    while(T--)
//    {
//        int n = 300000;
//        cout<<n<<endl;
//        for(int i = 0; i < n; i++)
//        {
//            cout<<rand()+1;
//            if(i == n-1) cout<<endl;
//            else cout<<" ";
//        }
//    }
//}

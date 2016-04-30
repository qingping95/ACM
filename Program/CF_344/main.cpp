#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
//#include <unordered_map>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const LL N = 200020;
struct info
{
    LL l;
    char c;
}tt[N], ss[N], t[N], s[N];
void update(info pre[], info cur[], LL n, LL& tail)
{
    tail = 0;
    cur[tail++] = pre[0];
    for(LL i = 1; i < n; i++)
    {
        if(pre[i].c == cur[tail-1].c) {
            cur[tail-1].l += pre[i].l;
            continue;
        }
        cur[tail++] = pre[i];
    }
}
unsigned long long h1[N], h2[N], base[N];
const LL MAGIC = 99999999999973LL;
inline void init_hash(info s[], unsigned long long h[], LL l)
{
    h[0]= 0;
    for(LL i = 1; i <= l;++i)
        h[i] = h[i-1] * MAGIC + s[i-1].c*123 + s[i-1].l;
    base[0] = 1;
    for(LL i = 1; i <= l; ++i)
        base[i] = base[i-1] * MAGIC;
}
inline unsigned long long string_hash(unsigned long long *h, LL l, LL r) //[0-base)
{
    return h[r] - h[l] * base[r-l];
}
int main()
{
    //Open();
    LL n, m;
    scanf("%I64d%I64d", &n, &m);
    for(LL i = 0; i<n; i++) scanf("%I64d-%c", &tt[i].l, &tt[i].c);
    for(LL i = 0; i<m; i++) scanf("%I64d-%c", &ss[i].l, &ss[i].c);
    update(tt, t, n, n);
    update(ss, s, m, m);
//    cout<<n<<" "<<m<<endl;
    LL ans = 0;
    if(m == 1) {
        for(LL i = 0; i < n; i++)
        {
            if(t[i].c == s[0].c && t[i].l >= s[0].l)
            {
                ans += t[i].l - s[0].l+1;
            }
        }
    }else if(m == 2){
        for(LL i = 0; i < n-1; i++)
        {
            if(t[i].c == s[0].c && t[i+1].c == s[1].c && t[i].l >= s[0].l && t[i+1].l >= s[1].l)
            {
                ans++;
            }
        }
    }else{
        init_hash(t, h1, n);
        init_hash(s, h2, m);
        for(int i = 0; i+m<=n; i++)
        {
            if(string_hash(h1, i+1, i+m-1) == string_hash(h2, 1, m-1)
                && t[i].l >= s[0].l && t[i+m-1].l >= s[m-1].l
                && t[i].c == s[0].c && t[i+m-1].c == s[m-1].c)
                    ans++;
        }
    }
    printf("%I64d\n", ans);
    return 0;
}

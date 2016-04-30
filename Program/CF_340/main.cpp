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
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const LL N = 100010;
struct node{
    int l, r, id;
    bool operator<(const node& o)const {
        return r < o.r;
    }
}query[N], tmp[N];
bool lcmp(const node& a, const node& b)
{
    return a.l < b.l;
}
int ans[N];
int n, m, k;
int a[N], cnt[N], cntk[N];
void update(int c1[], int c2[], int tmp, int& ans)
{
    int num = abs(tmp);
    if(tmp < 0) {
        if(c1[num] <= c2[num])
            ans--;
    }else{
        if(c1[num] < c2[num])
            ans++;
    }
}
void solve(int num)
{
    memset(cnt, 0, sizeof(cnt));
    memset(cntk, 0, sizeof(cntk));
    int tail = 0;
    int st = sqrt(n)*num, ed = sqrt(n)*(num+1);
    for(int i = 0; i < m; i++)
    {
        if(query[i].l < ed && query[i].r >= st)
            tmp[tail++] = query[i];
    }
    sort(tmp, tmp+tail);
    int L = st, R = st-1;
    int tans = 0;
    for(int i = 0; i < tail; i++)
    {
        while(R < tmp[i].r)
        {
            update(cnt, cntk, a[i], tans);
            cnt[a[R+1]]++;
            update(cntk, cnt, a[i], tans);
            cntk[a[R+1]^k]++;
            R++;
        }
        while(L < tmp[i].l)
        {
            update(cnt, cntk, -a[i], tans);
            cnt[a[L]]--;
            update(cntk, cnt, -a[i], tans);
            cntk[a[L]^k]--;
            L++;
        }
        while(L > tmp[i].l)
        {
            update(cnt, cntk, a[i], tans);
            cnt[a[L]]++;
            update(cntk, cnt, a[i], tans);
            cntk[a[L]^k]++;
            L--;
        }
        ans[tmp[i].id] = tans;
    }
}
int main()
{
//    Open();
    scanf("%d%d%d", &n, &m, &k);
    a[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        a[i] ^= a[i-1];
    }
    for(int i = 0; i < m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l--;
        query[i] = (node){l, r, i};
    }
    for(int i = 0; i * sqrt(n) < n; i ++)
    {
        solve(i);
    }
    for(int i = 0; i < m; i++)
    {
        printf("%d%c", ans[i], " \n"[i == m-1]);
    }
    return 0;
}

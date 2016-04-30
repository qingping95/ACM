#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
#include <unordered_map>
#define N 100010
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
const int mod = 1000000007;
void Open()
{
#ifndef ONLINE_JUDGE
    freopen("D:/in.txt","r",stdin);
    //freopen("D:/my.txt","w",stdout);
#endif // ONLINE_JUDGE
}
int n, k;
int a[77];
int kn[4];
struct info
{
    int s1, s2, c1, c2;
    info() {}
    info(int s1, int s2, int c1, int c2):s1(s1),s2(s2),c1(c1),c2(c2) {}
    bool operator==(const info& o)const
    {
        return s1==o.s1 && s2==o.s2 && c1==o.c1 && c2==o.c2;
    }
    bool operator<(const info& o)const
    {
        if(s1==o.s1 && s2==o.s2 && c1==o.c1) return c2<o.c2;
        if(s1==o.s1 && s2==o.s2) return c1 < o.c1;
        if(s1==o.s1) return s2<o.s2;
        return s1<o.s1;
    }
};
vector<int> m3p;
vector<int> m2p;
const int hash_size = 999983;
vector<pair<info, int> > h_table[hash_size];
int cnt = 0;
void hash_init()
{
    for(int i = 0; i < hash_size; i++) h_table[i].clear();
    cnt = 0;
}
int getidx(info o, bool isins)
{
    int res = o.s1 + o.s2 + o.c1 + o.c2;
    res %= hash_size;
    for(int i = 0; i < h_table[res].size(); i ++)
        if(h_table[res][i].first == o) return h_table[res][i].second;
    if(!isins) return -1;
    h_table[res].push_back(make_pair(o, cnt++));
    return cnt-1;
}
LL f[55];
void getfac()
{
    f[0] = f[1] = 1;
    for(int i = 2; i<30; i++) f[i] = f[i-1] * i % mod;
}
void threestart(int st, LL& ans, int& k1, int& k2)
{
    int limit = 1;
    int num = (st == 0 ? n / 2 : n - n / 2);
    for(int i = 0; i < num; i++) limit *= 3;
    for(int s = 0; s < limit; s++)
    {
        int tmps = s;
        int s1=0, s2=0, c1=0, c2=0;
        for(int i = 0; i < num; i++)
        {
            int sel = tmps % 3;
            if(sel == 1) s1 += a[st + i], c1 ++;
            if(sel == 2) s2 += a[st + i], c2 ++;
            tmps /= 3;
            if(s1 > k1 || s2 > k2) break;
        }
        if(s1 > k1 || s2 > k2) continue;
        if(st == 0)
        {
            info tin(s1, s2, c1, c2);
//            m3p[tin]++;
            int idx = getidx(tin, 1);
            if(m3p.size() <= idx) m3p.push_back(1);
            else m3p[idx]++;
        }
        else if(s1 <= k1 && s2 <= k2)
        {
            for(int i = 0; i <= n / 2; i ++)
                for(int j = 0; j <= n / 2 - i; j ++)
                {
                    info tin(k1 - s1, k2 - s2, i, j);
                    int idx = getidx(tin, 0);
                    if(idx == -1) continue;
                    int tnum = m3p[idx];
                    if(tnum == 0) continue;
                    ans = (ans - (LL)tnum*f[i+c1]%mod*f[j+c2]%mod*f[n-c1-c2-i-j]%mod)%mod;
                }
        }
    }
}

void midstart(int st, LL& ans, int& k1, int k2 = -1)
{
    int num = (st == 0 ? n/2: n-n/2);
    int limit = 1 << num;
    for(int s = 0; s < limit; s++)
    {
        int s1 = 0, c1 = 0;
        for(int j = 0; j < num; j++)
        {
            if(s & (1 << j))
                c1++, s1 += a[st + j];
            if(s1 > k1 && s1 > k2) break;
        }
        if(s1 > k1 && s1 > k2) continue;
        if(st == 0)
        {
            info tin(s1, 0, c1, 0);
            int idx = getidx(tin, 1);
            if(idx >= m2p.size()) m2p.push_back(1);
            else m2p[idx]++;
        }
        else
        {
            for(int i = 0; i <= n / 2; i++)
            {
                if(k1 >= s1){
                    info tin(k1 - s1, 0, i, 0);
                    int idx = getidx(tin, 0);
                    if(idx != -1){
                        int tnum = m2p[idx];
                        ans = (ans + (LL)tnum * f[i+c1]%mod*f[n-i-c1]%mod)%mod;
                    }
                }
                if(k2 >= s1)
                {
                    int idx = getidx(info(k2 - s1, 0, i, 0), 0);
                    if(idx == -1) continue;
                    int tnum = m2p[idx];
                    ans = (ans + (LL)tnum * f[i+c1]%mod*f[n-i-c1]%mod)%mod;
                }
            }
        }
    }
}

int main()
{
    Open();
    getfac();
    while(~scanf("%d", &n))
    {
        for(int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        int k;
        scanf("%d", &k);
        if(k == 0)
        {
            printf("%I64d\n", f[n]);
        }
        else
        {
            LL ans = 0;
            for(int i = 0; i < k; i ++)
                scanf("%d", &kn[i]);
            sort(kn, kn+k);
            k = unique(kn, kn+k) - kn;
            if(k == 2) kn[k++] = kn[1] - kn[0];
            if(k == 1)
            {
                midstart(0, ans, kn[0]);
                midstart(n/2, ans, kn[0]);
                printf("%I64d\n", (f[n] - ans + mod)%mod);
            }
            else
            {
                midstart(0, ans, kn[0], kn[1]);
                midstart(n/2, ans, kn[0], kn[1]);
                hash_init();
                threestart(0, ans, kn[0], kn[2]);
                threestart(n / 2, ans, kn[0], kn[2]);
                printf("%I64d\n", (f[n] - ans + mod)%mod);
            }
        }
    }
    return 0;
}
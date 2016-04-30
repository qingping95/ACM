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
const int INF=0x3f3f3f3f;
void Open()
{
#ifndef ONLINE_JUDGE
    freopen("F:/in.txt","r",stdin);
    //freopen("F:/my.txt","w",stdout);
#endif // ONLINE_JUDGE
}
const int MAG = 100010;
int n, m, k;
int base[N], one[N];
unsigned int hs[26][N], tmph[N];
int id[26][N], tail[26], tmpta[26];
vector<unsigned int> hast, haed;
inline void init_st(int n)
{
    base[0] = 1;
    one[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        base[i] = base[i-1] * MAG;
        one[i] = one[i-1] * MAG + 1;
    }
}
inline void init_h(int *s, unsigned int *h, int n)
{
    h[0] = 0;
    for(int i = 1; i <= n; i++)
        h[i] = h[i-1] * MAG + s[i-1];
}
inline unsigned int geths(unsigned * h, int l, int r)
{
    return h[r] - h[l] * base[r-l];
}
int ina[N];
int mod[N], sta[N];
int main()
{
//    Open();
    while(~scanf("%d%d%d", &n, &m, &k))
    {
        hast.clear(), haed.clear();
        memset(tmpta, 0, sizeof(tmpta));
        init_st(n);
        for(int i = 0; i < n; i++)
        {
            scanf("%d", &ina[i]);
        }
        int cnt = 0;
        for(int i = 0; i < m; i++)
        {
            scanf("%d", &mod[i]);
            sta[cnt++] = mod[i];
        }
        sort(sta, sta+cnt);
        cnt = unique(sta, sta+cnt) - sta;
        for(int i = 0; i < m; i++)
        {
            mod[i] = lower_bound(sta, sta+cnt, mod[i]) - sta + 1;
            id[mod[i]][tmpta[mod[i]]++] = i;
        }
        for(int i = 1; i <= cnt; i++)
        {
            init_h(id[i], tmph, tmpta[i]);
            hast.push_back(geths(tmph, 0, tmpta[i]));
        }

        memset(tail, 0, sizeof(tail));
        for(int i = 0; i < n; i++)
        {
            int x = ina[i];
            id[x][tail[x]++] = i;
        }
        for(int i = 1; i <= k; i++)
        {
            if(tail[i] == 0) continue;
            init_h(id[i], hs[i], tail[i]);
        }
        int pre = -1;
        int ans = 0;
        for(int i = 0; i < n && i + m <= n; i++)
        {
            if(i > pre){
                int ed = i + m;
                haed.clear();
                for(int j = 1; j <= k; j++)
                {
                    int l = lower_bound(id[j], id[j]+tail[j], i) - id[j];//×ó±ÕÓÒ¿ª
                    int r = lower_bound(id[j], id[j]+tail[j], ed) - id[j];
                    if(l >= r) continue;
                    haed.push_back(geths(hs[j], l, r));
                }
                if(haed.size() == hast.size())
                {
                    bool flag = true;
                    for(int j = 0; j < haed.size() && flag; j++)
                        flag = (haed[j] == hast[j]);
                    if(flag)
                    {
                        pre = ed - 1;
                        ans ++;
//                        cerr<<i<<" "<<ed<<endl;
                    }
                }
            }
            for(int j = 0; j < hast.size(); j++)
            {
                hast[j] += one[tmpta[j+1]];
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

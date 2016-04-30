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
int mar[20][222];
PII sta[2][11000];
int info[2][11000][12];
int vis[111][11000];
int doub[111][11111];
int cas = 1;
int tail[2];
PII pre[111111];
int ans[20][222];
int main()
{
    Open();
    LL T;
    scanf("%I64d", &T);
    while(T--)
    {
        cas++;
        int prenum = 0;
        int n, m;
        scanf("%d%d", &n, &m);
        memset(mar, 0, sizeof(mar));
        for(int i = 0; i < n; i++)
            for(int j = 1; j <= m; j++)
                scanf("%d", &mar[i][j]);
        int cur = 1;
        tail[0] = tail[1] = 0;
        sta[cur][tail[cur]++] = PII(0, -1);
        bool flag = false;
        for(int i = 1; i <= m; i++)
        {
            cur ^= 1;
            int& t = tail[cur];
            t = 0;
            if(tail[cur^1] == 0){
                flag = true;
                break;
            }
            for(int j = 0; j < tail[cur ^ 1]; j++)
            {
                int s = sta[cur^1][j].first;
                if(doub[i-1][s] == cas) continue;
                int *in = info[cur^1][j];
                for(int ss = 0; ss < (1 << (n-2)); ss++)
                {
                    int sp = ss << 1;
                    bool isok = true;
                    for(int k = 0; k < n && isok && i != 1; k++)
                    {
                        int num = k > 0 ? ((sp >> (k-1))&1) : 0;
                        num += (sp >> k) & 1;
                        if(k < n) num += (sp >> (k+1)) & 1;
                        if(num != in[k]) isok = false;
                    }
                    if(isok) {
                        if(vis[i][sp] == cas) {
                            doub[i][sp] = cas;
                            continue;
                        }
                        int *put = info[cur][t];
                        sta[cur][t] = PII(sp, prenum);
                        for(int k = 0; k < n && isok; k++)
                        {
                            int num = 0;
                            if(k > 0) num += ((sp >> (k-1))&1), num += ((s >> (k-1))&1);
                            if(k < n) num += ((sp >> (k+1))&1), num += ((s >> (k+1))&1);
                            num += ((sp >> (k))&1), num += ((s >> (k))&1);
                            if(num > mar[k][i] || (i == m && num != mar[k][i])) isok = false;
                            else put[k] = mar[k][i] - num;
                        }
                        if(isok){
                            pre[prenum++] = PII(sp, sta[cur^1][j].second);
                            vis[i][sp] = cas;
                            t++;
                        }
                    }
                }
            }
        }
        if(flag || tail[cur] == 0){
            printf("Impossible\n");
        }else{
            if(tail[cur] > 1){
                printf("Multiple\n");
            }else{
                int ppp = sta[cur][0].second;
                int *in = info[cur][0];
                flag = true;
                for(int i = 0; i < n; i++)
                    if(in[i] != 0) flag = false;
                if(flag == false)
                {
                    printf("Impossible\n");
                    continue;
                }
                int idx = m;
                while(ppp != -1 && idx)
                {
                    int sp = pre[ppp].first;
                    for(int i = 0; i < n; i++)
                    {
                        ans[i][idx] = (sp >> i) & 1;
                    }
                    ppp = pre[ppp].second;
                    idx--;
                }
                for(int i = 0; i < n; i++)
                    for(int j = 1; j <= m; j++)
                        printf("%d%c", ans[i][j], " \n"[j == m]);
            }
        }
    }
    return 0;
}

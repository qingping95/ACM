#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <climits>
#include <bitset>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int N = 200010;
char ss[N], st[N];
int sa[N], t[N], t2[N], c[N];//
int rk[N], height[N];//
//注意要在字符串最后增加一个最小值
//sa[i] 表示字典序第i个后缀的起始位置
//rk[i] 表示str第i个位置的后缀在字典序中的排位，rk从1开始计数
//height[i] 表示字典序排序中i和i-1后缀的最长公共前缀,从[2,len]有意义,左闭右闭
//调用的时候，build_sa(a, n+1, m), getHeight(a, n);
void getHeight(char *s, int n)
{
    int i, k = 0;
    for(i = 1; i <= n; i++) rk[sa[i]] = i;
    for(i = 0; i < n; i++)
    {
        if(k)k--;
        if(rk[i] == 0) continue;
        int j = sa[rk[i]-1];
        while(i+k < n && j+k < n && s[i+k] == s[j+k]) k++;
        height[rk[i]] = k;
    }
}
void build_sa(char *s, int n, int m)
{
    int i, *x = t, *y = t2;
    for(i = 0; i < m; i++) c[i] = 0;
    for(i = 0; i < n; i++) c[x[i] = s[i]]++;
    for(i = 1; i < m; i++) c[i] += c[i-1];
    for(i = n-1; i>=0; i--)sa[--c[x[i]]] = i;
    for(int k = 1; k <= n; k <<= 1){
        int p = 0;
        for(i = n-k; i < n; i++) y[p++] = i;
        for(i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i]-k;
        for(i = 0; i < m; i++) c[i] = 0;
        for(i = 0; i < n; i++) c[x[y[i]]]++;
        for(i = 1; i < m; i++) c[i] += c[i-1];
        for(i = n-1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
        swap(x, y);
        p = 1; x[sa[0]] = 0;
        for(i = 1; i < n; i++)
            x[sa[i]] = y[sa[i-1]]== y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k] ? p-1 : p++;
        if(p >= n) break;
        m = p;
    }
}
int dp[N][22];//
int mm[N];//
void makermqmi(int n,int b[],int dp[][22])
{
    int i,j;
    mm[0] = -1;
    for(i=0;i<n;i++)
        mm[i+1] = ((i&(i+1)) == 0)?mm[i]+1:mm[i], dp[i][0]=b[i];
    for(j=1;(1<<j)<=n;j++)
        for(i=0;i+(1<<j)-1<n;i++)
            dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
}
int rmq(int x,int y)//[x, y]
{
    int k = mm[y-x+1];
    return min(dp[x][k],dp[y-(1<<k)+1][k]);
}
int lcp(int a, int b)
{
    if(a > b) swap(a, b);
    a++;
    return rmq(a, b);
}
int getOtherLcp(char s[], char t[], int n, int m)
{
    int id = 0;
    while(id < n && id < m && s[id] == t[id]) id++;
    return id;
}
//int sum[N];
int nxt[N];//
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
    int T;scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        printf("Case #%d:\n", cas);
        memset(ss, 0, sizeof(ss));
        memset(height,0, sizeof(height));
        int n, m;
        scanf("%d%d", &n, &m);
        int len = 0;
        ss[len++] = '#';
        for(int i = 0; i < n; i++)
        {
            scanf("%s", ss+len);
            while(ss[len] != 0) len++;
            ss[len++] = '#';
        }
        ss[--len] = '\0';
        reverse(ss, ss+len);
        len--;
        ss[len] = '#';
//        cout<<ss<<endl;
        build_sa(ss, len+1, 222);
        getHeight(ss, len);
        nxt[len] = len;
        for(int i = len-1; i >= 0; i--)
        {
            if(ss[i] == '#') nxt[i] = i;
            else nxt[i] = nxt[i+1];
        }
        makermqmi(len+1, height, dp);
//        sum[0] = 0;
//        for(int i = 1; i <= len; i++)
//        {
//            int sid = sa[i];
//            int res = nxt[sid] - sid;
//            res -= height[i];
//            sum[i] = sum[i-1] + res;
//        }
        while(m--)
        {
            scanf("%s", st);
            int tlen = strlen(st);
            reverse(st, st+tlen);
            int lb = -1, ub = len+1;
            int up = -1, down = -1;
            while(lb + 1 < ub)
            {
                int mid = lb + ub >> 1;
                if(strcmp(ss+sa[mid], st) >= 0) up = ub = mid;
                else lb = mid;
            }
            if(ub == len+1) {
                printf("0\n");
                continue;
            }
            int res = 0;
            if(getOtherLcp(ss+sa[up], st, len-sa[up], tlen) == tlen) {
                lb = up, down = ub = len+1;
                while(lb + 1 < ub)
                {
                    int mid = lb + ub >> 1;
                    if(lcp(up, mid) >= tlen) lb = mid;
                    else down = ub = mid;
                }
                res += tlen - max(height[up], height[down]);
                int uid = sa[up];
                if(up + 1 != down) res += max(0, min(nxt[uid] - uid, lcp(up, down-1)) - tlen);
                else res += nxt[uid] - uid - tlen;
//                res += sum[down-1] - sum[up];
            }
            printf("%d\n", res);
        }
    }
    return 0;
}

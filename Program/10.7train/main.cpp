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
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f3f3f3f3fLL;
const double eps = 1e-10;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int suf[2][33][N];
int sufxor[33][N];
int n;
int a[N];
int c[N];
double ans[34];
void add(int x, int val){
    for(int i = x; i <= n + 10; i += i & (-i)) c[i] += val;
}
int getsum(int x)
{
    int res = 0;
    for(int i = x; i ;i -= i & (-i)) res += c[i];
    return res;
}
int getnum(int s, int idx)
{
    int res = 0;
    for(int i = 0; i < n; i++)
    {
        res += n - suf[s][idx][i];
    }
    return res;
}
int main()
{
    Open();
    int T; scanf("%d",&T);
    for(int t=1;t<=T;t++){
        memset(suf, 0, sizeof(suf));
        memset(sufxor, 0, sizeof(sufxor));
        printf("Case #%d: ",t);
        int n;scanf("%d", &n);
        for(int i = 0; i < n; i++)scanf("%d", &a[i]);
        for(int i = n-1; i >= 0; i--){
            int tmp = a[i];
//            while(tmp)
            for(int cnt = 0; cnt < 32; cnt ++)
            {
                sufxor[cnt][i] = sufxor[cnt][i+1] ^ (tmp & 1);
                suf[0][cnt][i] = suf[0][cnt][i+1];
                suf[1][cnt][i] = suf[1][cnt][i+1];
                suf[tmp & 1][cnt][i] = i;
                tmp >>= 1;
            }
        }
        int all = n * (n-1) / 2 + n;
        int mul = 1;
        ans[0] = ans[1] = ans[2] = 0;
        for(int i = 0; i < 32; i++, mul <<= 1)
        {
            ans[0] += (all - getnum(0, i)) * 1.0 / all * mul;//and
            ans[1] += getnum(1, i) * 1.0 / all * mul;
            int res = 0;
            int tmp = sufxor[i][0];
            res += tmp;
            for(int j = 1; j < n; j++){
                tmp += sufxor[i][j];
                if(sufxor[i][j]){
                    res += i + 1 - tmp;
                }else{
                    res += tmp;
                }
            }
            ans[2] += res*1.0 / all * mul;
        }
        printf("%.6f %.6f %.6f\n", ans[0], ans[1], ans[2]);
    }
    return 0;
}

/*
* ���⣺������һ���ƻ��޽��ĺ�����¥���ܹ���n��¥��ÿһ�㶼���޽�һ��ƹ����ݻ�����Ӿ�ݣ�
* 		ͬʱÿһ�㶼��Ti���˴�ƹ����Pi������Ӿ������ÿ��ֻ���޽�һ�ֳ��ݣ���͵�����һ
*		�����˻��ܵ�������һ�����������Ӧ��ʩ��¥��ȥ�档��ô����ÿ������˵������һ����
*		��(���Ѽ�Ϊ����˵���ʼ����Ŀ���Ĳ�����)��Ҫ��һ���޽�����ʹ���ܻ�����С�����
*		��С����
* 
* dp[i][j][k],��ʾ��i��λ�÷��õ���ʩΪk(0/1)��ǰ��������j��!k��ʩ����С���ѡ�
* ����dp[i][j][k] = min(dp[i-j][l][!k]) + sum(i-j, i);����l����Ҫö�٣�ֻ��Ҫ
* ��������м�һ����һά����Сֵ���ɡ�sum(i-j, i)Ԥ����ɵá�
* ���ﴦ��sum(i, j)֮��Ĵ�Ҳ��һЩ���ɣ����Ȳ�����i==1/j==n���������ô[i, j]�������
* �Ļ���Ϊv[i]*1 + v[i+1]*2 + v[i+2]*3 + ... + v[j-2]*3 + v[j-1]*2 + v[j]*1,Ҳ���ǿ��Կ�
* ���������Ȳ����еĺͣ�����sigma(v[i+k]*k)(1<=k<=j)������ʽ������ͣ����ǿ����ȴ����
* v[i]*i��v[i]��ǰ׺��prei[i]��pre[i]����ôsigma(v[i+k]*k)(1<=k<=j) = prei[j+k] - prei[i]
*  - (pre[j+k] - pre[i])*i;
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <ctime>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 4050
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;

typedef long long LL;
typedef pair<LL, LL> PII;
const LL INF=0x3f3f3f3f;
const double eps = 1e-10;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
LL v[N][2];
LL prei[N][2];
LL sufi[N][2];
LL pre[N][2];
LL n;
//LL dp[N][N][2];
LL res[N][2];
LL getsum(LL l, LL r, LL k)
{
    if(l == 1) return sufi[1][k] - sufi[r+1][k] - pre[r][k]*(n-r);
    if(r == n) return prei[n][k] - prei[l-1][k] - (pre[n][k] - pre[l-1][k])*(l-1);
    if(l == r) return v[l][k];
    if(l == r - 1) return v[l][k] + v[r][k];
    LL mid = l + r >> 1;
    LL res = prei[mid][k] - prei[l-1][k] - (pre[mid][k] - pre[l-1][k])*(l-1);
    l = mid+1;
    res += (sufi[l][k] - sufi[r+1][k]) - (pre[r][k] - pre[l-1][k])*(n-r);
    return res;
}
int main()
{
//    Open();
    LL T;scanf("%lld",&T);
    for(LL Cas = 1; Cas <= T;Cas++){
        printf("Case #%lld: ",Cas);
        scanf("%lld", &n);
        memset(res, 0x3f, sizeof(res));
        pre[0][0] = pre[0][1] = 0;
        prei[0][0] = prei[0][1] = 0;
        for(LL i = 1; i <= n; i++)
        {
            scanf("%lld%lld" ,&v[i][0], &v[i][1]);
            pre[i][0] = pre[i-1][0] + v[i][0];
            pre[i][1] = pre[i-1][1] + v[i][1];
            prei[i][0] = prei[i-1][0] + v[i][0] * i;
            prei[i][1] = prei[i-1][1] + v[i][1] * i;
        }
        sufi[n+1][0] = sufi[n+1][1] = 0;
        for(LL i = n, cnt = 1; i >= 1; i--, cnt++)
            for(LL k = 0; k < 2; k++)
                sufi[i][k] = sufi[i+1][k] + v[i][k]*cnt;
        res[0][0] = res[0][1] = 0;
        for(LL i = 1; i <= n; i++)
            for(LL j = 1; j <= i; j++)
                for(LL k = 0; k < 2; k++){
                    LL tmpans = res[i-j][!k] + getsum(i-j+1, i, !k);
                    if(j != n)res[i][k] = min(res[i][k], tmpans);
                }
        LL ans = min(res[n][0], res[n][1]);
        printf("%lld\n", ans);
    }
    return 0;
}


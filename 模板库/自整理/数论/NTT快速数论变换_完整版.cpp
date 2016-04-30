/*
题意就是节点数为n，高度为k的平衡二叉树的种类数。
于是dp[n][k] = sigma(dp[i][k-1]*dp[n-i-1][k-1]) 
			 + sigma(dp[i][k-1]*dp[n-i-1][k-2]) 
			 + sigma(dp[i][k-2]*dp[n-i-1][k-1])
所以这里用NTT跑15遍预处理出答案即可。
来一发常用原根表，仅供参考！
998244353 3
1004535809 3
985661441 3
880803841 26
786433 10
*/
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
const LL mod = 786433;
LL wn[40];
int g,prime[10010],L=0;
LL pow(LL x,LL n,LL mod)
{
    LL res=1;
    while(n>0){
        if(n&1)res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}
bool check(int x)
{
    for(int i=0;i<L;i++){
        if(pow(x,(mod-1)/prime[i],mod)==1)return false;
    }
    return true;
}
void init()
{
    LL x=mod-1;
    L=0;
    for(int i=2;i<=sqrt(x)+1;i++){
        if(x%i!=0)continue;
        while(x%i==0)x/=i;
        prime[L++]=i;
    }
    if(x!=1)prime[L++]=x;
    for(g=2;;g++){
        if(check(g))break;
    }
    for(int i=0;i<20;i++){
        LL x=1<<i;
        wn[i]=pow(g,(mod-1)/x,mod);
    }
}
void NTT(LL a[], int len, int on)
{
    int j = len >> 1;
    for(int i=1; i<len-1; i++)
    {
        if(i < j) swap(a[i], a[j]);
        int k = len >> 1;
        while(j >= k)
        {
            j -= k;
            k >>= 1;
        }
        if(j < k) j += k;
    }
    int id = 0;
    for(int h = 2; h <= len; h <<= 1)
    {
        id++;
        for(int j = 0; j < len; j += h)
        {
            LL w = 1;
            for(int k = j; k < j + h / 2; k++)
            {
                LL u = a[k] % mod;
                LL t = w * (a[k + h / 2] % mod) % mod;
                a[k] = (u + t) % mod;
                a[k + h / 2] = ((u - t) % mod + mod) % mod;
                w = w * wn[id] % mod;
            }
        }
    }
    if(on == -1)
    {
        for(int i = 1; i < len / 2; i++)
            swap(a[i], a[len - i]);
        LL Inv = pow(len, mod - 2, mod);
        for(int i = 0; i < len; i++)
            a[i] = a[i] % mod * Inv % mod;
    }
}
int dp[16][(1<<16)+10];
LL A[(1<<16)+10], B[(1<<16)+10], C[(1<<16)+10];
int main()
{
    //Open();
    init();
    dp[0][1] = 1;
    dp[1][1] = 0; dp[1][2] = 2; dp[1][3] = 1;
    for(int k = 2; k <= 15; k++)
    {
        int len = 1 << k;
        len <<= 1;
        for(int i = 0; i < len; i++) A[i] = dp[k-1][i], B[i] = dp[k-2][i];
        NTT(A, len, 1);
        NTT(B, len, 1);
        for(int i = 0; i < len; i++)
            C[i] = A[i]*A[i]%mod;
        NTT(C, len, -1);
        for(int i = 0; i < len; i++)
            dp[k][i] = (dp[k][i] + C[i-1])%mod;
        for(int i = 0; i < len; i++)
            C[i] = A[i]*B[i]%mod;
        NTT(C, len, -1);
        for(int i = 0; i < len; i++)
            dp[k][i] = (dp[k][i] + C[i-1]*2)%mod;
    }
    freopen("avl.in", "r", stdin);
    freopen("avl.out", "w", stdout);
    int n, k;
    while(~scanf("%d%d",&n, &k))
    {
        printf("%d\n", dp[k][n]%mod);
    }
    return 0;
}

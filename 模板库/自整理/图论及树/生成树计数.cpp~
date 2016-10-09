/*
* 基尔霍夫矩阵，Max-tree 矩阵，a[i][i]表示i节点的度数，如果有一条边(i,j)，则a[i][j]=-1
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
//        freopen("/home/qingping/out.txt","w",stdout);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 222;
LL mod;
LL a[N][N];
//求行列式的值
LL Det(LL a[][N], LL n)
{
    //mod = 1e9;
//    for(LL i = 0; i < n; i++)
//        for(LL j = 0; j < n; j++)
//            a[i][j] = (a[i][j]%mod+mod)%mod;
    LL ans = 1;
    for(LL i = 0; i < n; i++)
    {
        for(LL j = i+1; j < n; j++)
        {
            //欧几里得辗转相消
            while(a[j][i])
            {
                LL t = a[i][i] / a[j][i];
                for(LL k = i; k < n; k++)
//                    a[i][k] = (a[i][k] - a[j][k]*t%mod)%mod;
                    a[i][k] -= a[j][k]*t;
                for(LL k = i; k < n; k++)
                    swap(a[i][k], a[j][k]);
                ans = -ans;
            }
        }
        if(!a[i][i]) return 0;
//        ans = ans*a[i][i]%mod;
        ans = ans*a[i][i];
    }
    return ans;
//    return (ans + mod) % mod;
}
int main()
{
//    Open();
    int T;
    scanf("%d", &T);
    int n, m;
    while(T--)
    {
        scanf("%d%d", &n, &m);
        memset(a, 0, sizeof(a));
        while(m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            u--, v--;
            a[u][u] ++, a[v][v]++;
            a[v][u] --, a[u][v]--;
        }
        cout<<Det(a, n-1)<<endl;
        //printf("%d\n", Det(a, n-1));
    }
    return 0;
}


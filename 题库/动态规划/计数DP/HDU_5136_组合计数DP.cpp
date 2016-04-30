/*
* http://acm.hdu.edu.cn/showproblem.php?pid=5136
* HDU 5136 Yue Fei's Battle
* 题意：你需要求出一棵树，这棵树的最长的路径上面的点数需要恰好为K，每个点最多只能有三个相邻的点。问有多少种构造方式，同构的树算一种(翻转某节点的子树之后树的形态相同)。
* 
* 这个组合计数题对我来说还是比较困难，想了个大概，但是最主要的处理同构的地方完全没有想到。
* 首先这样考虑，因为这棵树的最长的路径上面的点数必须恰好为K，也就是说这棵树的直径为K，那么可以从这上面当做切入点。
* 设f[i]为层数为i的树，且每个节点的度数最多为3，根节点的度数最多为2的树的构造方案数，g[i] = sigma(f[j])(0<=j<=i);
* 假设从左到右构造;
* 直径上面的第i个点(端点为第0个点)我们都可以接上一棵层数为1~i的树，这样能保证这棵树的直径不超过K，假设当前0~(i-1)个点的方案数已经计算好，为tmp,(i<k/2)
* 那此时在第i个点上我们可以接上一棵层数为1~i的树，但是当接上一棵层数为i的树之后，主链势必会发生变化，也就是说当前接上去的子树会和之前已经构造的
* 0~(i-1)个点形成的树发生重构的现象，此时结果一定是计算重复了，那我们可以先将层数为i-2的树接上去，此时方案为tmp * g[i-1]; 对于接上一棵层数为i的
* 树的方案数来说，因为此时主链有两条，能形成一条主链的方案数为f[i]，由于需要避免同构，那么我们可以在f[i]中选择两种出来构成这两条主链，那么总方案
* 数即为 tmp * g[i-1] + f[i]*(f[i-1])/2+f[i](因为两条链的构成相同也是一种方案); 那么一直递推到直径中间即可。
* 
* 接下来还需要分类讨论，假设k为偶数，且前k/2个点的树的方案数为tmp，那么总的方案数即为tmp*(tmp-1)/2+tmp(加tmp的原因同上)。
* 如果k为奇数，那么还需要在中间的那个点上面接上树，此时可以接上层数为0~(k/2+1),和上面一样，这里在接上层数为(k/2+1)的树时会出现三条主链，那么有以下几种情况：
* 1. 三条主链都不同：此时方案为C(f[k/2+1], 3);
* 2. 两条主链相同，一条不同：此时方案为C(f[k/2+1], 2) * 2 (如果我选择的两种方案为A, B 那么组合方式可为{A,A,B},{A,B,B}两种)；
* 3. 三条主链都相同：此时方案为C(f[k/2+1], 1)；
* 于是此时的总方案为tmp*g[k/2]+C(f[k/2+1], 3)+C(f[k/2+1], 2)*2+C(f[k/2+1], 1);
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
#define LL long long
using namespace std;
#define N 300
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const LL maxn=100000;
const LL mod=1e9+7.5;
LL f[maxn+5];
LL g[maxn+5];
LL gcd(LL a,LL b,LL &d,LL &x,LL &y)
{
    if(!b){d=a;x=1;y=0;}
    else {gcd(b,a%b,d,y,x);y-=x*(a/b);}
}
LL inv(LL a,LL n)
{
    LL d,x,y;
    gcd(a,n,d,x,y);
    return d==1?(x+n)%n:-1;
}
int main()
{
//    Open();
    g[0]=1;
    f[0]=1;
    for(LL i=1;i<=maxn;i++)
    {
        f[i]=(f[i-1]*(g[i-2]+1)%mod+f[i-1]*(f[i-1]-1+mod)%mod*inv(2,mod))%mod;
        g[i]=(f[i]+g[i-1])%mod;
    }
    LL k;
    while(scanf("%I64d",&k)==1&&k)
    {
        if(k==1||k==2){printf("1\n");continue;}
        k-=2;
        LL ans=1LL;
        for(LL i=1;i<=k/2;i++){
            ans=(ans*(g[i-1]))%mod;
            ans = (ans + f[i] * (f[i] - 1)%mod * inv(2, mod) %mod)%mod;
            ans = (ans + f[i])%mod;
        }
        LL tmp = ans;
        ans = tmp*(tmp-1)%mod*inv(2, mod)%mod;
        ans = (ans + tmp)%mod;
        if(k%2==1){
            ans = ans * g[k/2]%mod;
            ans = (ans + tmp * (tmp - 1)%mod * (tmp - 2) %mod * inv(6, mod)%mod)%mod;
            ans = (ans + tmp * (tmp - 1)%mod)%mod;
            ans = (ans + tmp)%mod;
        }
        printf("%I64d\n",(ans+mod)%mod);
    }
    return 0;
}
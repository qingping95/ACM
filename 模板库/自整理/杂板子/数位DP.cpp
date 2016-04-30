#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 22
using namespace std;
typedef pair<long long,long long> PII;
const long long INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}

long long dit[N];
long long dp[N][3][3][3];
long long dfs(long long idx,bool ppre,long long pre,bool limit,long long edidx)
{
    if(dp[idx][ppre][pre][limit]!=-1)
        return dp[idx][ppre][pre][limit];

    if(idx==edidx+1)
    {
        if(ppre && pre == 1)
        {
            return dp[idx][ppre][pre][limit]=1;
        }
        return dp[idx][ppre][pre][limit]=0;
    }
    if(ppre && pre == 1)
    {
        long long cur=10;
        if(limit){
            int tmpidx=idx;
            cur=dit[edidx-idx];
            while(++tmpidx<=edidx)
            {
                cur*=10;
                cur+=dit[edidx-tmpidx];
            }
        }else{
            int tmpidx=idx;
            while(++tmpidx<=edidx)
            {
                cur*=10;
            }
        }
        return dp[idx][ppre][pre][limit]=cur;
    }

    long long ret=0;

    for(long long i=0;i <= (limit?dit[edidx-idx]:9);i++)
    {
        long long flag=0;
        if(i==4) flag=2;
        if(i==9) flag=1;
        ret+=dfs(idx+1,pre==2,flag,limit && i==dit[edidx-idx],edidx);
        //ret+=dfs(idx+1,pre,i,limit && i==dit[edidx-idx],edidx);
    }
    return dp[idx][ppre][pre][limit]=ret;
}

long long getval(long long x)
{
    long long ditnum=0;
    memset(dp,-1,sizeof dp);
    while(x)
    {
        dit[ditnum++]=x%10;
        x/=10;
    }
    return dfs(1,0,0,1,ditnum);
}

int main()
{
    Open();
    long long T;
    scanf("%I64d",&T);
    while(T--)
    {
        long long a;
        scanf("%I64d",&a);
        printf("%I64d\n",getval(a));
    }
    return 0;
}
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>
#define MAX_N 100000

using namespace std;
struct info
{
    int a;
    int b;
};

info ss[MAX_N+10];
int cmp(info x,info y)
{
    return x.a<y.a;
}
int main()
{
    //freopen("F:/std.in","r", stdin);
    //freopen("F:/std.out","w",stdout);
    int n,l,p;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<n;i++)
            scanf("%d%d",&ss[i].a,&ss[i].b);
        scanf("%d%d",&l,&p);
        for(int i=0;i<n;i++)
            ss[i].a=l-ss[i].a;
        ss[n].a=l,ss[n].b=0;
        n++;
        sort(ss,ss+n,cmp);
        priority_queue<int> que;
        int ans=0,index=0,tank=p;//ans是当前需要加油的次数，index是当前所处位置，tank是当前车的容量
        for(int i=0;i<n;i++)
        {
            int d=ss[i].a-index;
            while(tank-d<0)
            {
                if(que.empty())
                {
                    ans = -1;
                    break;
                }
                tank+=que.top();
                que.pop();
                ans++;
            }
            if(ans == -1) break;
            tank-=d;
            index=ss[i].a;
            que.push(ss[i].b);
        }
        printf("%d\n",ans);
    }
    return 0;
}
typedef long long LL;
int main1()
{
    freopen("F:/stdrandom.in","w", stdout);
    int T = 10;
    while(T--)
    {
        int n = (LL)rand()*rand()%100001;
        //int n = 100000;
        printf("%d\n", n);
        int L = (LL)rand()*rand()*rand()%1000000;
        int P = (LL)rand()*rand()%L;
        for(int i = 0; i < n; i++)
        {
            int x = (LL)rand()*rand()%L;
            int y = (LL)rand()*rand()%10000+1;
            printf("%d %d\n", x, y);
        }
        printf("%d %d\n", L, P);
    }
}

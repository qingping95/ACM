/*
*	首先考虑如何判定是不是合法的集合，如果合法的序列为a[]，那么a[i]这个点一定恰好能被i-1个点打败，那么记录集合中
*	每个点能被别的多少个点打败，那么这个数量就是其在合法序列中的位置，有冲突的话就不合法。
*	考虑如何给T1加点，可以发现这样的事实，已经在T1中的点不可能会改变位置，并且，每个点能放置的空隙(T1[i]~T1[i+1])
*	如果能够放那也一定是固定的位置。
*	基于上述事实，进一步抽象问题，将每一个空隙能放置的点求出来，空隙与空隙之间的点位置关系已经确定。另外，可以将T1
*	中的点抛开考虑，那么新加进来的点会是怎样的排列方式呢？一定是在T2中的相对顺序对不对！？所以只需要利用空隙给T2中
*	的点标上权值，基于T2合法序列跑一个最长不降子序列即可。
*/
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
typedef pair<LL, LL> PII;
const int INF = 0x3f3f3f3f;
const int mod = 1e9+7.5;
const int N = 1010;
int T1[N], T2[N], num[N];
bool vis[N];
int s1[N], s2[N];
bitset<1001> bt[N];
bitset<1001> pre[N];
bitset<1001> suf[N];

bool gett(int sta[], int m, int t1[])
{
    memset(num, 0, sizeof(num));
    memset(t1, -1, sizeof(int)*m);
    for(int i = 1; i <= m; i++)
    {
        num[i] = 0;
        int u = sta[i];
        for(int j = 1; j <= m; j++)
        {
            int v = sta[j];
            if(bt[u][v] == 0) num[i]++;
        }
        t1[num[i]] = u;
    }
    for(int i = 1; i <= m; i++)
    {
        if(t1[i] == -1) return false;
    }
    return true;
}
struct Reader{
    static const int MSIZE = 1000 * 20 * 1024;
    char buf[MSIZE], *pt = buf, *o = buf;
    void init(){
        fread(buf, 1, MSIZE, stdin);
    }
    char getch()
    {
        char ch;
        while((*pt < 'A' || *pt > 'Z') && (*pt < 'a' || *pt > 'z')) pt++;
        ch = *pt;pt++;
        return ch;
    }
    int getint()
    {
        int f = 1, x = 0;
        while(*pt != '-' && !isdigit(*pt)) pt++;
        if(*pt == '-') f = -1, pt++;
        else x = *pt++ - 48;
        while(isdigit(*pt)) x = x * 10 + *pt++ - 48;
        return x * f;
    }
}frd;
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
    frd.init();
    int cas = 0;
    int n, m;
    n = frd.getint();
    m = frd.getint();
    while(n || m)
    {
        memset(vis, 0, sizeof(vis));

        for(int i = 1; i <= n; i++){
            bt[i].reset();
            for(int j = 1; j <= n; j++)
            {
                int x;
                x = frd.getint();
                if(x) bt[i].set(j);
            }
        }
        for(int i = 1; i <= m; i++)
        {
            int x;
            x = frd.getint();
            vis[x] = 1;
            s1[i] = x;
        }
        bool flag = gett(s1, m, T1);
        int t = 0;
        for(int i = 1; i <= n; i++)
            if(vis[i] == 0) s2[++t] = i;
        flag &= gett(s2, t, T2);
        if(!flag)
        {
            n = frd.getint();
            m = frd.getint();
            puts("NO");
            continue;
        }
        pre[0].set();
        for(int i = 1; i <= m; i++)
        {
            pre[i] = pre[i-1] & bt[T1[i]];
        }
        suf[m+1].set();
        for(int i = m; i >= 1; i--)
        {
            suf[i] = bt[T1[i]];
            suf[i].flip();
            suf[i].reset(T1[i]);
            suf[i] &= suf[i+1];
        }
        memset(num, -1, sizeof(num));
        for(int i = 1; i <= m+1; i++)
        {
            bitset<1001> tmp = pre[i-1] & suf[i];
            for(int v = 1; v <= n; v++)
            {
                if(tmp[v])
                    num[v] = i-1;
            }
        }
        for(int i = 1; i <= t; i++)
        {
            T2[i] = num[T2[i]];
        }
        memset(num, 0x3f, sizeof(num));
        for(int i = 1; i <= t; i++)
        {
            if(T2[i] == -1) continue;
            *upper_bound(num, num+t, T2[i]) = T2[i];
        }
        printf("YES %d\n", lower_bound(num, num+t, INF) - num);
        n = frd.getint();
        m = frd.getint();
    }
    return 0;
}


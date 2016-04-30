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
using namespace std;
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define VINT vector<int>
#define PII pair<int,int>
#define MP(x,y) make_pair((x),(y))
#define ll long long
#define ull unsigned ll
#define MEM0(x)  memset(x,0,sizeof(x))
#define MEM(x,val) memset((x),val,sizeof(x))
#define scan(x) scanf("%d",&(x))
#define scan2(x,y) scanf("%d%d",&(x),&(y))
#define scan3(x,y,z) scanf("%d%d%d",&(x),&(y),&(z))
#define scan4(x,y,z,k) scanf("%d%d%d%d",&(x),&(y),&(z),&(k))
#define Max(a,b) a=max(a,b)
#define Min(a,b) a=min(a,b)
using namespace std;
const int N=400045;
int mp[N];
struct node
{
    int ty, l, r;
    node(){}
    node(int ty, int l, int r):ty(ty), l(l), r(r){}
}q[N];
int n;
int idx[N];
int cnt = 0;//
int rc[N];//
int lc[N];//
void add(int c[], int x, int val)
{
    if( x == 0 ) return ;
    for(int i=x;i <= cnt+10;i += i & (-i)) c[i] += val;
}
int getsum(int c[], int x)
{
    int rnt = 0;
    for(int i = x;i>0;i -= i & (-i)) rnt += c[i];
    return rnt;
}
template<class T>
inline bool read(T &n){
    T x = 0, tmp = 1; char c = getchar();
    while ((c < '0' || c > '9') && c != '-' && c != EOF) c = getchar();
    if (c == EOF) return false;
    if (c == '-') c = getchar(), tmp = -1;
    while (c >= '0' && c <= '9') x *= 10, x += (c - '0'), c = getchar();
    n = x*tmp;
    return true;
}
template <class T>
inline void write(T n) {
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    int len = 0, data[20];
    while (n) {
        data[len++] = n % 10;
        n /= 10;
    }
    if (!len) data[len++] = 0;
    while (len--) putchar(data[len] + 48);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("D:/in.txt","r",stdin);
#endif
    int Cas = 1;
    while(~scanf("%d", &n))
    {
        printf("Case #%d:\n",Cas++);
        memset(rc, 0, sizeof(rc));
        memset(lc, 0, sizeof(lc));
        cnt = 0;
        int len = 1;
        for(int i=1;i<=n;i++)
        {
            int a, b;
            scanf("%d%d", &a, &b);
//            read(a);read(b);
            if(a == 0){
                q[i] = node(a, b, b+len);
                mp[cnt++] = b, mp[cnt++] = b+len;
                idx[len] = i;
                len++;
            }else{
                q[i] = node(a, q[idx[b]].l, q[idx[b]].r);
            }
        }
        sort(mp, mp+cnt);
        cnt = unique(mp, mp+cnt) - mp;
        for(int i=1;i<=n;i++)
        {
            q[i].l = lower_bound(mp, mp+cnt, q[i].l) - mp + 1;
            q[i].r = lower_bound(mp, mp+cnt, q[i].r) - mp + 1;
        }
        for(int i=1;i<=n;i++)
        {
            if(q[i].ty == 0) {
                printf("%d\n", getsum(rc, q[i].r) - getsum(lc, q[i].l - 1));
                add(rc, q[i].r, 1), add(lc, q[i].l, 1);
            }else {
                add(rc, q[i].r, -1), add(lc, q[i].l, -1);
            }
        }
    }
    return 0;
}

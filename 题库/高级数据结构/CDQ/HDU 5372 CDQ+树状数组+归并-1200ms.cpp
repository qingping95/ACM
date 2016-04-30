/*
* Problem Description
* One day Lillian gets some segments from her fans Lawson with lengths of 1,2,3... and she intends to display them by adding them to a number line.At the i-th add operation,she will put the segment with length of i on the number line.Every time she put the segment on the line,she will count how many entire segments on that segment.During the operation ,she may delete some segments on the line.(Segments are mutually independent)
*  
* Input
* There are multiple test cases.
* The first line of each case contains a integer n — the number of operations(1<=n<=2∗105,∑n<=7∗105)
* Next n lines contain the descriptions of the operatons,one operation per line.Each operation contains two integers a , b. 
* if a is 0,it means add operation that Lilian put a segment on the position b(|b|<109) of the line.
* (For the i-th add operation,she will put the segment on [b,b+i] of the line, with length of i.)
* if a is 1,it means delete operation that Lilian will delete the segment which was added at the b-th add operation.
*  
* Output
* For i-th case,the first line output the test case number.
* Then for each add operation,ouput how many entire segments on the segment which Lillian newly adds.
* 
* 题意：有n条线段，每条线段的长度分别是1,2,3,...,n，现在要按顺序讲这些线段放在数轴上，两种操作：
*		第一种：将待放进去的线段放到数轴的b位置(起始位置为b),要求输出这条线段覆盖了多少条完整的
*		线段(还在数轴上的)，
*		第二种：将第b次操作放入的线段删除。
* 做法：这个题有两种做法，一种是CDQ，这种方法很暴力啦，不过要注意，这里不能再CDQ里面直接排序，而是需要用
*		下层排序之后的结果进行归并排序，降低复杂度，才能卡着过，至于在cdq里面的话，就是先保证左端点在当前
*		线段左端点右边，再去树状数组中查找有多少个右端点在当前线段的右端点的左边。
*		另一种是树状数组，上面CDQ没有利用到题目中的线段长度递增这一性质。只需要用两个树状数组，一个(lc)记录
*		左端点，一个(rc)记录右端点即可，对于一个区间[l,r]，ans = getsum(rc, r) - getsum(lc, l-1)。如果题目
*		没有规定长度递增的话，这样是有问题，因为在减左端点的时候，会将lp<l&&rp>r的那种区间减去，但是
*		这里规定了区间长度，所以这里也并没有那样的区间这样的话，代码也好写一些。
*
* 扩展：如果这里没有时效性的操作，可以将所有区间按照左端点排序，从左到右做一遍，维护树状数组的信息，这样
*		也可以求出所有区间内含的所有完整区间的个数。
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
int tmpidx[N];
int cnt = 0;//
int rc[N];//
int lc[N];//
int ans[N];
void add(int c[], int x, int val)
{
    if( x == 0 ) return ;
    for(int i=x;i <= cnt+10;i += i & (-i)) c[i] += val;
}

void bitclear(int c[], int x)
{
    if( x == 0 ) return ;
    for(int i=x;i <= cnt+10;i += i & (-i)) c[i] = 0;
}

int getsum(int c[], int x)
{
    int rnt = 0;
    for(int i = x;i>0;i -= i & (-i)) rnt += c[i];
    return rnt;
}
bool cmp(int a, int b)
{
    return q[a].l > q[b].l;
}
bool bigcmp(int a, int b)
{
    return a > b;
}
void divide(int l, int r)
{
    if(l >= r)
    {
        return ;
    }
    int mid = (l+r)/2;
    divide(l, mid);
    divide(mid+1, r);
    int midmid = (l + mid)/2;
    std::merge(tmpidx+l, tmpidx+midmid+1, tmpidx+midmid+1, tmpidx+mid+1, idx+l, cmp);
    midmid = (mid+1+r)/2;
    std::merge(tmpidx+mid+1, tmpidx+midmid+1, tmpidx+midmid+1, tmpidx+r+1, idx+mid+1, cmp);
    int tail = l;
    for(int i = mid+1; i<=r; i++)
    {
        if(q[idx[i]].ty == 1) continue;
        while(tail <= mid && q[idx[tail]].l >= q[idx[i]].l){
            if(q[idx[tail]].ty == 0) add(rc, q[idx[tail]].r, 1);
            else if(q[idx[tail]].ty == 1) add(rc, q[idx[tail]].r, -1);
            tail++;
        }

        if(q[idx[i]].ty == 0) ans[idx[i]] += getsum(rc, q[idx[i]].r);
    }
    for(int i = l; i <= mid ; i++)
        bitclear(rc, q[i].r);
    for(int i = l; i <= r; i++)
        tmpidx[i] = idx[i];
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
        memset(ans, 0, sizeof(ans));
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
            tmpidx[i] = i;
        divide(1, n);
        for(int i=1;i<=n;i++)
        {
            if(q[i].ty == 0){
//                printf("%d\n", ans[i]);
                write(ans[i]);
                putchar('\n');
            }
        }
    }
    return 0;
}
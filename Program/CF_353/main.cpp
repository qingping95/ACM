#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#define lson (x<<1)
#define rson (x<<1|1)
#define mid ((lt[x].l+lt[x].r)/2)
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
const int N = 100010;
int sta[N];
int a[N];
int b[N];
int L[N], R[N], ans[N];
struct node{
    int l, r, ma, mi;
}lt[N*8];
void pushup(int x)
{
    lt[x].ma = max(lt[lson].ma, lt[rson].ma);
    lt[x].mi = min(lt[lson].mi, lt[rson].mi);
}
void build(int l, int r, int x)
{
    lt[x] = (node){l, r, -INF, INF};
    if(l == r){
        lt[x] = (node){l, r, b[l], b[l]};
        return;
    }
    build(l, mid, lson);
    build(mid+1, r, rson);
    pushup(x);
}
int querymi(int l, int r, int x)
{
    if(lt[x].l >= l && lt[x].r <= r){
        return lt[x].mi;
    }
    if(r <= mid) return querymi(l, r, lson);
    else if(l > mid) return querymi(l, r, rson);
    else return min(querymi(l, mid, lson), querymi(mid+1, r, rson));
}
void update(int idx, int x)
{
    if(lt[x].l == idx && lt[x].r == idx)
    {
        lt[x].ma = -INF;
        lt[x].mi = INF;
        return ;
    }
    if(idx <= mid) update(idx, lson);
    else if(idx > mid) update(idx, rson);
    pushup(x);
}

int main()
{
//    Open();
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]), sta[i] = a[i];
    sort(sta, sta+n);
    for(int i = 0; i < n; i++)
        a[i] = lower_bound(sta, sta+n, a[i]) - sta + 1, b[a[i]] = i;
    build(1, n, 1);
    priority_queue<int, vector<int>, greater<int> > que;
    que.push(0);
    update(a[0], 1);
    for(int i = 0; i < n; i++) L[i] = 1, R[i] = n;
    while(!que.empty())
    {
        int ci = que.top();que.pop();
        int l = L[ci], r = R[ci];
        int miid = INF, maid = INF;
        if(l <= a[ci]) miid = querymi(l, a[ci], 1);
        if(a[ci] <= r) maid = querymi(a[ci], r, 1);
        if(miid != INF){
            ans[miid] = a[ci];
            L[miid] = max(L[miid], L[ci]);
            R[miid] = min(R[miid], a[ci]);
            update(a[miid], 1);
            que.push(miid);
        }
        if(maid != INF){
            ans[maid] = a[ci];
            L[maid] = max(L[maid], a[ci]);
            R[maid] = min(R[maid], R[ci]);
            update(a[maid], 1);
            que.push(maid);
        }
    }
    for(int i = 1; i < n; i++)
        printf("%d%c", sta[ans[i]-1], " \n"[i == n-1]);
    return 0;
}

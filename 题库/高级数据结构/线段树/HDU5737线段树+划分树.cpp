/*
*   HDU5737 线段树+有序表，nlogn*logn
*   只需要再类似划分树那样，记录大区间分别在两个子区间内的rank，就能够递归的去更新答案，需要注意
×   修改的x小于全部当前区间的数的情况
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
#include <ctime>
//#include <unordered_map>
#define ls (x<<1)
#define rs (x<<1|1)
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
//        freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int mod = 1e9+7.5;
const int N = 100010;
int A, B;
int C = ~(1<<31), M = (1<<16)-1;
int rnd(int last) {
    A = (36969 + (last >> 3)) * (A & M) + (A >> 16);
    B = (18000 + (last >> 3)) * (B & M) + (B >> 16);
    return (C & ((A << 16) + B)) % 1000000000;
}

struct node{
    int l, r, ans, fg;
    node(int l = 0, int r = 0, int ans = 0, int fg = -1):l(l), r(r), ans(ans), fg(fg){}
}lt[N*6];//
int a[N], b[N];//
int st[N*6], ed[N*6];//
int allb[N*18], rkl[N*18], rkr[N*18];//
int cur;//
void push_down(int x)
{
    if(lt[x].fg >= 0){
        int tmp = lt[x].fg;
        lt[x].fg = -1;
        lt[ls].fg = rkl[tmp];
        lt[ls].ans = max(0, rkl[tmp] - st[ls]+1);
        lt[rs].fg = rkr[tmp];
        lt[rs].ans = max(0, rkr[tmp] - st[rs]+1);
    }
}
void push_up(int x)
{
    lt[x].ans = lt[ls].ans + lt[rs].ans;
}
void build(int l, int r, int x)
{
    lt[x] = node(l,r,0,-1);
    if(l == r){
        lt[x].ans = a[l] >= b[l];
        st[x] = cur;
        allb[cur++] = b[l];
        ed[x] = cur;
        return ;
    }
    int mid = l + r >> 1;
    build(l, mid, ls);
    build(mid+1, r, rs);

    st[x] = cur;
    int al = st[ls], ar = ed[ls], bl = st[rs], br = ed[rs];
    while(al < ar && bl < br) allb[cur++] = allb[al]>allb[bl] ? allb[bl++] : allb[al++];
    while(al < ar) allb[cur++] = allb[al++];
    while(bl < br) allb[cur++] = allb[bl++];
    ed[x] = cur;

    al = st[ls], bl = st[rs];
    for(int i = st[x]; i < ed[x]; i++)
    {
        while(al < ar && allb[al] <= allb[i]) al++;
        while(bl < br && allb[bl] <= allb[i]) bl++;
        rkl[i] = al-1;rkr[i] = bl-1;
        if(al == st[ls]) rkl[i] = 0;
        if(bl == st[rs]) rkr[i] = 0;
    }
    push_up(x);
}
void update(int l, int r, int rk, int x)
{
    if(l <= lt[x].l && r >= lt[x].r)
    {
        lt[x].fg = rk;
        lt[x].ans = max(0, rk - st[x] + 1);
        return ;
    }
    push_down(x);
    int mid = lt[x].l + lt[x].r >> 1;
    if(r <= mid) update(l, r, rkl[rk], ls);
    else if(l > mid) update(l, r, rkr[rk], rs);
    else update(l, mid, rkl[rk], ls), update(mid+1, r, rkr[rk], rs);
    push_up(x);
}
int query(int l, int r, int x)
{
    if(l <= lt[x].l && r >= lt[x].r)
    {
        return lt[x].ans;
    }
    push_down(x);
    int mid = lt[x].l + lt[x].r >> 1;
    if(r <= mid) return query(l, r, ls);
    else if(l > mid) return query(l, r, rs);
    else return query(l, mid, ls)+query(mid+1, r, rs);
}
int main(){
//    Open();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        cur = 1;
        rkl[0] = 0, rkr[0] = 0;
        int n, m;
        scanf("%d%d%d%d", &n, &m, &A, &B);
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
        build(1, n, 1);
        int last = 0;
        int sum = 0;
        for(int i = 1; i <= m; i++)
        {
            int l = (rnd(last)%n+1), r = (rnd(last)%n+1), x = (rnd(last)+1);
            if(l > r) swap(l, r);
            if(!((l+r+x)&1)){
                last = query(l, r, 1);
                sum = ((LL)sum + (LL)i*last)%mod;
            }else{
                int tmp = upper_bound(allb+st[1], allb+ed[1], x) - allb - 1;
                if(tmp < st[1]) tmp = 0;
                update(l, r, tmp, 1);
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}


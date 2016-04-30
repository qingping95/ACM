#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 201000
#define lson x<<1
#define rson x<<1|1
#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<PII, int> PIII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int a[N];
struct node
{
    int l, r;
    int lazy;
    int mi;
    node(){}
    node(int ll, int rr, int lazyy, int mii){
        l = ll, r = rr, lazy = lazyy, mi = mii;
    }
}lt[N*10];
void push_up(int x)
{
    lt[x].mi = min(lt[lson].mi, lt[rson].mi);
}
void push_down(int x)
{
    if(lt[x].lazy){
        lt[lson].mi += lt[x].lazy;
        lt[lson].lazy += lt[x].lazy;
        lt[rson].mi += lt[x].lazy;
        lt[rson].lazy += lt[x].lazy;
        lt[x].lazy = 0;
    }
}
void build(int l, int r, int x)
{
    lt[x] = node(l, r, 0, 0);
    if(l == r){
        lt[x].mi = a[l];
        return ;
    }
    build(l, mid, lson);
    build(mid+1, r, rson);
    push_up(x);
}
void update(int l, int r, int val, int x){
    if(l > r) return ;
    if(lt[x].l >= l && lt[x].r <= r){
        lt[x].mi += val;
        lt[x].lazy += val;
        return ;
    }
    push_down(x);
    if(r <= mid) update(l, r, val, lson);
    else if(l > mid) update(l, r, val, rson);
    else update(l, mid, val, lson), update(mid+1, r, val, rson);
    push_up(x);
}
int query(int l, int r, int x)
{
    if(lt[x].l == lt[x].r){
        if(lt[x].mi == 0) return lt[x].l;
        else return -1;
    }
    if(lt[x].l >= l && lt[x].r <= r && lt[x].mi > 0){
        return -1;
    }
    push_down(x);
    int res;
    if(r <= mid) res =  query(l, r, lson);
    else if(l > mid) res = query(l, r, rson);
    else {
        int lres = query(l, mid, lson);
        int rres = query(mid+1, r, rson);
        if(lres != -1) res = lres;
        else if(rres != -1) res = rres;
        else res = -1;
    }
    push_up(x);
    return res;
}
int ans[N];
int main()
{
    Open();
    int n;
    while(scanf("%d",&n)==1)
    {
        if(!n)break;
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        build(1, n, 1);
        int cnt = 2 * n;
        queue<int> q;
        bool flag = true;
        int tail = 0;
        while(cnt-- && flag)
        {
            int idx = query(1, n, 1);
            if(idx == -1){
                if(q.empty()) {
                    flag = false;
                    continue;
                }else{
                    int res = q.front();q.pop();
                    ans[tail++] = -res;
//                    printf("%d", -res);
                    update(res+1, n, -1, 1);
                }
            }else{
                ans[tail++] = idx;
                q.push(idx);
                update(1, idx - 1, -1, 1);
                update(idx, idx, INF, 1);
            }
        }
        if(!flag){
            printf("Impossible\n");
        }else{
            for(int i = tail - 1; i >= 0; i--)
            {
                printf("%d", ans[i]);
                if(i) printf(" ");
                else printf("\n");
            }
        }
    }
    return 0;
}

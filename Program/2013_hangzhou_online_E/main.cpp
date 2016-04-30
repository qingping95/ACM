#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 100020
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;

const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const LL mod = 1<<30;
LL n;
struct node{
    LL x, y, z, ans, num;
    void read()
    {
        scanf("%I64d%I64d%I64d", &x, &y, &z);
    }
    bool operator<(const node& o)const
    {
        return x < o.x || (x == o.x && y < o.y) || (x == o.x && y == o.y && z < o.z);
    }
}info[N];
LL tmp[N];
LL stay[N], staz[N];
PII c[N];
LL cmp(LL a, LL b)
{
    return info[a].y < info[b].y;
}
void add(LL x, LL val, LL num)
{
    if(x == 0) return ;
    for(LL i = x; i < n + 10; i += i & -i){
        if(c[i].first == val){
            c[i].second = (c[i].second + num) % mod;
        }else{
            c[i] = max(c[i], PII(val, num));
        }
    }
}
void set0(LL x)
{
    if(x == 0) return;
    for(LL i = x; i < n + 10; i += i & -i) c[i] = PII(0, 0);
}
PII getsum(LL x)
{
    PII res = PII(0, 0);
    for(LL i = x; i; i -= i & -i)
    {
        if(res.first == c[i].first){
            res.second = (res.second + c[i].second)%mod;
        }else
            res = max(res, c[i]);
    }
    return res;
}
void divide(LL l, LL r)
{
    if(l + 1 >= r) return ;
    LL mid = l + r >> 1;
    divide(l, mid);
    for(LL i = l; i < r; i++) tmp[i] = i;
    sort(tmp+l, tmp+mid, cmp);
    sort(tmp+mid, tmp+r, cmp);
    LL lid = l;
    for(LL i = mid; i < r; i++)
    {
        while(lid < mid && info[tmp[lid]].y <= info[tmp[i]].y)
            add(info[tmp[lid]].z, info[tmp[lid]].ans, info[tmp[lid]].num), lid++;
        PII pp = getsum(info[tmp[i]].z);
        if(info[tmp[i]].ans == pp.first+1 && pp.first){
            info[tmp[i]].num = (pp.second + info[tmp[i]].num) % mod;
        } else if(info[tmp[i]].ans < pp.first + 1){
            info[tmp[i]].ans = pp.first+1;
            info[tmp[i]].num = pp.second;
        }
    }
    for(LL i = l; i < mid; i++)
        set0(info[i].z);
    divide(mid, r);
}
int main()
{
//    Open();
    LL T;scanf("%I64d", &T);
    while(T--)
    {
        scanf("%I64d", &n);
        LL ty = 0, tz = 0;
        for(LL i = 0; i < n; i++)
        {
            info[i].read();
            stay[ty++] = info[i].y;
            staz[tz++] = info[i].z;
            info[i].ans = 1;
            info[i].num = 1;
        }
        sort(stay, stay+ty);
        sort(staz, staz+tz);
        ty = unique(stay, stay+ty) - stay;
        tz = unique(staz, staz+tz) - staz;
        for(LL i = 0; i < n; i++){
            info[i].y = lower_bound(stay, stay+ty, info[i].y) - stay + 1;
            info[i].z = lower_bound(staz, staz+tz, info[i].z) - staz + 1;
        }
        sort(info, info+n);
        divide(0, n);
        LL ans = 0, num = 0;
        for(LL i = 0; i < n; i++)
        {
            if(ans == info[i].ans)
                num = (num + info[i].num) %mod;
            else if(ans < info[i].ans){
                ans = info[i].ans;
                num = info[i].num;
            }
        }
        printf("%I64d %I64d\n", ans, num);
    }
    return 0;
}

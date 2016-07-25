#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <bitset>
#define lson x<<1
#define rson x<<1|1
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
        freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 100110;
PII seg[N];
char p[6], s[N];
int val[N];
int slen, plen;
int t;
void getSeg()
{
    memset(val, 0, sizeof(val));
    slen = strlen(s);
    plen = strlen(p);
    t = 1;
    for(int i = 0; i+plen <= slen; i++)
    {
        bool ocr = true;
        for(int j = 0; j < plen; j++)
        {
            char pp = tolower(p[j]);
            char ss = tolower(s[i+j]);
            if(pp != ss) {ocr = false; break;}
        }
        if(ocr) seg[t++] = PII(i, i+plen-1);
    }
    for(int i = 1; i < t; i++)
    {
        for(int j = seg[i].first, id = 0; j <= seg[i].second; j++, id++)
        {
            if(p[id] != s[j]) val[i] |= (1<<id);
        }
    }
}
struct node{
    int l, r, mi, ma;
    bool flag;
    void updateMIMA()
    {
        int tmp = mi;
        mi = plen - ma;
        ma = plen - tmp;
    }
}lt[N*6];
void push_up(int x)
{
    lt[x].mi = min(lt[lson].mi, lt[rson].mi);
    lt[x].ma = max(lt[lson].ma, lt[rson].ma);
}
void push_down(int x)
{
    if(lt[x].flag)
    {
        lt[lson].flag ^= 1;
        lt[lson].updateMIMA();
        lt[rson].flag ^= 1;
        lt[rson].updateMIMA();
        lt[x].flag = 0;
    }
}
void build(int l, int r, int x)
{
    if(l == r){
        int tmp = __builtin_popcount(val[l]);
        lt[x] = (node){l, r, tmp, tmp, 0};
        return ;
    }
    lt[x].l = l, lt[x].r = r, lt[x].flag = 0;
    build(l, mid, lson);
    build(mid+1, r, rson);
    push_up(x);
}
void updateSeg(int l, int r, int x)
{
    if(l <= lt[x].l && r >= lt[x].r)
    {
        lt[x].updateMIMA();
        lt[x].flag ^= 1;
        return ;
    }
    push_down(x);
    if(r <= mid) updateSeg(l, r, lson);
    else if(l > mid) updateSeg(l, r, rson);
    else updateSeg(l, mid, lson), updateSeg(mid+1, r, rson);
    push_up(x);
}
void update(int idx, int val, int x)
{
    if(idx == lt[x].l && lt[x].r == idx)
    {
        lt[x].ma = lt[x].mi = val;
        return ;
    }
    push_down(x);
    if(idx <= mid) update(idx, val, lson);
    else update(idx, val, rson);
    push_up(x);
}
PII query(int l, int r, int x)
{
    if(l <= lt[x].l && r >= lt[x].r)
    {
        return PII(lt[x].mi, lt[x].ma);
    }
    push_down(x);
    if(r <= mid) return query(l, r, lson);
    else if(l > mid) return query(l, r, rson);
    else{
        PII q1 = query(l, mid, lson);
        PII q2 = query(mid+1, r, rson);
        return PII(min(q1.first, q2.first), max(q1.second, q2.second));
    }
}
int c[N];
void add(int x, int val)
{
    if(x < 1) return ;
    for(int i = x; i; i -= i & -i)
        c[i] += val;
}
int getval(int x)
{
    if(x < 1) return 0;
    int res = 0;
    for(int i = x; i < t+10; i += i & -i)
        res += c[i];
    return res;
}
int main()
{
//    Open();
    int n;
    while(~scanf("%d", &n))
    {
        scanf("%s%s", p, s);
        memset(c, 0, sizeof(c));
        getSeg();

        if(t > 1)build(1, t-1, 1);
        for(int i = 0; i < n; i++)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            if(t == 1){
                printf("-1\n");
                continue;
            }
            l --, r--;
            int tl = l, tr = r;
//            cout<<i<<" -> "<<tl<<", "<<tr<<endl;
            r -= plen-1;
            l = lower_bound(seg+1, seg+t, PII(l, 0)) - seg;
            r = upper_bound(seg+1, seg+t, PII(r, INF)) - seg - 1;
//            cout<<i<<" -> "<<l<<", "<<r<<endl;
            if(l <= r)
                printf("%d\n", query(l, r, 1).second);
            else
                printf("-1\n");

            //flip
            if(l <= r)
            {
                updateSeg(l, r, 1);
                add(r, 1);
                add(l-1, -1);
            }

            int pre = l-1;
            while(pre >= 1 && seg[pre].first <= tl && seg[pre].second >= tl)
            {
                int res = getval(pre);
                if(res & 1){
                    val[pre] ^= (1<<plen)-1;
                }
                add(pre, -res);
                add(pre-1, res);
                for(int j = seg[pre].first, id = 0; j <= seg[pre].second; j++, id++)
                {
                    if(tl <= j && j <= tr)
                    {
                        val[pre] ^= (1<<id);
                    }
                }
                update(pre, __builtin_popcount(val[pre]), 1);
                pre--;
            }
            int suf = r+1;
            while(suf < t && seg[suf].first <= tr && seg[suf].second >= tr)
            {
                if(suf < l) {suf++;continue;}
                int res = getval(suf);
                if(res & 1)
                {
                    val[suf] ^= (1<<plen)-1;
                }
                add(suf, -res);
                add(suf-1, res);
                for(int j = seg[suf].first, id = 0; j <= seg[suf].second; j++, id++)
                {
                    if(tl <= j && j <= tr)
                        val[suf] ^= (1<<id);
                }
                update(suf, __builtin_popcount(val[suf]), 1);
                suf++;
            }
        }
    }
    return 0;
}

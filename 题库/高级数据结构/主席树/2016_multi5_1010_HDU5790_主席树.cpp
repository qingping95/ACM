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
const LL mod = 1125899839733759LL;
const LL base = 9987;
const LL N = 100010;
struct node{
    int val;
    int ls, rs;
    node(int val = 0):val(val){
        ls = rs = -1;
    }
}lt[N*40];//
int tot;//
PII op[N];//
LL sta[N];//
int Tr[N];//
int maidx[N];//
char str[N];//
void push_up(int x)
{
    lt[x].val = lt[lt[x].ls].val + lt[lt[x].rs].val;
}
int build(int l, int r)
{
    int rt = tot++;
    lt[rt] = node(0);
    if(l == r) return rt;
    int mid = l + r >> 1;
    lt[rt].ls = build(l, mid);
    lt[rt].rs = build(mid+1, r);
    return rt;
}
int update(int rt, int idx, int val, int l, int r)
{
    int crt = tot++;
    lt[crt] = lt[rt];
    if(idx == l && idx == r)
    {
        lt[crt].val += val;
        return crt;
    }
    int mid = l + r >> 1;
    if(idx <= mid) lt[crt].ls = update(lt[crt].ls, idx, val, l, mid);
    else lt[crt].rs = update(lt[crt].rs, idx, val, mid+1, r);
    push_up(crt);
    return crt;
}
int query(int rt, int L, int l, int r)
{
    if(L <= l)
    {
        return lt[rt].val;
    }
    int mid = l + r >> 1;
    int res = 0;
    if(L <= mid) res += query(lt[rt].ls, L, l, mid);
    if(L <= r) res += query(lt[rt].rs, L, mid+1, r);
    return res;
}
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
    int n;
    while(~scanf("%d", &n))
    {
        memset(maidx, -1, sizeof(maidx));
        tot = 0;

        int t = 0;
        for(int id = 1; id <= n; id++)
        {
            scanf("%s", str);
            int len = strlen(str);
            LL hs = 0;
            for(int i = 0; i < len; i++)
            {
                hs = (hs * base % mod + str[i])%mod;
                op[t] = PII(hs, id);
                sta[t++] = hs;
            }
        }
        sort(sta, sta+t);
        int ta = unique(sta, sta+t) - sta;
        for(int i = 0; i < t; i++)
            op[i].first = lower_bound(sta, sta+ta, op[i].first) - sta+1;
        Tr[0] = build(1, n);
        ta = 0;
        for(int i = 1; i <= n; i++)
        {
            Tr[i] = Tr[i-1];
            while(ta < t && op[ta].second <= i)
            {
                int hs = op[ta].first, id = op[ta].second;
                ta++;
                if(maidx[hs] != -1)  Tr[i] = update(Tr[i], maidx[hs], -1, 1, n);
                maidx[hs] = id;
                Tr[i] = update(Tr[i], id, 1, 1, n);
            }
        }
        int Q;
        scanf("%d", &Q);
        int Z = 0;;
        while(Q--)
        {
            int l, r;scanf("%d%d", &l, &r);
            l = (Z+l)%n, r = (Z+r)%n;
            l++, r++;
            if(l > r) swap(l, r);
            Z = query(Tr[r], l, 1, n);
            printf("%d\n", Z);
        }
    }
    return 0;
}


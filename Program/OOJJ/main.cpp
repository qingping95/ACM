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
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define PII pair<int,int>
#define MP(x,y) make_pair((x),(y))
#define ll long long
#define ull unsigned ll
#define scan(x) scanf("%d",&(x))
#define scan2(x,y) scanf("%d%d",&(x),&(y))
#define scan3(x,y,z) scanf("%d%d%d",&(x),&(y),&(z))
#define scan4(x,y,z,k) scanf("%d%d%d%d",&(x),&(y),&(z),&(k))
#define Max(a,b) a=max(a,b)
#define Min(a,b) a=min(a,b)
#define fuck(x) cout<<#x<<" "<<x<<endl
const ll MX = 101111;
ll fn[MX], f[MX];
#define lson x<<1
#define rson x<<1|1
struct Node {
    ll l, r,len;
    ll sum, al, laz;///sum should be ll
};
struct Seg{
    Node  node[MX * 6];
    inline void pushup(ll x) {
        node[x].sum = node[lson].sum + node[rson].sum;
        if(node[lson].al == node[rson].al && node[lson].al != 0) node[x].al = node[lson].al;
        else node[x].al = 0;
    }
    inline void pushdown(ll x) {
        if(node[x].al){
            node[lson].al = node[rson].al = node[x].al;
            node[lson].sum = node[lson].al * node[lson].len;
            node[rson].sum = node[rson].al * node[rson].len;
            node[lson].laz = node[rson].laz = node[x].laz = 0;
            node[x].al=0;
        }else if (node[x].laz) {
            ll lz = node[x].laz;
            node[lson].laz += lz;
            node[lson].sum += lz * node[lson].len;
            node[rson].laz += lz;
            node[rson].sum += lz * node[rson].len;
            if(node[lson].al) node[lson].al += lz;
            if(node[rson].al) node[rson].al += lz;
            node[x].laz = 0;
        }
    }

    void build(ll l, ll r, ll x) {
        node[x].l = l; node[x].r = r; node[x].al = 0; node[x].laz = 0;
        node[x].len = r - l + 1;
        if (l == r) {
            node[x].al=f[l];
            node[x].sum = f[l];
            return;
        }
        ll mid = (l + r) / 2;
        build(l, mid, lson);
        build(mid + 1, r, rson);
        pushup(x);
    }

    void update1(ll l, ll r, ll val, ll x) {
        if (node[x].l >= l && node[x].r <= r) {
            node[x].laz += val;
            node[x].sum += 1LL * node[x].len * val;
            if(node[x].al) node[x].al += val;
            return;
        }
        ll mid = (node[x].l + node[x].r) / 2;
        pushdown(x);
        //if(node[x].al) node[x].al = 0;
        if (l <= mid) update1(l, r,val, lson);
        if (r > mid) update1(l, r,val, rson);
        pushup(x);
    }

    void update2(ll l, ll r, ll x) {
        if (node[x].l >= l && node[x].r <= r && node[x].al) {
            ll val = 0;
            if(node[x].al < MX) val = fn[node[x].al];
            else val = sqrt(node[x].al);
            node[x].sum = 1LL * val * node[x].len;
            node[x].al = val;
            return;
        }
        //if(node[x].al > 1 ) node[x].al=0;
        ll mid = (node[x].l + node[x].r) / 2;
        pushdown(x);
        //node[x].al = 0;
        if (l <= mid) update2(l, r, lson);
        if (r > mid) update2(l, r, rson);
        pushup(x);
    }

    ll query(ll l, ll r, ll x) {
        if (node[x].l >= l && node[x].r <= r) {
            return node[x].sum;
        }
        ll mid = (node[x].l + node[x].r) / 2;
        pushdown(x);
        ll ans = 0;///mind!!ll
        if (l <= mid) ans += query(l, r, lson);
        if (r > mid) ans += query(l, r, rson);
        pushup(x);
        return ans;
    }
}seg;
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
//    freopen("F:/in.txt","r",stdin);
    frd.init();
    for(ll i=0;i<MX;i++) fn[i] = sqrt(i);
    ll T;
    T = frd.getint();
    //cout<<T<<endl;
    //scanf("%d",&T);
    //read(T);
    while(T--){
        ll n,m;
        //scanf("%d%d",&n,&m);
        //read(n);read(m);
        n = frd.getint();
        m = frd.getint();
        for(ll i=1;i<=n;i++){
            //scanf("%d",&f[i]);
            //read(f[i]);
            f[i] = frd.getint();
        }
        seg.build(1,n,1);
        for(ll i=1;i<=m;i++){
            ll tp,l,r;
            //scanf("%d%d%d",&tp,&l,&r);
            //read(tp); read(l); read(r);
            tp = frd.getint();l = frd.getint();r = frd.getint();
            if(tp == 1){
                ll x;
                //scanf("%d",&x);
                //read(x);
                x = frd.getint();
                if(x == 0) continue;
                seg.update1(l,r,x,1);
            }else if(tp == 2){
                seg.update2(l,r,1);
            }else{
                ll ans = seg.query(l,r,1);///mind ll
                printf("%I64d\n", ans);
            }
        }
    }
    return 0;
}

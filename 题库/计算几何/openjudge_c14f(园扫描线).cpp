#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
//#include <unordered_map>
#define N 200020
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
#define ID(x, y) ((x)*m+(y))
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f3f3f3f3fLL;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}

#define D(x) ((x)*(x))
const double eps = 1e-8;
LL n;
struct Cir{
    LL x, y, r, ty, id;
    void read()
    {
        scanf("%lld%lld%lld", &x, &y, &r);
    }
    Cir(){}
    Cir(LL _x, LL _y, LL _r, LL _id, LL _ty = 0){
        x = _x, y = _y, r = _r, id = _id, ty = _ty;
    }
    bool operator<(const Cir& o)const{
        return x < o.x;
    }
}c[N], ac[N];
LL curx;
double delty, deltoy, cy, oy;
struct info{
    LL id, ty;
    info(){}
    info(LL _id, LL _ty){
        id = _id, ty = _ty;
    }
    double y()const{
        if(id == -1) return (ty == 1 ? INF : -INF);
        delty = sqrt((double)D(c[id].r) - D(curx - c[id].x));
        if(ty == 1) return c[id].y + delty;
        return c[id].y - delty;
    }
    bool operator<(const info& o)const{
        cy = y(), oy = o.y();
        if(abs(cy - oy) < eps) return ty < o.ty;
        return y() < o.y();
    }
};
LL ans[N];
multimap<info, LL> mp;
multimap<info, LL>::iterator it, preit, nxtit, itr[N][2];
LL nxtid, preid;
bool CinsC(LL a, LL b)
{
    double d = sqrt((double)D(c[a].x - c[b].x) + D(c[a].y - c[b].y));
    if(c[a].r + c[b].r > d + eps) return true;
    else return false;
}
void ins(LL y, LL id){
    it = mp.insert(make_pair(info(id, 1), 0));
    //it = mp.find(info(id, 1));
    nxtit = preit = it;
    LL res = 0;
    nxtit++, preit--;
    nxtid = (nxtit -> first).id;
    if(nxtid == -1 || CinsC(id, nxtid)) res = max(res, (nxtit -> second)+1);
    else res = max(res, nxtit -> second);
    preid = (preit -> first).id;
    if(preid == -1 || CinsC(id, preid)) res = max(res, (preit -> second)+1);
    else res = max(res, preit -> second);
    it -> second = res;
    itr[id][0] = it;
    itr[id][1] = mp.insert(make_pair(info(id, -1), res));
    ans[res]++;
}
int main()
{
//    Open();
    LL T;scanf("%lld", &T);
    while(T--)
    {
        scanf("%lld", &n);
        for(LL i = 0; i < n; i++)
        {
            c[i].read();
            ac[i*2] = Cir(c[i].x - c[i].r, c[i].y, c[i].r, i, 1);
            ac[i*2 + 1] = Cir(c[i].x + c[i].r, c[i].y, c[i].r, i, -1);
        }
        memset(ans, 0, sizeof(ans));
        sort(ac, ac+2*n);
        mp.clear();
        mp.insert(make_pair(info(-1, 1), 0));
        mp.insert(make_pair(info(-1, -1), 0));
        for(LL i = 0; i < 2 * n; i++)
        {
            curx = ac[i].x;
            if(ac[i].ty == 1){
                ins(ac[i].y, ac[i].id);
            }else{
                mp.erase(itr[ac[i].id][0]);
                mp.erase(itr[ac[i].id][1]);
            }
        }
        for(LL i = 1; ans[i]; i++)
        {
            printf("%lld\n", ans[i]);
        }
    }
    return 0;
}


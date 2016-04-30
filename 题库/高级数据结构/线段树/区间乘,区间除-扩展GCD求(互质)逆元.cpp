/*
* 题意：先给出n个数，然后有区间乘和区间除的操作。要求对于每个询问操作输出当前区间的乘积mod M
* 
* 做法：这里由于M是给出来的数，并不一定是质数，所以不能直接求逆，但是对于与M互质的a来说，a却是
* 		有逆元存在的，所以这里线段树每个节点维护M的所有质因子表(存储指数数目)，每次修改先将操作数分解
*		质因数，对于在M的质因子表中的质因子，则直接在指数上进行加减，而其余的就直接对M求逆即可。
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>
#include <assert.h>
#include <cmath>
#include <time.h>
#define N 10010
#define lson x<<1
#define rson x<<1|1
#define mid ((lt[x].l+lt[x].r)/2)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
void gcd(int a, int b, int& d, int& x, int& y){
    if(!b){d = a; x = 1; y = 0;}
    else {gcd(b, a%b, d, y, x); y -= x * (a / b);}
}
int inv(int a, int n)
{
    int d, x, y;
    gcd(a, n, d, x, y);
    return d == 1 ? (x + n) % n : -1;
}
int pow_mod(int x, int k, int mod)
{
    int res = 1;
    while(k)
    {
        if(k & 1) res = (LL)res * x % mod;
        x = (LL)x * x % mod;
        k >>= 1;
    }
    return res;
}
int n, M;//
int Mplist[111];//
int b[N];//
int apcnt[N][20];//
int addpro;//
vector<PII> addp;//
map<int, int> pid;//
bool pvis[100010];//
int pri[100010];//
int prin;//
int mcnt = 0;//
void getpri(int UP){
    prin = 0;
    memset(pvis, 0, sizeof(pvis));
    for(int i = 2; i < UP; i++) {
        if(pvis[i] == 0) pri[prin++] = i;
        for(int j = 0; j < prin && (LL)pri[j]*i < UP; j++) {
            pvis[pri[j]*i] = 1;
            if(i % pri[j] == 0) break;
        }
    }
}
struct node{
    int l, r, pro;
    int pcnt[20];
    int lazy[20];
    int lazypro;
    bool la;
    bool exist0;
    node(){}
    node(int _l, int _r)
    {
        l = _l, r = _r;
        pro = 1;
        la = false;
        lazypro = 1;
        exist0 = false;
        memset(pcnt, 0, sizeof(pcnt));
        memset(lazy, 0, sizeof(lazy));
    }
    void set0()
    {
        pro = lazypro = la = 0;
        exist0 = 1;
    }
    int len()
    {
        return r - l + 1;
    }
}lt[N * 6];
void push_up(int x)
{
    for(int i = 0; i < addp.size(); i++){
        int id = addp[i].first;
        lt[x].pcnt[id] = lt[lson].pcnt[id] + lt[rson].pcnt[id];
    }
    lt[x].pro = (LL)lt[lson].pro * lt[rson].pro % M;
    lt[x].exist0 = lt[lson].exist0 || lt[rson].exist0;
    if(lt[lson].lazypro == 0 && lt[rson].lazypro == 0) lt[x].lazypro = 0;
}
void push_down(int x)
{
    if(lt[x].lazypro == 0){
        lt[lson].set0();
        lt[rson].set0();
        return ;
    }
    if(lt[x].la){
        lt[x].la = false;
        for(int i = 0; i < mcnt; i++) {
            if(lt[x].lazy[i] == 0) continue;
            lt[lson].pcnt[i] += lt[x].lazy[i] * lt[lson].len();
            lt[rson].pcnt[i] += lt[x].lazy[i] * lt[rson].len();
            lt[lson].lazy[i] += lt[x].lazy[i];
            lt[rson].lazy[i] += lt[x].lazy[i];
            lt[x].lazy[i] = 0;
        }
        lt[lson].la = true;
        lt[rson].la = true;
    }
    if(lt[x].lazypro > 1){
        lt[lson].pro = (LL)lt[lson].pro * pow_mod(lt[x].lazypro, lt[lson].len(), M) % M;
        lt[rson].pro = (LL)lt[rson].pro * pow_mod(lt[x].lazypro, lt[rson].len(), M) % M;
        lt[lson].lazypro = (LL)lt[lson].lazypro * lt[x].lazypro % M;
        lt[rson].lazypro = (LL)lt[rson].lazypro * lt[x].lazypro % M;
        lt[x].lazypro = 1;
    }
}
void build(int l, int r, int x)
{
    lt[x] = node(l, r);
    if(l == r)return ;
    build(l, mid, lson);
    build(mid+1, r, rson);
    push_up(x);
}
void update(int l, int r, int x)
{
    if(lt[x].lazypro == 0) return ;
    if(lt[x].l >= l && lt[x].r <= r){
        if(addpro == 0){
            lt[x].set0();
            return ;
        }
        lt[x].la = true;
        for(int i = 0; i < addp.size(); i++)
        {
            lt[x].lazy[addp[i].first] += addp[i].second;
            lt[x].pcnt[addp[i].first] += addp[i].second * lt[x].len();
        }
        lt[x].pro = (LL)lt[x].pro * pow_mod(addpro, lt[x].len(), M) % M;
        lt[x].lazypro = (LL)lt[x].lazypro * addpro % M;
        return ;
    }
    push_down(x);
    if(r <= mid) update(l, r, lson);
    else if(l > mid) update(l, r, rson);
    else update(l, mid, lson), update(mid+1, r, rson);
    push_up(x);
}
int query(int l, int r, int x)
{
    if(lt[x].lazypro == 0) return 0;
    if(lt[x].l >= l && lt[x].r <= r)
    {
        if(lt[x].exist0) return 0;
        int res = lt[x].pro;
        for(int i = 0; i < mcnt; i++)
        {
            res = (LL)res * pow_mod(Mplist[i], lt[x].pcnt[i], M) % M;
        }
        return res % M;
    }
    push_down(x);
    if(r <= mid) return query(l, r, lson);
    else if(l > mid) return query(l, r, rson);
    else return (LL)query(l, mid, lson) * query(mid+1, r, rson) % M;
}
void getUpArg(int val, bool isMul)
{
    if(val == 0){
        addpro = 0;
        return ;
    }
    int res = 0;
    for(int i = 0; i < mcnt && Mplist[i] <= val; i++){
        while(val % Mplist[i] == 0){
            res++;
            val /= Mplist[i];
        }
        if(res){
            if(!isMul) res = -res;
            addp.push_back(PII(i, res));
            res = 0;
        }
    }
    addpro = val;
    if(!isMul) addpro = inv(addpro, M);
}
int main()
{
//    Open();
    getpri(100010);
    int T ;scanf("%d", &T);
    int cas = 1;
    while(T--)
    {
        pid.clear();
        memset(apcnt, 0, sizeof(apcnt));
        mcnt = 0;
        scanf("%d%d", &n, &M);
        int tmpm = M;
        for(int i = 0; i < prin && pri[i] <= tmpm; i++){
            assert(tmpm != 0);
            if(tmpm % pri[i] == 0) Mplist[mcnt] = pri[i], pid[pri[i]] = mcnt++;
            while(tmpm % pri[i] == 0) tmpm /= pri[i];
        }
        if(tmpm > 1){
            Mplist[mcnt] = tmpm;
            pid[tmpm] = mcnt++;
        }
        build(1, n, 1);
        assert(mcnt < 20);
        for(int i = 1; i <= n; i++)
        {
            int tmp;scanf("%d", &tmp);
            getUpArg(tmp, 1);
            update(i, i, 1);
            addp.clear();
        }
        int q;scanf("%d" ,&q);
        printf("Case #%d:\n", cas++);
        while(q--)
        {
            char op[3];
            int L, R;
            scanf("%s%d%d", op, &L, &R);
            if(op[0] == 'M'){
                int x;scanf("%d", &x);
                getUpArg(x, 1);
                update(L, R, 1);
                addp.clear();
            }else if(op[0] == 'D') {
                int x ;scanf("%d", &x);
                getUpArg(x, 0);
                update(L, R, 1);
                addp.clear();
            }else{
                printf("%d\n", query(L, R, 1));
            }
        }
    }
    return 0;
}

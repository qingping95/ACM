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
typedef long long LL;
int rf[9], rb[9], ru[9], rd[9], rl[9], rr[9];

int f[9], b[9], u[9], d[9], l[9], r[9], tmp[9], ch;
//int ddidx;
int ror(int a[9]){
    for(int i=0;i<9;i++) tmp[i] = a[i];
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) a[i*3 + j] = tmp[3*(2-j) + i];
}
//L面顺时针旋转90度
void L(int cnt=1){
    for(;cnt>0;cnt--){
        ror(l);
        ch=u[0], u[0]=b[8], b[8] = d[0], d[0]=f[0], f[0] = ch;
        ch=u[3], u[3]=b[5], b[5] = d[3], d[3]=f[3], f[3] = ch;
        ch=u[6], u[6]=b[2], b[2] = d[6], d[6]=f[6], f[6] = ch;
    }
}
//R面顺时针旋转90度，后面的一样
void R(int cnt=1){
    for(;cnt>0;cnt--){
        ror(r);
        ch=u[2], u[2]=f[2], f[2] = d[2], d[2]=b[6], b[6] = ch;
        ch=u[5], u[5]=f[5], f[5] = d[5], d[5]=b[3], b[3] = ch;
        ch=u[8], u[8]=f[8], f[8] = d[8], d[8]=b[0], b[0] = ch;
    }
}
void U(int cnt=1){
    for(;cnt>0;cnt--){
        ror(u);
        ch=f[0], f[0]=r[0], r[0] = b[0], b[0]=l[0], l[0] = ch;
        ch=f[1], f[1]=r[1], r[1] = b[1], b[1]=l[1], l[1] = ch;
        ch=f[2], f[2]=r[2], r[2] = b[2], b[2]=l[2], l[2] = ch;
    }
}
void D(int cnt=1){
    for(;cnt>0;cnt--){
        ror(d);
        ch=f[6], f[6]=l[6], l[6] = b[6], b[6]=r[6], r[6] = ch;
        ch=f[7], f[7]=l[7], l[7] = b[7], b[7]=r[7], r[7] = ch;
        ch=f[8], f[8]=l[8], l[8] = b[8], b[8]=r[8], r[8] = ch;
    }
}
void F(int cnt=1){
    for(;cnt>0;cnt--){
        ror(f);
        ch=u[6], u[6]=l[8], l[8] = d[2], d[2]=r[0], r[0] = ch;
        ch=u[7], u[7]=l[5], l[5] = d[1], d[1]=r[3], r[3] = ch;
        ch=u[8], u[8]=l[2], l[2] = d[0], d[0]=r[6], r[6] = ch;
    }
}
void B(int cnt=1){
    for(;cnt>0;cnt--){
        ror(b);
        ch=u[0], u[0]=r[2], r[2] = d[8], d[8]=l[6], l[6] = ch;
        ch=u[1], u[1]=r[5], r[5] = d[7], d[7]=l[3], l[3] = ch;
        ch=u[2], u[2]=r[8], r[8] = d[6], d[6]=l[0], l[0] = ch;
    }
}
//顺时针旋转某个面
void shun(int x[])
{
    int tmp = x[0];
    x[0] = x[6];
    x[6] = x[8];
    x[8] = x[2];
    x[2] = tmp;
    tmp = x[1];
    x[1] = x[3];
    x[3] = x[7];
    x[7] = x[5];
    x[5] = tmp;
}
//逆时针旋转某个面
void lis(int x[])
{
    int tmp = x[0];
    x[0] = x[2];
    x[2] = x[8];
    x[8] = x[6];
    x[6] = tmp;
    tmp = x[1];
    x[1] = x[5];
    x[5] = x[7];
    x[7] = x[3];
    x[3] = tmp;
}
//将整个魔方绕Y轴顺时针旋转90度（朝Y轴正方向）
void RY()
{
    int tmp[9];
    memcpy(tmp, u, sizeof(int)*9);
    shun(l); for(int i = 0; i < 9; i++) u[i] = l[i];
    shun(d); for(int i = 0; i < 9; i++) l[i] = d[i];
    shun(r); for(int i = 0; i < 9; i++) d[i] = r[i];
    shun(tmp); for(int i=0; i < 9; i++) r[i] = tmp[i];
    shun(f);
    lis(b);
}
//将整个魔方绕Z轴顺时针旋转90度（朝Z轴负方向）
void RZ()
{
    int tmp[9];
    memcpy(tmp, b, sizeof(int)*9);
    for(int i = 0; i < 9; i++) b[i] = l[i];
    for(int i = 0; i < 9; i++) l[i] = f[i];
    for(int i = 0; i < 9; i++) f[i] = r[i];
    for(int i = 0; i < 9; i++) r[i] = tmp[i];
    shun(u);
    lis(d);
}
//将整个魔方绕X轴顺时针旋转90度（朝Z轴负方向）
void RX()
{
    int tmp[9];
    memcpy(tmp, u, sizeof(int)*9);
    for(int i = 0; i < 9; i++) u[i] = f[i];
    for(int i = 0; i < 9; i++) f[i] = d[i];
    for(int i = 0; i < 9; i++) d[i] = b[8-i];
    for(int i = 0; i < 9; i++) b[i] = tmp[8-i];
    shun(r);
    lis(l);
}
//给每个格子编号
void init(){
    ru[0] = 0, ru[8] = 8;
    rl[0] = 9, rl[8] = 17;
    rf[0] = 18, rf[8] = 26;
    rr[0] = 27, rr[8] = 35;
    rb[0] = 36, rb[8] = 44;
    rd[0] = 45, rf[8] = 53;
    for(int i = 1; i <= 8; i++) ru[i] = ru[i-1]+1;
    for(int i = 1; i <= 8; i++) rl[i] = rl[i-1]+1;
    for(int i = 1; i <= 8; i++) rf[i] = rf[i-1]+1;
    for(int i = 1; i <= 8; i++) rr[i] = rr[i-1]+1;
    for(int i = 1; i <= 8; i++) rb[i] = rb[i-1]+1;
    for(int i = 1; i <= 8; i++) rd[i] = rd[i-1]+1;

    for(int i = 0; i <= 8; i++) f[i] = rf[i];
    for(int i = 0; i <= 8; i++) u[i] = ru[i];
    for(int i = 0; i <= 8; i++) d[i] = rd[i];
    for(int i = 0; i <= 8; i++) r[i] = rr[i];
    for(int i = 0; i <= 8; i++) l[i] = rl[i];
    for(int i = 0; i <= 8; i++) b[i] = rb[i];
}
//24种角度查看魔方的映射
//虽然存储了32种映射，应为有冗余，只有24种不同的映射
int rflct[66][35];
LL hs(int qqq[], int tl)
{
    LL res = 0;
    sort(qqq, qqq+tl);
    for(int i = 0; i < tl; i++)
        res = res * 54 + qqq[i];
    return res;
}
int t;
set<LL> st;
int sta[66];
int qqq[66];
int ans;
void dfs(){
    int tl=0;
    for(int i = 0; i <= 8; i++) if(f[i] == -1) qqq[tl++] = rf[i];
    for(int i = 0; i <= 8; i++) if(u[i] == -1) qqq[tl++] = ru[i];
    for(int i = 0; i <= 8; i++) if(d[i] == -1) qqq[tl++] = rd[i];
    for(int i = 0; i <= 8; i++) if(r[i] == -1) qqq[tl++] = rr[i];
    for(int i = 0; i <= 8; i++) if(l[i] == -1) qqq[tl++] = rl[i];
    for(int i = 0; i <= 8; i++) if(b[i] == -1) qqq[tl++] = rb[i];

    bool flag = true;
    for(int i = 0; i < t; i++)
    {
        for(int j = 0; j < tl; j++)
            sta[j] = rflct[qqq[j]][i];
        LL res = hs(sta, tl);
        if(flag && st.find(res) != st.end()) return;
        flag = false;
        st.insert(res);
    }
    ans++;
    L();
    dfs();
    L(3);

    R();
    dfs();
    R(3);

    U();
    dfs();
    U(3);

    D();
    dfs();
    D(3);

    F();
    dfs();
    F(3);

    B();
    dfs();
    B(3);
}
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
//    freopen("/home/qingping/out.txt","w",stdout);
    init();
    t = 0;
    for(int i = 0; i < 4; i++)
    {
        RX();
        for(int j = 0; j < 4; j++)
        {
            RY();
            for(int i = 0; i <= 8; i++) rflct[rf[i]][t] = f[i];
            for(int i = 0; i <= 8; i++) rflct[ru[i]][t] = u[i];
            for(int i = 0; i <= 8; i++) rflct[rd[i]][t] = d[i];
            for(int i = 0; i <= 8; i++) rflct[rr[i]][t] = r[i];
            for(int i = 0; i <= 8; i++) rflct[rl[i]][t] = l[i];
            for(int i = 0; i <= 8; i++) rflct[rb[i]][t] = b[i];
            t++;
        }
    }
    for(int i = 0; i < 4; i++)
    {
        RZ();
        for(int j = 0; j < 4; j++)
        {
            RY();
            for(int i = 0; i <= 8; i++) rflct[rf[i]][t] = f[i];
            for(int i = 0; i <= 8; i++) rflct[ru[i]][t] = u[i];
            for(int i = 0; i <= 8; i++) rflct[rd[i]][t] = d[i];
            for(int i = 0; i <= 8; i++) rflct[rr[i]][t] = r[i];
            for(int i = 0; i <= 8; i++) rflct[rl[i]][t] = l[i];
            for(int i = 0; i <= 8; i++) rflct[rb[i]][t] = b[i];
            t++;
        }
    }
    int T;scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        init();
        printf("Case #%d: ", cas);
        int n;scanf("%d",&n);
        for(int i=0;i<n;i++){
            int x;
            scanf("%d",&x);
            for(int i = 0; i <= 8; i++) if(rf[i] == x) f[i] = -1;
            for(int i = 0; i <= 8; i++) if(ru[i] == x) u[i] = -1;
            for(int i = 0; i <= 8; i++) if(rd[i] == x) d[i] = -1;
            for(int i = 0; i <= 8; i++) if(rr[i] == x) r[i] = -1;
            for(int i = 0; i <= 8; i++) if(rl[i] == x) l[i] = -1;
            for(int i = 0; i <= 8; i++) if(rb[i] == x) b[i] = -1;
        }
        st.clear();
        ans = 0;
        dfs();
//        int sz = st.size();
        printf("%d\n",ans);
    }
    return 0;
}


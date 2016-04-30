

//树状数组
#define N 100001
int n;
int c[N];// 每个C数组代表v[i-lowbit(i)+1]到v[i]之间的和
void add(int i,int x)
{
    while(i<=n)
    {
        c[i]+=x;
        c[i]%=mod;
        i+= i & -i;
    }
}
int getsum(int i)
{
    int cnt=0;
    while(i>0)
    {
        cnt+=c[i];
        cnt%=mod;
        i-=i & -i;
    }
    return cnt%mod;
}
int getK(int K)  //已知前n项和为K，返回n值！
{  
    int ans = 0,cnt=0;  
    for(int i=18;i>=0;i--)//i>=0  
    {  
        ans+=(1<<i);  
        if(ans>=N||cnt+c[ans]>=K)ans-=(1<<i);  
        else cnt+=c[ans];  
    }  
    return ans+1;  
}  
//树状数组


//求前缀最大, 更新值只能增大。
int c[N];
void update(int x, int val)
{
    if(x == 0) return ;
    for(int i=x;i<=N;i+=i&-i) c[i] = max(c[i], val);
}
int getmax(int x)
{
    int rnt = -INF;
    for(int i=x;i>0;i-=i&-i) rnt = max(rnt, c[i]);
    return rnt;
}
//求前缀最大


//二维树状数组
int Lowbit(int x)  
{  
    return x & (-x);  
}  
void Updata(int x,int y,int a)  
{  
    int i,k;  
    for(i=x; i<=n; i+=Lowbit(i))  
        for(k=y; k<=n; k+=Lowbit(k))  
           c[i][k]+=a;                 
}  
int Getsum(int x,int y)  
{  
    int i,k,sum = 0;  
    for(i=x; i>0; i-=Lowbit(i))  
        for(k=y; k>0; k-=Lowbit(k))  
            sum += c[i][k];  
    return sum;  
}
//二维树状数组

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
#define Lowbit(x) ((x)&(-x))
/*
    index from 1,like 1,2,3,4,5,,,,
    array c is the 2-dimensional BIT array
*/
int c[4][4];
int m[4][4];
int n=3;
void add(int x, int y,int delta){
    int i=y;
    while(x<=n){
        y=i;
        while(y<=n){
            c[x][y]+=delta;
            y+=Lowbit(y);
        }
        x+=Lowbit(x);
    }
}
int Sum(int x, int y){
    int i=y, sum=0;
    while(x>0){
        y=i;
        while(y>0){
            sum+=c[x][y];
            y-=Lowbit(y);
        }
        x-=Lowbit(x);
    }
    return sum;
}
int main() {
    //freopen("G:/in.txt","r",stdin);
    /* the input is
        1 2 2
        2 1 3
        3 4 5
    */
    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++){
            scanf("%d",&m[i][j]);
            add(i,j,m[i][j]);
        }
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++){
            cout<<Sum(i,j)<<' ';
        }
        cout<<endl;
    }
    /* the output should be
        1 3 5
        3 6 11
        6 13 23
    */
    return 0;
}



//区间修改，点查询
long long c[N];  
long long sum[N];  
long long n;  
long long getnum(long long x)  
{  
    long long rnt=0;  
    for(long long i=x;i<=n;i+=(i&(-i)))  
    {  
        rnt+=c[i];  
    }  
    return rnt;  
}  
void add(long long i,long long a)  
{  
    while(i>=1)  
    {  
        c[i]+=a;  
        i-=(i&(-i));  
    }  
}  


//区间修改，区间查询, cnt 相当于cas清空用
LL query(LL a[][2], int x)  
{  
    LL res = 0;  
    for(; x > 0; x -= (x&(-x)))  
    {  
        if(a[x][0] == cnt) res += a[x][1];  
    }  
    return res;  
}  
LL query(int l, int r)  
{  
    return query(x1, l)*(r-l+1)+ (r+1)*(query(x1, r)-query(x1, l)) - (query(x2, r)-query(x2, l));  
}  
void add(LL a[][2], int x, LL c)  
{  
    for(; x <= n; x += ((-x)&x))  
    {  
        if(a[x][0] == cnt) a[x][1] += c;  
        else a[x][0] = cnt, a[x][1] = c;  
    }  
}  
void add(int l, int r, int c)  
{  
    add(x1, l, c);  
    add(x2, l, (LL)l*c);  
    add(x1, r+1, -c);  
    add(x2, r+1, (LL)(r+1)*(-c));  
}  
//区间修改，区间查询
//推导: http://www.cnblogs.com/lazycal/archive/2013/08/05/3239304.html



//二维区间查询-区间修改
const int N = 2210;
#define lowbit(x) ((x)&(-(x)))
PII a[N][N],b[N][N],c[N][N],d[N][N];
int X, Y;
inline int gs(PII a[N][N],int x,int y, int id){
    int s=0,t;
    for(; x; x-=lowbit(x))
        for(t=y; t; t-=lowbit(t)){
            if(a[x][t].second != id) a[x][t].first = 0;
            a[x][t].second = id;
            s+=a[x][t].first;
        }
    return s;
}
inline void gp(PII a[N][N],int x,int y,int w, int id)
{
    int t;
    for(; x<X+5 && x; x+=lowbit(x))
        for(t=y; t<Y+5 && t; t+=lowbit(t)){
            if(a[x][t].second != id) a[x][t].first = 0;
            a[x][t].second = id;
            a[x][t].first+=w;
        }
}
inline int sum(int x,int y, int id)
{
    return (x+1)*(y+1)*gs(a,x,y,id)-(y+1)*gs(b,x,y,id)-(x+1)*gs(c,x,y,id)+gs(d,x,y,id);
}
inline int sum(int x1, int y1, int x2, int y2, int id)
{
    if(x1 > x2 || y1 > y2) return 0;
    return sum(x2, y2, id) - sum(x1-1, y2, id) - sum(x2, y1-1, id) + sum(x1-1, y1-1, id);
}
inline void update(int x1,int y1,int x2,int y2,int w, int id)
{
    if(x1 > x2 || y1 > y2) return ;
    gp(a,x1,y1,w,id);
    gp(a,x2+1,y1,-w,id);
    gp(a,x1,y2+1,-w,id);
    gp(a,x2+1,y2+1,w,id);
    gp(b,x1,y1,w*x1,id);
    gp(b,x2+1,y1,-w*(x2+1),id);
    gp(b,x1,y2+1,-w*x1,id);
    gp(b,x2+1,y2+1,w*(x2+1),id);
    gp(c,x1,y1,w*y1,id);
    gp(c,x2+1,y1,-w*y1,id);
    gp(c,x1,y2+1,-w*(y2+1),id);
    gp(c,x2+1,y2+1,w*(y2+1),id);
    gp(d,x1,y1,w*x1*y1,id);
    gp(d,x2+1,y1,-w*(x2+1)*y1,id);
    gp(d,x1,y2+1,-w*x1*(y2+1),id);
    gp(d,x2+1,y2+1,w*(x2+1)*(y2+1),id);
}


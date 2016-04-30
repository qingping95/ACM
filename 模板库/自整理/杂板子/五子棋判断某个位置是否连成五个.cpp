#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 100010
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
#define ID(x, y) ((x)*m+(y))
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
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
int g[22][22];
int n = 15, m = 15;
bool judge(int play , int xp, int yp){
    int n0=0 , n1=0 ,n2=0,n3=0,n4=0,n5=0,n6=0,n7=0;
    for(int x=xp , y=yp+1 ; CHECK(x,y) && g[x][y]==play ; n0++ , y++);
    for(int x=xp+1 , y=yp+1 ; CHECK(x,y) && g[x][y]==play ; n1++ ,x++, y++);
    for(int x=xp+1 , y=yp ; CHECK(x,y) && g[x][y]==play ; n2++ , x++);
    for(int x=xp+1 , y=yp-1 ; CHECK(x,y) && g[x][y]==play ; n3++ ,x++, y--);
    for(int x=xp , y=yp-1 ; CHECK(x,y) && g[x][y]==play ; n4++ , y--);
    for(int x=xp-1 , y=yp-1 ; CHECK(x,y) && g[x][y]==play ; n5++ ,x--, y--);
    for(int x=xp-1 , y=yp ; CHECK(x,y) && g[x][y]==play ; n6++ , x--);
    for(int x=xp-1 , y=yp+1 ; CHECK(x,y) && g[x][y]==play ; n7++ , x--,y++);
    int a0 = n0+n4+1 , a1 = n1+n5+1 , a2=n2+n6+1, a3=n3+n7+1;
    return a0>=5 || a1>=5 || a2>=5 || a3>=5;
}
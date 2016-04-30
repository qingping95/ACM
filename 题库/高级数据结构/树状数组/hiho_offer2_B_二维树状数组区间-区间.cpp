#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<double,int> PDI;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
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

int stax[N], stay[N];

int tailx, taily;
struct rec{
    int x1, y1, x2, y2;
    void update()
    {
        x1 = lower_bound(stax, stax+tailx, x1) - stax + 1;
        x2 = lower_bound(stax, stax+tailx, x2) - stax + 1;
        y1 = lower_bound(stay, stay+taily, y1) - stay + 1;
        y2 = lower_bound(stay, stay+taily, y2) - stay + 1;
    }
}r[N];
int main()
{
    //Open();
    int T;
    T = 1;
    while(T--)
    {
        memset(c, 0, sizeof(c));
        int W, H;
        int n;
        scanf("%d%d%d", &W, &H, &n);
//        cout<<n<<endl;
        //X = W, Y = H;
        tailx = taily = 0;
        for(int i = 0; i < n; i++)
        {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            if(x1 > x2) swap(x1, x2);
            if(y1 > y2) swap(y1, y2);
            r[i] = (rec){x1, y1, x2, y2};
            stax[tailx++] = x1;
            stax[tailx++] = x2;
            stay[taily++] = y1;
            stay[taily++] = y2;
        }
        sort(stax, stax+tailx);
        tailx = unique(stax, stax+tailx) - stax;
        X = tailx;
        sort(stay, stay+taily);
        taily = unique(stay, stay+taily) - stay;
        Y = taily;
        for(int i = 0; i < n; i++) r[i].update();
        int ans = 0, idx = -1;
        for(int i = n-1; i >= 0; i--)
        {
            int id = i;
            bool c1 = false, c2 = false, c3 =false, c4 = false;
            for(int j = i+1; j < n; j++)
            {
                if(c1 && c2 && c3 && c4) break;
                if(!c1){
                    int x = r[i].x1, y = r[i].y1;
                    if(r[j].x1 < x && x < r[j].x2 && r[j].y1 < y && y < r[j].y2) c1 = true;
                }
                if(!c2){
                    int x = r[i].x2, y = r[i].y1;
                    if(r[j].x1 < x && x < r[j].x2 && r[j].y1 < y && y < r[j].y2) c2 = true;
                }
                if(!c3){
                    int x = r[i].x1, y = r[i].y2;
                    if(r[j].x1 < x && x < r[j].x2 && r[j].y1 < y && y < r[j].y2) c3 = true;
                }
                if(!c4){
                    int x = r[i].x2, y = r[i].y2;
                    if(r[j].x1 < x && x < r[j].x2 && r[j].y1 < y && y < r[j].y2) c4 = true;
                }
            }
            if(c1 && c2 && c3 && c4) continue;
            int tmp = 1;
            update(r[i].x1, r[i].y1, r[i].x2-1, r[i].y2-1, 1, id);
            for(int j = i+1; j < n; j++)
            {
                if(sum(r[j].x1, r[j].y1, r[j].x2-1, r[j].y2-1, id) != 0){
                    tmp++;
                    update(r[j].x1, r[j].y1, r[j].x2-1, r[j].y2-1, 1, id);
                }
            }
            if(ans < tmp){
                ans = tmp;
                idx = i;
            }
        }
        printf("%d %d\n", ans, idx+1);
    }
    return 0;
}

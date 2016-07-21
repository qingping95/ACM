#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
#include <ctime>
//#include <unordered_map>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
//        freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 2600010;
int UP;///////////////////
int c[N];
void add(int x, int val)
{
    if(x == 0) return ;
    for(int i = x; i <= UP; i += i&-i)
        c[i] += val;
}
int getval(int x)
{
    int res = 0;
    for(int i = x; i; i -= i & -i)
        res += c[i];
    return res;
}
int stx[N];
int sty[N];
int sx, sy;
int a[1010];
int suma[1010];
int sumb[1010];
PII query[N];
struct Q{
    int x, y1, y2, ty;
    Q(int x = 0, int y1 = 0, int y2 = 0, int ty = 0):x(x), y1(y1), y2(y2), ty(ty){}
    void update()
    {
        x = lower_bound(stx, stx+sx, x) - stx + 1;
        y1 = lower_bound(sty, sty+sy, y1) - sty + 1;
        if(ty != 1){
            y2 = lower_bound(sty, sty+sy, y2) - sty + 1;
        }
    }
    bool operator<(const Q& o)const{
        return x == o.x ? ty < o.ty : x < o.x;
    }
}que[N];
int ans[N];
//fread 加速
static const int MSIZE = 1000 * 25 * 1024;
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
template <class T>
void read(T &res)
{
    T f = 1, x = 0;
    while(*pt != '-' && !isdigit(*pt)) pt++;
    if(*pt == '-') f = -1, pt++;
    else x = *pt++ - 48;
    while(isdigit(*pt)) x = x * 10 + *pt++ - 48;
    res = x * f;
}
//fread 加速

int main(){
//    Open();
    init();
    int T;
    read(T);
    //scanf("%d", &T);
    while(T--)
    {
        memset(c, 0, sizeof(c));
        int n, m;
        read(n), read(m);
        //scanf("%d%d", &n, &m);
        int ma0 = 0, ma1 = 0;
        suma[0] = sumb[0] = 0;
        for(int i = 1; i <= n; i++)
        {
            read(a[i]);
            //scanf("%d", &a[i]);
            if(!(i & 1)){
                ma1 = max(ma1, a[i]);
                sumb[i] = sumb[i-1] + a[i];
                suma[i] = suma[i-1];
            }else{
                ma0 = max(ma0, a[i]);
                suma[i] = suma[i-1] + a[i];
                sumb[i] = sumb[i-1];
            }
        }
        sx = 0, sy = 0;
        suma[n+1] = suma[n];
        sumb[n+1] = sumb[n];
        int qt = 0;
        for(int i = 1; i <= n; i++){
            if(i > 1){
                int x1 = 0, y1 = 0;
                int x2 = a[i-1], y2 = a[i];
                if(i & 1){
                    swap(x2, y2);
                }
                que[qt++] = Q(x1, y1, y2, 0);
                que[qt++] = Q(x2, y1, y2, 2);
                stx[sx++] = x1;
                stx[sx++] = x2;
                sty[sy++] = y1;
                sty[sy++] = y2;
//                cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
            }
            for(int j = i ;j <= n; j++)
            {
                int x1 = suma[j] - suma[i-1];
                int y1 = sumb[j] - sumb[i-1];
                int x2 = suma[j+1], y2 = sumb[j+1];
                if(i > 1)
                    x2 -= suma[i-2], y2 -= sumb[i-2];
                que[qt++] = Q(x1, y1, y2, 0);
                que[qt++] = Q(x2, y1, y2, 2);
                stx[sx++] = x1;
                stx[sx++] = x2;
                sty[sy++] = y1;
                sty[sy++] = y2;
//                cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
            }
        }

        for(int i = 0; i < m; i++)
        {
            int x,y;
            read(x), read(y);
            //scanf("%d%d", &x, &y);
            query[i] = PII(x, y);
            que[qt++] = Q(x, y, i, 1);
            stx[sx++] = x;
            sty[sy++] = y;
        }
        sort(stx, stx+sx);
        sx = unique(stx, stx+sx) - stx;
        sort(sty, sty+sy);
        sy = unique(sty, sty+sy) - sty;
        UP = sy+10;
        for(int i = 0; i < qt; i++)
        {
            que[i].update();
        }
        sort(que, que+qt);
        for(int i = 0; i < qt; i++)
        {
            int ty = que[i].ty;
            if(ty == 0){
                add(que[i].y2+1, -1);
                add(que[i].y1, 1);
            }else if(ty == 1){
                int tmp = getval(que[i].y1);
                ans[que[i].y2] = (tmp != 0);
            }else{
                add(que[i].y2+1, 1);
                add(que[i].y1, -1);
            }
        }
        for(int i = 0; i < m; i++)
        {
            if(query[i].first == 0){
                ans[i] = (query[i].second <= ma1);
            }else if(query[i].second == 0){
                ans[i] = (query[i].first <= ma0);
            }
        }
        for(int i = 0; i < m; i++)
            printf("%d", ans[i]);
        printf("\n");
    }
    return 0;
}


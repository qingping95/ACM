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
#define LD double
typedef long long LL;
typedef pair<int, int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
struct Point{
    LD x,y;
    Point(LD x=0, LD y=0):x(x),y(y){}
    void read(){
        double xx,yy;
        scanf("%lf%lf",&xx,&yy);
        x = xx ,y= yy;
    }
}p[11111];//
const LD eps = 1e-10;
typedef Point Vector;
int dcmp(LD x){
    return x<-eps?-1:x>eps;
}
Vector operator+ (Point A, Point B){return Point(A.x + B.x , A.y + B.y);}
Vector operator- (Point A, Point B){return Point(A.x - B.x , A.y - B.y);}
Vector operator* (Point A, LD B){return Point(A.x*B , A.y*B);}
Vector operator/ (Point A, LD B){return Point(A.x/B , A.y/B);}
bool operator == (const Point& a, const Point& b){
    return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
}
bool operator < (const Point& a, const Point& b){
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
LD Dot(Vector A, Vector B){
    return A.x * B.x + A.y * B.y;
}
LD Length(Vector A){
    return sqrt(Dot(A,A));
}
LD Angle(Vector A, Vector B){
    return acos(Dot(A,B) / Length(A) / Length(B));
}
LD Cross(Vector A, Vector B){
    return A.x * B.y - A.y * B.x;
}
int ConvexHull(Point* p, int n, Point* ch){
    sort(p, p+n);
    int m= 0;
    for(int i=0;i<n;i++){
        while(m>1 && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    int k=m;
    for(int i=n-2;i>=0;i--){
        while(m>k && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    if(n > 1) m--;
    return m;
}
int n;
#define D(x) (x)*(x)
LD p2p(Point a,Point b){
    return sqrt(D(a.x-b.x) + D(a.y-b.y));
}
LD l[10111];//
const LD PI = acos(-1.0);
LD getArea(LD rx){
    if(dcmp(l[n-1] - rx) < 0 ) return 1e20;
    LD sum = rx * rx;
    LD tmp = rx;
    for(int i=0;i<n-1;i++){
        if( dcmp(l[i] - tmp) < 0 ) return 1e20;
        sum += D((l[i] - tmp));
        tmp = l[i] - tmp;
    }
    if(dcmp(l[n-1] - tmp) < 0) return 1e20;
    return sum * PI;
}
#define pb push_back
void getAndPrint(LD r){
    vector<LD > ans;
    ans.pb(r);
    bool imposi=false;
    LD tmp = r;
    LD sum = r * r;
    for(int i=0;i<n-1 && !imposi;i++){
        if(dcmp(l[i] - tmp) < 0){
            imposi=true;
            puts("IMPOSSIBLE");
            return;
        }
        sum += D((l[i] - tmp));
        ans.pb(l[i] - tmp);
        tmp = l[i] - tmp;
    }
    if(dcmp(l[n-1] - tmp - r) != 0){
        imposi=true;
        puts("IMPOSSIBLE");
        return ;
    }
    if(imposi) return;
    else{
        double tttt = sum*PI;
        printf("%.2f\n",tttt);
        int siz = ans.size();
        if(siz!=n) siz/=0;
        for(int i=0;i<ans.size();i++){
            tttt = ans[i]+eps;
            printf("%.2f\n",tttt);
        }
    }
}
void getLR(LD& L, LD& R){
    L = 0 , R = 1e6;
    LD tmp = l[0] - l[1];
    for(int i=1;i<n;i+=2){
        L = max(L , tmp);
        if(i+2 < n) tmp = tmp + l[i+1] - l[i+2];
    }
    tmp = l[0];
    for(int i=0;i<n;i+=2){
        R = min(R, tmp);
        if(i+2 < n) tmp = tmp -l[i+1] + l[i+2];
    }
}
int main()
{
    Open();
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d", &n);
        for(int i=0;i<n;i++){
            p[i].read();
        }
        for(int i=0;i<n;i++){
            l[i] = p2p(p[(i+1)%n], p[i]);
        }
        LD sum1 = 0 , sum2 = 0;
        for(int i=0;i<n;i+=2) sum1+=l[i];
        for(int i=1;i<n;i+=2) sum2+=l[i];
        if(n&1){
            LD r = (sum1 - sum2) / 2;
            if(dcmp(sum1 - sum2) < 0){
                puts("IMPOSSIBLE");
            }else{
                getAndPrint(r);
            }
        }else{
            if(dcmp(sum1 - sum2) == 0){
                LD l = 0, r = 1e6;
                getLR(l,r);
                if(dcmp(l-r) > 0 ){
                    puts("IMPOSSIBLE");
                    continue;
                }
                LD m1 = l + (r-l)/3;
                LD m2 = l + (r-l)*2/3;
                int times = 666;
                while(times--){
                    LD res1 = getArea(m1);
                    LD res2 = getArea(m2);
                    //cerr<<res1<<" "<<res2<<endl;
                    //cerr<<l<<" "<<r<<endl;
                    if(res1 > res2) l = m1;
                    else r = m2;
                    m1 = l + (r-l)/3;
                    m2 = l + (r-l)*2/3;
                    if(dcmp(m1 - 1e20) == 0 || dcmp(m2 - 1e20) == 0) m1/=0;
                }
                if(dcmp(getArea(l) - 1e20) == 0 ) puts("IMPOSSIBLE");
                else{
                    getAndPrint(l);
                }
            }else puts("IMPOSSIBLE");
        }
    }
    return 0;
}

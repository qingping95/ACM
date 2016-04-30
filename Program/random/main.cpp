#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
#include <ctime>
#define MP make_pair
#define scan(x) scanf("%d",&(x))
#define scan2(x,y) scanf("%d%d",&(x),&(y))
#define scan3(x,y,z) scanf("%d%d%d",&(x),&(y),&(z))
//#include <unordered_map>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/inlrt.txt","r",stdin);
        freopen("F:/baoli.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const LL N = 300010;
LL dir[1111][2];

PII POS[111];
#define D(x) (x)*(x)
struct st{
    int *p;
    int i;
    char a;
};
int val240(int k)
{
    int ret = 0;
    ret = ret * k + 2;
    ret = ret * k + 4;
    ret = ret * k + 0;
    return ret;
}
int val12(int k)
{
    int ret = 0;
    ret = ret * k + 1;
    ret = ret * k + 2;
    return ret;
}
int val2880(int k)
{
    int ret = 0;
    ret = ret * k + 2;
    ret = ret * k + 8;
    ret = ret * k + 8;
    ret = ret * k + 0;
    return ret;
}
int main()
{
    for(int i = 14; i <= 19; i++)
    {
        cout<<val240(i)<<endl;
        cout<<val12(i)<<endl;
        cout<<val2880(i)<<endl;
        if(val240(i) * val12(i) == val2880(i))
            cout<<i<<endl;
        cout<<endl;
    }
    return 0;
    freopen("F:/inlrt.txt","r",stdin);
    freopen("F:/baoli.txt","w",stdout);

    dir['U'][0] = -1, dir['U'][1] = 0;
    dir['L'][0] = 0, dir['L'][1] = -1;
    dir['D'][0] = 1, dir['D'][1] = 0;
    dir['R'][0] = 0, dir['R'][1] = 1;
    LL n, m;
    while(~scanf("%I64d%I64d", &n, &m))
    {
        for(LL i = 1; i <= n; i++)
        {
            LL x, y;
            scanf("%I64d%I64d", &x, &y);
            POS[i] = MP(x,y);
        }
        char op[2];
        scanf("%I64d",&m);
        while(m--)
        {
            scanf("%s", op);
            if(op[0] == 'Q') {
                int X;scan(X);
                int x=POS[X].first , y = POS[X].second;
                LL ans=0;
                for(int i=1;i<=n;i++){
                    if(POS[i].first == x || POS[i].second == y){
                        ans += D(POS[i].first - x) + D(POS[i].second - y);
                        POS[i].first = x , POS[i].second = y;
                    }
                }

                printf("%I64d\n", ans);
            }else{
                int X,d; scan2(X,d);
                POS[X].first += dir[op[0]][0] * d;
                POS[X].second += dir[op[0]][1] * d;
            }
        }
    }
    return 0;
}
#define YUE(x) ((x)>m || (x)<1)
int main1(){
    freopen("F:/inlrt.txt","w",stdout);
    srand(time(NULL));
    PII POS[101];
    memset(POS,0,sizeof(POS));
    char chose[4] = {'L','R','U','D'};
    int T=100;
    while(T--){
        int n = rand()%7+1;
        int m = rand()%7+1;
        cout<<n<<" "<<m<<endl;
        for(int i=1;i<=n;i++){
            int xx = rand()%m + 1;
            int yy = rand()%m + 1;
            POS[i] = MP(xx,yy);
            cout<<xx<<" "<<yy<<endl;
        }
        int Q = rand()%12+1;
        cout<<Q<<endl;
        while(Q--){
            int k = rand()%2;
            if(k==0){
                char o1;
                int X, d;
                do{
                    o1 = chose[rand()%4];
                    X = rand()%n + 1;
                    d = rand()%7;
                }while(YUE(POS[X].first + dir[o1][0]) || YUE(POS[X].second + dir[o1][1]));
                cout<<o1<<" "<<X<<" "<<d<<endl;
            }else{
                int X = rand()%n + 1;
                cout<<"Q"<<" "<<X<<endl;
                for(int i=1;i<=n;i++){
                    if(POS[i].first == POS[X].first || POS[i].second == POS[X].second){
                        POS[i].first = POS[X].first;
                        POS[i].second = POS[X].second;
                    }
                }
            }
        }
    }
    return 0;
}

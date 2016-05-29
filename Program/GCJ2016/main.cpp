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
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
#define pb push_back
#define Vector Point
#define LD long long double
const int INF=0x3f3f3f3f;
void Open()
{
        freopen("A-small-attempt2.in","r",stdin);
        freopen("A-small-attempt2.out","w",stdout);
    #ifndef ONLINE_JUDGE
        //freopen("/home/qingping/in.txt","r",stdin);
//        freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 10020;

int main()
{
//    Open();
    int T;
    scanf("%d", &T);
    int cas = 1;
    while(T--)
    {
        scanf("%d", &n);
        n = 1 << n;
        scanf("%d%d%d", &r, &p, &s);
        printf("Case #%d: ", cas++);
        if(dfs(0, 0, 0, 0)) {
            for(int i = 0 ; i < n; i++)
            {
                printf("%c", "PRS"[sta[i]]);
            }
            printf("\n");
        }else{
            printf("IMPOSSIBLE\n");
        }
    }
    return 0;
}

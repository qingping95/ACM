#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 444;
int pri[N];
int vis[N];
int pn;
void getpri()
{
    pn = 0;
    for(int i = 2; i <= 100; i++)
    {
        if(vis[i] == 0) pri[pn++] = i;
        for(int j = i; j <= 100; j += i)
            vis[j] = 1;
    }
}
int main()
{
    //Open();
    getpri();
//    cout<<pn<<endl;
//    for(int i= 0; i < pn; i++)
//        cout<<pri[i]<<endl;
    int num = 0;
    char str[1110];
    for(int i = 0; i < pn && pri[i] < 50; i++)
    {
        for(int j = pri[i]; j <= 100 && num < 2; j *= pri[i])
        {
            printf("%d\n", j);
            fflush(stdout);
            scanf("%s", str);
            if(strcmp(str, "yes") == 0){
                num++;
            }else{
                break;
            }
        }
        if(num >= 2) break;
    }
    if(num == 0 || num == 1) printf("prime\n");
    else printf("composite\n");
    fflush(stdout);
    return 0;
}

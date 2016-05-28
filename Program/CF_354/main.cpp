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
const int N = 100010;
LL a[N];
bool vis[N];
char coe[111];
int main()
{
    //Open();
    LL n, k;
    scanf("%I64d%I64d", &n, &k);
    LL qn = 0;
    LL idx = n+1;
    bool zero = false;
    for(LL i = 0; i <= n; i++)
    {
        scanf("%s", coe);
        if(coe[0] == '?') qn++, idx = i;
        else{
            sscanf(coe, "%I64d", &a[i]);
            if(i == 0) zero = true;
        }
    }
    if(k == 0)
    {
        if(zero){
            if(a[0] == 0)printf("Yes\n");
            else printf("No\n");
        }else{
            if((n + 1 - qn) & 1) printf("Yes\n");
            else printf("No\n");
        }
    } else if(qn == 0){
        bool flag = true;
        LL pre = a[n];
        for(LL i = n-1; i >= 1; i--)
        {
            pre = a[i] + k * pre;
            if(abs(pre) > 1000000) {flag = false;break;}
        }
        if(flag == false || -pre*k != a[0]) printf("No\n");
        else
            printf("Yes\n");
    }else{
        if(n & 1)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}

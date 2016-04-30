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
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 222;
int n;
PII peo[5555];
int male[5555];
int main()
{
    //Open();
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        int x, y;
        char s[2];
        scanf("%s%d%d", s, &x, &y);
        male[i] = (s[0] == 'M');
        peo[i] = PII(x, y);
    }
    int ans = 0;
    for(int i = 1; i <= 366; i++)
    {
        int M = 0, F = 0;
        for(int j = 0; j < n; j++)
        {
            if(i >= peo[j].first && i <= peo[j].second)
            {
                if(male[j]) M++;
                else F++;
            }
        }
        ans = max(ans, min(M, F));
    }
    printf("%d\n", ans*2);
    return 0;
}

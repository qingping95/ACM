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
        freopen("C:/Users/qingp/Downloads/C-small-attempt2.in", "r",stdin);
        freopen("C-small.out","w",stdout);
    #endif // ONLINE_JUDGE
}
int pn = 15;
int pri[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
LL getK(LL x, int k, int n)
{
    LL cur = 0;
    for(int i = n-1; i >= 0; i--)
    {
        cur = cur*k + ((x & (1 << i)) != 0);
    }
    //cout<<k<<" -> "<<cur<<endl;
    return cur;
}
int check(LL x)
{
    for(int i =0; i < pn; i++)
    {
        if(x%pri[i] == 0) return pri[i];
    }
    return -1;
}
int ans[111];
int sta[111];
int main()
{
//    Open();
    int T;
    scanf("%d", &T);
    int cas = 1;
    while(T--)
    {
        int n, j;
        scanf("%d%d", &n, &j);
        printf("Case #%d:\n", cas++);
        int UP = n-2;
        for(int s = 0; (s < (1 << UP)) && j; s++)
        {
            LL cur = 1 << UP;cur+=s;cur<<=1;cur++;
            bool can = true;
            for(int i = 2; i <= 10 && can; i++)
            {
                int tmp = check(getK(cur, i, n));
                if(tmp == -1) can = false;
                else ans[i] = tmp;
            }
            if(can)
            {
                j--;
                int idx = 0;
                while(cur)
                {
                    sta[idx++] = cur & 1;
                    cur >>= 1;
                }
                while(idx--)
                {
                    printf("%d", sta[idx]);
                }
                for(int i = 2; i <= 10; i++) printf(" %d", ans[i]);
                putchar('\n');
            }
        }
        if(j) cout<<"not enough!!"<<endl;
    }
    return 0;
}

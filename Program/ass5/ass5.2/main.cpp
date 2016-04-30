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
const int N = 100010;
int a[N];
int n, d;
int main()
{
    //Open();
    cout<<"请输入您的油箱满的时候能够行驶的距离：";
    cin >> d;
    cout<<"请输入加油站的个数：";
    cin >> n;
    cout<<"请从近到远输入相邻两个加油站之间的距离(以空格隔开)："<<endl;
    for(int i = 1; i < n; i++)
        cin >> a[i];

    int cur = d;
    int ans = 0;
    for(int i = 1; i < n; i++)
    {
        if(cur < a[i])
        {
            cur = d;
            ans ++;
        }
        cur -= a[i];
        if(cur < 0){
            printf("汽车无法到达终点!!\n");
            return 0;
        }
    }
    cout<<"利用贪心法求解的最少加油次数为："<<ans<<endl;
    return 0;
}
/*
10 5
5 5 5 5
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
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

int main()
{
    //Open();
    LL x, k;
    cin >> x >> k;
    int idx = 0;
    LL y = 0;
    LL mi2 = 1;
    while((1LL << idx) <= k)
    {
        if(x & 1) ;
        else{
            y += (k & (1LL << idx)) ? mi2 : 0;
            idx++;
        }
        mi2 <<= 1;
        x >>= 1;
    }
    cout<< y <<endl;
    return 0;
}

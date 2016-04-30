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
struct info
{
    int lma, rma, res;
};
const int N = 100010;
int n;
int a[N];
int pre[N];
info divide(int l, int r)
{
    if(l == r)
    {
        int res = max(a[l], 0);
        return (info){res, res, res};
    }
    int mid = l + r >> 1;
    info lres = divide(l, mid);
    info rres = divide(mid+1, r);
    int curlma = max(lres.lma, rres.lma + pre[mid] - pre[l-1]);
    int currma = max(rres.rma, lres.rma + pre[r] - pre[mid]);
    int curans = max(lres.res, rres.res);
//    curans = max()
    curans = max(curans, lres.rma + rres.lma);
    return (info){curlma, currma, curans};
}
int main()
{
    //Open();
    cout<<"请输入给定序列的元素个数: ";
    int k;
    cin >> n;
    pre[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pre[i] = a[i];
        pre[i] += pre[i-1];
    }
    cout<<"给定序列的最大子段和为："<<divide(1, n).res<<endl;
    return 0;
}
/*
5
4 -2 5 -2 3
*/

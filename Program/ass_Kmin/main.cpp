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
int n;
int a[N];
void divide(int l, int r, int k)
{
    if(l == r)
    {
        printf("给定序列的第k小的元素值为：%d\n", l);
        return ;
    }
    int mid = l + r >> 1;
    int num = 0;
    for(int i = 0; i < n; i++)
    {
        num += (a[i] <= mid);
    }
    if(num >= k) divide(l, mid, k);
    else divide(mid+1, r, k - num);
}
int main()
{
    //Open();
    cout<<"请输入给定序列的元素个数以及k值，用空格隔开: ";
    int k;
    cin >> n >> k;
    int mi = INF, ma = -INF;
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        mi = min(mi, a[i]);
        ma = max(ma, a[i]);
    }
    divide(mi, ma, k);
    return 0;
}
/*
5 4
4 5 1 2 2
5 3
4 5 1 2 2
*/

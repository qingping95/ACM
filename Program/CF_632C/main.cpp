#include <iostream>
#include <cstdio>
#include <stack>
#include <string>
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
bool cmp(const string &a, const string &b)
{
    return a+b < b+a;
}
string str[50011];
int main()
{
    //Open();
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) cin >> str[i];
    sort(str, str+n, cmp);
    for(int i = 0; i <n; i++) cout << str[i];
    return 0;
}

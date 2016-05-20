#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#define lson x<<1
#define rson x<<1|1
#define mid ((lt[x].l+lt[x].r)/2)
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
const int N = 200020;
int a[N];
int nxt[N];
vector<int> v[N];
int H[N];
struct node{
    int l , r, val, flag;
    int sum = 0;
}lt[N*6];
void push_up(int x)
{
    lt[x].sum = lt[lson].sum+lt[rson].sum;
}
void push_down(int x)
{
    if(lt[x].flag)
    {
        lt[lson].flag = max(lt[lson].flag, lt[x].flag);
        lt[rson].flag = max(lt[rson].flag, lt[x].flag);
        lt[x].flag = 0;
    }
}
void build(int l, int r, int x)
{
    lt[x] = (node){l, r, 0, 0, 0};
    if(l == r) {
        lt[x].sum = lt[x].val = nxt[l];
        return ;
    }
    build(l, mid, lson);
    build(mid+1, r, rson);
    push_up(x);
}
void update(int l, int r, int val, int x)
{
    if(lt[x].l >= l && lt[x].r <= r)
    {
        lt[x].flag = max(val, lt[x].flag);
    }
}
int main()
{
    //Open();
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    return 0;
}

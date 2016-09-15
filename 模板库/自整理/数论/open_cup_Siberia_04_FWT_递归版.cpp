/*
*	c[i] = sigma(str[u][j]*str[v][j^i])
*	于是裸裸的FWT，不需要取模的话，直接除2就好
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <climits>
#include <bitset>
using namespace std;
#define fuck(x) cout<<#x<<" "<<x<<endl
typedef long long ll;
const int N = (1<<22)+10;

void arrMul(ll n, ll *c, ll *a, ll *b)
{
    for(ll i = 0; i < n; i++)
        c[i] = a[i]*b[i];
}
void FWT(int l, int r, long long a[], int rev)
{
    if(l+1==r) return;
    int len=(r-l)>>1, mid=len+l;
    for(int i=l; i<mid; i++)
    {
        long long x1=a[i], x2=a[i+len];
        if(rev==1)
        {
            a[i]=x1-x2;
            a[i+len]=x1+x2;
        }
        else
        {
	    //如果需要取模的话，注意乘以2d逆元
            a[i]=(x1+x2)/2;
            a[i+len]=(x2-x1)/2;
        }
    }
    FWT(l,mid,a,rev);
    FWT(mid,r,a,rev);
}
int str[7][N];
ll ans[N];
ll A[N], B[N];
int main()
{
//	freopen("/home/qingping/in.txt","r",stdin);
    ll n, m, k;
    scanf("%lld%lld%lld", &n, &m, &k);
    for(ll i = 0; i < m; i++)
        for(ll j = 0; j < (1<<n); j++)
            scanf("%1d", &str[i][j]);
    ll len = 1;
    while(len < (1<<n)) len <<= 1;
    //len <<= 1;
    for(ll i = 0; i < k; i++)
    {
        ll u, v;
        scanf("%lld%lld", &u, &v);
        for(ll j = 0; j < len; j++)
        {
            if(j < (1<<n)) A[j] = str[u][j], B[j] = str[v][j];
            else B[j] = A[j] = 0;
        }
        FWT(0, len, A, 1);
        FWT(0, len, B, 1);
        arrMul(len, A, A, B);
        FWT(0, len, A, -1);
        for(ll j = 0; j < (1<<n); j++)
        {
            printf("%d", (A[j] > 0));
        }
        printf("\n");
    }
    return 0;
}

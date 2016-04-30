#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 100000010
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const LL INF=0x3f3f3f3f3f3f3f3fLL;
const double eps = 1e-8;
const LL mod = 1000000007;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
bool isp[N];
bool pvis[N];
int pri[5761456+10];
int prin;
void getpri(){
    prin = 0;
    memset(pvis, 0, sizeof(pvis));
    for(int i = 2; i < N; i++) {
        if(pvis[i] == 0) pri[prin++] = i, isp[i] = 1;
        for(int j = 0; j < prin && (LL)pri[j]*i < N; j++) {
            pvis[pri[j]*i] = 1;
            if(i % pri[j] == 0) break;
        }
    }
}
bool check(int n){
    for(int i = 0; i < prin; i++){
        if(n % pri[i] == 0) return false;
    }
    return true;
}
int sub[111] = {100000007, 200000033, 300000007, 400000009, 500000009, 600000007, 699999953, 799999999, 900000053};
int ans[111];
int main()
{
//    Open();
//    get_prime();
    getpri();
//    cout<<prin<<endl;
    int n;
    scanf("%d", &n);
    int tail = 0;
    while(n >= 100000007 && tail < 3)
    {
        int idx = upper_bound(sub, sub + 9, n) - sub - 1;
        ans[tail++] = sub[idx];
        n -= sub[idx];
    }
    if(n == 0){
        printf("%d\n", tail);
        for(int i =0 ; i < tail; i++) printf("%d ", ans[i]);
        return 0;
    }
    if(tail == 0){
        for(int i = prin-1; i >= 0; i--)
        {
            if(pri[i] == n){
                ans[tail++] = pri[i];
                n -= pri[i];
                break;
            }
            if(n - pri[i] > 9 && i >= 0){
                n -= pri[i];
                ans[tail++] = pri[i];
                break;
            }
        }
    }
    int i;
    for(i = prin-1; i >= 0 && n; i--)
    {
        if(pri[i] == n){
            ans[tail++] = pri[i];
            n -= pri[i];
            break;
        }
        if(pri[i] < n && isp[n - pri[i]] && tail <= 1 && n - pri[i] >= 2){
            ans[tail++] = pri[i];
            ans[tail++] = n-pri[i];
            break;
        }
    }
    printf("%d\n", tail);
    for(int i =0 ; i < tail; i++) printf("%d ", ans[i]);
    return 0;
}

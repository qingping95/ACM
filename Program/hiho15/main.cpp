#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 311
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
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int n;
int a[N][N], b[N][N];
int ta[N][N], tb[N][N];
int fa[N], fb[N];
int yaa[N], yab[N];
vector<PII> v;
bool swapc(int s, int t, int a[][N])
{
    if(s == t) return false;
    for(int i = 0; i < n; i++)
        swap(a[i][s], a[i][t]);
    return true;
}
int getnum(int a[], int b[], int ta[][N])
{
    v.clear();
    int n1 = 0, n2 = 0;
    for(int i = 0; i < n; i++) fa[a[i]] = i;
    for(int i = 0; i < n; i++) fb[b[i]] = i;
    for(int i = 0; i < n; i++){
        if(a[i] == b[i]) continue;
        int idx = fa[b[i]];
        if(a[i] == b[idx] && idx > i){
            n2++;
            v.push_back(PII(i, idx));
        }
    }
    int res = 0;
    for(int i = 0; i < v.size(); i++){
        res += swapc(v[i].first, v[i].second, ta);
    }
    for(int i = 0; i < n; i++) fa[ta[0][i]] = i;
    for(int i = 1; i <= n; i++){
        if(fa[i] == fb[i]) continue;
        res += swapc(fa[i], fb[i], ta);
        for(int i = 0; i < n; i++) fa[ta[0][i]] = i;
    }
    return res;
}
int getnum(int a[], int b[])
{
    int n1 = 0, n2 = 0;
    for(int i = 0; i < n; i++) fa[a[i]] = i;
    for(int i = 0; i < n; i++) fb[b[i]] = i;
    for(int i = 0; i < n; i++){
        if(a[i] == b[i]) continue;
        int idx = fa[b[i]];
        if(a[i] == b[idx] && idx > i){
            n2++;
        }else{
            n1++;
        }
    }
    return max(n1-1, 0) + n2;
}
const int mod = 99997;
int hashnum;
int idx[mod];
int gethash(int a[])
{
    int res = 0;
    for(int i = 0; i < n; i++)
        res = (res * 301%mod + a[i])%mod;
    if(idx[res] == -1) return idx[res] = hashnum++;
    return idx[res];
}
int main()
{
//    Open();
    while(~scanf("%d", &n))
    {
        memset(idx, -1, sizeof(idx));
        hashnum = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                scanf("%d", &a[i][j]);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                scanf("%d", &b[i][j]);
        int ans = INF;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
                for(int k = 0; k < n; k++) ta[j][k] = a[j][k], tb[j][k] = b[j][k];
            int res = getnum(ta[0], tb[i], ta);
            if(i) res++;
            for(int j = 0; j < n; j++)
                swap(ta[0][j], ta[i][j]);
            //res += swapc(0, i ,ta);
            memset(idx, -1, sizeof(idx));
            hashnum = 0;
            for(int j = 0; j < n; j++)yaa[j] = gethash(ta[j]), yab[j] = gethash(tb[j]);
//            if(hashnum != n) continue;
            res += getnum(yaa, yab);
            ans = min(ans, res);
        }
        if(ans >= 3 * n ) ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}

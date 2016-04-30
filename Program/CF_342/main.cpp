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
        freopen("F:/my.txt","r",stdin);
        freopen("F:/out.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
char np[100010];
int n[100010], ans1[100010], ans2[100010];
int len;
bool solve(int idx, int rminus)
{
    int peer = len-idx-1;

    if(idx > peer) {
        if(rminus) return false;
        return true;
    }

    int prep = n[peer];
    if(rminus){
        if(n[peer] >= rminus)n[peer] -= rminus, rminus = 0;
        else n[peer] = 10 - rminus, rminus = 1;
    }
    if(idx == peer){
        if(rminus) return false;
        if(n[idx] & 1) return false;
        ans1[idx] = ans1[peer] = n[idx]/2;
        return true;
    }

    if(n[peer] > n[idx]) return false;

    if(n[idx] == n[peer] && n[idx] == 0)
    {
        ans1[idx] = ans1[peer] = 0;
        if(solve(idx+1, rminus)) return true;
    }
    int up = min(9, n[idx]);
    for(int j = (idx==0); j <= up; j++)
    {
        int npe = n[peer], npe1 = n[peer-1];
        ans1[idx] = j;
        if(n[peer] >= j){
            ans1[peer] = n[peer] - j;
        }else if(n[peer] < j && rminus == 0 && n[peer] + 10 <= n[idx]){
            n[peer] += 10;
            if(n[peer-1] > 0) n[peer-1] --;
            else rminus = 1;
            ans1[peer] = n[peer] - j;
        }else if(n[idx] > j && n[idx] == n[peer] + 1 && idx + 1 != peer){
            n[idx] -- ;
            n[idx+1] += 10;
            ans1[peer] = n[idx] - j;
            if(solve(idx+1, rminus)) return true;
            n[idx+1] -= 10;
            n[idx]++;
        }
        if(n[idx] == n[peer] + 1 && n[idx] > j && idx + 1 != peer)
        {
            n[idx]--;
            n[idx+1] += 10;
            if(solve(idx+1, rminus)) return true;
            n[idx+1] -= 10;
            n[idx]++;
        }
        if(n[idx] == n[peer])
            if(solve(idx+1, rminus)) return true;
        n[peer] = npe, n[peer-1] = npe1;
    }
    if(rminus == 0)
    {
        int npe = n[peer], npe1 = n[peer-1];
        n[peer] += 10;
        if(n[peer-1] > 0) n[peer-1] --;
        else rminus = 1;
        for(int j = (idx==0); j <= up; j++)
        {
            ans1[idx] = j;
            if(n[peer] >= j){
                ans1[peer] = n[peer] - j;
            }else if(n[peer] < j && rminus == 0 && n[peer] + 10 <= n[idx]){
                n[peer] += 10;
                if(n[peer-1] > 0) n[peer-1] --;
                else rminus = 1;
                ans1[peer] = n[peer] - j;
            }else if(n[idx] > j && n[idx] == n[peer] + 1 && idx + 1 != peer){
                n[idx] -- ;
                n[idx+1] += 10;
                ans1[peer] = n[idx] - j;
                if(solve(idx+1, rminus)) return true;
                n[idx+1] -= 10;
                n[idx]++;
            }
            if(n[idx] == n[peer] + 1 && n[idx] > j && idx + 1 != peer)
            {
                n[idx]--;
                n[idx+1] += 10;
                if(solve(idx+1, rminus)) return true;
                n[idx+1] -= 10;
                n[idx]++;
            }
            if(n[idx] == n[peer])
                if(solve(idx+1, rminus)) return true;
        }
        n[peer] = npe, n[peer-1] = npe1;
    }
    n[peer] = prep;
    return false;
}

bool check(int s, int t)
{
    t -= s;
    int tmp = 0;
    while(s)
    {
        tmp = tmp * 10 + s % 10;
        s /= 10;
    }
    return t == tmp;
}
int main1()
{
    freopen("F:/out.txt", "r", stdin);
    int s, t;
    int T = 0;
    while(~scanf("%d%d", &s, &t))
    {
        T++;
        if(check(t, s));
        else printf("%d\n", T);
    }
}
int main()
{
    //Open();
    ans1[3] = 9;
    while(~scanf("%s", np))
    {
        //printf("%s ", np);
        len = strlen(np);
        for(int i = 0; i < len ;i++) n[i] = np[i] - '0';
        bool flag = solve(0, 0);
        if(flag) {
            for(int i = 0; i < len ;i++) printf("%d", ans1[i]);
            printf("\n");
        }else{
            if(n[0] != 1 || len == 1)
                printf("0\n");
            else{
                len--;
                for(int i = 0; i < len; i++)
                    n[i] = n[i+1];
                n[0] += 10;
                if(solve(0, 0)){
                    for(int i = 0; i < len ;i++) printf("%d", ans1[i]);
                    printf("\n");
                }else{
                    printf("0\n");
                }
            }
        }
    }
    return 0;
}
int main2()
{
    freopen("F:/my.txt","w",stdout);
    int T = 1000;
    while(T--)
    {
        int n = rand();
        int np = 0;
        int sum = n;
        while(n)
        {
            np = np*10 + n%10;
            n/=10;
        }
        printf("%d\n", sum+np);
        //printf("%d - %d\n", sum+np, np);
    }
}

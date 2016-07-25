/*
*Rainto96
*Beijing University of Posts and Telecommunications School of Software
Engineering
*http://blog.csdn.net/u011775691
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
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define VINT vector<int>
#define PII pair<int,int>
#define MP(x,y) make_pair((x),(y))
#define ll long long
#define ull unsigned ll
#define MEM0(x)  memset(x,0,sizeof(x))
#define MEM(x,val) memset((x),val,sizeof(x))
#define scan(x) scanf("%d",&(x))
#define scan2(x,y) scanf("%d%d",&(x),&(y))
#define scan3(x,y,z) scanf("%d%d%d",&(x),&(y),&(z))
#define scan4(x,y,z,k) scanf("%d%d%d%d",&(x),&(y),&(z),&(k))
#define Max(a,b) a=max(a,b)
#define Min(a,b) a=min(a,b)
#define fuck(x) cout<<#x<<" "<<x<<endl
ll dp[12][100];
ll a[12];
ll b[12];
ll geta(ll x)
{
    ll t = 0;
    while(x)
    {
        a[t++] = x % 10;
        x /= 10;
    }
    return t;
}
ll getBval(ll idx)
{
    ll res = 0;
    for(ll i = idx-1; i >= 0; i--)
        res = res * 10 + b[i];
    return res;
}
void getB(int idx, int sum)
{
    for(int i = idx; i>= 0; i--)
    {
        b[i] = min(9, sum);
        sum -= b[i];
    }
}
ll dfs(ll idx, ll sum, bool limit)
{
    if(sum < 0) return 0;
    if(idx == -1) return sum == 0;
    if(limit == false && dp[idx][sum] != -1){
        if(dp[idx][sum] != 0) getB(idx, sum);
        return dp[idx][sum];
    }
    ll UP = limit ? a[idx] : 9;
    ll res = 0;
    for(ll i = 0; i <= UP; i++)
    {
        ll tmp = dfs(idx-1, sum - i, limit & (i == UP));
        if(tmp != 0) b[idx] = i;
        res += tmp;
    }
    if(limit == false) dp[idx][sum] = res;
    return res;
}
ll solve(ll n, ll sum)
{
    memset(b, 0, sizeof(b));
    memset(dp, -1, sizeof(dp));
    ll t = geta(n);
    return dfs(t-1, sum, 1);
}
int main(){
    //freopen("/home/rainto96/in.txt","r",stdin);
    ll n;
//    while(cin >> n >> k)
//        cout<<solve(n, k)<<endl;

    int nn = 0;
    scanf("%d", &nn);
    n = nn;
    int ans = 0;
    ll cul = 0;
    for(ll sum = 1; sum <= 81; sum++)
    {
        ll len = solve(n, sum);
        ll lb = cul, ub = cul+len+1;
        if(len == 0) continue;
        while(lb + 1 < ub)
        {
            ll mid = lb + ub >> 1;
//            solve(mid, sum);
            if(mid <= solve(mid,sum) + cul)
                lb = mid;
            else
                ub = mid;
        }
//        for(lb -= 10; lb <= ub +10; lb++)
//        {
            if(lb > cul && lb - cul <= len)
            {
                solve(lb, sum);
                ll t = geta(lb);
                if(lb == solve(lb,sum) + cul && getBval(t) == lb) {
                    ans++;
//                    cout<<lb<<endl;
                }
            }
//        }
        cul += len;
    }
    printf("%d\n", ans);
    return 0;
}

/*
*Rainto96
*Beijing University of Posts and Telecommunications School of Software Engineering
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
using namespace std;
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define VINT vector<int>
#define PII pair<int,int>
#define MP(x,y) make_pair((x),(y))
#define ll long long
#define ull unsigned long long
#define MEM0(x)  memset(x,0,sizeof(x))
#define MEM(x,val) memset((x),val,sizeof(x))
#define scan(x) scanf("%d",&(x))
#define scan2(x,y) scanf("%d%d",&(x),&(y))
#define scan3(x,y,z) scanf("%d%d%d",&(x),&(y),&(z))
#define scan4(x,y,z,k) scanf("%d%d%d%d",&(x),&(y),&(z),&(k))
#define Max(a,b) a=max(a,b)
#define Min(a,b) a=min(a,b)
#define fuck(x) cout<<#x<<" - "<<x<<endl
int dp[(1<<20)+100];//
int que[1000];//
bool vis[129];
int a[1010];

int n,k,L;

int f[1001111];
int ft;

void dfs(int state,int num, int last){
    if(num>k){
        return;
    }
    if(state!=0) f[ft++] = state;
    for(int i=last;i<n;i++){
        dfs(state|(1<<i), num+1, i+1);
    }
}
bool cmp(const int& a, const int& b)
{
    return dp[a] < dp[b];
}
int main(){
    //freopen("in.txt","r",stdin);
    while(scan3(n,k,L)==3){
        ft=0;
        for(int i=0;i<n;i++){
            scan(a[i]);
        }
        sort(a, a+n);
        memset(dp,-1,sizeof(dp));
        dfs(0,0,0);
        for(int ii=0;ii<ft;ii++){
            int i = f[ii];
            int tail=0;
            for(int j=0;j<n;j++){
                if(i&(1<<j)){
                    que[tail++] = a[j];
                }
            }
            memset(vis,0,sizeof(vis));
            for(int s=0;s<(1<<tail);s++){
                int sum=0;
                for(int j=0;j<tail;j++){
                    if(s&(1<<j)){
                        sum^=que[j];
                    }
                }
                vis[sum]=true;
            }
            int j = L;
            while(vis[j]) j++;
            dp[i] = j-1;
        }
        sort(f, f+ft, cmp);
        int ans=0;
        for(int ii=ft-1;ii>=0;ii--){
            int i = f[ii];
            if(dp[i]==-1) continue;
            if(dp[i]<=ans) continue;
            //if(__builtin_popcount(i) > k) continue;
            int tail=0;
            for(int j=0;j<n;j++){
                if(i&(1<<j)){
                    que[tail++] = a[j];
                }
            }
            do{
                memset(vis,0,sizeof(vis));
                for(int i=0;i<tail;i++){
                    int sum=0;
                    for(int len=0, j=i;len<k;len++,j++){
                        if(j >= tail) j -= tail;
                        sum ^= que[j];
                        vis[sum]=true;
                    }
                }
                int j = L;
                while(vis[j]) j++;
                j--;
                if(ans < j) ans = j;
            }while(next_permutation(que,que+tail));
        }
        printf("%d\n",ans);
    }
    return 0;
}

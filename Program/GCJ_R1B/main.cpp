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
#define VINT vector<ll>
#define PII pair<ll,ll>
#define MP(x,y) make_pair((x),(y))
#define ll long long

char C[1999];
char J[1999];
#define P(x) ((x)-'0')
ll len;
ll dif,ans1,ans2;
void PRINT(ll len, ll x){
    char tmp[100];
    sprintf(tmp,"%lld",x);
    ll l = strlen(tmp);
    for(ll i=0;i<len-l;i++) printf("0");
    printf("%s",tmp);
}
void dfs(ll now,ll st,ll cc,ll jj){
    if(now == len){
        if(abs(cc-jj) < dif){
            dif = abs(cc-jj);
            ans1 = cc , ans2 = jj;
        }else if(abs(cc-jj) == dif && cc < ans1){
            ans1 = cc , ans2 = jj;
        }else if(abs(cc-jj) == dif && cc == ans1 && jj < ans2){
            ans1 = cc , ans2 = jj;
        }
        return;
    }
    ll i = now;
    if(!isdigit(C[i]) ){
        if(isdigit(J[i]) ){
            if(st == 0){
                dfs(now+1, 0, cc*10+P(J[i]), jj*10+P(J[i]) );
                if(P(J[i])+1 <= 9) dfs(now+1, 1, cc*10+P(J[i])+1, jj*10+P(J[i]) );
                if(P(J[i])-1 >= 0) dfs(now+1, -1, cc*10+P(J[i])-1, jj*10+P(J[i]) );
            }else if(st==1){
                dfs(now+1, 1, cc*10+P('0'), jj*10+P(J[i]) );
            }else{
                dfs(now+1, -1, cc*10+P('9'), jj*10+P(J[i]) );
            }
        }else{
            if(st==0){
                dfs(now+1, 0, cc*10+P('0'), jj*10+P('0') );
                dfs(now+1, 1, cc*10+P('1'), jj*10+P('0') );
                dfs(now+1, -1, cc*10+P('0'), jj*10+P('1') );
            }else if(st == 1){
                dfs(now+1, 1, cc*10+P('0'), jj*10+P('9') );
            }else{
                dfs(now+1, -1, cc*10+P('9'), jj*10+P('0') );
            }
        }
    }else{
        if(isdigit(J[i]) ){
            if(st == 0) {
                if(C[i]>J[i]) dfs(now+1, 1, cc*10+P(C[i]), jj*10+P(J[i]) );
                else if(C[i]<J[i]) dfs(now+1, -1, cc*10+P(C[i]), jj*10+P(J[i]) );
                else{
                    dfs(now+1, 0, cc*10+P(C[i]), jj*10+P(J[i]) );
                }
            }else
                dfs(now+1, st, cc*10+P(C[i]), jj*10+P(J[i]) );
        }else{
            if(st==0){
                dfs(now+1, 0, cc*10+P(C[i]), jj*10+P(C[i]) );
                if(P(C[i])+1 <= 9) dfs(now+1, -1, cc*10+P(C[i]), jj*10+P(C[i])+1 );
                if(P(C[i])-1 >= 0) dfs(now+1, 1, cc*10+P(C[i]), jj*10+P(C[i])-1 );
            }else if(st == 1){
                dfs(now+1, 1, cc*10+P(C[i]), jj*10+P('9') );
            }else{
                dfs(now+1, -1, cc*10+P(C[i]), jj*10+P('0') );
            }
        }

    }
}
int main(){
    //freopen("C:/OJ/OJ/in.txt","r",stdin);
    freopen("B-small-attempt0.in","r",stdin);
    freopen("B-small-attempt0my.out","w",stdout);

    ll T;
    scanf("%lld", &T);
    for(ll cas=1;cas<=T;cas++){
        ll dif = 0x7fffffffffffffffLL;
        scanf("%s %s",C,J);
        len = strlen(C);
        dfs(0,0,0,0);
        printf("Case #%lld: ", cas);
        //printf("%s %s\n",C, J);
        PRINT(len, ans1);
        printf(" ");
        PRINT(len, ans2);
        printf("\n");
    }
    return 0;
}

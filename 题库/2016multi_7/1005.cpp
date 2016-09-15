/*
*	a[i]从大到小排序，对于i点每次只链接前a[i]个点即可。因为这a[i]个点已经不可能与别的点链接
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
#define PII pair<int,int>
#define MP(x,y) make_pair((x),(y))
#define ll long long
#define ull unsigned ll
#define scan(x) scanf("%d",&(x))
#define scan2(x,y) scanf("%d%d",&(x),&(y))
#define scan3(x,y,z) scanf("%d%d%d",&(x),&(y),&(z))
#define scan4(x,y,z,k) scanf("%d%d%d%d",&(x),&(y),&(z),&(k))
#define Max(a,b) a=max(a,b)
#define Min(a,b) a=min(a,b)
#define fuck(x) cout<<#x<<" "<<x<<endl
const int MX = 1011;
PII a[MX];
PII ans[MX*MX];
#define F first
#define S second
int main(){
    //freopen("/home/rainto96/in.txt","r",stdin);
    int T;scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        printf("Case #%d: ", cas);
        int tl=0;
        int n;scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i].first);
            a[i].second = i;
        }
        sort(a+1,a+1+n);
        bool suc= true;
        for(int i=1;i<=n;i++){
            if(a[i].F > i-1){
                puts("No");
                suc=false;
                break;
            }else{
                for(int j=1;j<=a[i].F;j++){
                    ans[tl++] = MP(a[i].S, a[j].S);
                }
            }
        }
        if(suc == false) continue;
        puts("Yes");
        printf("%d\n", tl);
        for(int i=0;i<tl;i++){
            printf("%d %d\n", ans[i].F, ans[i].S);
        }
    }
    return 0;
}

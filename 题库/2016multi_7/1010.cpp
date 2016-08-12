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
const int MX = 151111;
int tot, l[MX], r[MX], d[MX];
PII v[MX];
int Merge(int x,int y){
    if(!x) return y;
    if(!y) return x;
    if(v[x].first < v[y].first) swap(x,y);
    r[x] = Merge(r[x], y);
    if(d[l[x]] < d[r[x]]) swap(l[x], r[x]);
    d[x] = d[r[x]] + 1;
    return x;
}
int init(int x,int t){
    tot++;
    v[tot] = MP(t, x);
    l[tot] = r[tot] = d[tot] = 0;
    return tot;
}
int Insert(int x,int y,int t){
    return Merge(x, init(y, t));
}
int top(int x) {
    return v[x].second;
}
int pop(int x){
    return Merge(l[x], r[x]);
}
char tp[22];
char s1[22], s2[22];
int main(){
    //freopen("/home/rainto96/in.txt","r",stdin);
    int n;
    int cas=1;
    while(scanf("%d", &n) == 1){
        if(n == 0) break;
        printf("Case #%d:\n", cas++);
        tot=0;
        int A = 0, B = 0;
        for(int i=1;i<=n;i++){
            scanf("%s", tp);
            if(tp[1] == 'u'){
                int x;
                scanf("%s%d",tp, &x);
                if(tp[0] == 'A'){
                    if(A==0) A = init(x,i);
                    else A = Insert(A, x, i);
                }else{
                    if(B==0) B = init(x,i);
                    else B = Insert(B, x, i);
                }
            }else if(tp[1] == 'o'){
                scanf("%s",tp);
                //fuck(tp);
                int ans;
                if(tp[0] == 'A'){
                    ans = top(A);
                    A = pop(A);
                }else{
                    ans = top(B);
                    B = pop(B);
                }
                printf("%d\n", ans);
            }else{
                scanf("%s%s",s1,s2);
                if(s1[0] == 'A'){
                    A = Merge(A,B);
                    B = 0;
                }else{
                    B = Merge(A,B);
                    A = 0;
                }
            }
        }
    }
    return 0;
}


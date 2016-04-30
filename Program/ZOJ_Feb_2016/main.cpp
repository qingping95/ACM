#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define ll long long
///gai long long !!!!!
struct Wupin{
    ll ai,bi,di,i;
    bool operator < (const Wupin& s2) const{
        return bi < s2.bi;
    }
}w[101111];

struct Houmian{
    ll ai,bi,di,i;
    bool operator < (const Houmian& s2) const{
        return ai==s2.ai ? di>s2.di : ai < s2.ai;
    }
};
bool cmp(const Wupin& s1, const Wupin& s2){
    return s1.di > s2.di;
}

bool vis[101111];//

bool inque[101111];//

int main()
{
    freopen("F:/in.txt","r",stdin);
    ll T;scanf("%lld",&T);
    while(T--){
        memset(vis,0,sizeof(vis));
        memset(inque,0,sizeof(inque));

        ll n,k,m;
        scanf("%lld%lld%lld",&n,&k,&m);
        ll sum=0;
        for(ll i=0;i<n;i++){
            ll ai,bi;
            scanf("%lld%lld",&ai,&bi);
            w[i] = (Wupin){ai,bi,ai-bi,i};
            sum+=ai;
        }
        sort(w,w+n,cmp);
        priority_queue<Wupin> que;
        priority_queue<Houmian> hou;
        for(ll i=0;i<k;i++){
            w[i].i = i;
            que.push(w[i]);
            sum -= w[i].di;
        }
        for(ll i=k;i<n;i++) hou.push((Houmian){w[i].ai, w[i].bi, w[i].di, i});

        ll num=n;
        for(ll i=k;i<n;i++){
            if(sum <= m) break;
            else{
                if(vis[i]) continue;
                ll tp1 = que.size()>0 ? que.top().bi + w[i].di : 0;
                ll tp2 = hou.top().ai;
                num--;
                if(tp1>=tp2){
                    que.pop();
                    sum-=tp1;
                    que.push(w[i]);
                }else{
                    vis[hou.top().i]=true;
                    sum-=tp2;
                    hou.pop();
                    i--;
                }
                while(hou.size() > 0 && hou.top().i <= i ) hou.pop();
            }
        }

        vector<ll> vc;
        while(!que.empty()){
            inque[que.top().i]=true;
            vc.push_back(que.top().bi);
            que.pop();
        }
        while(!hou.empty()){
            if(inque[hou.top().i]) hou.pop();
            else{
                vc.push_back(hou.top().ai);
                hou.pop();
            }
        }
        sort(vc.begin(), vc.end(), greater<ll>());
        ll i=0;
        while(sum>m && i<vc.size()){
            sum -= vc[i];
            num--;
            i++;
        }
        printf("%lld\n",num);
    }
    return 0;
}

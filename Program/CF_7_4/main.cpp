#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
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
        freopen("F:/in.txt","r",stdin);
//        freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 201000;
PII p[N];
int sta[N];
vector<int> G[N];
set<PII > s[2];
set<PII >::iterator it1, it2;
void printSet(set<PII > S)
{
    for(it1 = S.begin(); it1 != S.end(); it1++)
    {
        cout<<it1->first <<" , "<<it1->second<<endl;;
    }
}
int main()
{
//    Open();
    int n, m;
    scanf("%d%d", &n, &m);
    int t = 0;
    bool flag = true;
    for(int i = 0; i < m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        p[i] = PII(x, y);
        sta[t++] = x;
        if(x == n && y == n) flag = false;
    }
    if(!flag){
        printf("-1\n");
        return 0;
    }
//    p[m++] = PII(n, n+1);
    sta[t++] = n;
    sta[t++] = 1;
    sort(sta, sta+t);
    t = unique(sta, sta+t) - sta;
    for(int i = 0; i < t; i++)
    {
        p[m++] = PII(sta[i], n+1);
    }
    sort(p, p+m);
    int cur = 0;
    int pre = 1;
    s[cur].insert(PII(0, 0));
    s[cur].insert(PII(INF, INF));
    s[cur].insert(PII(1, 1));
    int id = 0;
    for(int i = 0; i < t; i++)
    {
        cur ^= 1;
        pre ^= 1;
        s[cur].clear();
        s[cur].insert(PII(0, 0));
        s[cur].insert(PII(INF, INF));

        if(i > 0 && sta[i] != sta[i-1]+1){
            it1 = s[pre].upper_bound(PII(0, INF));
//            cout<<it1->first <<" , "<<it1->second<<endl;;
            if(it1->first <= n) s[cur].insert(PII(it1->first, n));
//            printSet(s[cur]);
            cur ^= 1;
            pre ^= 1;
            s[cur].clear();
            s[cur].insert(PII(0, 0));
            s[cur].insert(PII(INF, INF));
        }
        int x = sta[i];
        int st = 1;
        while(id < m && p[id].first == x)
        {
            int y = p[id].second;
            int S = st, T = y-1, mis = INF;
            it1 = s[pre].upper_bound(PII(S, INF));
            it1--;
            if(it1->second >= S)
                mis = S;
            else{
                it1++;
                mis = it1->first;
            }
            if(T >= mis)
                s[cur].insert(PII(mis, T));
            st = y+1;
            id++;
        }
//        printSet(s[cur]);
    }
    it1 = s[cur].upper_bound(PII(n, INF));
    it1--;
//    cout<<it1->first <<" , "<<it1->second<<endl;
    if((it1->first) <= n && n <= (it1->second))
        printf("%d\n", n+n-2);
    else
        printf("-1\n");
    return 0;
}

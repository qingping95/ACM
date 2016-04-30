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
int a, b, c, d;
PII ans[101000];
priority_queue<PII> que;
bool vis[1100][1100];
PII sta[100101];
int num[11010];
int main()
{
    //freopen("in.txt","r",stdin);
    freopen("kids.in","r",stdin);
    freopen("kids.out","w",stdout);
    scanf("%d%d%d%d", &a, &b, &c, &d);
    int gcd = __gcd(b, c);
    int x = c / gcd, y = b / gcd;
    while(x <= a || y <= b || (x % 2 && a % 2) || (y % 2 && d % 2) || x < c || y < b){
        x += c/gcd;
        y += b/gcd;
    }
//    int x = a+1, y = d+1;
//    while(b*x != c*y){
//        if(b*x > c*y){
//            y = max(y+1, (int)ceil((double)b*x/c));
//        }else{
//            x = max(x+1, (int)ceil((double)c*y/b));
//        }
//        if(a*x % 2) x++;
//        if(d*y % 2) y++;
//    }
    while(true)
    {
        int tail = 0;
        bool flag = false;
        memset(num, 0, sizeof(num));
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= x; i++) que.push(PII(a, i));
        while(!que.empty())
        {
            int u = que.top().second, v, dv;
            int du = que.top().first;
            que.pop();
            int t = 0;
            if(que.empty()) {flag = true;break;}
            do{
                v = que.top().second;
                dv = que.top().first;
                que.pop();
                if(vis[u][v])
                    sta[t++] = PII(dv, v);
            }while(vis[u][v] && !que.empty());
            if(vis[u][v]) {flag = true;break;}
            for(int i = 0; i < t; i++) que.push(sta[i]);
            vis[u][v] = vis[v][u] = 1;
            ans[tail++] = PII(u, v);
            du--, dv--;
            if(du) que.push(PII(du, u));
            if(dv) que.push(PII(dv, v));
        }
        if(flag) {
            x += c/gcd;
            y += b/gcd;
            continue;
        }
        for(int i = x+1; i<= x+y; i++) que.push(PII(d, i));
        while(!que.empty())
        {
            int u = que.top().second, v, dv;
            int du = que.top().first;
            que.pop();
            int t = 0;
            if(que.empty()) {flag = true;break;}
            do{
                v = que.top().second;
                dv = que.top().first;
                que.pop();
                if(vis[u][v])
                    sta[t++] = PII(dv, v);
            }while(vis[u][v] && !que.empty());
            if(vis[u][v]) {flag = true;break;}
            for(int i = 0; i < t; i++) que.push(sta[i]);
            vis[u][v] = vis[v][u] = 1;
            ans[tail++] = PII(u, v);
            du--, dv--;
            if(du) que.push(PII(du, u));
            if(dv) que.push(PII(dv, v));
        }
        if(flag) {
            x += c/gcd;
            y += b/gcd;
            continue;
        }
        for(int i = 1; i<= x; i++)
        {
            num[i] = 0;
            for(int j = x+1; j <= x+y && num[i] < b; j++)
            {
                if(vis[i][j] || num[j] == c) continue;
                vis[i][j] = vis[j][i] = 1;
                num[i]++, num[j]++;
                ans[tail++] = PII(i, j);
            }
            if(num[i] != b) {flag = true;break;}
        }
        for(int j = x+1;j <= x+y; j++){
            if(num[j] != c) {flag =true;break;}
        }
        if(flag) {
            x += c/gcd;
            y += b/gcd;
            continue;
        }
        printf("%d %d\n", x, y);
        for(int i= 0; i < tail; i++)
        {
            printf("%d %d\n", ans[i].first, ans[i].second);
        }
        break;
    }
    return 0;
}

/*
写这题感触较深的就是，只要访问儿子，就一定要先push_down！
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <climits>
#include <map>
using namespace std;
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define PII pair<int,int>
#define MP(x,y) make_pair((x),(y))
#define ll long long
#define ull unsigned ll
#define Max(a,b) a=max(a,b)
#define Min(a,b) a=min(a,b)
#define fuck(x) cout<<#x<<" "<<x<<endl
const int INF = 0x3f3f3f3f;
const int N = 200010;
PII val[N], a[N];
int pre[N], ch[N][2], flip[N], sz[N], mi[N];
int tot, root;
struct Splay
{

    void init()
    {
        val[0] = PII(INF, INF);
        tot = root = 0;
    }
    int newnode(int fa, PII v)
    {
        int k = ++tot;
        ch[k][0] = ch[k][1] = 0;
        pre[k] = fa;
        val[k] = v;
        mi[k] = k;
        flip[k] = 0;
        sz[k] = 1;
        return k;
    }
    void P(int x)
    {
        if(flip[x])
        {
            flip[x] = 0;
            swap(ch[x][0], ch[x][1]);
            if(ch[x][0] != 0) flip[ch[x][0]] ^= 1;
            if(ch[x][1] != 0) flip[ch[x][1]] ^= 1;
        }
    }
    void push_up(int x)
    {
        sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
        mi[x] = x;
        if(val[mi[x]] > val[mi[ch[x][0]]])
        {
            mi[x] = mi[ch[x][0]];
        }
        if(val[mi[x]] > val[mi[ch[x][1]]])
        {
            mi[x] = mi[ch[x][1]];
        }
        //val[x] = min(val[x], min(val[ch[x][0]], val[ch[x][1]]));
    }
    void rotate(int x)
    {
        int y = pre[x], d = (ch[y][1] == x);
        P(y); P(x);
        ch[y][d] = ch[x][!d];
        if(ch[x][!d]) pre[ch[x][!d]] = y;
        ch[x][!d] = y;
        pre[x] = pre[y];
        pre[y] = x;
        if(pre[x]) ch[pre[x]][ch[pre[x]][1] == y] = x;
        push_up(y);
        push_up(x);
    }
    void splay(int x, int goal)
    {
        while(pre[x] != goal)
        {
            int f = pre[x], ff = pre[f];
            P(ff); P(f);
            if(ff == goal) rotate(x);
            else if((ch[ff][1] == f) == (ch[f][1] == x))
                rotate(f), rotate(x);
            else
                rotate(x), rotate(x);
        }
        push_up(x);
        if(goal == 0) root = x;
    }
    int build(int l, int r, int fa)
    {
        if(l > r) return 0;
        int mid = l + r >> 1;
        int k = newnode(fa, a[mid]);
        if(fa == 0) root = k;
        ch[k][0] = build(l, mid-1, k);
        ch[k][1] = build(mid+1, r, k);
        push_up(k);
        return k;
    }
    int kth(int k)
    {
        int x = root;
        while(x)
        {
            P(x);
            if(sz[ch[x][0]] >= k) x = ch[x][0];
            else {
                k -= sz[ch[x][0]] + 1;
                if(k == 0) return x;
                x = ch[x][1];
            }
        }
        return x;
    }
    void reverse(int k)
    {
        splay(k, 0);
        P(k);
        int left = sz[ch[k][0]]+1;
        int idx = kth(left+1);
        if(idx == 0) flip[root] ^= 1;
        else splay(idx, 0), P(idx), flip[ch[idx][0]] ^= 1;
    }
    void removeLeft()
    {
        int idx = kth(2);
        splay(idx, 0);
        P(idx);
        int son = ch[idx][0];
        pre[son] = 0;
        ch[idx][0] = 0;
        sz[son] = 0;
        push_up(idx);
    }
    int query()
    {
        int idx = mi[root];
        splay(idx, 0);
        P(idx);
        return idx;
    }
    void Treaval(int x)
    {
        if(x)
        {
            P(x);
            Treaval(ch[x][0]);
            printf("%2d: left:%2d right:%2d father:%2d  sz = %2d, mi = %2d, val.first = %2d, val.second = %2d\n", x, ch[x][0], ch[x][1], pre[x], sz[x], mi[x], val[x].first, val[x].second);
            Treaval(ch[x][1]);
        }
    }
}sp;
int main(){
//    freopen("/home/rainto96/in.txt","r",stdin);
    int n;
    while(~scanf("%d", &n) && n)
    {
        sp.init();
        for(int i = 1; i <= n; i++)
        {
            int x;
            scanf("%d", &x);
            a[i] = PII(x, i);
        }
        //root = sp.newnode(0, PII(INF, INF));
        sp.build(1, n, 0);
        ch[0][0] = root;
//        sp.Treaval(root);
        for(int i = 1; i < n; i++)
        {
            int idx = sp.query();
//            cout<<idx<<" : "<<val[idx].first<<" "<<val[idx].second<<endl;
            printf("%d ", sz[ch[idx][0]]+1+i-1);
            sp.reverse(idx);
            sp.removeLeft();
//            cout<<" ======================== "<<endl;
//            sp.Treaval(root);
        }
        printf("%d\n", n);
    }
    return 0;
}
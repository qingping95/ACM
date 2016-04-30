#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 400010
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef pair<char,int> PCI;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int a[N];
int n, m;
int st[N], ed[N];
//int mx[N];//存储以该节点为根的子树中的最大值
int sz[N];//存储以该结点为根的子树中的节点数
int pre[N], ch[N][2];//该节点的儿子和父亲
int val[N];
int tot, root;//tot总共有多少个节点，root根节点的编号
int key[N];
int rev[N];
struct Splay
{
    void init()
    {
        tot = root = 0;
    }
    int newnode(int fa, int idx, int preidx)
    {
        int k;
        if(!preidx) k = ++tot;
        else k = preidx;
        key[idx] = k;
        rev[k] = idx;
        ch[k][0] = ch[k][1] = 0;
        pre[k] = fa;
//        val[k] = v;
        val[k] = sz[k] = ed[idx] - st[idx] + 1;
        return k;
    }
    void push_up(int x)
    {
        sz[x] = sz[ch[x][1]] + sz[ch[x][0]] + val[x];
    }
    void rotate(int x)
    {
        int y = pre[x], d = (ch[y][1] == x);
		//push_down(y);push_down(x);
        ch[y][d] = ch[x][!d];
        if(ch[x][!d]) pre[ch[x][!d]] = y;
        ch[x][!d] = y;
        pre[x] = pre[y];
        pre[y] = x;
        if(pre[x]) ch[pre[x]][ch[pre[x]][1] == y] = x;
        push_up(y);
        push_up(x);
    }
    void splay(int x, int goal)//将x旋转到goal的下面
    {
        while(pre[x] != goal)
        {
            int f = pre[x], ff = pre[f];
            if(ff == goal) rotate(x);
            else if((ch[ff][1] == f) == (ch[f][1] == x))
                rotate(f), rotate(x);
            else
                rotate(x), rotate(x);
        }
        push_up(x);
        if(goal == 0) root = x;//根的父亲为null
    }
    int kth(int k)//寻找splay中的第k大的节点
    {
        int x = root;
        while(x)
        {
            if(sz[ch[x][0]] >= k) x = ch[x][0];
            else {
                k -= sz[ch[x][0]];
                if(k <= val[x]) return st[rev[x]] + k - 1;
                else k -= val[x];
//                if(k == 0) return st[rev[x]];
                x = ch[x][1];
            }
        }
        return st[rev[x]];
    }
    int build(int l, int r, int fa)
    {
        if(l > r) return 0;
        int mid = l + r >> 1;
        int k = newnode(fa, mid, 0);
        ch[k][0] = build(l, mid-1, k);
        ch[k][1] = build(mid+1, r, k);
        push_up(k);
        return k;
    }
    void remove(int x)
    {
        splay(x, 0);
        if(ch[x][0] == 0){
            root = ch[x][1];
            pre[ch[x][1]] = 0;
            return ;
        }
        int y = ch[x][0];
        while(ch[y][1]) y =ch[y][1];
        splay(y, x);
        ch[y][1] = ch[x][1];
        if(ch[x][1]) pre[ch[x][1]] = y;
        pre[y] = 0;
        root = y;
        return ;
    }
    void insert(int v, int preidx)//将节点插入树中，并让其变为树中最左端的节点
    {
        int x = root;
        while(ch[x][0]) x = ch[x][0];
        int tmp = newnode(x, v, preidx);
        ch[x][0] = tmp;
        while(x) push_up(x), x = pre[x];
        splay(tmp, 0);
    }
}spl;
PCI query[N];
char op[11];
int sta[N];
int binaryS(int l, int r, int x)
{
    int lb = l - 1, ub = r + 1;
    int mid;
    while(lb + 1 < ub)
    {
        mid = lb + ub >> 1;
        if(st[mid] <= x && ed[mid] >= x) return mid;
        else if(st[mid] > x) ub = mid;
        else if(ed[mid] < x) lb = mid;
    }
    return mid;
}
int main()
{
    Open();
    int T;scanf("%d", &T);
    int cas = 1;
    while(T--)
    {
        scanf("%d%d", &n, &m);
        spl.init();
        int cnt = 0;
        sta[cnt++] = 1;
        for(int i = 0; i < m; i++)
        {
            int x;
            scanf("%s%d", op, &x);
            query[i] = PCI(op[0], x);
            if(op[0] != 'R')
                sta[cnt++] = x;
        }
        sta[cnt++] = n;
        sort(sta, sta+cnt);
        cnt = unique(sta, sta+cnt) - sta;
        int tail = 0;
        for(int i = 0; i < cnt; i++){
            if(i && sta[i] != sta[i-1] + 1){
                st[tail] = sta[i-1] + 1;
                ed[tail++] = sta[i] - 1;
            }
            st[tail] = ed[tail] = sta[i];
            tail++;
        }
        root = spl.build(0, tail - 1, 0);
        for(int i = 0; i < m; i++)
            if(query[i].first != 'R')
                query[i].second = binaryS(0, tail, query[i].second);
        printf("Case %d:\n", cas++);
        for(int i = 0; i < m; i++)
        {
            if(query[i].first == 'Q') {
                int x = query[i].second;
                spl.splay(key[x], 0);
                int res = sz[ch[root][0]] + 1;
                printf("%d\n", res);
            }else if(query[i].first == 'R') {
                printf("%d\n", spl.kth(query[i].second));
            }else if(query[i].first == 'T') {
                int x = query[i].second;
                spl.remove(key[x]);
                spl.insert(x, key[x]);
            }
        }
    }
    return 0;
}

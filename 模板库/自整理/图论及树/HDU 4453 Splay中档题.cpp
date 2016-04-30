/*
* HDU 4453 Looploop
* 。。。这个题太恶心了，写得精疲力尽，但是无疑是对splay又更加理解了
* 六种操作：
* 1. add x: 找到树中的第k2+1个点，旋转为根，然后给左儿子打标记即可
* 2. reverse: 找到树中的第k1+1个点，旋转为根，然后给左儿子打标记即可
* 3. insert x: 啊。。我这里是比较丑的写法，直接找到最左边的儿子，
*              把新节点变成这个节点的父亲，然后暴力往上push_up。。但是
*              其实利用splay旋转的性质完全可以不这么做，比如说将最左边
*              儿子旋转到根，然后再插入，这样更新会方便一些吧。
* 4. delete: 就只是删除最左边一个点而已，旋转到根，然后删。
* 5. move x: 将第一个点放到最后去，也就是将第一个点删除，然后给尾巴添加
*            一个新节点。挺简单的一个操作。不过我这里写的太挫了。。
* 6. query: 这个不用说啦，找到最左一个点，然后输出即可。
* 
* 需要注意的就是push_down, push_up需要随时考虑用不用
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 300010
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
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int a[N];
int val[N];
int pre[N], ch[N][2], add[N], flip[N], sz[N];
int tot, root;
struct Splay
{
    void Treaval(int x) {
        if(x) {
            Treaval(ch[x][0]);
            printf("结点%2d:左儿子 %2d 右儿子 %2d 父结点 %2d size = %2d ,key = %2d \n",x, ch[x][0], ch[x][1], pre[x], sz[x], val[x]);
            Treaval(ch[x][1]);
        }
    }
    void init()
    {
        tot = root = 0;
    }
    int newnode(int fa, int v)
    {
        int k = ++tot;
        ch[k][0] = ch[k][1] = 0;
        pre[k] = fa;
        val[k] = v;
        add[k] = 0, flip[k] = 0;
        sz[k] = 1;
        return k;
    }
    void push_down(int x)
    {
        if(add[x]){
            int lc = ch[x][0];
            int rc = ch[x][1];
            if(lc != 0) val[lc] += add[x], add[lc] += add[x];
            if(rc != 0) val[rc] += add[x], add[rc] += add[x];
            add[x] = 0;
        }
        if(flip[x]){
            flip[x] = 0;
            swap(ch[x][0], ch[x][1]);
            if(ch[x][0] != 0) flip[ch[x][0]] ^= 1;
            if(ch[x][1] != 0) flip[ch[x][1]] ^= 1;
        }
    }
    void push_up(int x)
    {
        sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
    }
    void rotate(int x)
    {
        int y = pre[x], d = (ch[y][1] == x);
        push_down(y);push_down(x);
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
        while(pre[x] != goal){
            int f = pre[x], ff = pre[f];
            if(ff == goal) rotate(x);
            else if((ch[ff][1] == f) == (ch[f][1] == x))
                rotate(f), rotate(x);
            else
                rotate(x), rotate(x);
        }
        push_up(x);
        if(goal == 0) root = x;
    }
    int kth(int k)
    {
        int x = root;
        while(x)
        {
            push_down(x);
            if(sz[ch[x][0]] >= k) x = ch[x][0];
            else {
                k -= sz[ch[x][0]] + 1;
                if(k == 0) return x;
                x = ch[x][1];
            }
        }
        return x;
    }
    int build(int l, int r, int fa){
        if(l > r) return 0;
        int mid = l + r >> 1;
        int k = newnode(fa, a[mid]);
        ch[k][0] = build(l, mid-1, k);
        ch[k][1] = build(mid+1, r, k);
        push_up(k);
        return k;
    }
    void increase(int k, int x)
    {
        int idx = kth(k + 1);
        if(idx == 0){
            val[root] += x;
            add[root] += x;
            return ;
        }
        splay(idx, 0);
        val[ch[idx][0]] += x;
        add[ch[idx][0]] += x;
    }
    void reverse(int k)
    {
        int idx = kth(k + 1);
        if(idx == 0){
            flip[root] ^= 1;
            return ;
        }
        splay(idx, 0);
//        Treaval(root);
        flip[ch[idx][0]] ^= 1;
    }
    void remove()
    {
        int x = root;
        push_down(x);
        while(ch[x][0]) x = ch[x][0], push_down(x);
        splay(x, 0);
        if(ch[x][0] == 0){
            root = ch[x][1];
            pre[ch[x][1]] = 0;
            return ;
        }
        int y = ch[x][0];
        push_down(y);
        while(ch[y][1]) y = ch[y][1], push_down(y);
        splay(y, x);
        ch[y][1] = ch[x][1];
        if(ch[x][1]) pre[ch[x][1]] = y;
        pre[y] = 0;
        root = y;
        push_up(y);
    }
    void insert(int v){
        if(ch[root][0] == 0) splay(ch[root][1], 0);
        int x = root;
        push_down(x);
        while(ch[x][0]) x = ch[x][0], push_down(x);
        int tmpk = newnode(pre[x], v);
        ch[tmpk][0] = x, ch[tmpk][1] = ch[x][1];
        ch[pre[x]][0] = tmpk;

        if(ch[x][1] != 0) pre[ch[x][1]] = tmpk;
        ch[x][1] = 0;
        pre[x] = tmpk;
        while(x) push_up(x), x = pre[x];
    }
    void move(int kind){
        if(kind == 1){
            int x = root;push_down(x);
            while(ch[x][1]) x = ch[x][1], push_down(x);
            splay(x, 0);
            int y = ch[x][0];push_down(y);
            while(ch[y][1]) y = ch[y][1], push_down(y);
            splay(y, x);
            pre[y] = 0;
            root = y;
            push_up(y);

            ch[x][1] = ch[x][0] = 0;
            y = root;push_down(y);
            while(ch[y][0]) y = ch[y][0], push_down(y);
            splay(y, 0);
            ch[y][0] = x; pre[x] = y;
            sz[x] = 1;
            push_up(y);
        }else{
            int x = root; push_down(x);
            while(ch[x][0]) x = ch[x][0], push_down(x);
            splay(x, 0);
            int y = ch[x][1]; push_down(y);
            while(ch[y][0]) y = ch[y][0], push_down(y);
            splay(y, x);
            pre[y] = 0; root = y;
            push_up(y);

            ch[x][1] = ch[x][0] = 0;
            y = root; push_down(y);
            while(ch[y][1]) y = ch[y][1], push_down(y);
            splay(y, 0);
            ch[y][1] = x, pre[x] = y;
            sz[x] = 1; push_up(y);
        }
    }
    int query()
    {
        int x = root;push_down(x);
        while(ch[x][0]) x = ch[x][0], push_down(x);
        return val[x];
    }
}spl;
char tmp[22];
int main()
{
    Open();
    int n, m, k1, k2;
    int cas = 1;
    while(scanf("%d%d%d%d", &n, &m, &k1, &k2), n||m||k1||k2)
    {
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        spl.init();
        root = spl.build(1, n, 0);
//        spl.Treaval(root);
        printf("Case #%d:\n", cas++);
        while(m --)
        {
            scanf("%s", tmp);
            if(tmp[0] == 'm')
            {
                int kind;
                scanf("%d", &kind);
                spl.move(kind);
            }
            if(tmp[0] == 'q')
            {
                printf("%d\n", spl.query());
            }
            if(tmp[0] == 'i')
            {
                int v;scanf("%d", &v);
                spl.insert(v);
            }
            if(tmp[0] == 'r')
            {
                spl.reverse(k1);
            }
            if(tmp[0] == 'a')
            {
                int v;scanf("%d", &v);
                spl.increase(k2, v);
            }
            if(tmp[0] == 'd')
            {
                spl.remove();
            }
//            printf("--------------------------%s------------------------\n", tmp);
//            spl.Treaval(root);
            int asdfasd = 11212;
        }
    }
    return 0;
}

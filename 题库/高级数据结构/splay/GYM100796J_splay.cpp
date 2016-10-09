#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <assert.h>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
#define CHECK(x, y) ((x)>0 && (x)<=n && (y)>0 && (y)<=n)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
//        freopen("/home/qingping/out.txt","w",stdout);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 200010;
int n, m;
//int mx[N];//存储以该节点为根的子树中的最大值
int sz[N];//存储以该结点为根的子树中的节点数
int pre[N], ch[N][2];//该节点的儿子和父亲
int tot, root;//tot总共有多少个节点，root根节点的编号
int key[N];
struct Splay
{
    void init()
    {
        //root并不是虚点，虚点始终为0
        sz[0] = 0;
        tot = root = 0;
    }
    int newnode(int fa, int idx)
    {
        int k = ++tot;
        key[idx] = k;
        ch[k][0] = ch[k][1] = 0;
        pre[k] = fa;
        sz[k] = 1;
        return k;
    }
    void push_up(int x)
    {
        if(x) sz[x] = sz[ch[x][1]] + sz[ch[x][0]] + 1;
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
    int kth(int k)
    {
        int x = root;
        while(x)
        {
            //push_down(x);
            if(sz[ch[x][0]] >= k) x = ch[x][0];
            else {
                k -= sz[ch[x][0]] + 1;
                if(k == 0) return x;
                x = ch[x][1];
            }
        }
        return x;
    }
    int getF()
    {
        int x = root;
        while(ch[x][0]) x = ch[x][0];
        return x;
    }
    int getB()
    {
        int x = root;
        while(ch[x][1]) x = ch[x][1];
        return x;
    }

    //删除x节点，并将sz小的一边儿子切割并返回编号
    //删除代码的时候，一定要记得维护好ch数组pre数组的关系，就算是虚根也需要做
    //同时，插入点和删除点之后，要及时做splay操作，保证root随时有效
    int remove(int x, int& cid)
    {
        splay(x, 0);
        cid = 0;
        if(sz[ch[x][1]] < sz[ch[x][0]]) cid = 1;
        int res = ch[x][cid];
        if(ch[0][0] == x) ch[0][0] = ch[x][cid^1];
        if(ch[0][1] == x) ch[0][1] = ch[x][cid^1];
        root = ch[x][cid^1];
        pre[ch[x][cid^1]] = 0;
        return res;
    }
    //新插入一个节点，或者将某节点接到某个节点下面
    void insert(int fa, int idx, int cid, int preidx = 0)
    {
        splay(fa, 0);
        int tmp;
        if(preidx == 0) tmp = newnode(fa, idx);
        else tmp = preidx;
        ch[fa][cid] = tmp;
        pre[tmp] = fa;
        push_up(fa);
        splay(tmp, 0);
        ///之所以要加这个，是因为当树中只有虚点的时候，需要修改root的取值
    }
    void Treaval(int x) {
        if(x) {
            Treaval(ch[x][0]);
            printf("结点%2d:左儿子 %2d 右儿子 %2d 父结点 %2d size = %2d \n",x, ch[x][0], ch[x][1], pre[x], sz[x]);
            Treaval(ch[x][1]);
        }
    }
}spl;
int main()
{
//    Open();
    int n;
    scanf("%d", &n);
    char op[2];
    int x;
    int cnt = 1;
    spl.init();
    while(n--)
    {
        scanf("%s", op);
        if(op[0] == 'F')
        {
            spl.insert(spl.getF(), cnt++, 0);
        }
        else if(op[0] == 'B')
        {
            spl.insert(spl.getB(), cnt++, 1);
        }
        else
        {
            scanf("%d", &x);
            x = key[x];
            int cid;
            int child = spl.remove(x, cid);
            int res = sz[child];
            if(child)spl.insert(cid?spl.getF():spl.getB(), cnt, cid^1, child);
//            printf("ans : %d\n", res);
            printf("%d\n", res);
        }
//        cout<<n<<" : ----------------------------------"<<endl;
//        spl.Treaval(root);
    }
    return 0;
}


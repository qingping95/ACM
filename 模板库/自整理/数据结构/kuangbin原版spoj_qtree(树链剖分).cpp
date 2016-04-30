/* **********************************************
Author      : kuangbin
Created Time: 2013/8/11 22:00:02
File Name   : F:\2013ACM练习\专题学习\数链剖分\SPOJ_QTREE.cpp
*********************************************** */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;
const int MAXN = 10010;
int top[MAXN];//top[v]表示v所在的重链的顶端节点
int fa[MAXN]; //父亲节点
int deep[MAXN];//深度
int num[MAXN];//num[v]表示以v为根的子树的节点数
int p[MAXN];//p[v]表示v与其父亲节点的连边在线段树中的位置
int fp[MAXN];//和p数组相反
int son[MAXN];//重儿子
int pos;


struct Edge
{
    int to,next;
}edge[MAXN*2];
int head[MAXN],tot;
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
    pos = 0;
    memset(son,-1,sizeof(son));
}
void addedge(int u,int v)
{
    edge[tot].to = v;edge[tot].next = head[u];head[u] = tot++;
}

////////////////////线段树////////////////////
#define lson(x) (x)<<1
#define rson(x) ((x)<<1)|1
struct Node
{
    int l,r;
    int num;
    Node(int ll=0,int rr=0,int n=0){
        l = ll,r = rr,num = n;
    }
    //bool flag;
}st[N*6];

struct Seg{
    void bulid(int idx,int l,int r)
    {
        st[idx] = Node(l,r,0);
        if(l == r)
        {
            st[idx].num = w[fp[l]];
            return ;
        }
        int mid = (l + r) / 2;
        bulid(lson(idx),l,mid);
        bulid(rson(idx),mid+1,r);
    }
    void pushdown(int idx)
    {
        int tmp = st[idx].num;
        if(tmp)
        {
            st[lson(idx)].num += tmp;
            st[rson(idx)].num += tmp;
        }
        st[idx].num = 0;
    }
    void update(int idx, int l, int r, int value)
    {
        if(st[idx].l >= l && st[idx].r <= r)
        {
            st[idx].num += value;
            return ;
        }
        pushdown(idx);
        int mid = (st[idx].l+st[idx].r)/2;
        if(r <= mid) update(lson(idx),l,r,value);
        else if(l > mid) update(rson(idx),l,r,value);
        else{
            update(lson(idx),l,mid,value);
            update(rson(idx),mid+1,r,value);
        }
    }
    int query(int idx, int k)
    {
        if(st[idx].l == st[idx].r && st[idx].l == k)
        {
            //if(st[idx].num)
            return st[idx].num;
        }
        pushdown(idx);
        int mid = (st[idx].l + st[idx].r)/2;
        if(k <= mid) return query(lson(idx),k);
        else return query(rson(idx),k);
    }
}seg;


////////////////////树链剖分////////////////////
struct TreeLink{
    void build(){
        dfs1(1,0,0);
        getpos(1,1);
    }
    int find(int u,int v)//查询u->v边的最大值
    {
        int f1 = top[u], f2 = top[v];
        int tmp = 0;
        while(f1 != f2)
        {
            if(deep[f1] < deep[f2])
            {
                swap(f1,f2);
                swap(u,v);
            }
            tmp = max(tmp,seg.query(1,p[f1],p[u]));
            u = fa[f1]; f1 = top[u];
        }
        if(u == v)return tmp;
        if(deep[u] > deep[v]) swap(u,v);
        return max(tmp,seg.query(1,p[son[u]],p[v]));//如果属性在点上，那这里的p[son[u]]需要修改为p[u].
    }
    /*Useless*/
    void dfs1(int u,int pre,int d) //第一遍dfs求出fa,deep,num,son
    {
        deep[u] = d;
        fa[u] = pre;
        num[u] = 1;
        for(int i = head[u];i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            if(v != pre)
            {
                dfs1(v,u,d+1);
                num[u] += num[v];
                if(son[u] == -1 || num[v] > num[son[u]])
                    son[u] = v;
            }
        }
    }
    void getpos(int u,int sp) //第二遍dfs求出top和p
    {
        top[u] = sp;
        if(son[u] != -1)
        {
            p[u] = pos++;
            fp[p[u]] = u;
            getpos(son[u],sp);
        }
        else
        {
            p[u] = pos++;
            fp[p[u]] = u;
            return;
        }
        for(int i = head[u] ; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            if(v != son[u] && v != fa[u])
                getpos(v,v);
        }
    }
}trlnk;




int e[MAXN][3];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    int n;
    scanf("%d",&T);
    while(T--)
    {
        init();
        scanf("%d",&n);
        for(int i = 0;i < n-1;i++)
        {
            scanf("%d%d%d",&e[i][0],&e[i][1],&e[i][2]);
            addedge(e[i][0],e[i][1]);
            addedge(e[i][1],e[i][0]);
        }
        trlnk.build();
        seg.build(1,0,pos-1);
        for(int i = 0;i < n-1; i++)
        {
            if(deep[e[i][0]] > deep[e[i][1]])
                swap(e[i][0],e[i][1]);
            seg.update(1,p[e[i][1]],e[i][2]);
        }
        char op[10];
        int u,v;
        while(scanf("%s",op) == 1)
        {
            if(op[0] == 'D')break;
            scanf("%d%d",&u,&v);
            if(op[0] == 'Q')
                printf("%d\n",trlnk.find(u,v));
            else seg.update(1,p[e[u-1][1]],v);
        }
    }
    return 0;
}

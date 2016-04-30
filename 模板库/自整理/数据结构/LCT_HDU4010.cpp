#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <stdio.h>
const int maxn=100011;
const int INF=0x7fffffff;
using namespace std;

struct SplayTree
{
    int val,mn,lazy;
    bool remark;
    int ch[2],pre;
};

SplayTree *tree;
int N;
int val[maxn];

void Init_Splay(int x)
{
    tree[x].ch[0]=tree[x].ch[1]=tree[x].pre=0;
    tree[x].remark=0;
    tree[x].val=val[x];
    tree[x].mn=val[x];
}

bool IsRoot(int x)
{
    return !tree[x].pre || (tree[tree[x].pre].ch[0]!=x && tree[tree[x].pre].ch[1]!=x);
}

void DynamicTree(int n)
{
    N=n;
    tree=new SplayTree[n+1];
    for(int i=0; i<=n; i++) Init_Splay(i);
    tree[0].val=-INF;
    tree[0].mn=-INF;
}

void Inc(int x,int d)
{
    tree[x].val+=d;
    tree[x].mn+=d;
    tree[x].lazy+=d;
}

void Rev(int x)
{
    swap(tree[x].ch[0],tree[x].ch[1]);
    tree[x].remark^=1;
}

void PushDown(int x)
{
    if(!x) return;
    if(tree[x].lazy)
    {
        if(tree[x].ch[0]) Inc(tree[x].ch[0],tree[x].lazy);
        if(tree[x].ch[1]) Inc(tree[x].ch[1],tree[x].lazy);
        tree[x].lazy=0;
    }
    if(tree[x].remark)
    {
        if(tree[x].ch[0]) Rev(tree[x].ch[0]);
        if(tree[x].ch[1]) Rev(tree[x].ch[1]);
        tree[x].remark=0;
    }
}

void Update(int x)
{
    if(!x) return;
    tree[x].mn=tree[x].val;
    if(tree[x].ch[0]) tree[x].mn=max(tree[tree[x].ch[0]].mn,tree[x].mn);
    if(tree[x].ch[1]) tree[x].mn=max(tree[tree[x].ch[1]].mn,tree[x].mn);
}

void Rotate(int p,int c)
{
    int x=tree[p].pre,y=tree[x].pre;
    tree[p].pre=y;
    tree[x].pre=p;
    if(y) if(x==tree[y].ch[0]) tree[y].ch[0]=p;
        else if(x==tree[y].ch[1]) tree[y].ch[1]=p;
    tree[x].ch[!c]=tree[p].ch[c];
    if(tree[x].ch[!c]) tree[tree[x].ch[!c]].pre=x;
    tree[p].ch[c]=x;
    Update(x);
}

int stack[maxn];

void Splay(int x)
{
    int top=1;
    stack[0]=x;
    for(int q=x; !IsRoot(q);) stack[top++]=(q=tree[q].pre);
    while(top) PushDown(stack[--top]);
    while(!IsRoot(x))
    {
        int q=tree[x].pre;
        if(IsRoot(q)) if(tree[q].ch[0]==x) Rotate(x,1);
            else Rotate(x,0);
        else
        {
            if(q==tree[tree[q].pre].ch[0])
                if(tree[q].ch[0]==x) Rotate(q,1),Rotate(x,1);
                else Rotate(x,0),Rotate(x,1);
            else if(x==tree[q].ch[1]) Rotate(q,0),Rotate(x,0);
            else Rotate(x,1),Rotate(x,0);
        }
    }
    Update(x);
}

int Head(int x)
{
    Splay(x);
    for(PushDown(x); tree[x].ch[0]; x=tree[x].ch[0]) PushDown(x);
    Splay(x);
    return x;
}

int Expose(int x)
{
    int y;
    for(y=0; x; x=tree[x].pre) Splay(x),PushDown(x),tree[x].ch[1]=y,Update(y=x);
    return y;
}

void ChangeRoot(int x)
{
    Rev(Expose(x));
}

void Change(int x,int y,int val)
{
    ChangeRoot(y);
    Expose(x);
    Splay(x);
    tree[x].val+=val;
    tree[x].lazy+=val;
    tree[x].mn+=val;
//    PushDown(x);
//    Update(x);
}

int AskMax(int x,int y)
{
    ChangeRoot(x);
    Expose(y);
    Splay(y);
    return tree[y].mn;
}

void Link(int x,int y)//link操作即为链接两个树，那么要先进性expose操作，把到路径上的边都变为实边，这样才能进行把x调整到根部，进而通过更改祖先来进行链接
{
    ChangeRoot(x);
    Splay(x);
    tree[x].pre=y;
}

void Cut(int x,int y)
{
    ChangeRoot(y);
    Splay(x);
    if(tree[x].ch[0])
    {
        tree[tree[x].ch[0]].pre=tree[x].pre;
        tree[x].pre=tree[x].ch[0]=0;
    }
    else tree[x].pre=0;
}

int LCA(int x,int y)
{
    int p=Head(Expose(x));
    int q=Expose(y),w=Head(q);
    if(p==w) return q;
    return 0;
}

struct data
{
    int x,y;
} a[maxn];

int main()
{
    int n,m;
    while(scanf("%d",&n)==1)
    {
        for(int i=1; i<n; i++) scanf("%d%d",&a[i].x,&a[i].y);
        val[0]=val[n+1]=-INF;
        for(int i=1; i<=n; i++) scanf("%d",&val[i]);
        DynamicTree(n+1);
        for(int i=1; i<n; i++) Link(a[i].x,a[i].y);
        scanf("%d",&m);
        for(int i=1; i<=m; i++)
        {
            int c;
            int x,y,val;
            scanf("%d",&c);
            if(c==1)
            {
                scanf("%d%d",&x,&y);
                if(!LCA(x,y)) Link(x,y);
                else printf("-1\n");
            }
            else if(c==2)
            {
                scanf("%d%d",&x,&y);
                if(LCA(x,y) && x!=y) Cut(y,x);
                else printf("-1\n");
            }
            else if(c==3)
            {
                scanf("%d%d%d",&val,&x,&y);
                if(LCA(x,y)) Change(x,y,val);
                else printf("-1\n");
            }
            else if(c==4)
            {
                scanf("%d%d",&x,&y);
                int tmp=LCA(x,y);
                if(tmp) printf("%d\n",AskMax(x,y));
                else printf("-1\n");
            }
        }
        printf("\n");
    }
    return 0;
}

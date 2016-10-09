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
#include <assert.h>
#include <bitset>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int mod = 2012;
const int N = 2000010;
struct node{
    int stp, cnt, sum;
    int rtn; //number of right set
    int flag; // 标记该点应该被加多少次
    node *nxt[52], *pre;
    void clear()
    {
        pre = 0;
        cnt = sum = stp = 0;
        flag = rtn = 0;
        memset(nxt, 0, sizeof(nxt));
    }
}*root, *last, lt[N], *cur;
//第0号点为root点，不需要计算答案
//root -> 根节点
//last -> 当前字符串尾巴的节点/状态机的终结状态
//cur -> node池中的下一个点
//指针往回跳的时候，一定要注意指针为空的情况
void init()
{
    cur = lt;
    root = last = cur++;
    root->clear();
}
void insert(int w)
{
    node *p = last;
    node *np = cur++;np->clear();
    np->stp = p->stp+1;
    while(p && !p->nxt[w]) p->nxt[w] = np, p = p->pre;
    if(p == 0) np->pre = root;
    else {
        node *q = p->nxt[w];
        if(p->stp + 1 == q->stp) np -> pre = q;
        else {
            node *nq = cur++;
            nq->clear();
            memcpy(nq->nxt, q->nxt, sizeof(q->nxt));
            nq->stp = p->stp+1;
            nq->pre = q->pre;
            np->pre = q->pre = nq;
            while(p && p->nxt[w] == q) p->nxt[w] = nq, p = p->pre;
        }
    }
    last = np;
}
int c[N];
int idx[N];
void Sort(int tot)
{
    for(int i = 0; i < tot; i++) c[i] = 0;
    for(int i = 0; i < tot; i++) c[lt[i].stp]++;
    for(int i = 1; i < tot; i++) c[i] += c[i-1];
    for(int i = 0; i < tot; i++) idx[--c[lt[i].stp]] = i;
}
//得到每个集合right集合的大小
///需要先调用Sort函数
void getright(char s[], int n)
{
    node *rt = root;
    for(int i = 0; i < n; i++)
    {
        int id = s[i] - 'a';
        rt = rt->nxt[id];
        rt -> rtn++;
    }
    for(int i = cur-lt-1; i >= 1; i--)
    {
        rt = &lt[idx[i]];
        rt -> pre -> rtn += rt -> rtn;
    }
}
char s[N];
char s2[N];
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
    init();
    scanf("%s", s);
    int len = strlen(s);
    for(int i = 0; i < len; i++) insert(s[i]-'a');
    int tot = cur - lt;
    Sort(tot);
    getright(s, len);
    int q;
    scanf("%d", &q);
    while(q--)
    {
        scanf("%s", s2);
        int n = strlen(s2);
        node *t = root;
        int l = 0;
        int ans = 0;
        for(int i = 0; i < n ;i++)
        {
            int id = s2[i]-'a';
            if(t->nxt[id]) t = t->nxt[id], l++;
            else{
                while(t && !t->nxt[id]) t = t->pre;
                if(!t) t = root, l = 0;
                else l = t->stp;
                if(t->nxt[id]) t = t->nxt[id], l++;
                else l = 0;
            }
        }
        for(int i = 0; i < n ;i++)
        {
            int id = s2[i]-'a';
            if(t->nxt[id]) t = t->nxt[id], l++;
            else{
                while(t && !t->nxt[id]) t = t->pre;
                if(!t) t = root, l = 0;
                else l = t->stp;
                if(t->nxt[id]) t = t->nxt[id], l++;
                else l = 0;
            }
            while(l >= n && t->pre->stp >= n) t = t -> pre;
            if(l >= n && t->stp >= n && t->flag != q + len)
            {
                t->flag = q + len;
                ans += t->rtn;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}


/*
*	可持久化字典树，由于回文串的长度最多20，我们可以对不同长度的回文串都建立一棵字典树，之所以要这样做
*	是因为由于查询的只是后半部分，插入字典树的也应该是后半部分，那么查询[l,r]区间的合法串就不好得出答案，
*	但是如果字典树中的串全是相同长度的话，对于询问[l,r]我们就可以每次枚举长度，查询长度为1的在[l,r]区间的
*	合法数量,查询长度为2的在[l+1,r]区间的合法数量,3的[l+2,r]...20的[l+19,r]。
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
#include <bitset>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PII;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
const LL mod = 1e9+7.5;
const LL N = 100010;
struct node{
    int v;
    int nxt[5];
}lt[N*30];
int tot = 0;//
int Tr[N][21];//
bool pre[N][21];//
int newnode(int rt = -1)
{
    if(rt == -1){
        lt[tot].v = 0;
        memset(lt[tot].nxt, -1, sizeof(lt[tot].nxt));
        return tot++;
    }else{
        lt[tot].v = lt[rt].v;
        memcpy(lt[tot].nxt, lt[rt].nxt, sizeof(int)*5);
        return tot++;
    }
}
int insert(int rt, char* s, int n)
{
    int crt = newnode(rt);
    int rrt = crt;
    for(int i = 0; i < n; i++)
    {
        int id = s[i] - 'a';
        if(lt[crt].nxt[id] == -1) lt[crt].nxt[id] = newnode(-1);
        else lt[crt].nxt[id] = newnode(lt[crt].nxt[id]);
        crt = lt[crt].nxt[id];
        lt[crt].v++;
    }
    return rrt;
}
int query(int lrt, char* s, int n)
{
    for(int i = 0; i < n; i++)
    {
        int id = s[i] - 'a';
        if(lt[lrt].nxt[id] == -1) return 0;
        lrt = lt[lrt].nxt[id];
        //rrt = lt[rrt].nxt[id];
    }
    return lt[lrt].v;
//    return lt[rrt].v - lt[lrt].v;
}
int getid(int l, int r)
{
    return (l+r+1)>>1;
}
char s[N];
char t[111];
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
    while(~scanf("%s", s))
    {
        tot = 0;
        memset(pre, 0, sizeof(pre));
        int n = strlen(s);
        for(int i = 0; i < n; i++)
        {
            for(int j = 1; j <= 20; j++) Tr[i][j] = (i == 0 ? newnode() : Tr[i-1][j]);
            pre[i][1] = pre[i][0] = 1;
            Tr[i][1] = insert(Tr[i][1], s+i, 1);
            for(int j = 2; j <= 20 && i - j + 1 >= 0; j++)
            {
                if(pre[i-1][j-2] && s[i] == s[i-j+1]){
                    int id = getid(i-j+1, i);
                    Tr[i][j] = insert(Tr[i][j], s+id, (j+1)/2);
                    pre[i][j] = true;
                }
            }
        }
        int q;
        scanf("%d", &q);
        while(q--)
        {
            int l, r;
            scanf("%d%d%s", &l, &r, t);
            r--, l--;
            int len = strlen(t);
            int ans = 0;
            for(int i = 1; i <= 20; i++)
            {
                if(l + i - 2 >= r) break;
                ans += query(Tr[r][i], t, len);
                if(l+i-2 >= 0) ans -= query(Tr[l+i-2][i], t, len);
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}


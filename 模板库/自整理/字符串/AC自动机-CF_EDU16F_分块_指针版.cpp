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
const int N = 300010;
const int SN = sqrt(N);
//const int SN = 1101;
struct Trie{
    int ch[26];
    int val;
    int pre;
    int last;
}pl[N*20];
int tot;
Trie* newnode()
{
    memset(pl[tot].ch, 0, sizeof(pl[tot].ch));
    pl[tot].val = pl[tot].pre = pl[tot].last = 0;
    return &pl[tot++];
}
struct ACam{
    int sum;
    Trie *lt;//包含Trie数组上的某段区间
    void init()
    {
        sum = 0;
        this -> lt = ::pl+tot;//为了让每个自动机的Trie编号都从0开始，方便处理
        newnode();
    }
    void insert(char *s, int n, int v)
    {
        int rt = 0;
        for(int i = 0; i < n; i++)
        {
            int id = s[i] - 'a';
            if(lt[rt].ch[id] == 0) lt[rt].ch[id] = newnode()-lt;
            rt = lt[rt].ch[id];
        }
        lt[rt].val += v;
    }
    void print(int j, int& ans)
    {
        if(j)
        {
            ans += lt[j].val;
            print(lt[j].last, ans);
        }
    }
    int findStr(char *s, int n)
    {
        int ans = 0;
        int rt = 0;
        for(int i = 0; i < n; i++)
        {
            int id = s[i] - 'a';
            while(rt && !lt[rt].ch[id]) rt = lt[rt].pre;
            rt = lt[rt].ch[id];
            if(lt[rt].val) print(rt, ans);
            else if(lt[rt].last) print(lt[rt].last, ans);
        }
        return ans;
    }
    void getFail()
    {
        queue<int> q;
        lt[0].pre = 0;
        for(int i = 0; i < 26; i++)
        {
            int u = lt[0].ch[i];
            if(u) { lt[u].pre = 0; q.push(u); lt[u].last = 0; }
        }
        while(!q.empty())
        {
            int r = q.front(); q.pop();
            for(int c = 0; c < 26; c ++)
            {
                int u = lt[r].ch[c];
                if(!u){
//                    lt[r].ch[c] = lt[lt[r].pre].ch[c];
                    continue;
                }
                q.push(u);
                int v = lt[r].pre;
                while(v && !lt[v].ch[c]) v = lt[v].pre;
                lt[u].pre = lt[v].ch[c];
                lt[u].last = lt[lt[u].pre].val ? lt[u].pre : lt[lt[u].pre].last;
            }
        }
    }
}ac[SN];
int act;
void init()
{
    tot = 0;
    act = 0;
}
char s[N];
char s2[N];
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
//    cout<<SN<<endl;
    init();
    int q;
    scanf("%d", &q);
    ac[0].init();
    while(q--)
    {
        int ty;
        scanf("%d%s", &ty, s);
        int n = strlen(s);
        if(ty == 3){
            LL ans = 0;
            for(int i = 0; i <= act; i++)
            {
                ans += ac[i].findStr(s, n);
            }
            cout<<ans<<endl;
        }else{
            if(ac[act].sum > SN) ac[++act].init();
            ac[act].sum += n;
            ac[act].insert(s, n, ty==1?1:-1);
            ac[act].getFail();
        }
    }
    return 0;
}

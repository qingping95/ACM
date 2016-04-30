/*
* 题意：给出n个(a, b), m个(c, d, e)，构造一个集合(a, c, d)当存在b=e的时候，
* 问构造出来的集合中有多少个TOP三元组(不存在三个元素都大于该三元组的三元组)
*
* 首先将m个三元组排序，第一关键字为ci，第二关键字为di，从大到小排序。
* 然后将ai和bi处理为一个vector，用二维树状数组搞一搞即可
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
//#include <unordered_map>
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
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
#define N 100100
int man, mam;
int c[1110][1110];
void Update(int x, int y, int a)
{
    for(int i = x; i ; i -= i & -i)
        for(int j = y; j ; j -= j & -j)
            c[i][j] = max(c[i][j], a);
}
int getmax(int x, int y)
{
    int res = 0;
    for(int i = x; i < man + 10; i += i & -i)
        for(int j = y; j < mam + 10; j += j & -j)
            res = max(res, c[i][j]);
    return res;
}

template<class T>
inline bool read(T &n){
    T x = 0, tmp = 1; char c = getchar();
    while ((c < '0' || c > '9') && c != '-' && c != EOF) c = getchar();
    if (c == EOF) return false;
    if (c == '-') c = getchar(), tmp = -1;
    while (c >= '0' && c <= '9') x *= 10, x += (c - '0'), c = getchar();
    n = x*tmp;
    return true;
}
struct node
{
    int c, d, e;
    void input()
    {
        read(c);
        read(d);
        read(e);
//        scanf("%d%d%d", &c, &d, &e);
    }
    bool operator<(const node& o)const
    {
        return c > o.c || (c == o.c && d > o.d);
    }
    bool cmp(const node& o)const
    {
        return c == o.c && d == o.d;
    }
}E[N];
vector<int> B[N];
PII maB[N];
PII BB[N];
int main()
{
//    Open();
    int T;//scanf("%d", &T);
    read(T);
    int cas = 1;
    while(T--)
    {
        memset(c, 0, sizeof(c));
        memset(maB, 0, sizeof(maB));
        int n, m;
        read(n);read(m);
        int mab = 0;
//        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++)
        {
            int a, b;
//            scanf("%d%d", &a, &b);
            read(a);read(b);
            mab = max(mab, b);
            BB[i] = PII(a, b);
            B[b].push_back(a);
        }
        for(int i = 1; i <= mab; i++)
        {
            if(B[i].size() == 0) continue;
            sort(B[i].begin(), B[i].end(), greater<int>());
            int j = 0;
            while(j < B[i].size() && B[i][j] == B[i][0]) j++;
            maB[i] = PII(B[i][0], j);
        }
        man = mam = 0;
        for(int i = 0; i < m; i++)
        {
            E[i].input();
            man = max(man, E[i].c);
            mam = max(mam, E[i].d);
        }
        sort(E, E+m);
        LL ans = 0;
        for(int i = 0; i < m; i++)
        {
            int ed = i; int ma = 0;
            while(ed < m && E[ed].cmp(E[i]))
            {
                int b = E[ed].e;
                ma = max(ma, maB[b].first);
                ed++;
            }
            LL sum = 0;
            if(ma != 0)
            {
                for(int j = i; j < ed; j++)
                {
                    int b = E[j].e;
                    if(ma == maB[b].first) sum += maB[b].second;
                }
                int exitma = getmax(E[i].c, E[i].d);
                if((exitma != 0 && exitma < ma) || exitma == 0)
                {
                    ans += sum;
                }
                Update(E[i].c, E[i].d, ma);
            }
            i = ed-1;
        }
        for(int i = 0; i < n; i++)
            B[BB[i].second].clear();
        printf("Case #%d: %I64d\n",cas++, ans);
    }
    return 0;
}

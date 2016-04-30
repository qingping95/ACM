/*
* 题意：一个狗国家的狗国王有一个装糖的盒子，每颗糖有两个属性p,q，分别代表甜度和咸度，每只狗
*		对于甜度和咸度的偏爱度不一样，所以每条狗有两个参数x,y，每颗糖对于特定的狗的
*		美味度等于p*x+q*y。现在有50000个操作，分为三种：
*			将新的糖(p,q)放入盒子中
*			将盒子中存在的糖(p,q)吃掉
*			给出一条狗的参数(x,y)，询问当前存在的糖的最大美味度。
* 
* 做法：这个题是2014年广州现场赛的A题，模拟赛做的时候虽然推出了公式，但是并没有发现最优解为凸包
* 的性质，于是一直到比赛结束都没有做出这个题，但是当时最诡异的是，有一个排名比较靠后的队伍在
* 16分钟就将此题一血拿走，整场比赛解出此题的不过10支左右队伍。当比赛结束的时候，看了一下别人的
* 代码，发现我能在hust上面看到的代码居然都是暴力水过去的！…我觉得好醉啊…，继续在网上买了搜索此
* 题题解，发现都是直接n2暴力来一遍的…，仔细想了一下，n2暴力的话，复杂度在最坏的情况下
* 为25000∗25000，大概6∗108左右，这种复杂度我是无论如何都不敢敲的…，但是如果数据是随机生成的
* 话，询问，插入，删除操作只占50000∗1/3，那么这个复杂度以当时的30s的时限来说，还是可以跑出结
* 果的…于是这么一个现场10支队伍过的难题，就被这样水过去了。
* 
* 此题虽然能够暴力水过去，但是无疑思考更一般的通解是很有必要的。 
* 后来听说翁教他们当时是分块暴力重建凸包过去的，我就去请教了一下翁教，终于由之前的公式发现了
* 最优解在凸包上的这一重大性质。 
* 此题正解应该是cdq分治+维护动态凸包，或者分块暴力重建凸包。而我的做法是CDQ维护凸包。具体是这样的：
* 
* 首先得先分析出最优解一定在凸包上这一性质：
* 考虑这样的两颗糖果A(p1,q1),B(p2,q2)，假设A比B优，那么存在这样的表达式：p1∗x+q1∗y≥p2∗x+q2∗y,
* 变形一下式子之后得到这样的表达式：p2−p1q2−q1≤−yx(x>0且q2>q1)，也就是说，只要A，B满足上述式
* 子就一定存在A比B更优。我们可以将q看成横坐标，p看成纵坐标，将每一颗糖看成一个点。假设K=−yx，
* 考虑这样的三个点A(q1,p1),B(q2,p2),C(q3,p3)。 设AB的斜率为k1, BC的斜率为k2, 则A比B优
* 需要满足k1<K，B比C更优需要满足k2<K，那么B比A,C都优的话，就需要满足k2<K<k1，也就是说需要满
* 足k2<k1，这种情况只有在三个点构成的图为上凸壳的时候才满足，如果图形是下凸壳的话，中间的B点
* 一定不可能比AC都优。 
* 于是这里可以知道的是对于特定的K来说，最优解一定在可选点构成的上凸包上面，由于之前限定
* 了(x>0且q2>q1)当这个条件改变的时候，最优解也可能在下凸包上。于是我们只需要维护一个动态的凸包，
* 对于每一个询问，在相应的上凸壳或下凸壳上二分斜率就能找到最优解。
* 
* 至于这里如何维护凸包的话，如果做过维护动态凸包的类似题的话，此时肯定就迎刃而解。
* 
* 我的方法是用CDQ分治做这个凸包。 
* 对于一个区间[l,r]，我首先将存在于[l, mid]中的点集取出来做出一个凸包，对于[l, mid]之间的
* ‘-1’操作，如果删除的是[l, mid]之间的点，那么就正常的删点；如果删的点是l左边的点，那么这个删除操作
* 就忽略。然后利用构建好的这个凸包去更新[mid+1, r]中的所有询问操作。
* 
* 看似好像没问题，但是实际上这是错的… 
* 因为在区间[mid+1, r]中可能存在删除操作，删掉了之前构建好的凸包上面的点，导致更新后面的询问出现错误，
* 那么我们还需要做的就是在删除点之后，继续维护这个凸包。对于[mid+1, r]中的加点操作，我们是可以忽略的，
* 因为后面更新右区间的时候也会更新的。 
* 删除点的维护操作是这样的，首先现在凸包上面找到这个点，如果没找到说明不会改变凸包，但是
* 也要将这个点标记为已删除的点。如果这个点在凸包上面，那么找到这个点的在凸包上的前驱和后继，
* 将该点删除，然后在最开始构筑凸包的那个数组中，重新构造前驱到后继之间的凸包，最后在加上后面的凸包
* 即可。 
* 做完这一步的话，就可以正常的更新所有询问咯~ 
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
//#include <unordered_map>
#define N 50010
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const LL INF=0x3f3f3f3f3f3f3f3fLL;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
struct Point
{
    int x, y;
    int ty, opid;
    bool operator<(const Point& o)const{
        return x < o.x || (x == o.x && y < o.y);
    }
}can[N], p1[N], p2[N], pt[N], tmp[N];
int n;
int m1, m2;
map<PII, int> mp;
LL ans[N];
bool vis[N];
int cnt;

LL Cross(Point A, Point B){return (LL)A.x * B.y - (LL)A.y * B.x;}
Point operator-(Point A, Point B) {return (Point){A.x - B.x, A.y - B.y};}
void getConvex(int n)
{
    m1 = m2 = 0;
    sort(pt, pt+n);
    for(int i = 0; i < n; i++)
    {
        while(m1 > 1 && Cross(pt[i] - p1[m1-2], p1[m1-1] - p1[m1-2]) <= 0) m1--;
        p1[m1++] = pt[i];
    }
    for(int i = n-1; i >= 0; i--)
    {
        while(m2 > 1 && Cross(pt[i] - p2[m2-2], p2[m2-1] - p2[m2-2]) <= 0) m2--;
        p2[m2++] = pt[i];
    }
}

void updateConvex(Point deltP)
{
    int idx = -1;
    for(int i = 0; i < m1; i++)
    {
        if(p1[i].x == deltP.x && p1[i].y == deltP.y){idx = i;break;}
    }
    if(idx != -1)
    {
        int l = idx - 1, r = idx + 1;
        int tail = 0;
        for(int i = r+1; i < m1; i++)
            tmp[tail++] = p1[i];
        int lpt, rpt;
        if(l == -1) lpt = -1;
        if(r == m1) rpt = cnt - 1;
        for(int i = 0; i < cnt; i++){
            if(l != -1 && pt[i].x == p1[l].x && pt[i].y == p1[l].y && vis[pt[i].opid]) lpt = i;
            if(r != m1 && pt[i].x == p1[r].x && pt[i].y == p1[r].y && vis[pt[i].opid]) rpt = i;
        }
        ///
        m1 = l+1;
        for(int i = lpt + 1; i <= rpt; i++)
        {
            if(vis[pt[i].opid] == 0) continue;
            while(m1 > 1 && Cross(pt[i] - p1[m1-2], p1[m1-1] - p1[m1-2]) <= 0) m1--;
            p1[m1++] = pt[i];
        }
        for(int i = 0; i < tail; i++)
            p1[m1++] = tmp[i];
    }

    idx = -1;
    for(int i = 0; i < m2; i++)
    {
        if(p2[i].x == deltP.x && p2[i].y == deltP.y) {idx = i;break;}
    }
    if(idx != -1)
    {
        int l = idx - 1, r = idx + 1;
        int tail = 0;
        for(int i = r+1; i < m2; i++)
            tmp[tail++] = p2[i];
        int lpt, rpt;
        if(l == -1) lpt = cnt;
        if(r == m2) rpt = 0;
        for(int i = 0; i < cnt; i++){
            if(l != -1 && pt[i].x == p2[l].x && pt[i].y == p2[l].y && vis[pt[i].opid]) lpt = i;
            if(r != m2 && pt[i].x == p2[r].x && pt[i].y == p2[r].y && vis[pt[i].opid]) rpt = i;
        }
        ///
        m2 = l+1;
        for(int i = lpt - 1; i >= rpt; i--)
        {
            if(vis[pt[i].opid] == 0) continue;
            while(m2 > 1 && Cross(pt[i] - p2[m2-2], p2[m2-1] - p2[m2-2]) <= 0) m2--;
            p2[m2++] = pt[i];
        }
        for(int i = 0; i < tail; i++)
            p2[m2++] = tmp[i];
    }
}

void updateans(int x, int y, int idx)
{
    Point o =(Point){x, -y};
    if(m1 <= 2){
        for(int i = 0; i < m1; i++)
            ans[idx] = max(ans[idx], (LL)p1[i].x * y + (LL)p1[i].y * x);
    }else{
        int lb = -1, ub = m1-1;
        while(lb + 1 < ub)
        {
            int mid = lb + ub >> 1;
            if(Cross(p1[mid+1] - p1[mid], o) <= 0) lb = mid;
            else ub = mid;
        }
        lb = max(0, lb);
        ans[idx] = max(ans[idx], (LL)p1[lb].x * y + (LL)p1[lb].y * x);
        if(ub < m1) ans[idx] = max(ans[idx], (LL)p1[ub].x * y + (LL)p1[ub].y * x);
    }
    if(m2 <= 2) {
        for(int i = 0; i < m2; i++)
            ans[idx] = max(ans[idx], (LL)p2[i].x * y + (LL)p2[i].y * x);
    }else{
        int lb = -1, ub = m2 - 1;
        while(lb + 1 < ub){
            int mid = lb + ub >> 1;
            if(Cross(p2[mid+1] - p2[mid], o) <= 0) lb = mid;
            else ub = mid;
        }
        lb = max(0, lb);
        ans[idx] = max(ans[idx],(LL)p2[lb].x * y + (LL)p2[lb].y * x);
        if(ub < m2) ans[idx] = max(ans[idx], (LL)p2[ub].x * y + (LL)p2[ub].y * x);
    }
}
void divide(int l, int r)
{
    if(l >= r) return ;
    int mid = l + r >> 1;

    for(int i = l; i <= mid; i++) vis[i] = 0;
    for(int i = l; i <= mid; i++)
    {
        if(can[i].ty == 1) vis[i] = 1;
        if(can[i].ty == -1 && can[i].opid >= l && can[i].opid <= mid) vis[can[i].opid] = 0;
    }
    cnt = 0;
    for(int i = l; i <= mid; i++)
        if(vis[i]) pt[cnt++] = can[i];

    getConvex(cnt);

    for(int i = mid+1; i <= r; i++){
        if(can[i].ty == 0) updateans(can[i].x, can[i].y, i);
        if(can[i].ty == -1 && can[i].opid >= l && can[i].opid <= mid && vis[can[i].opid]){
            vis[can[i].opid] = 0;
            updateConvex(can[can[i].opid]);
        }
    }

    divide(l, mid);
    divide(mid+1, r);
}
int main()
{
    Open();

    while(true)
    {
//        read(n);
        scanf("%d", &n);
        if(n == 0) break;
        mp.clear();
        for(int i = 0; i < n; i++)
        {
            int ty, x, y;
//            read(ty);read(x);read(y);
            scanf("%d%d%d", &ty, &x, &y);
            can[i] = (Point){y, x, ty, i};
            if(ty == 0) swap(can[i].x, can[i].y), ans[i] = -INF;
            if(ty == 1) mp[PII(y, x)] = i;
            if(ty == -1) can[i].opid = mp[PII(y, x)];
        }
        divide(0, n-1);
        for(int i = 0; i < n; i++)
        {
            if(can[i].ty == 0)
                printf("%I64d\n", ans[i]);
        }
//        cout<<endl;
    }
    return 0;
}

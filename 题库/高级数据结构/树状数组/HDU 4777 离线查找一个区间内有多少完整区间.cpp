/*
* ������Ԥ�����L[i],R[i]���飬�ֱ��ʾС��i������һ����i�����ʵ��±꣬�ʹ���i���ǰ��һ����i�����ʵ��±ꡣ
* ����˼·���Ǽ���ÿ�������ж��ٸ����ܵ��ˣ�����һ��ѯ�ʣ����ȼ�ȥ�������(L<=i<=R)����L[i]>=L���ж��ٸ���
* R[i]<=R���ж��ٸ���ȫ�����������������������L[i],R[i]������������������ټ�ȥ��Щ�����ˡ� 
* ����ÿһ��i��˵������������[L[i], i], [i, R[i]], [L[i], R[i]], �𰸾��ǵ�һ��������+�ڶ���-������
* �ȶ�������ѯ��[L,R], �ٽ���������������Ҷ˵�ȫ��������״������(+1)����ô��ֻ��Ҫ������[L, R]���ж��ٸ�1������,
* ������������㵽��˵�С��L�����䣬��������ֻ��Ҫ��ɨ��i֮�󣬽���iΪ��˵��������Ҷ˵�ȫ����ȥ(-1)���ɡ�
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 200210
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int MAXN = 222222;
int last[MAXN];
int L[MAXN] , R[MAXN];
int f[MAXN];
int zhishu[666];
int tail;
int n,m;
int prm[888+11];
bool visP[888+11];
int pn;
void getPrm(){
    for(int i=2;i<=888;i++){
        if(!visP[i]){
            prm[pn++] = i;
            for(int j=i;j<=888;j+=i) visP[j]=true;
        }
    }
}

void fenjie(int x){
    tail=0;
    for(int i=0;i<pn && prm[i] * prm[i] <= x;i++){
        if(x % prm[i] == 0){
            zhishu[tail++] = prm[i];
            while(x % prm[i] == 0) x /= prm[i];
        }
    }
    if(x > 1) zhishu[tail ++ ] = x;
    int sldfkjadsf=1;
}
void getLR(){
    for(int i=1;i<=n;i++){
        fenjie(f[i]);
        int maxer = 0;
        for(int j=0;j<tail;j++){
            maxer = max(maxer , last[zhishu[j]] );
        }
        L[i] = maxer;
        for(int j=0;j<tail;j++){
            last[zhishu[j]] = i;
        }
    }
    fill(last+1 , last+MAXN , n+1 );
    for(int i=n;i>=1;i--){
        fenjie(f[i]);
        int miner = n+1;
        for(int j=0;j<tail;j++){
            miner = min(miner , last[zhishu[j]] );
        }
        R[i] = miner;
        for(int j=0;j<tail;j++){
            last[zhishu[j]] = i;
        }
    }
}
int c1[N], c2[N];
vector<int> vli[N];
vector<int> vlr[N];
vector<PII > vqu[N];
int ans[N];
void add(int c[], int x, int val)
{
    if(x == 0) return ;
    for(int i = x; i <= n+10; i += (-i) & i) c[i] += val;
}
int getsum(int c[], int x)
{
    int res = 0;
    for(int i = x; i > 0; i -= (-i) & i) res += c[i];
    return res;
}
int main()
{
    getPrm();
    while(scanf("%d%d",&n,&m)==2){
        memset(last , 0 , sizeof(last));
        memset(c1, 0, sizeof(c1));
        memset(c2, 0, sizeof(c2));
        for(int i=1;i<=n;i++){
            vli[i].clear();
            vlr[i].clear();
            vqu[i].clear();
            scanf("%d",&f[i]);
        }
        getLR();
        for(int i=1;i<=n;i++){
            if(L[i] != 0){
                vli[L[i]].push_back(i);
                vlr[L[i]].push_back(R[i]);
                add(c1, i, 1);
                add(c2, R[i], 1);
            }
            vli[i].push_back(R[i]);
            add(c1, R[i], 1);
        }
        for(int i = 1; i <= m; i++)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            vqu[l].push_back(PII(r, i));
        }
        for(int i = 1; i <= n; i++)
        {
            for(int j = 0; j < vqu[i].size(); j ++)
            {
                int r = vqu[i][j].first, idx = vqu[i][j].second;
                ans[idx] = (r - i + 1) - (getsum(c1, r) - getsum(c1, i - 1)) + (getsum(c2, r) - getsum(c2, i - 1));
            }
            for(int j = 0; j < vli[i].size(); j++){
                add(c1, vli[i][j], -1);
            }
            for(int j = 0; j < vlr[i].size(); j++){
                add(c2, vlr[i][j], -1);
            }
        }
        for(int i = 1;i <= m; i++)
            printf("%d\n", ans[i]);
    }
    return 0;
}

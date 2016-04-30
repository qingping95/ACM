#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
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
const double PI = acos(-1.0);
struct complex
{
    double r,i;
    complex(double _r = 0,double _i = 0)
    {
        r = _r; i = _i;
    }
    complex operator +(const complex &b)
    {
        return complex(r+b.r,i+b.i);
    }
    complex operator -(const complex &b)
    {
        return complex(r-b.r,i-b.i);
    }
    complex operator *(const complex &b)
    {
        return complex(r*b.r-i*b.i,r*b.i+i*b.r);
    }
};
void change(complex y[],int len)
{
    int i,j,k;
    for(i = 1, j = len/2;i < len-1;i++)
    {
        if(i < j)swap(y[i],y[j]);
        k = len/2;
        while( j >= k)
        {
            j -= k;
            k /= 2;
        }
        if(j < k)j += k;
    }
}
void FFT(complex y[],int len,int on)
{
    change(y,len);
    for(int h = 2;h <= len;h <<= 1)
    {
        complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j = 0;j < len;j += h)
        {
            complex w(1,0);
            for(int k = j;k < j+h/2;k++)
            {
                complex u = y[k];
                complex t = w*y[k+h/2];
                y[k] = u+t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    if(on == -1)
        for(int i = 0;i < len;i++)
            y[i].r /= len;
}
const int N = 200020;
int pri[N];
int pn;
bool nop[N];
void get_prime(int n)
{
    for(int i = 2; i < n; i++)
    {
        if(nop[i]) continue;
        pri[pn++] = i;
        for(int j = i; j < n; j += i)
            nop[j] = 1;
    }
}
//a, b:卷积数组，res结果数组，n,m 数组a,b的长度
complex x1[N], x2[N];
int num[N];
LL FFTstarto(vector<int>& v, LL *res)
{
    if(v.size() == 0) return 0;
    int len1 = v[v.size() - 1] + 1;
    int len = 1;
    while(len < len1 * 2) len <<= 1;
    for(int i = 0; i < len; i++) num[i] = 0;
    for(int i = 0; i < v.size(); i++)
    {
        num[v[i]]++;
    }
    for(int i = 0; i < len; i++)
    {
        if(i < len1) x1[i] = complex(num[i], 0);
        else x1[i] = complex(0, 0);
        if(i < len1) x2[i] = complex(num[i], 0);
        else x2[i] = complex(0, 0);
    }

    FFT(x1, len, 1);
    FFT(x2, len, 1);
    for(int i = 0; i < len; i++)
        x1[i] = x1[i] * x2[i];
    FFT(x1, len, -1);
    for(int i = 0; i < len; i++)
        res[i] = (LL)(x1[i].r + 0.5);
    for(int i = 0; i < v.size(); i++)
        res[v[i]+v[i]]--;
    for(int i = 0; i < len; i++)
        res[i] /= 2;
    LL ans = 0;
    for(int i = 0; i < pn && pri[i] < len; i++)
        ans += res[pri[i]];
    return ans;
}
vector<int> G[N], all, sub;
int root, s[N], f[N];
LL res[N];
bool vis[N];
LL ans;
int maxn;
int getroot(int now, int fa, int sz)
{
    int cnt = 1;
    int mx = 0;
    for(int i = 0; i < G[now].size(); i++)
    {
        int to = G[now][i];
        if(to == fa || vis[to]) continue;
        f[to] = getroot(to, now, sz);
        mx = max(mx, f[to]);
        cnt += f[to];
    }
    mx = max(mx, sz - cnt);
    if(mx < maxn)
    {
        maxn = mx, root = now;
        for(int i = 0; i < G[now].size(); i++)
        {
            int to = G[now][i];
            if(vis[to]) continue;
            if(to == fa){s[to] = sz - cnt; continue;}
            s[to] = f[to];
        }
    }
    return cnt;
}
void dfsgao(int u, int fa, int dis)
{
    all.push_back(dis);
    sub.push_back(dis);
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(vis[v] || v == fa) continue;
        dfsgao(v, u, dis+1);
    }
}
void dfs(int u)
{
    maxn = INF;getroot(u, 0, s[u]);
    int trt = root;
    vis[trt] = 1;
    all.clear();
    all.push_back(0);
//    cout<<trt<<":"<<endl;
    for(int i = 0; i < G[trt].size(); i++)
    {
        int v = G[trt][i];
        if(vis[v]) continue;
        sub.clear();
        dfsgao(v, trt, 1);
        sort(sub.begin(), sub.end());
//        cout<<v<<":"<<endl;
//        for(int j = 0; j < sub.size(); j++)
//            cout<<sub[j]<<" ";
//        cout<<endl;
        ans -= FFTstarto(sub, res);
    }
    sort(all.begin(), all.end());
//    for(int j = 0; j < all.size(); j++)
//        cout<<all[j]<<" ";
//    cout<<endl;
//    cout<<endl;
    ans += FFTstarto(all, res);

    for(int i = 0 ; i < G[trt].size(); i++)
    {
        int v = G[trt][i];
        if(vis[v]) continue;
        dfs(v);
    }
}
int main()
{
//    Open();
    int n;
    scanf("%d", &n);
    get_prime(n);
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    ans = 0;
    s[1] = n;
    dfs(1);
//    cout<<ans<<endl;
    printf("%.6f\n", (double)ans / ((LL)n*(n-1)/2));
    return 0;
}

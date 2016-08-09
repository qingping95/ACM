/*以下代码中n代表方程个数，m代表未知数个数，f[]数组用来判断哪些未知数是
* 变元，x[]数组用来存求得的解。
* 
* 该代码只在解为int的时候使用，如果有double解，要注意修改x数组的类型
*/
int gcd(int a,int b)  
{  
    return b ? gcd(b,a%b):a;  
}  
  
int lcm(int a,int b)  
{  
    return a / gcd(a,b) * b;  
}  
  
/**n个方程，m个未知数，r代表当前处理的行，c代表当前处理的列*/  
void Gauss(int a[][N],int n,int m,int &r,int &c)  
{  
    r = c = 0;  
    for(; r<n && c<m; r++,c++)  
    {  
        int maxi = r;  
        for(int i=r+1; i<n; i++)  
            if(abs(a[i][c]) > abs(a[maxi][c]))  
                maxi = i;  
        if(maxi != r)  
        {  
            for(int i=r; i<m+1; i++)  
                swap(a[r][i],a[maxi][i]);  
        }  
        if(a[r][c] == 0)  
        {  
            r--;  
            continue;  
        }  
        for(int i=r+1; i<n; i++)  
        {  
            if(a[i][c] != 0)  
            {  
                int x = abs(a[i][c]);  
                int y = abs(a[r][c]);  
                int LCM = lcm(x,y);  
                int tx = LCM / x;  
                int ty = LCM / y;  
                if(a[i][c] * a[r][c] < 0)  
                    ty = -ty;  
                for(int j=c; j<m+1; j++)  
                    a[i][j] = a[i][j] * tx - a[r][j] * ty;  
            }  
        }  
    }  
}  
  
int Rewind(int a[][N],int x[],bool f[],int n,int m,int r,int c)  
{  
    for(int i=r; i<n; i++)  
        if(a[i][c] != 0)  
            return -1;  
    if(r < m)  
    {  
        memset(f,1,sizeof(f));  
        for(int i=r-1; i>=0; i--)  
        {  
            int id = 0;  
            int cnt = 0;  
            for(int j=0; j<m; j++)  
            {  
                if(a[i][j] != 0 && f[j])  
                {  
                    cnt++;  
                    id = j;  
                }  
            }  
		//说明此时有自由元
            if(cnt > 1) continue;  
            int t = a[i][m];  
            for(int j=0; j<m; j++)  
            {  
                if(a[i][j] != 0 && j != id)  
                    t -= a[i][j] * x[j];  
            }  
            x[id] = t / a[i][id];  
            f[id] = 0;  
        }  
        return m - r;  
    }  
    for(int i=r-1; i>=0; i--)  
    {  
        int t = a[i][c];  
        for(int j=i+1; j<c; j++)  
        {  
            if(a[i][j] != 0)  
                t -= a[i][j] * x[j];  
        }  
        if(t % a[i][i] != 0) return -2;  
        x[i] = t / a[i][i];  
    }  
    return 0;  
}  
  

//HDU 5755
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define ls (x<<1)
#define rs (x<<1|1)
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
#define CHECK(x, y) ((x)>=1 && (x)<=n && (y)>=1 && (y)<=m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
const LL mod = 1000000007;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 903;

int lcm(int a,int b)
{
    return a / __gcd(a,b) * b;
}
int a[N][N], x[N], r, c;
bool f[N];
/**n个方程，m个未知数，r代表当前处理的行，c代表当前处理的列*/
void Gauss(int a[][N],int n,int m,int &r,int &c)
{
    r = c = 0;
    for(; r<n && c<m; r++,c++)
    {
        int maxi = r;
        for(int i=r+1; i<n; i++)
            if(abs(a[i][c]) > abs(a[maxi][c]))
                maxi = i;
        if(maxi != r)
        {
            for(int i=r; i<m+1; i++)
                swap(a[r][i],a[maxi][i]);
        }
        if(a[r][c] == 0)
        {
            r--;
            continue;
        }
        for(int i=r+1; i<n; i++)
        {
            if(a[i][c] != 0)
            {
                int x = abs(a[i][c]), y = abs(a[r][c]);
                int LCM = lcm(x,y);
                int tx = LCM / x, ty = LCM / y;
                if(a[i][c] * a[r][c] < 0) ty = -ty;
                for(int j=c; j<m+1; j++)
                    a[i][j] = (a[i][j] * tx - a[r][j] * ty)%3;
            }
        }
    }
}
int sta[N];
//返回自由元的个数
int Rewind(int a[][N], int x[], bool f[], int n,int m,int r,int c)
{
    for(int i=r; i<n; i++)
        if(a[i][c] != 0)
            return -1;
    if(r < m)
    {
        memset(f,1,sizeof(bool)*N);
        for(int i=r-1; i>=0; i--)
        {
            int id = 0;
            int cnt = 0;
            for(int j=0; j<m; j++)
            {
                //如果cnt>1,说明这些是自由元
                if(a[i][j] != 0 && f[j]) sta[cnt++] = j;
            }
            //给cnt-1个自由元全赋值，最后一个自由元的值就确定了
            for(int j = 0; j < cnt-1; j++)
            {
                x[sta[j]] = 0;
                f[sta[j]] = 0;
            }
            id = sta[cnt-1];
            //if(cnt > 1) continue;
            int t = a[i][m];
            for(int j=0; j<m; j++)
            {
                if(a[i][j] != 0 && j != id)
                    t = (t - a[i][j] * x[j]%3)%3;
            }
            x[id] = t * a[i][id]%3;
            if(x[id] < 0) x[id] += 3;
            f[id] = 0;
        }
        return m - r;
    }
    for(int i=r-1; i>=0; i--)
    {
        int t = a[i][c];
        for(int j=i+1; j<c; j++)
        {
            if(a[i][j] != 0)
                t = (t - a[i][j] * x[j]%3)%3;
        }
        //if(t % a[i][i] != 0) return -2;
        x[i] = t * a[i][i]%3;
        if(x[i] < 0) x[i] += 3;
    }
    return 0;
}
int val[33][33], id[33][33];//
PII ans[2*N*N];
int main()
{
//    Open();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n, m;
        int t = 0;
        scanf("%d%d", &n, &m);
        memset(a, 0, sizeof(a));
        memset(x, 0, sizeof(x));
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                scanf("%d", &val[i][j]), id[i][j] = t++, a[id[i][j]][n*m] = val[i][j];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
            {
                int cid = id[i][j];
                a[cid][cid] = 2;
                if(i > 0) a[cid][id[i-1][j]] = 1;
                if(j > 0) a[cid][id[i][j-1]] = 1;
                if(i < n-1) a[cid][id[i+1][j]] = 1;
                if(j < m-1) a[cid][id[i][j+1]] = 1;
            }
        Gauss(a, n*m, n*m, r, c);
        Rewind(a, x, f, n*m, n*m, r, c);
        int num = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0 ; j < m; j++)
                while(x[id[i][j]] % 3)
                {
                    ans[num++] = PII(i+1,j+1);
                    //printf("%d %d\n", i, j);
                    x[id[i][j]] ++;
                }
        printf("%d\n", num);
        for(int i = 0; i < num; i++)
            printf("%d %d\n", ans[i].first, ans[i].second);
    }
    return 0;
}


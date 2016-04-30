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
typedef pair<int, int> PII;
const int INF=0x3f3f3f3f;
const double eps = 1e-10;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int MAXN = 6;
typedef double Matrix[MAXN][MAXN];
bool gauss(Matrix A, int n){
    int i,j,k,r;
    for(i=0;i<n;i++){
        r = i;
        for(j=i+1;j<n;j++)
            if(fabs(A[j][i]) > fabs(A[r][i]) ) r = j;
        if(r != i) for(j = 0;j<=n;j++) swap(A[r][j], A[i][j]);

        for(k = i+1;k<n;k++){
            if(abs(A[i][i]) < eps)
                return false;
            double f = A[k][i] / A[i][i];
            for(j = i;j<=n;j++) A[k][j] -= f * A[i][j];
        }
    }
    for(i = n-1;i>=0;i--){
        for(j = i+1; j<n ;j++)
            A[i][n] -= A[j][n] * A[i][j];
        if(abs(A[i][i]) < eps)
            return false;
        A[i][n] /= A[i][i];
    }
    return true;
}

#define D(x) (x)*(x)
#define LD double
int main()
{
    Open();
    int T;scanf("%d",&T);
    while(T--){
        double x1,y1,r1 , x2,y2,r2 , x3,y3,r3;
        scanf("%lf%lf%lf",&x1,&y1,&r1);
        scanf("%lf%lf%lf",&x2,&y2,&r2);
        scanf("%lf%lf%lf",&x3,&y3,&r3);
        Matrix A;
         A[0][0] = 2*x1 - 2*x2, A[0][1] = 2*y1 - 2*y2, A[0][2] = -2*r1 + 2*r2, A[0][3] = -(D(x2) - D(x1) + D(y2) - D(y1) - D(r2) + D(r1));
         A[1][0] = 2*x1 - 2*x3, A[1][1] = 2*y1 - 2*y3, A[1][2] = -2*r1 + 2*r3, A[1][3] = -(D(x3) - D(x1) + D(y3) - D(y1) - D(r3) + D(r1));
         A[2][0] = 2*x2 - 2*x3, A[2][1] = 2*y2 - 2*y3, A[2][2] = -2*r2 + 2*r3, A[2][3] = -(D(x3) - D(x2) + D(y3) - D(y2) - D(r3) + D(r2));

        bool res = gauss(A,3);
        if(res == false){
            puts("no solution");
        }else{
            printf("%.8f %.8f %.8f\n",A[0][3],A[1][3],A[2][3]);
        }
    }
    return 0;
}

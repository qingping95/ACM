//http://acm.hust.edu.cn/vjudge/contest/view.action?cid=87817#problem/F
/*
* Annie Sweety is studying the problem to select rectangular regions in a given image. She views an
* image being just a rectangular matrix with pixels as miniature rectangles sandwiched together. The
* rectangular regions Annie is interested are those rectangular blocks within the pixels matrix that are
* large enough and also with brightest possible averaged value pixels.
* Formally, given an m × n integer matrix, you are asked to write a program to find the submatrix,
* so that the average is maximum on the condition that the total number of elements in the submatrix
* need to be no less than a given number k. The submatrix in request consists of continuous rows and
* columns of the given matrix. That is, it is a continuous rectangle region of the matrix in question. Here
* we define the average in a submatrix as the sum between all the elements on the submatrix divided by
* the number of elements evaluating. For example, given constraint k = 4 and the following 3×5 matrix:
* 9 2 6 3 9
* 7 7 5 7 8
* 4 7 8 7 5
* The constrained maximum average submatrix is the following 2 3 submatrix
* 7 5 7
* 7 8 7
* with size 6, while its average is (7 + 5 + 7 + 7 + 8 + 7)/6 = 41/6 = 6.833 .
* Technical Specification
* • The row, m, of each matrix can be as large as 600, and column, n, can be as large as 10,000.
* • The value of each element of the matrix is a nonnegative integer at most 5,000.
* • k ≤ mn ≤ 1, 000, 000.
* 
* Input
* The input consists of several instances of matrices with corresponding constrained sizes. The inputs are
* just a list of integers. The first input integer indicates the total number of input instances. For each
* instance of matrix and constraint, the first two integers are the row number, m, and column number
* n of the given matrix, representing a following m × n integer matrix. Following m, n, the third integer
* represents the constraint size k.
* After (m, n, k), there will be m lines representing the m rows of the matrix; each line (row) contains
* exactly n integers. Thus, there is totally m · n integers for the particular matrix.
* 
* Output
* For each matrix of the input, calculate its constrained maximum average submatrix and output the
* average value of the submatrix rounded to the nearest thousandth.
* 
* 题意：给出一个n*m的矩阵，以及一个k，求一个元素不小于k的子矩阵的平均值的最大
*
* 做法：很明显的分数规划问题，需求就是max(sigma(a[i])/n)的最大值，设答案为ans，代入式子中，再变一下形：
*		sigma(a[i]) - n*ans = 0,那么这里可以二分枚举ansp，这有下面不等式成立：
*		max(sigma(a[i]) - n*ansp) < 0 => ansp > ans
*		max(sigma(a[i]) - n*ansp) > 0 => ansp < ans
*		按照这个规则二分ans即可，求max这一部分可以用单调队列解决，需要先处理出每一列的前缀和，
*		在二份函数中变为一个一维数组的单调队列，如此即可高效算出max(sigma(a[i]) - n*ansp);
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 10100
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
const double eps = 1e-5;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
double f[610][10010];
double colsum[10010];
int n, m, K;
double sta[N];
bool check(double g)
{
    for(int i = 1; i <= n; i++)
        for(int j = i; j <= n; j++)
        {
            int rowlen = j - i + 1;
            int collen = (K - 1) / rowlen + 1;
            collen = max(1, collen);
            int tail = 0;
//            sta[tail++] = 0;
            colsum[0] = 0;
            for(int k = 1; k <= m; k++)
            {
                colsum[k] = f[j][k] - f[i-1][k] - g * rowlen + colsum[k-1];
                while(k >= collen && tail > 0 && sta[tail - 1] > colsum[k - collen]) tail--;
                if(k >= collen) sta[tail++] = colsum[k - collen];
                if(tail > 0 && colsum[k] - sta[0] > -eps) return true;
            }
        }
    return false;
}
int main()
{
    Open();
    int T;scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &n, &m, &K);
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                scanf("%lf", &f[i][j]);
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                f[i][j] += f[i-1][j];
        double lb = -1, ub = 5001;
        while(lb + eps < ub){
            double mid = (lb + ub) / 2;
            if(check(mid)) lb = mid;
            else ub = mid;
        }
        printf("%.3f\n", lb);
    }
    return 0;
}

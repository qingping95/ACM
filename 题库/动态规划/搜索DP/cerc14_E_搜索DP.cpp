/*
* Some computer games are extremely fun and this problem may be about one of these.
* You are given a sequence of one dimensional blocks, each of length that is a power of two.
* The goal of the game is to merge all the blocks into one big block. The blocks are presented
* one by one, and for each one you have to decide whether to stick it immediately to the left or
* immediately to the right of the previous blocks.
* Every time two blocks of the same size are adjacent, they merge into one block that is twice
* as long as each of them. Note that, as long as possible, the resulting blocks immediately merge
* with adjacent ones. For example, if the current sequence of blocks is 2, 4, 16, then sticking 2 on
* the left side leads to 8, 16, while sticking it on the right side gives 2, 4, 16, 2. Note that at any
* moment there is at most one mergeable pair of blocks.
* You have lost the game (again!) and you are wondering whether there was any way to win
* at all. Analyze the sequence to find out.
*
* Input
* The first line of input contains the number of test cases 𝑇 . The descriptions of the test cases
* follow:
* Each test case consists of two lines. The first one contains a positive integer 𝑛 ¬ 1 000 – the
* length of the sequence. The next line contains a sequence of 𝑛 block lengths, each a power of
* two. The sum of all the lengths does not exceed 213.
*
* Output
* For each test case, output one line containing the word no if winning the game is not possible.
* Otherwise, output a word consisting of 𝑛 letters l and r, denoting whether the corresponding
* block should be stuck to the left or to the right. Note that for the first block it does not matter.
* 
* 题意：这是一个类似2048的游戏，不过这个游戏只会在原有图形的左边或者右边会出现新的方块，也仍然是相同
* 		的会合并，只会出现二次幂的数。那么给出第i次出现的方块的值，并不知道出现在左边还是右边，问给出
*		的序列能不能通过某种(每块方块放左/右)方案使得最后只剩下一个数字，有一个限制为所有值的和不超过
*		1<<13
*
* 做法：这里既然限制了所有数的加和，且给出的数都是二进制数，那么很明显可以在这上面做文章(切入点)。
*		抽象的想一下，任何一个合法状态都只能是这样的：中间的值最大，两边递减，类似梯形。对于每个数来说
*		不是放左边就是放右边，每个方块有两种方式，还是很像一个DP，于是首先以dp[i][sl][sr]做状态，表示
*		处理到第i个方块，左边的状态为sl，右边的状态为sr，这一状态可不可行，这里的左边右边是相对于最大值
*		的，由于最大值也只可能一个，规定最大值一定在左边。现在考虑状态如何表示，分析可知，左边的值由于
* 		是严格递增的，也就是说每一个数不可能出现大于1次，这意味着状态可用一个二进制数表示，同时还有一个
*		性质：表示sl这个状态的整数即为左边的方块的值的加和，这一个性质可以大大降低编程复杂度，右边也一样。
*		但是这样复杂度很明显为n*(1<<13)*(1<<13)一定是不行的，然后突然又发现，对于一个特定的i来说，确定
*		sl的话，意味着sr就确定了，因为sl+sr一定为a[1]+a[2]+...+a[i],也就是说这里复杂度降低一维！
*		于是，此题可解！
*		当然还是有许多细节处理，由于规定了最大值一定在左边，那么每次的更新都要维护这一性质，检测右边是否
*		大于左边。同时更新其间也有很多位运算。
*/

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 1010
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
int dp[N][1<<14];
PII p[N][1<<14];
int cas = 1;
int n, sum[N], sta[N];
int f[N];
int main()
{
    Open();
    int T;scanf("%d", &T);
    while(T--)
    {
        cas ++;
        scanf("%d", &n);
        for(int i = 0; i < n; i++){
            scanf("%d", &f[i]);
            sum[i] = f[i];
            if(i) sum[i] += sum[i-1];
        }
        dp[0][f[0]] = cas;
        p[0][f[0]] = PII(0, 0);
        dp[0][0] = cas;
        p[0][0] = PII(0, 1);
        for(int i = 1;i < n; i++)
        {
            int cur = f[i];
            for(int j = 0; j <= sum[i-1]; j++)
            {
                if(dp[i-1][j] != cas) continue;
                int rit = sum[i-1] - j;
                if(j == 0 || (cur <= (j & (-j)))){
                    int rcnt = 31 - __builtin_clz(rit);
                    int lcnt = 31 - __builtin_clz(j + cur);
                    if(rcnt == lcnt)
                        dp[i][j + cur + (1<<lcnt)] = cas, p[i][j + cur + (1<<lcnt)] = PII(j, 0);
                    else
                        dp[i][j + cur] = cas, p[i][j + cur] = PII(j, 0);
                }
                if(rit == 0 || cur <= (rit & (-rit))){
                    int rcnt = 31 - __builtin_clz(cur + rit);
                    int lcnt = 31 - __builtin_clz(j);
                    if(rcnt == lcnt)
                        dp[i][j + (1 << lcnt)] = cas, p[i][j + (1 << lcnt)] = PII(j, 1);
                    else
                        dp[i][j] = cas, p[i][j] = PII(j, 1);
                }
                if(__builtin_popcount(j) == 1 && j > rit && cur > j){
                    dp[i][cur] = cas, p[i][cur] = PII(j, 0);
                }
                if(__builtin_popcount(rit) == 1 && rit > j && cur > rit){
                    dp[i][j + rit] = cas, p[i][j + rit] = PII(j, 1);
                }
            }
        }
        int tail = 0;
        if(__builtin_popcount(sum[n-1]) != 1 || (dp[n-1][sum[n-1]] != cas && dp[n-1][0] != cas)){
            printf("no\n");
            continue;
        }
        
        int pre, cnt;
        if(dp[n-1][sum[n-1]] == cas)
            pre = sum[n-1], cnt = n-1;
        else
            pre = 0, cnt = n-1;

        while(cnt >= 0){
            PII cur = p[cnt][pre];
            sta[tail++] = cur.second;
            pre = cur.first;
            cnt--;
        }
        for(int i = tail - 1; i >= 0; i--)
        {
            printf("%c", "lr"[sta[i]]);
        }
        printf("\n");
    }
    return 0;
}

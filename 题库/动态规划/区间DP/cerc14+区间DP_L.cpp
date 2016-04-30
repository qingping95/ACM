//http://codeforces.com/gym/100543/attachments
/*
* 	The aliens from outer space have (finally!) invaded Earth. Defend yourself, or be disintegrated!
* 	Or assimilated. Or eaten. We are not yet sure.
* 	The aliens follow a known attack pattern. There are 𝑛 attackers, the 𝑖-th one appears at time
* 	𝑎𝑖, at distance 𝑑𝑖 from you. He must be destroyed no later than at time 𝑏𝑖, or else he will fire his
* 	weapon, which will definitely end the fight.
* 	Your weapon is an area-blaster, which can be set to any given power. If fired with power 𝑅,
* 	it momentarily destroys all aliens at distance 𝑅 or smaller. It also consumes 𝑅 fuel cells.
* 	Determine the minimal cost (measured in fuel cells) of destroying all the aliens, without being
* 	killed.

* 	Input
* 	The first line of input contains the number of test cases 𝑇. The descriptions of the test cases
* 	follow:
* 	Each test case starts with a line containing the number of aliens 𝑛 (1 <= 𝑛 <= 300). Of the next
* 	𝑛 lines, the 𝑖-th one contains three integers 𝑎𝑖, 𝑏𝑖, 𝑑𝑖, (1 <= 𝑎𝑖 < 𝑏𝑖 <= 10 000; 1 <= 𝑑𝑖 <= 10 000).
* 	The 𝑖-th alien appears at time 𝑎𝑖, is idle until 𝑏𝑖, and his distance from you is 𝑑𝑖.
* 	
*	Output
*	For each test case, output one line containing the minimum number of cells needed to destroy
*	all the aliens.
*  
*   题意：外星人正在计划入侵地球！你得知了会有n个外星人将会降临到地球上，每个外星人会在ai时刻降临在距离
*		  di的地方，而且必须在bi时刻前消灭它，不然就会外星人将会攻击你，你每一次的攻击可以选定一个值R，
*		  与此同时，与你距离小于等于R的所有外星人将会被你消灭，同时你会消耗R点能量，需要求出最小的能量消耗
*
*	做法：区间dp，首先将所有时刻点离散化出来，dp[i][j]表示消灭出现在(p[i],p[j])这个开区间内的所有敌人消灭的
*		  最小花费，其中p数组为离散化的数组，这里更新比较不一样，一般的dp[i][j]都是枚举i~j中的全部中间点，
*		  去更新当前dp值，但是这里要使得(p[i],p[j])这个区间中的所有外星人都消灭的话，首先R必须选择这个区间
*		  内的最大距离，记这个外星人的下标为i，那么分裂点只能在a[i]~b[i]之间，才能保证这个距离最远的外星人
*		  会被消灭。
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 610
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
int dp[N][N];
vector<int> p;
int a[N], b[N], d[N];
int n;
int main()
{
    Open();
    int T;scanf("%d", &T);
    while(T--)
    {
        p.clear();
        scanf("%d", &n);
        for(int i=0;i<n;i++)
        {
            scanf("%d%d%d", &a[i], &b[i], &d[i]);
            p.push_back(a[i]), p.push_back(b[i]);
        }
        p.push_back(-INF), p.push_back(INF);
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());
        for(int len = 0; len < p.size(); len++)
        {
            for(int i = 0; i < p.size();i++)
            {
                int j = i + len, hst = -1;
                for(int l = 0; l < n; l++)
                {
                    if(a[l] > p[i] && b[l] < p[j] && (hst == -1 || d[hst] < d[l])) hst = l;
                }
                if(hst == -1) dp[i][j] = 0;
                else {
                    dp[i][j] = INF;
                    int l = lower_bound(p.begin(), p.end(), a[hst]) - p.begin();
                    int r = lower_bound(p.begin(), p.end(), b[hst]) - p.begin();
                    for(int k = l; k <= r; k++)
                    {
                        dp[i][j] = min(dp[i][j], d[hst] + dp[i][k] + dp[k][j]);
                    }
                }
            }
        }
        printf("%d\n", dp[0][p.size() - 1]);
    }
    return 0;
}

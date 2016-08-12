/*
*	贪心，每次直接跳到q点两侧，大于的一边继续递归做，由于每次停顿可以休息也可以+1，先记录休息了多少次，
*	最后如果要增加的话，就减掉休息的次数即可。
*/
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
#include <bitset>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PII;
const int INF = 0x3f3f3f3f;
const int N = 100010;
const int mod = 1000000007;
LL two[44];
int ta;
LL solve(int p, int q, int s)
{
    if(p < 0) p = 0;
    if(p <= q) return max(q-p-s, 0);
    int idx = upper_bound(two+1, two+ta, p-q) - two;
    int res = idx;
    LL a1 = res + solve(p-two[idx], q, s);
    LL a2 = res + solve(p-two[idx-1], q, s+1) - (p-two[idx-1] == q);
    return min(a1, a2);
}
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
    ta = 1;
    two[ta++] = 1;
    while(two[ta-1] < 1e9+10) two[ta] = two[ta-1]*2+1, ta++;
    int T;
    scanf("%d", &T);
    while(T--)
    {
        LL p, q;
        scanf("%I64d%I64d", &p, &q);
        printf("%I64d\n", solve(p, q, 0));
    }

    return 0;
}

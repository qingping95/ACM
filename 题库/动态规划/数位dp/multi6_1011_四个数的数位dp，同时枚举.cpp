/*
*	数位dp，四个数同时枚举，另外因为有两个不等式限制，还需要将两个不等式的信息挂为状态，由于是两个数的加和比较，
*	所以在某位差值超过2的话，之后无论如何都加不回来了，所以只需要存储差值为-1,0,1,2的状态，其中2表示所有差值大
*	于2的情况。
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
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
const LL mod = 1e9+7.5;
const LL N = 100010;
LL dp[66][1<<4][4][4];
LL num[5];
int getf(int v, int f)
{
    if(f == 3) return f;
    int tmp = f-1;
    tmp *= 2;
    tmp += v;
    if(tmp > 1) return 3;
    if(tmp < -1) return -1;
    //if(abs(tmp) > 1) return -1;
    return tmp + 1;
}
LL dfs(int pos, int s, int f1, int f2)
{
    if(pos == -1) {
        return f1 >= 2 && f2 >= 1;
    }
    if(dp[pos][s][f1][f2] != -1) return dp[pos][s][f1][f2];
    int up[4];
    for(int i = 0; i < 4; i++) up[i] = ((s >> i)&1) == 1 ? ((num[i]>>pos)&1) : 1;
    LL res = 0;
    for(int a = 0; a <= up[0]; a++)
        for(int b = 0; b <= up[1]; b++)
            for(int c = 0; c <= up[2]; c++)
                for(int d = 0; d <= up[3]; d++)
                {
                    int cf1 = getf(a+c-b-d, f1);
                    int cf2 = getf(a+d-c-b, f2);
                    if(cf1 == -1 || cf2 == -1) continue;
                    int cs = s;
                    if((cs & 1) && a != up[0]) cs ^= 1;
                    if((cs & 2) && b != up[1]) cs ^= 2;
                    if((cs & 4) && c != up[2]) cs ^= 4;
                    if((cs & 8) && d != up[3]) cs ^= 8;
                    res = (res + dfs(pos-1, cs, cf1, cf2))%mod;
                }
    return dp[pos][s][f1][f2] = res;
    //return res;
}
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
    int T;
    scanf("%d", &T);
    while(T--)
    {
        memset(dp, -1, sizeof(dp));
        for(int i = 0; i < 4; i++)
            scanf("%I64d", &num[i]);
//        cout<<"FUCK"<<endl;
        printf("%I64d\n", dfs(61, 15, 1, 1));

    }
    return 0;
}


// Paste me into the FileEdit configuration dialog
// Paste me into the FileEdit configuration dialog

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <deque>
#include <cmath>
#include <queue>
#include <stack>
#include <ctime>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <sstream>
#include <complex>
#include <string>
#include <vector>
#include <cstdio>
#include <bitset>
#include <functional>
#include <algorithm>
typedef long long LL;
using namespace std;

/*
preB - B
preC:
0 -- 无C
1 -- C
2 -- CX
*/
bool dp[55][55][55][2][3];
char ans[55];
bool dfs(int A, int B, int C, int preB, int preC, int idx)
{
    if(A == 0 && B == 0 && C == 0) return true;
    if(dp[A][B][C][preB][preC]) return false;
    int n = A+B+C;
    if(n < 3*(C-1)+1 || n < 2*B-1)
    {
        dp[A][B][C][preB][preC] = true;
        return false;
    }
    if(A > 0 && dfs(A-1, B, C, 0, ((preC == 1)? 2: 0), idx+1))
    {
        ans[idx] = 'A';
        return true;
    }
    if(B > 0 && preB < 1 && dfs(A, B-1, C, 1, ((preC == 1)? 2: 0), idx+1))
    {
        ans[idx] = 'B';
        return true;
    }
    if(C > 0 && preC < 1 && dfs(A, B, C-1, 0, 1, idx+1))
    {
        ans[idx] = 'C';
        return true;
    }
    dp[A][B][C][preB][preC] = true;
    return false;
}
class ThreeProgrammers {
public:
    string validCodeHistory( string code ) {
        memset(dp, 0, sizeof(dp));
        int A = 0, B = 0, C = 0;
        for(int i = 0; i < code.length(); i++)
        {
            if(code[i] == 'A') A++;
            if(code[i] == 'B') B++;
            if(code[i] == 'C') C++;
        }
        if(!dfs(A, B, C, 0, 0, 0)) return string("impossible");
        else {
            ans[A+B+C] = '\0';
            //cout<<string(ans)<<endl;
            return string(ans);
        }
    }
};

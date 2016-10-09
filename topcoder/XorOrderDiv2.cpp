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
const int N = 1010;
LL w[N][33][2];
LL dp[33][N];
// 0 - 该位选0
// 1 - 该位选1
class XorOrderDiv2 {
public:
   vector<long long> getExpectation( int m, vector <int> a ) {
        memset(w, 0, sizeof(w));
        for(int i = 0; i < a.size(); i++)
        {
            for(int j = i+1; j < a.size(); j++)
            {
                int x = a[i] ^ a[j];
                int idx = 0;
                while(x >> idx) idx++;
                //idx--;
                if(a[i] > a[j]) w[i][idx][0]++, w[j][idx][1]++;
                else w[i][idx][1]++, w[j][idx][0]++;
            }
        }
        vector<LL> ans;
        int n = a.size();
        for(int i = 0; i < a.size(); i++)
        {
            memset(dp, 0, sizeof(dp));
            dp[0][0] = 1;
            for(int j = 0; j < m; j++)
            {
                for(int k = 0; k <= n; k++)
                {
                    if(dp[j][k])
                    {
                        dp[j+1][k+w[i][j+1][0]] += dp[j][k];
                        dp[j+1][k+w[i][j+1][1]] += dp[j][k];
                    }
                }
            }
            LL res = 0;
            for(LL j = 0; j < n; j++)
            {
                res += dp[m][j] * j*j;
            }
            ans.push_back(res);
        }
        return ans;
   }
};


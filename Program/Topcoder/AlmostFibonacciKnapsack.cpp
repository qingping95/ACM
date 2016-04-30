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

LL f[111];
vector<int> ans;
class AlmostFibonacciKnapsack {
public:
   vector <int> getIndices( long long x ) {
        ans.clear();
        f[0] = 2, f[1] = 3;
        LL pre = f[1];
        int n = 0;
        for(int i = 2; pre < 1000000000000000000LL; i++)
        {
            f[i] = pre = f[i-1] + f[i-2] - 1;
            n = i;
        }
        int up = 23;
        int sum = 0;
        for(int i = 0; i < up; i++) sum += f[i];
        sum -= 3;
        int idx = n+1;
        while(x > sum)
        {
            idx--;
            if(x >= f[idx] + 2)
            {
                x -= f[idx];
                ans.push_back(idx+1);
            }
        }
        for(int s = 0; s < (1 << up); s++)
        {
            int num = 0;
            for(int i = 0; i < up; i++)
            {
                if(s & (1 << i))
                {
                    num += f[i];
                }
            }
            if(num == x)
            {
                for(int i = 0; i < up; i++)
                    if(s & (1 << i)) ans.push_back(i+1);
                break;
            }
        }
        return ans;
   }
};

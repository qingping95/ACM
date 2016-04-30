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


class MultiplicationTable2 {
public:
   int minimalGoodSet( vector <int> table ) {
        int n = 0;
        for(n = 1; n*n <= table.size(); n++)
        {
            if(n*n == table.size()) break;
        }
        int ma = 0;
        for(int i = 0; i < n; i++)
        {
            int ans = i+1;
            for(int j = 0; j <= i; j++)
            {
                ma = max(ma, table[i*n+j]);
            }
            for(int j = 0; j <= i; j++)
                ma = max(ma, table[j*n+i]);
            if(ma <= i) return ans;
        }
        return n;
   }
};

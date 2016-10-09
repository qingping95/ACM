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


class TriangleMaking {
public:
   int maxPerimeter( int a, int b, int c ) {
        int ans = 0;
        for(int x = 1; x <= a; x++)
        {
            for(int y = 1; y <= b; y++)
            {
                for(int z = 1; z <= c; z++)
                {
                    if(x + y > z && x + z > y && y + z > x)
                    {
                        ans = max(ans, x+y+z);
                    }
                }
            }
        }
        return ans;
   }
};


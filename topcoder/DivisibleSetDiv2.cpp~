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


class DivisibleSetDiv2 {
public:
   string isPossible( vector <int> b ) {
        for(int sum = b.size(); sum <= 100000; sum++)
        {
            int res = sum;
            bool flag = true;
            for(int i = 0; i < b.size() && flag; i++)
            {
                int ned = floor(sum*1.0 / b[i]);
                while(ned == 0 || ned*b[i] < sum) ned++;
                if(res < ned)
                {
                    flag = false;
                    break;
                }
                res -= ned;
            }
            if(flag) return "Possible";
        }
        return "Impossible";
   }
};


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
//typedef int LL;
using namespace std;


class PlaneGame {
public:
    bool isline(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        LL ux = x2 - x1, uy = y2 - y1;
        LL vx = x3 - x1, vy = y3 - y1;
        return uy * vx == vy * ux;
    }
    bool ischuizhi(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
    {
        LL ux = x2 - x1, uy = y2 - y1;
        LL vx = x4 - x3, vy = y4 - y3;
        return ux * vx + uy * vy == 0;
    }
    int bestShot( vector <int> x, vector <int> y ) {
        if(x.size() <= 3) return x.size();
        int ans = 0;
        for(int i = 0; i < x.size(); i++)
        {
            for(int j = i+1; j < x.size(); j++)
            {
                for(int k = 0; k < x.size(); k++)
                {
                    if(i == k || k == j) continue;
                    int res = 3;
                    for(int l = 0; l < x.size(); l++)
                    {
                        if(i == l || j == l || k == l) continue;
                        if(isline(x[i], y[i], x[j], y[j], x[l], y[l]))
                        {
                            res++;
                            continue;
                        }
                        if(ischuizhi(x[i], y[i], x[j], y[j], x[k], y[k], x[l], y[l]))
                        {
                            res++;
                            continue;
                        }
                    }
                    ans = max(ans, res);
                }
            }
        }
        return ans;
   }
};

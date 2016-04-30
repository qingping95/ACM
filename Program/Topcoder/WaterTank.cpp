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
const int INF = 0x3f3f3f3fLL;
const double eps = 1e-11;
class WaterTank
{
public:
    bool check( vector <int> t, vector <int> x, int C , double out)
    {
        int n = t.size();
        double cur = 0;
        for(int i = 0; i < n; i++)
        {
            cur += (LL)t[i]*x[i];
            cur -= out*t[i];
            cur = max(0.0, cur);
            if(cur - eps > C) return false;
        }
        return true;
    }
    double minOutputRate( vector <int> t, vector <int> x, int C )
    {
        double ans = 0, lb = 0, ub = INF;
        ub *= 4.0;
        int time = 200;
        while(time--)
        {
            double mid = (lb+ub)/2;
            if(check(t, x, C, mid)) ans = ub = mid;
            else lb = mid;
        }
        return ans;
    }
};

/*
        int t[]                   = {9000,3};
        int x[]                   = {1000000,2000000};
        int C                     = 1000000000;
        double expected__         = 0.9999999999999999;
*/
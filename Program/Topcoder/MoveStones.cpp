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


class MoveStones {
public:
   long long get( vector <int> a, vector <int> b ) {
        long long n = a.size();
        long long suma = 0, sumb = 0;
        for(long long i = 0; i < n; i++)
            suma += a[i];
        for(long long i = 0; i < n; i++)
            sumb += b[i];
        if(suma != sumb) return -1;
        long long ans = 0;
        for(long long i = 0; i < n; i++)
        {
            if(a[i] <= b[i]) continue;
            long long res = a[i] - b[i];
            for(long long j = 1; j <= n/2 && res; j++)
            {
                long long idx = (i+j)%n;
                if(a[idx] < b[idx])
                {
                    a[idx] += res;
                    ans += j * res;
                    if(a[idx] > b[idx]) res = a[idx] - b[idx], ans -= res * j;
                }
            }
            for(long long j = 1; j <= n/2 && res; j++)
            {
                long long idx = (i-j+n)%n;
                if(a[idx] < b[idx])
                {
                    a[idx] += res;
                    ans += j * res;
                    if(a[idx] > b[idx]) res = a[idx] - b[idx], ans -= res * j;
                }
            }
        }
        return ans;
   }
};
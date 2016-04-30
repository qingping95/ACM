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


class SumFullSet {
public:
   string isSumFullSet( vector <int> elements ) {
        if(elements.size() <= 1) return "closed";
        set<int> s;
        for(int i = 0; i < elements.size(); i++)
            s.insert(elements[i]);
        for(int i = 0; i < elements.size(); i++)
            for(int j = i+1; j < elements.size(); j++)
            {
                int num = elements[i] + elements[j];
                if(s.find(num) == s.end())
                    return "not closed";
            }
        return "closed";
   }
};

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

map<int, int> X;
map<int, int> Y;
class RelationClassifier {
public:
   string isBijection( vector <int> domain, vector <int> range ) {
        X.clear();Y.clear();
        for(int i = 0; i < domain.size(); i++)
        {
            if(X.find(domain[i]) == X.end()) {
                X[domain[i]] = range[i];
            }else if(X[domain[i]] != range[i]){
                return "Not";
            }
            if(Y.find(range[i]) == Y.end()) {
                Y[range[i]] = domain[i];
            }else if(Y[range[i]] != domain[i]){
                return "Not";
            }
        }
        return "Bijection";
   }
};

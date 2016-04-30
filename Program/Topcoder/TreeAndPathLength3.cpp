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


class TreeAndPathLength3
{
public:
    vector<int> res;
    vector <int> construct( int s )
    {
        res.clear();
        int K = 1;
        while(K * (K - 1) <= s)  K++;
        K--;
//        cout<<K<<endl;
        int num = 0;
        for(int i = 1; i <= K; i++)
        {
            res.push_back(0);
            res.push_back(++num);
            res.push_back(num);
            res.push_back(++num);
        }
//        cout<<num<<endl;
        for(int ans = K * (K - 1); ans < s; ans++)
        {
            res.push_back(num);
            res.push_back(++num);
        }
//        for(int i = 0; i < res.size(); i++)
//            cout<<res[i]<<" ";
//        cout<<endl;
        return res;
    }
};

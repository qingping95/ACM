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

LL que[3333];
map<LL, LL> mp;
class CliqueParty {
public:
    bool judge(vector<LL> a, LL k, LL length)
    {
        mp.clear();
        LL head = 0, tail = 0;
        for(LL i = 0; i < a.size(); i++)
        {
            if(tail - head < length)
            {
                que[tail++] = a[i];
                for(LL j = head; j < tail-1; j++)
                {
                    LL val = abs(que[j] - que[i]);
                    mp[val]++;
                }
            }
            if(tail - head == length)
            {
                //cout<<mp.rbegin()->first<<" "<<mp.begin()->first<<endl;
                if((mp.rbegin()->first) <= (mp.begin()->first)*k)
                    return true;
                head++;
                for(LL j = head; j < tail; j++)
                {
                    LL val = abs(que[head-1] - que[j]);
                    mp[val]--;
                    if(mp[val] <= 0) mp.erase(val);
                }
            }
        }
        return false;
    }
   LL maxsize( vector <LL> a, LL k ) {

        sort(a.begin(), a.end());
        for(LL i = a.size(); i >= 2; i--)
        {
            if(judge(a, k, i)) return i;
        }
        return 2;
   }
};
int main()
{
    vector<LL> a;
    a.push_back(1);
    a.push_back(100);
    a.push_back(101);
    a.push_back(201);
    cout<<CliqueParty().maxsize(a, 25)<<endl;
}

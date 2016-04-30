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
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
typedef long long LL;
#define PSI pair<multiset<int>, int>
using namespace std;

const int N = 10000000;
int prime[1000000];
multiset<int> s[1000000];
multiset<int>::iterator it;
vector<PSI > vs[2];
int pn;
bool vis[N];
void get_prime()
{
    for(int i=2;i<N;i++)
    {
        if(vis[i]) continue;
        prime[pn++]=i;
        for(int j=i;j<N;j+=i)
        {
            vis[j]=1;
        }
    }
    //printf("%d\n", pn);
}
int a[N];
const int mod = 1000000007;
class GCDLCM2 {
public:
   int getMaximalSum( vector <int> start, vector <int> d, vector <int> cnt ) {
        get_prime();
        memset(vs, 0, sizeof(vs));
        memset(s, 0, sizeof(s));
        int n = 0;
        for(int i = 0; i < start.size(); i++)
            for(int j = 0; j < cnt[i]; j++)
                a[n++] = start[i] + j * d[i];
        //cout<<n<<endl;
        int allnum = 0;
        for(int i = 0; i < n; i++)
        {
            int x = a[i];
            for(int j = 0; j < pn && x != 1; j++)
            {
                if(x % prime[j]) continue;
                int num = 0;
                while(x % prime[j] == 0) x /= prime[j], num++;
                s[j].insert(num);
                allnum ++;
            }
        }
        cout<<allnum<<endl;
        return 0;
        LL ans = 0;
        int cur = 1;
        for(int j = 0; j < pn; j++)
        {
            if(s[j].empty()) continue;
            vs[cur].push_back(PSI(s[j], prime[j]));
        }
        while(vs[cur].size() && n)
        {
            vs[cur^1].clear();
            LL tmp = 1;
            for(int i = 0; i < vs[cur].size(); i++)
            {
                it = vs[cur][i].first.end();
                it--;
                int num = *it;
                int p = vs[cur][i].second;
                while(num--)
                {
                    tmp = tmp * p % mod;
                }
                vs[cur][i].first.erase(it);
                if(vs[cur][i].first.empty()) continue;
                else vs[cur^1].push_back(vs[cur][i]);
            }
            ans = (ans + tmp) % mod;
            cur ^= 1;
            n--;
        }
        ans = (ans + n) % mod;
        return ans;
   }
};

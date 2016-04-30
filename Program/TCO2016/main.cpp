#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
//#include <unordered_map>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 1000010;
class ReplacingDigit
{
public:
    int getMaximumStockWorth( vector <int> A, vector <int> D)
    {
        priority_queue<int, vector<int>, greater<int> > num[11];
        vector<int> ans[11];
        int ma = 0;
        for(int i = 0; i < A.size(); i++)
        {
            int tmp = A[i];
            int idx = 0;
            while(tmp)
            {
                num[idx].push(tmp % 10);
                tmp /= 10;
                idx++;
            }
            ma = max(idx, ma);
        }

        int UP = ma;
        for(int i = 8; i >= 0 && ma >= 0; i--)
        {
            int cur = i+1;
            while(D[i] && ma >= 0)
            {
                if(!num[ma].empty())
                {
                    if(num[ma].top() < cur) {
                        num[ma].pop();
                        ans[ma].push_back(cur);
                        D[i]--;
                    }else{
                        while(!num[ma].empty())
                        {
                            ans[ma].push_back(num[ma].top());
                            num[ma].pop();
                        }
                        ma--;
                    }
                }else {
                    ma--;
                }
            }
        }
        while(ma >= 0)
        {
            while(!num[ma].empty())
            {
                ans[ma].push_back(num[ma].top());
                num[ma].pop();
            }
            ma--;
        }
        int ANS = 0;
        for(int i = UP; i >= 0; i--)
        {
            ANS = ANS * 10;
            for(int j = 0; j < ans[i].size(); j++)
            {
                ANS += ans[i][j];
            }
        }
        return ANS;
    }
};

int main()
{
    return 0;
}

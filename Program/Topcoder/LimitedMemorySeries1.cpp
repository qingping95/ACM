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
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
using namespace std;

class LimitedMemorySeries1
{
public:
    int N, X0, A, B;
    int sta[1111];
    int tmp1[1111];
    int tmp2[1111];
    LL ans;
    void divide(int l, int r, int tl, int tr)
    {
        if(tl >= tr) return;
        if(l == r)
        {
            for(int i = tl; i < tr; i++)
                ans += l;
            return ;
        }
        int mid = l + r >> 1;
        int num = (X0 <= mid && X0 >= l);
        LL pre = X0;
        for(int i = 1; i < N; i++)
        {
            pre = ((LL)pre*A+B)%mod;
            num += (pre >= l && pre <= mid);
        }
        int Ln = 0, Rn = 0;
        for(int i = tl; i < tr; i++)
        {
            if(num >= sta[i]) tmp1[Ln++] = sta[i];
            else tmp2[Rn++] = sta[i] - num;
        }
        for(int i = 0; i < Ln ; i++) sta[tl+i] = tmp1[i];
        for(int i = 0; i < Rn ; i++) sta[tl+Ln+i] = tmp2[i];
        divide(l, mid, tl, tl+Ln);
        divide(mid+1, r, tl+Ln, tl+Ln+Rn);
    }
    long long getSum( int n, int x0, int a, int b, vector <int> query )
    {
        N = n, X0 = x0, A = a, B = b;
        ans = 0;
        int tail = 0;
        for(int i = 0; i < query.size(); i++)
            sta[tail++] = query[i]+1;
        divide(0, mod, 0, tail);
        return ans;
    }
};

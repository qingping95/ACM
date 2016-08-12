#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
/*
*	lasker's NIM变形，可以通过直接打表发现规律，但是由于我的失误，直接将1～i-1置1，导致打表错误，这题卡了很久
*/
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <climits>
#include <bitset>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PII;
const int INF = 0x3f3f3f3f;
const int N = 100010;
int getsg(int x)
{
    if(x % 8 == 0) return x-1;
    else if((x+1)%8 == 0) return x+1;
    else return x;
}
int main(){
//    freopen("/home/qingping/in.txt","r",stdin);
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n;
        scanf("%d", &n);
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            int x;
            scanf("%d", &x);
            ans ^= getsg(x);
        }
        if(ans) printf("First player wins.\n");
        else printf("Second player wins.\n");
    }
    return 0;
}

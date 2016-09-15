///用的时候记得将mod改回去
///以及数据类型
///卷积外面的部分与普通FFT，FWT相同
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <climits>
#include <bitset>
#define CHECK(x, y) ((x)>=0&&(x)<n&&(y)>=0&&(y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PII;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
//const LL mod = 1e9+7.5;
const LL N = 1010;
const LL mod = 1LL<<32;
typedef unsigned int uint;
uint cur = 0;
uint a, b;
uint nextRand()
{
    cur = cur * a + b;
    return cur / (1<<16);
}
uint f[1<<17], g[1<<17];
void fwt(uint *x, uint n, int op)  {
    int mm;
    for (mm = 1; mm < n; mm <<= 1)  { //2m
        for (int st = 0; st < n; st += mm << 1)
            for (uint i = 0; i < mm; i ++)  {
                uint a = x[st + i], b = x[st + i + mm];
                x[st+i] = a;
                if(op == 1) x[st + i + mm] = (b+a)%mod;
                else x[st+i+mm] = (b-a)%mod;
                if(x[st+i+mm] < 0) x[st+i+mm] += mod;
            }
    }
}
int main(){
//	freopen("/home/qingping/in.txt","r",stdin);
	uint n, T;
	scanf("%u%u", &n, &T);
	scanf("%u%u", &a, &b);
//	cout<<n<<" "<<T<<endl;
	while(T--)
	{
        uint limit = 1<<n;
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        for(uint i = 0; i < limit; i++)
        {
            f[i] = nextRand();
//            cout<<f[i]<<" ";
        }
//        cout<<endl;
        for(uint i = 0; i < limit; i++)
        {
            g[i] = nextRand();
//            cout<<g[i]<<" ";
        }
//        cout<<endl;
        uint len = limit<<1;
        fwt(f, len, 1);
        fwt(g, len, 1);
        for(uint i = 0; i < len; i++)
            f[i] = f[i] * g[i] % mod;
        fwt(f, len, -1);
        uint ans = 0;
        for(uint i = 0; i < limit; i++)
        {
//            cout<<f[i]<<" ";
            ans += f[i] * (i+1)%mod;
        }
//        cout<<endl;
        printf("%u\n", ans);
	}
    return 0;
}


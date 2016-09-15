/*
*	注意到相邻两个数之间的绝对值符号只会在二进制位不同的最高位改变时才会改变，那么可以按照这个最高位分类，记
*	录每一位的数目，然后枚举X(0~1<<20),快速得到答案，但是如果直接O(400)去处理的话，会T，所以再加一个记忆化搜索
*	因为对于某个类别来说，最高位以下的数如果已经确定了的话，答案也已经确定了，用两个数组分别记忆最高位为0和为1的
*	答案
*/
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
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
const int N = 100010;
LL v1[1<<20][2];
LL v0[1<<20][2];
int num[33][33];
int a[N];
int cas = 0;
LL getval(int x, int idx)
{
//    if(v1[idx][x] != -1) return v1[idx][x];
    int tag = x&((1<<(idx+1))-1);
    if((x&(1<<idx)) && v1[tag][1] == cas) return v1[tag][0];
    if((x&(1<<idx)) == 0 && v0[tag^(1<<idx)][1] == cas) return v0[tag^(1<<idx)][0];
    bool bitid = x&(1<<idx);
    LL res = (1LL<<idx)*num[idx][idx];
    for(LL i = idx-1; i >= 0; i--)
    {
        bool bitcu = x & (1<<i);
        if(bitid == bitcu) res += (1LL<<i)*num[idx][i];
        else res -= (1LL<<i)*num[idx][i];
    }
    if(x&(1<<idx)) v1[tag][0] = res, v1[tag][1] = cas;
    else v0[tag^(1<<idx)][0] = res, v0[tag^(1<<idx)][1] = cas;
    return res;
}
struct Reader{
    static const int MSIZE = 1000 * 8 * 1024;
    char buf[MSIZE], *pt = buf, *o = buf;
    void init(){
        fread(buf, 1, MSIZE, stdin);
    }
    char getch()
    {
        char ch;
        while((*pt < 'A' || *pt > 'Z') && (*pt < 'a' || *pt > 'z')) pt++;
        ch = *pt;pt++;
        return ch;
    }
    int getint()
    {
        int f = 1, x = 0;
        while(*pt != '-' && !isdigit(*pt)) pt++;
        if(*pt == '-') f = -1, pt++;
        else x = *pt++ - 48;
        while(isdigit(*pt)) x = x * 10 + *pt++ - 48;
        return x * f;
    }
}frd;
int main(){
////    freopen("1006.in","r",stdin);
//    freopen("/home/qingping/in.txt","r",stdin);
    //cout<<31-__builtin_clz(3)<<endl;
    frd.init();
    int T;
    T = frd.getint();
    //scanf("%d", &T);
    while(T--)
    {
        cas++;
//        memset(v1, -1, sizeof(v1));
//        memset(v0, -1, sizeof(v0));
        memset(num, 0, sizeof(num));
        int n;
        n = frd.getint();
        //scanf("%d", &n);
        for(int i = 0; i < n; i++)
            //scanf("%d",&a[i]);
            a[i] = frd.getint();
        for(int i = 0; i < n; i++)
        {
            if(i && a[i] != a[i-1])
            {
                int l = 31-__builtin_clz(a[i]^a[i-1]);
                for(int j = l; j >= 0; j--)
                {
                    int iv = (a[i]&(1<<j)), pv = (a[i-1]&(1<<j));
                    if(iv == pv) continue;
                    if((a[i] > a[i-1]) == (iv > pv)) num[l][j]++;
                    else num[l][j]--;
                }
            }
        }
        int ax = 1<<21;
        LL ans = INF;
        for(int x = 0; x < (1<<20); x++)
        {
            LL res = 0;
            for(int i = 19; i >= 0; i--)
            {
                res += getval(x, i);
                if(res >= ans) break;
            }
            if(ans > res)
            {
                ans = res;
                ax = x;
            }
        }
        printf("%d %I64d\n", ax, ans);
    }
    return 0;
}


#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAXN = 10010;
long long a[MAXN];
long long N,M;

vector<long long> factor;

void getFactor(long long m)
{
    factor.clear();
    int limit = sqrt(m+1);
    for(int i = 2; i <= limit; ++i){
        if(m % i == 0){
            factor.push_back(i);
            if(m / i != i)
                factor.push_back(m / i);
        }
    }
    sort(factor.begin(),factor.end());
}

int cnt[MAXN];

long long solve()
{
    memset(cnt,0,sizeof(cnt));
    for(int i = 0; i < N; ++i){
        long long g = __gcd(a[i],M);
        if(g == 1)
            return (long long)M * (M -1) / 2;
        for(int i = factor.size() - 1; i >= 0; --i){
            long long l = factor[i] * g / __gcd(factor[i],g);
            int id = lower_bound(factor.begin(),factor.end(),l) - factor.begin();
            int inc = cnt[i] * -1;
            cnt[id] += inc;
        }
        int id = lower_bound(factor.begin(),factor.end(),g) - factor.begin();
        cnt[id]++;
    }
    long long sum = 0;
    for(int i = 0; i < factor.size(); ++i){
        long long n = M / factor[i];
        sum += cnt[i] * n * (n-1) / 2 * factor[i];
    }
    return sum;
}


int main(void)
{
   // freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    scanf("%d",&T);
    for(int cas = 1; cas <= T; ++ cas){
        scanf("%lld%lld",&N,&M);
        getFactor(M);
        for(int i = 0; i < N; ++i)
            scanf("%lld",&a[i]);
        printf("Case #%d: %lld\n",cas,solve());
    }
    return 0;
}

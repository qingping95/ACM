//
int prime[N];
int pn;
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
}

//--------------------O(n)筛法------------------------//
bool pvis[N];
int pri[N];
int prin;
void getpri(){
    prin = 0;
    memset(pvis, 0, sizeof(pvis));
    for(int i = 2; i < N; i++) {
        if(pvis[i] == 0) pri[prin++] = i;
        for(int j = 0; j < prin && (long long)pri[j]*i < N; j++) {
            pvis[pri[j]*i] = 1;
            if(i % pri[j] == 0) break;
        }
    }
}

// ----------------------频繁分解质因数时使用，最优算法------------------------------- // 

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <set>
#include <map>
#include <unordered_map>
#define lson x<<1
#define rson x<<1|1
#define mid ((lt[x].l+lt[x].r)/2)
#define mkpr make_pair
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const int mod = 1e9+7;
const int INF=0x3f3f3f3f;
const int N = 200010;
set<pair<int, int> > plist[N];
int gcd_pc[N];
int nxt[N];
unordered_map<int, int> pcount[N];
void get_prime()
{
	for (int i = 2; i < N; ++i) {
        if (nxt[i] == 0) {
            nxt[i] = i;
            if (i > 10000) continue;
            for (int j = i * i; j < N; j += i) {
                if (nxt[j] == 0) nxt[j] = i;
            }
        }
    }
}

int main()
{
	get_prime();
	int n, q;
	scanf("%d%d", &n, &q);
	int ans = 1;
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		if(i == 1) ans = x;
		else ans = __gcd(ans, x);
		while(x != 1)
		{
			int pri = nxt[x];
			int cnt = 0;
			while(nxt[x] == pri)
			{
				cnt += 1;
				x /= nxt[x];
			}
			if(cnt == 0) continue;
			plist[pri].insert(PII(cnt, i));
			pcount[i][pri] = cnt;
		}
	}
	while(q--)
	{
		int idx, x;
		scanf("%d%d", &idx, &x);
		while(x != 1)
		{
			int pri = nxt[x];
			int cnt = 0;
			while(nxt[x] == pri)
			{
				cnt += 1;
				x /= nxt[x];
			}
			if(cnt == 0) continue;
			int gcd_cnt = (int)plist[pri].size() == n ? plist[pri].begin()->first : gcd_pc[pri];
			int old_cnt = pcount[idx][pri];
			int new_cnt = old_cnt + cnt;
			plist[pri].erase(mkpr(old_cnt, idx));
			plist[pri].insert(mkpr(new_cnt, idx));
			pcount[idx][pri] = new_cnt;
			if((int)plist[pri].size() == n){
				int cur_gcd_cnt = plist[pri].begin()->first;
				for(int k = gcd_cnt; k < cur_gcd_cnt; k++)
				{
					ans = (LL)ans * pri % mod;
				}
				while(plist[pri].begin()->first == cur_gcd_cnt) plist[pri].erase(plist[pri].begin());
				gcd_pc[pri] = cur_gcd_cnt;
			}
		}
		printf("%d\n", ans);
	}
	
	return 0;
}

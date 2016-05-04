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

const LL NN = 100010;
LL a[NN];
LL dp[NN], num[NN], tmp[NN];
LL sta[NN];
vector<LL> G[NN];
const LL mod = 1000000007;
LL pow_mod(LL x, LL k, LL mod)
{
    LL res = 1;
    while(k)
    {
        if(k & 1) res = res * x % mod;
        x = x * x % mod;
        k >>= 1;
    }
    return res%mod;
}
void dfs(LL u, LL f)
{
    num[u] = 1;
    dp[u] = 0;
    LL son = 0;
    for(LL i = 0; i < G[u].size(); i++)
    {
        LL v = G[u][i];
        //if(v == f) continue;
        dfs(v, u);
        son++;
        num[u] += num[v];
    }
    LL sumoftmp = 0;
    for(LL v : G[u])
    {
        sta[v] = tmp[v] * pow_mod(2, num[u]-1-num[v], mod) % mod;
        sumoftmp += sta[v];
    }

    LL res = 0;
    tmp[u] = 0;
    for(LL v : G[u])
    {
        //if(v == f) continue;
        dp[u] = (dp[u] + dp[v] * pow_mod(2, num[u]-num[v], mod) % mod) % mod;
        dp[u] = (dp[u] + tmp[v]*2%mod*pow_mod(2, num[u]-1-num[v], mod) % mod) % mod;
        LL inv = pow_mod(pow_mod(2, num[v], mod), mod-2, mod);
        res = (res + tmp[v] * (sumoftmp - sta[v]) % mod * inv % mod) % mod;
        tmp[u] = (tmp[u] + tmp[v] * pow_mod(2, num[u] - num[v] - 1, mod) % mod)%mod;
    }
    dp[u] = (dp[u] + res) % mod;
    tmp[u] = (tmp[u] + pow_mod(2, num[u]-1, mod))%mod;
}

class TreeWalker {
public:
   LL calc( LL N, LL A0, LL B, LL C, LL MOD ) {
        a[0] = A0;
        for(LL i = 0; i < N; i++) G[i].clear();
        for(LL i = 1; i < N - 1; i++)
            a[i] = (B*a[i-1]%MOD+C)%MOD;
        for(LL i = 1; i < N; i++)
        {
            LL j = a[i-1] % i;
            //G[i].push_back(j);
            G[j].push_back(i);
        }
        dfs(0, -1);
        return dp[0];
   }
};

// BEGIN CUT HERE
namespace moj_harness {
	LL run_test_case(LL);
	void run_test(LL casenum = -1, bool quiet = false) {
		if ( casenum != -1 ) {
			if ( run_test_case( casenum ) == -1 && !quiet )
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
			return;
		}

		LL correct = 0, total = 0;
		for ( LL i=0;; ++i ) {
			LL x = run_test_case(i);
			if ( x == -1 ) {
				if ( i >= 100 ) break;
				continue;
			}
			correct += x;
			++total;
		}

		if ( total == 0 ) {
			cerr << "No test cases run." << endl;
		} else if ( correct < total ) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}

	LL verify_case(LL casenum, const LL &expected, const LL &received, clock_t elapsed) {
		cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if ( expected == received ) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}

		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (LL i=0; i<(LL)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;

		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl;
			cerr << "    Received: " << received << endl;
		}

		return verdict == "PASSED";
	}

	LL run_test_case( LL casenum ) {
		switch( casenum ) {
		case 0: {
			LL N                     = 10;
			LL A0                    = 0;
			LL B                     = 0;
			LL C                     = 0;
			LL MOD                   = 1;
			LL expected__            = 13824;
			clock_t start__           = clock();
			LL received__            = TreeWalker().calc( N, A0, B, C, MOD );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {

			LL N                     = 4;
			LL A0                    = 0;
			LL B                     = 1;
			LL C                     = 1;
			LL MOD                   = 1000;
			LL expected__            = 34;

			clock_t start__           = clock();
			LL received__            = TreeWalker().calc( N, A0, B, C, MOD );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			LL N                     = 16;
			LL A0                    = 15;
			LL B                     = 1;
			LL C                     = 1;
			LL MOD                   = 16;
			LL expected__            = 917506;

			clock_t start__           = clock();
			LL received__            = TreeWalker().calc( N, A0, B, C, MOD );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			LL N                     = 1000;
			LL A0                    = 385498676;
			LL B                     = 349131547;
			LL C                     = 115776323;
			LL MOD                   = 614879544;
			LL expected__            = 245566366;

			clock_t start__           = clock();
			LL received__            = TreeWalker().calc( N, A0, B, C, MOD );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			LL N                     = 100000;
			LL A0                    = 111222333;
			LL B                     = 444555666;
			LL C                     = 777888999;
			LL MOD                   = 123456789;
			LL expected__            = 119729770;

			clock_t start__           = clock();
			LL received__            = TreeWalker().calc( N, A0, B, C, MOD );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 5: {
			LL N                     = ;
			LL A0                    = ;
			LL B                     = ;
			LL C                     = ;
			LL MOD                   = ;
			LL expected__            = ;

			clock_t start__           = clock();
			LL received__            = TreeWalker().calc( N, A0, B, C, MOD );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			LL N                     = ;
			LL A0                    = ;
			LL B                     = ;
			LL C                     = ;
			LL MOD                   = ;
			LL expected__            = ;

			clock_t start__           = clock();
			LL received__            = TreeWalker().calc( N, A0, B, C, MOD );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 7: {
			LL N                     = ;
			LL A0                    = ;
			LL B                     = ;
			LL C                     = ;
			LL MOD                   = ;
			LL expected__            = ;

			clock_t start__           = clock();
			LL received__            = TreeWalker().calc( N, A0, B, C, MOD );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
		default:
			return -1;
		}
	}
}


int main(LL argc, char *argv[]) {
//    int MOD = 991;
//    cout<<pow_mod(512, MOD-2, MOD)<<endl;
//    cout<<pow_mod(pow_mod(2, 9, MOD), MOD-2, MOD)<<endl;

//	if (argc == 1) {
		moj_harness::run_test();
//	} else {
//		for (LL i=1; i<argc; ++i)
//			moj_harness::run_test(atoi(argv[i]));
//	}
}
// END CUT HERE

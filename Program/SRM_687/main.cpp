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

LL f[111];
vector<int> ans;
class AlmostFibonacciKnapsack {
public:
   vector <int> getIndices( long long x ) {
       LL judge = x;
        ans.clear();
        f[0] = 2, f[1] = 3;
        LL pre = f[1];
        int n = 0;
        for(int i = 2; pre < 1000000000000000000LL; i++)
        {
            f[i] = pre = f[i-1] + f[i-2] - 1;
            n = i;
        }
        int up = 23;
        int sum = 0;
        for(int i = 0; i < up; i++) sum += f[i];
        sum -= 3;
        int idx = n+1;
        while(x > sum)
        {
            idx--;
            if(x >= f[idx] + 2)
            {
                x -= f[idx];
                ans.push_back(idx+1);
            }
        }
        for(int s = 0; s < (1 << up); s++)
        {
            int num = 0;
            for(int i = 0; i < up; i++)
            {
                if(s & (1 << i))
                {
                    num += f[i];
                }
            }
            if(num == x)
            {
                for(int i = 0; i < up; i++)
                    if(s & (1 << i)) ans.push_back(i+1);
                break;
            }
        }
        return ans;
   }
};

// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if ( casenum != -1 ) {
			if ( run_test_case( casenum ) == -1 && !quiet )
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
			return;
		}

		int correct = 0, total = 0;
		for ( int i=0;; ++i ) {
			int x = run_test_case(i);
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

	template<typename T> ostream& operator<<( ostream &os, const vector<T> &v ) { os << "{"; for ( typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi ) { if ( vi != v.begin() ) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, clock_t elapsed) {
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
			for (int i=0; i<(int)info.size(); ++i) {
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

	int run_test_case( int casenum ) {
		switch( casenum ) {
		case 0: {
			long long x               = 148LL;
			int expected__[]          = {6, 10, 8, 5 };

			clock_t start__           = clock();
			vector <int> received__   = AlmostFibonacciKnapsack().getIndices( x );
			return verify_case( casenum, vector <int>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}
		case 1: {
			long long x               = 2LL;
			int expected__[]          = {1 };

			clock_t start__           = clock();
			vector <int> received__   = AlmostFibonacciKnapsack().getIndices( x );
			return verify_case( casenum, vector <int>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}
		case 2: {
			long long x               = 13LL;
			int expected__[]          = {2, 3, 4 };

			clock_t start__           = clock();
			vector <int> received__   = AlmostFibonacciKnapsack().getIndices( x );
			return verify_case( casenum, vector <int>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}
		case 3: {
			long long x               = 3LL;
			int expected__[]          = {2 };

			clock_t start__           = clock();
			vector <int> received__   = AlmostFibonacciKnapsack().getIndices( x );
			return verify_case( casenum, vector <int>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}
		case 4: {
			long long x               = 86267769395LL;
			int expected__[]          = {3, 14, 15, 9, 26, 53, 5, 8 };

			clock_t start__           = clock();
			vector <int> received__   = AlmostFibonacciKnapsack().getIndices( x );
			return verify_case( casenum, vector <int>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}

		// custom cases

/*      case 5: {
			long long x               = LL;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = AlmostFibonacciKnapsack().getIndices( x );
			return verify_case( casenum, vector <int>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}*/
/*      case 6: {
			long long x               = LL;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = AlmostFibonacciKnapsack().getIndices( x );
			return verify_case( casenum, vector <int>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}*/
/*      case 7: {
			long long x               = LL;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = AlmostFibonacciKnapsack().getIndices( x );
			return verify_case( casenum, vector <int>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}*/
		default:
			return -1;
		}
	}
}

bool vis[150010];
int main(int argc, char *argv[]) {
////    LL a1 = 2, a2 = 3;
////    LL a3 = a1 + a2 - 1;
////    LL cnt = 3;
//    f[0] = 2, f[1] = 3;
//    for(int i = 2; i <= 30; i++)
//        f[i] = f[i-2] + f[i-1] - 1;
//    int n = 23;
//    LL sum = 0;
//    for(int i = 0; i < n; i++) sum+= f[i];
//    cout<<sum<<endl;
//    for(int s = 0; s < (1 << n); s++)
//    {
//        LL num = 0;
//        for(int i = 0; i < n; i++)
//        {
//            if(s & (1 << i))
//            {
//                num += f[i];
//            }
//        }
//        if(num < 150010) vis[num] = 1;
//    }
//    int cnt = 0;
//    bool flag = true;
//    for(int i = 2; i < 150010; i++)
//    {
//        if(vis[i]) continue;
//        cnt++;
//        if(flag) flag = false, cout<<i<<endl;
//    }
//    cout<<cnt<<endl;
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE

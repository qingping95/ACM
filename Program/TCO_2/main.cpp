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


class TriangleTriples {
public:
   int count( int A, int B, int C ) {

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

	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) {
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
			int A                     = 1;
			int B                     = 10;
			int C                     = 20;
			int expected__            = 10;

			clock_t start__           = clock();
			int received__            = TriangleTriples().count( A, B, C );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			int A                     = 2;
			int B                     = 2;
			int C                     = 1000000000;
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = TriangleTriples().count( A, B, C );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			int A                     = 10;
			int B                     = 10;
			int C                     = 10;
			int expected__            = 505;

			clock_t start__           = clock();
			int received__            = TriangleTriples().count( A, B, C );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			int A                     = 1;
			int B                     = 1;
			int C                     = 1;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = TriangleTriples().count( A, B, C );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			int A                     = 123456789;
			int B                     = 987654321;
			int C                     = 555555555;
			int expected__            = 64296241;

			clock_t start__           = clock();
			int received__            = TriangleTriples().count( A, B, C );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 5: {
			int A                     = ;
			int B                     = ;
			int C                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TriangleTriples().count( A, B, C );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			int A                     = ;
			int B                     = ;
			int C                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TriangleTriples().count( A, B, C );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 7: {
			int A                     = ;
			int B                     = ;
			int C                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TriangleTriples().count( A, B, C );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE

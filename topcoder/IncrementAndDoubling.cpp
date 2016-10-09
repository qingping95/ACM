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


class IncrementAndDoubling {
public:
   int getMin( vector <int> desiredArray ) {

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
			int desiredArray[]        = {2, 1};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = IncrementAndDoubling().getMin( vector <int>( desiredArray, desiredArray + ( sizeof desiredArray / sizeof desiredArray[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			int desiredArray[]        = {16, 16, 16};
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = IncrementAndDoubling().getMin( vector <int>( desiredArray, desiredArray + ( sizeof desiredArray / sizeof desiredArray[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			int desiredArray[]        = {100};
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = IncrementAndDoubling().getMin( vector <int>( desiredArray, desiredArray + ( sizeof desiredArray / sizeof desiredArray[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			int desiredArray[]        = {0, 0, 1, 0, 1};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = IncrementAndDoubling().getMin( vector <int>( desiredArray, desiredArray + ( sizeof desiredArray / sizeof desiredArray[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			int desiredArray[]        = {123, 234, 345, 456, 567, 789};
			int expected__            = 40;

			clock_t start__           = clock();
			int received__            = IncrementAndDoubling().getMin( vector <int>( desiredArray, desiredArray + ( sizeof desiredArray / sizeof desiredArray[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 5: {
			int desiredArray[]        = {7,5,8,1,8,6,6,5,3,5,5,2,8,9,9,4,6,9,4,4,1,9,9,2,8,4,7,4,8,8,6,3,9,4,3,4,5,1,9,8,3,8,3,7,9,3,8,4,4,7};
			int expected__            = 84;

			clock_t start__           = clock();
			int received__            = IncrementAndDoubling().getMin( vector <int>( desiredArray, desiredArray + ( sizeof desiredArray / sizeof desiredArray[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 6: {
			int desiredArray[]        = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = IncrementAndDoubling().getMin( vector <int>( desiredArray, desiredArray + ( sizeof desiredArray / sizeof desiredArray[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 7: {
			int desiredArray[]        = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = IncrementAndDoubling().getMin( vector <int>( desiredArray, desiredArray + ( sizeof desiredArray / sizeof desiredArray[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 8: {
			int desiredArray[]        = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = IncrementAndDoubling().getMin( vector <int>( desiredArray, desiredArray + ( sizeof desiredArray / sizeof desiredArray[0] ) ) );
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

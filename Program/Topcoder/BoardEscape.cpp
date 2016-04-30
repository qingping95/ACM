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


class BoardEscape {
public:
   string findWinner( vector <string> s, int k ) {

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
	
	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) { 
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
			cerr << "    Expected: \"" << expected << "\"" << endl; 
			cerr << "    Received: \"" << received << "\"" << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case( int casenum ) {
		switch( casenum ) {
		case 0: {
			string s[]                = {"TE"};
			int k                     = 2;
			string expected__         = "Alice";

			clock_t start__           = clock();
			string received__         = BoardEscape().findWinner( vector <string>( s, s + ( sizeof s / sizeof s[0] ) ), k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			string s[]                = {"E#E",  "#T#",  "E#E"};
			int k                     = 1000000;
			string expected__         = "Bob";

			clock_t start__           = clock();
			string received__         = BoardEscape().findWinner( vector <string>( s, s + ( sizeof s / sizeof s[0] ) ), k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			string s[]                = {"T.T.T.",  ".E.E.E"};
			int k                     = 1;
			string expected__         = "Alice";

			clock_t start__           = clock();
			string received__         = BoardEscape().findWinner( vector <string>( s, s + ( sizeof s / sizeof s[0] ) ), k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			string s[]                = {"TTE"};
			int k                     = 6;
			string expected__         = "Alice";

			clock_t start__           = clock();
			string received__         = BoardEscape().findWinner( vector <string>( s, s + ( sizeof s / sizeof s[0] ) ), k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			string s[]                = {"..........................",  "......TTT..TTT..T...T.....",  ".....T.....T..T.TT.TT.....",  "......TTT..TTT..T.T.T.....",  ".........T.T.T..T...T.....",  "......TTT..T..T.T...T.....",  "..........................",  "...E#E#E#E#E#E#E#E#E#E#...",  "..........................",  "......TTT..TTT...TTT......",  ".....T........T.T.........",  "......TTT.....T..TTT......",  ".....T...T...T..T...T.....",  "......TTT....T...TTT......",  "..........................",  "...#E#E#E#E#E#E#E#E#E#E...",  "..........................",  "....TT...T...T..T.TTT.T...",  "...T.....T...T..T.T...T...",  "...T.TT..T...TTTT.TT..T...",  "...T..T..T...T..T.T.......",  "....TT...TTT.T..T.T...T...",  ".........................."};
			int k                     = 987654321;
			string expected__         = "Bob";

			clock_t start__           = clock();
			string received__         = BoardEscape().findWinner( vector <string>( s, s + ( sizeof s / sizeof s[0] ) ), k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 5: {
			string s[]                = ;
			int k                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = BoardEscape().findWinner( vector <string>( s, s + ( sizeof s / sizeof s[0] ) ), k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			string s[]                = ;
			int k                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = BoardEscape().findWinner( vector <string>( s, s + ( sizeof s / sizeof s[0] ) ), k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 7: {
			string s[]                = ;
			int k                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = BoardEscape().findWinner( vector <string>( s, s + ( sizeof s / sizeof s[0] ) ), k );
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

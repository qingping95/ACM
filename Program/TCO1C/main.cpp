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

/*
preB - B
preC:
0 -- ÎÞC
1 -- C
2 -- CX
*/
bool dp[55][55][55][2][3];
char ans[55];
bool dfs(int A, int B, int C, int preB, int preC, int idx)
{
    if(A == 0 && B == 0 && C == 0) return true;
    if(dp[A][B][C][preB][preC]) return false;
    int n = A+B+C;
    if(n < 3*(C-1)+1 || n < 2*B-1)
    {
        dp[A][B][C][preB][preC] = true;
        return false;
    }
    if(A > 0 && dfs(A-1, B, C, 0, ((preC == 1)? 2: 0), idx+1))
    {
        ans[idx] = 'A';
        return true;
    }
    if(B > 0 && preB < 1 && dfs(A, B-1, C, 1, ((preC == 1)? 2: 0), idx+1))
    {
        ans[idx] = 'B';
        return true;
    }
    if(C > 0 && preC < 1 && dfs(A, B, C-1, 0, 1, idx+1))
    {
        ans[idx] = 'C';
        return true;
    }
    dp[A][B][C][preB][preC] = true;
    return false;
}
class ThreeProgrammers {
public:
    string validCodeHistory( string code ) {
        memset(dp, 0, sizeof(dp));
        int A = 0, B = 0, C = 0;
        for(int i = 0; i < code.length(); i++)
        {
            if(code[i] == 'A') A++;
            if(code[i] == 'B') B++;
            if(code[i] == 'C') C++;
        }
        if(!dfs(A, B, C, 0, 0, 0)) return string("impossible");
        else {
            ans[A+B+C] = '\0';
            //cout<<string(ans)<<endl;
            return string(ans);
        }
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
			string code               = "CABCABC";
			string expected__         = "CABCABC";

			clock_t start__           = clock();
			string received__         = ThreeProgrammers().validCodeHistory( code );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			string code               = "CBB";
			string expected__         = "BCB";

			clock_t start__           = clock();
			string received__         = ThreeProgrammers().validCodeHistory( code );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			string code               = "BB";
			string expected__         = "impossible";

			clock_t start__           = clock();
			string received__         = ThreeProgrammers().validCodeHistory( code );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			string code               = "BBA";
			string expected__         = "BAB";

			clock_t start__           = clock();
			string received__         = ThreeProgrammers().validCodeHistory( code );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			string code               = "CAC";
			string expected__         = "impossible";

			clock_t start__           = clock();
			string received__         = ThreeProgrammers().validCodeHistory( code );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 5: {
			string code               = "ACAC";
			string expected__         = "CAAC";

			clock_t start__           = clock();
			string received__         = ThreeProgrammers().validCodeHistory( code );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 6: {
			string code               = "ACABC";
			string expected__         = "ACABC";

			clock_t start__           = clock();
			string received__         = ThreeProgrammers().validCodeHistory( code );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 7: {
			string code               = "BAABCABBCCACBAACABAABABBCCAACABCCAACCABCACACCBABAB";
			string expected__         = "BACBABCAACBACABCBACBACABCBACBACABCABCAACBACAACABCA";

			clock_t start__           = clock();
			string received__         = ThreeProgrammers().validCodeHistory( code );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 8: {
			string code               = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = ThreeProgrammers().validCodeHistory( code );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 9: {
			string code               = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = ThreeProgrammers().validCodeHistory( code );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 10: {
			string code               = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = ThreeProgrammers().validCodeHistory( code );
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

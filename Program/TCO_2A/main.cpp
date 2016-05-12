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


int a[444], b[444];
bool vis[444];
class LCMGCD {
public:
   string isPossible( vector <int> x, int t ) {
        int t2 = 0, t3 = 0;
        while(t%2 == 0) t >>= 1, t2++;
        while(t%3 == 0) t /=  3, t3++;
        int idx = -1;
        for(int i = 0; i < x.size(); i++)
        {
            vis[i] = 0;
            int tmp = x[i];
            a[i] = b[i] = 0;
            while(tmp%2 == 0) tmp >>= 1, a[i]++;
            while(tmp%3 == 0) tmp /=  3, b[i]++;
            if(a[i] == t2 && b[i] == t3) idx = i;
        }
        if(idx != -1){
            int big = 0, sma = 0;
            bool flag = false;
            for(int i = 0; i < x.size(); i++)
            {
                if(i == idx) continue;
                if(a[i] < t2 && b[i] > t3) sma++;
                else if(a[i] > t2 && b[i] < t3) big++;
                else flag = true;
            }
            if(flag) return "Possible";
            else{
                if((big+sma>0) && (big == 0 || sma == 0)) return "Impossible";
                else return "Possible";
            }
        }else{
            int idx3 = -1;
            for(int i = 0; i < x.size(); i++)
            {
                if(a[i] == t3){
                    idx3 = i;
                    break;
                }
            }
            if(idx3 == -1) return "Impossible";
            idx = -1;
            for(int i = 0; i < x.size(); i++)
            {
                if(a[i] == t2){
                    idx = i;
                    break;
                }
            }
            if(idx == -1) return "Impossible";

            vis[idx] = 1;
            int idx2 = -1;
            for(int i = 0; i < x.size(); i++)
            {
                if(vis[i]) continue;
                if(min(a[i], a[idx]) == t2 && min(b[i], b[idx]) == t3)
                {
                    idx2 = i;
                    break;
                }
                if(max(a[i], a[idx]) == t2 && max(b[i], b[idx]) == t3)
                {
                    idx2 = i;
                    break;
                }
            }
            if(idx2 != -1) {
                vis[idx2] = 1;
                int big = 0, sma = 0;
                bool flag = false;
                for(int i = 0; i < x.size(); i++)
                {
                    if(vis[i]) continue;
                    if(a[i] < t2 && b[i] > t3) sma++;
                    else if(a[i] > t2 && b[i] < t3) big++;
                    else flag = true;
                }
                if(flag) return "Possible";
                else{
                    if((big+sma>0) && (big == 0 || sma == 0)) return "Impossible";
                    else return "Possible";
                }
            }else{
                vis[idx3] = 1;
                int big = 0, sma = 0;
                bool flag = false;
                for(int i = 0; i < x.size(); i++)
                {
                    if(vis[i]) continue;
                    if(a[i] < t2 && b[i] > t3) sma++;
                    else if(a[i] > t2 && b[i] < t3) big++;
                    else flag = true;
                }
                if(b[idx] < t3 && sma > 0){
                    sma = 0;
                    if(flag) return "Possible";
                    else{
                        if((big+sma>0) && (big == 0 || sma == 0)) return "Impossible";
                        else return "Possible";
                    }
                }else if(b[idx] > t3 && big > 0){
                    big = 0;
                    if(flag) return "Possible";
                    else{
                        if((big+sma>0) && (big == 0 || sma == 0)) return "Impossible";
                        else return "Possible";
                    }
                }
                return "Impossible";
            }
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
			int x[]                   = {2,3};
			int t                     = 6;
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = LCMGCD().isPossible( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), t );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			int x[]                   = {4,9};
			int t                     = 6;
			string expected__         = "Impossible";

			clock_t start__           = clock();
			string received__         = LCMGCD().isPossible( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), t );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			int x[]                   = {6,12,24,18,36,72,54,108,216};
			int t                     = 36;
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = LCMGCD().isPossible( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), t );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			int x[]                   = {6,27,81,729};
			int t                     = 6;
			string expected__         = "Impossible";

			clock_t start__           = clock();
			string received__         = LCMGCD().isPossible( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), t );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			int x[]                   = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
			int t                     = 1;
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = LCMGCD().isPossible( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), t );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 5: {
			int x[]                   = {72,16,16,16,16,16,27,27,27,27,27,27,27,27,27};
			int t                     = 72;
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = LCMGCD().isPossible( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), t );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 6: {
			int x[]                   = {100663296, 544195584, 229582512, 59049};
			int t                     = 60466176;
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = LCMGCD().isPossible( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), t );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 7: {
			int x[]                   = {2,4,8,16,32,64};
			int t                     = 256;
			string expected__         = "Impossible";

			clock_t start__           = clock();
			string received__         = LCMGCD().isPossible( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), t );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 8: {
			int x[]                   = ;
			int t                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = LCMGCD().isPossible( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), t );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 9: {
			int x[]                   = ;
			int t                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = LCMGCD().isPossible( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), t );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 10: {
			int x[]                   = ;
			int t                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = LCMGCD().isPossible( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), t );
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

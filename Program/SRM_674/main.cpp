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
//typedef int LL;
using namespace std;


class PlaneGame {
public:
    bool isline(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        int ux = x2 - x1, uy = y2 - y1;
        int vx = x3 - x1, vy = y3 - y1;
        cout<<"Debug: " <<uy*vx<<endl;
        cout<<"Debug: " <<vy*ux<<endl;
        return uy * vx == vy * ux;
    }
    bool ischuizhi(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
    {
        int ux = x2 - x1, uy = y2 - y1;
        int vx = x4 - x3, vy = y4 - y3;
        cout<<"Debug: " <<ux*vx<<endl;
        cout<<"Debug: " <<vy*uy<<endl;
        return ux * vx + uy * vy == 0;
    }
    int bestShot( vector <int> x, vector <int> y ) {
        if(x.size() <= 3) return x.size();
        int ans = 0;
        for(int i = 0; i < x.size(); i++)
        {
            for(int j = i+1; j < x.size(); j++)
            {
                for(int k = 0; k < x.size(); k++)
                {
                    if(i == k || k == j) continue;
                    int res = 3;
                    for(int l = 0; l < x.size(); l++)
                    {
                        if(i == l || j == l || k == l) continue;
                        if(isline(x[i], y[i], x[j], y[j], x[l], y[l]))
                        {
                            res++;
                            continue;
                        }
                        if(ischuizhi(x[i], y[i], x[j], y[j], x[k], y[k], x[l], y[l]))
                        {
                            res++;
                            continue;
                        }
                    }
                    ans = max(ans, res);
                }
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
			int x[]                   = {0, 5};
			int y[]                   = {0, 5};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = PlaneGame().bestShot( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), vector <int>( y, y + ( sizeof y / sizeof y[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			int x[]                   = {0, -1, 1, 1, -1};
			int y[]                   = {0, -1, -1, 1, 1};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = PlaneGame().bestShot( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), vector <int>( y, y + ( sizeof y / sizeof y[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			int x[]                   = {0, 0, 0, 1, -1};
			int y[]                   = {0, 1, -1, 0, 0};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = PlaneGame().bestShot( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), vector <int>( y, y + ( sizeof y / sizeof y[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			int x[]                   = {0, -3, 3, 3, -3, 0, 0, 3, -3};
			int y[]                   = {0, -3, -3, 3, 3, 3, -3, 0, 0};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = PlaneGame().bestShot( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), vector <int>( y, y + ( sizeof y / sizeof y[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			int x[]                   = {0};
			int y[]                   = {0};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = PlaneGame().bestShot( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), vector <int>( y, y + ( sizeof y / sizeof y[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 5: {
			int x[]                   = {-1000000, -1, 999998, 1, -1001, 1000000, -999999, 999999, 0, 0};
			int y[]                   = {1000000, 1, 1000000, -1, -999, 1000000, 0, 0, -999999, 999999};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = PlaneGame().bestShot( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), vector <int>( y, y + ( sizeof y / sizeof y[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 6: {
			int x[]                   = ;
			int y[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PlaneGame().bestShot( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), vector <int>( y, y + ( sizeof y / sizeof y[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 7: {
			int x[]                   = ;
			int y[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PlaneGame().bestShot( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), vector <int>( y, y + ( sizeof y / sizeof y[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 8: {
			int x[]                   = ;
			int y[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PlaneGame().bestShot( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), vector <int>( y, y + ( sizeof y / sizeof y[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
//	if (argc == 1) {
//		moj_harness::run_test();
//	} else {
//		for (int i=1; i<argc; ++i)
//			moj_harness::run_test(atoi(argv[i]));
//	}
	vector<int> x, y;
	x.push_back(1000000);
	x.push_back(-1000000);
	x.push_back(-300000);
	x.push_back(-900000);
	y.push_back(500000);
	y.push_back(-500000);
	y.push_back(300000);
	y.push_back(-900000);
	cout<<"test: " << PlaneGame().bestShot(x, y)<<endl;
}
// END CUT HERE

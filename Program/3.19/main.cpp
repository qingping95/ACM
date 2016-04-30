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


class MultiplicationTable2 {
public:
    int deep = 0;
    int n;
    vector<int> T;
    int sta[55];
    bool vis[55];
    bool dfs(int dep, int idx)
    {
        if(dep == deep){
            for(int i = 0; i < dep; i++)
            {
                for(int j = 0; j < dep; j++)
                {
                    if(vis[T[sta[i]*n+sta[j]]]) continue;
                    else return false;
                }
            }
            return true;
        }
        for(int i = idx; i < n; i++)
        {
            sta[dep] = i;
            vis[i] = 1;
            if(dfs(dep+1, i+1)) return true;
            vis[i] = 0;
        }
        return false;
    }
   int minimalGoodSet( vector <int> table ) {
        n = 0;
        for(n = 1; n*n <= table.size(); n++)
        {
            if(n*n == table.size()) break;
        }
        for(int i = 0; i < table.size(); i++)
            T.push_back(table[i]);
        int ans = n;
        for(int i = 0; i < n; i++)
        {
            queue<int> que;
            int tail = 0;
            memset(vis, 0, sizeof(vis));
            vis[i] = 1;
            sta[tail++] = i;
            if(vis[table[i*n+i]] == 0)
                que.push(table[i*n+i]), vis[table[i*n+i]] = 1, sta[tail++] = table[i*n+i];
            while(!que.empty())
            {
                int u = que.front(); que.pop();
                int up = tail;
                for(int i = 0; i < up;i++)
                    for(int j = 0; j < up; j++)
                {
                    int cur = T[sta[i]*n+sta[j]];
                    if(vis[cur] == 0)
                    {
                        que.push(cur);
                        vis[cur] = 1;
                        sta[tail++] = cur;
                    }
                }
            }
            ans = min(ans, tail);
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
			int table[]               = {1,1,2,3,  1,0,3,2,  2,0,1,3,  1,2,3,0};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = MultiplicationTable2().minimalGoodSet( vector <int>( table, table + ( sizeof table / sizeof table[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			int table[]               = {0,1,2,3,  1,2,3,0,  2,3,0,1,  3,0,1,2};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = MultiplicationTable2().minimalGoodSet( vector <int>( table, table + ( sizeof table / sizeof table[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			int table[]               = {1,1,1,1,  2,2,2,2,  3,3,3,3,  0,0,0,0};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = MultiplicationTable2().minimalGoodSet( vector <int>( table, table + ( sizeof table / sizeof table[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			int table[]               = {0};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = MultiplicationTable2().minimalGoodSet( vector <int>( table, table + ( sizeof table / sizeof table[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 4: {
			int table[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MultiplicationTable2().minimalGoodSet( vector <int>( table, table + ( sizeof table / sizeof table[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 5: {
			int table[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MultiplicationTable2().minimalGoodSet( vector <int>( table, table + ( sizeof table / sizeof table[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			int table[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MultiplicationTable2().minimalGoodSet( vector <int>( table, table + ( sizeof table / sizeof table[0] ) ) );
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

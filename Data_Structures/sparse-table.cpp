#include <bits/stdc++.h>
using namespace std;

// time complexity:
//  - filling DP table: O(N log N)
//  - answering queries: O (log N)

namespace SparseTable {
    const int MAXN = 10000;
    const int MAXLOG = 31 - __builtin_clz(MAXN);
    int DP[MAXN][MAXLOG+1];
    vector<int>* values;

    void reset(vector<int>& _values) {
        values = &_values;
        // we are using -1 to mark unsolved cells in the DP table,
        // so make sure -1 is not a valid value, otherwise use
        // a different value
        memset(DP, -1, sizeof DP);
    }

    // dp(i,e) = min { values[j] } for j in {i, i+1, ..., i+2^e-1}
    int dp(int i, int e) { 
        int& ans = DP[i][e];
        if (ans != -1) return ans;
        if (e == 0) return ans = (*values)[i];
        return ans = dp(i, e-1) + dp(i+(1<<(e-1)), e-1);
    }

    // range minimun query
    // rmq(l,r) = min { values[j] } for j in {l, l+1, ..., r}
    int rmq(int l, int r) {
        int ans = INT_MAX;
        int d = r-l+1;
        assert (d >= 1);
        int i = l;
        for (int e = 0; d; e++, d>>=1) {
            if (d & 1) {
                ans = min(ans, dp(i, e));
                i += 1 << e;
            }
        }
        assert (i == r);
        return ans;
    }
}

// example of usage
int main() {
    vector<int> values = {1, 3, 4, 3, 1, 6, 7, 4, 8, 9};
    SparseTable::reset(values);
    while (true) {
        int l, r; cin >> l >> r; // read query
        cout << SparseTable::rmq(l,r) << '\n'; // print minimum
    }
    return 0;    
}
#include <bits/stdc++.h>
using namespace std;

// time complexity:
//  - filling DP table: O(N log N)
//  - answering queries: O(1) / O(log N)

template<class t> class SparseTable {
    int n;
    vector<int> memo, *arr;    
public:
    SparseTable(vector<int>& _arr) {
        arr = &_arr;
        n = arr->size();
        int maxlog = 31 - __builtin_clz(n);
        memo.assign(n * (maxlog + 1), -1);
    }
    int dp(int i, int e) { 
        int& ans = memo[e * n + i];
        if (ans != -1) return ans;
        if (e == 0) return ans = (*arr)[i];
        return ans = t::merge(dp(i, e-1), dp(i+(1<<(e-1)), e-1));
    }
    // option 1: complexity O(1)
    // ** only works if queries can overlap (e.g. max, min, OR)
    int query_O1(int l, int r) {
        int e = 31 - __builtin_clz(r - l + 1);
        return t::merge(dp(l,e), dp(r - (1 << e) + 1, e));
    }    
    // option 2: complexity O(log N)
    int query_Ologn(int l, int r) {
        int ans = t::neutro;
        int d = r-l+1;
        for (int e = 0; d; e++, d>>=1) {
            if (d & 1) {
                ans = t::merge(ans, dp(l, e));
                l += 1 << e;
            }
        }
        return ans;
    }
};
struct RangeMin {
    static const int neutro = INT_MAX;
    static int merge(int x, int y) { return min(x, y); }
};
struct RangeMax {
    static const int neutro = INT_MIN;
    static int merge(int x, int y) { return max(x, y); }
};
struct RangeOR {
    static const int neutro = 0;
    static int merge(int x, int y) { return x | y; }
};


// example of usage
int main() {
    vector<int> arr = {1, 3, 4, 3, 1, 6, 7, 4, 8, 9};
    SparseTable<RangeMin> st_min(arr);
    SparseTable<RangeMax> st_max(arr);
    while (true) {
        int l, r; cin >> l >> r; // read query
        cout << st_min.query_O1(l,r) << '\n'; // print min
        cout << st_max.query_O1(l,r) << '\n'; // print max
    }
    return 0;    
}
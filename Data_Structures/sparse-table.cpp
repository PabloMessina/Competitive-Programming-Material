#include <bits/stdc++.h>
using namespace std;

// time complexity:
//  - filling DP table: O(N log N)
//  - answering queries: O(1) / O(log N)

struct SparseTable {
    int n;
    vector<int> memo;
    vector<int>* arr;
    SparseTable(vector<int>& _arr) {
        arr = &_arr;
        n = arr->size();
        int maxlog = 31 - __builtin_clz(n);
        memo.assign(n * (maxlog + 1), -1);
    }
    // dp(i,e) = min { arr[j] } for j in {i, i+1, ..., i+2^e-1}
    int dp(int i, int e) { 
        int& ans = memo[e * n + i];
        if (ans != -1) return ans;
        if (e == 0) return ans = (*arr)[i];
        return ans = dp(i, e-1) + dp(i+(1<<(e-1)), e-1);
    }
    
    // ---- RMQ = Range Minimun Query ----
    // rmq(l,r) = min { arr[j] } for j in {l, l+1, ..., r}
    
    // option 1: complexity O(1)
    int rmq_O1(int l, int r) {
        int e = 31 - __builtin_clz(r - l + 1);
        return min(dp(l,e), dp(r - (1 << e) + 1, e));
    }
    
    // option 2: complexity O(log N)
    int rmq_Ologn(int l, int r) {
        int ans = INT_MAX;
        int d = r-l+1;
        for (int e = 0; d; e++, d>>=1) {
            if (d & 1) {
                ans = min(ans, dp(l, e));
                l += 1 << e;
            }
        }
        return ans;
    }
};

// example of usage
int main() {
    vector<int> arr = {1, 3, 4, 3, 1, 6, 7, 4, 8, 9};
    SparseTable st(arr);
    while (true) {
        int l, r; cin >> l >> r; // read query
        cout << st.rmq_O1(l,r) << '\n'; // print minimum
    }
    return 0;    
}
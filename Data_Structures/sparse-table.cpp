#include <bits/stdc++.h>
using namespace std;
// time complexity:
//  - filling DP table: O(N log N)
//  - answering queries: O(1) / O(log N)
// ---------- recursive ---------------
template<class t> struct SparseTable {
    int n; vector<int> memo, log2, *arr;
    SparseTable(vector<int>& _arr) {
        arr = &_arr; log2.resize(n+1); n = arr->size();
        rep(i,2,n+1) log2[i] = 1 + log2[i >> 1];
        memo.assign(n * (log2[n] + 1), -1);
    }
    int dp(int i, int e) {
        int& ans = memo[e][i];
        if (ans != -1) return ans;
        if (e == 0) return ans = (*arr)[i];
        return ans = t::merge(dp(i, e-1), dp(i+(1<<(e-1)), e-1));
    }
    // option 1: complexity O(1)
    // ** only works if queries can overlap (e.g. max, min, or, and)
    int query_O1(int l, int r) {
        int e = log2[r - l + 1];
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
// ---------- iterative ---------------
template<class t> struct SparseTable {
    int n; vector<int> log2; vector<vector<int>> st;
    SparseTable(vector<int>& _arr) {
        log2.resize(n+1); n = arr->size();
        rep(i,2,n+1) log2[i] = 1 + log2[i >> 1];
        int maxe = log2[n];
        st.assign(n, vector<int>(maxe+1));
        rep(i,0,n) st[i][0] = arr[i];
        rep(e,1,maxe+1) {
            int d = 1 << (e-1);
            rep(i,0,n) {
                int j = i + d;
                st[i][e] = j < n ? t::merge(st[i][e-1], st[j][e-1]) : st[i][e-1];
            }            
        }
    }
    // option 1: complexity O(1)
    // ** only works if queries can overlap (e.g. max, min, or, and)
    int query_O1(int l, int r) {
        int e = log2[r - l + 1];
        return t::merge(st[l][e], st[r - (1 << e) + 1][e]);
    }    
    // option 2: complexity O(log N)
    int query_Ologn(int l, int r) {
        int ans = t::neutro;
        int d = r-l+1;
        for (int e = 0; d; e++, d>>=1) {
            if (d & 1) {
                ans = t::merge(ans, st[l][e]);
                l += 1 << e;
            }
        }
        return ans;
    }
};
struct MIN {
    static const int neutro = INT_MAX;
    static int merge(int x, int y) { return min(x, y); }
};
struct MAX {
    static const int neutro = INT_MIN;
    static int merge(int x, int y) { return max(x, y); }
};
struct OR {
    static const int neutro = 0;
    static int merge(int x, int y) { return x | y; }
};
// example of usage
int main() {
    vector<int> arr = {1, 3, 4, 3, 1, 6, 7, 4, 8, 9};
    SparseTable<MIN> st_min(arr);
    SparseTable<MAX> st_max(arr);
    while (true) {
        int l, r; cin >> l >> r; // read query
        cout << st_min.query_O1(l,r) << '\n'; // print min
        cout << st_max.query_O1(l,r) << '\n'; // print max
    }
    return 0;    
}
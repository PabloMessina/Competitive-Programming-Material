// tags: sparse tables, binary search, difference array, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
template<class t> struct SparseTable {
    int n; vector<int> memo, *arr;
    SparseTable(vector<int>& _arr) {
        arr = &_arr; n = arr->size();
        int maxlog = 31 - __builtin_clz(n);
        memo.assign(n * (maxlog + 1), -1);
    }
    int dp(int i, int e) {
        int& ans = memo[e * n + i];
        if (ans != -1) return ans;
        if (e == 0) return ans = (*arr)[i];
        return ans = t::merge(dp(i, e-1), dp(i+(1<<(e-1)), e-1));
    }
    int query(int l, int r) {
        int e = 31 - __builtin_clz(r - l + 1);
        return t::merge(dp(l,e), dp(r - (1 << e) + 1, e));
    }
};
struct MAX {
    static const int neutro = INT_MIN;
    static int merge(int x, int y) { return max(x, y); }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    vector<int> H(N);
    for (int& x : H) cin >> x;
    vector<int> D(N+1);
    SparseTable<MAX> st(H);
    rep(i,0,N) {
        int a, b, l, r;
        
        l = i+1, r = N;
        while (l < r) {
            int m = (l + r) >> 1;
            if (st.query(i, m) > H[i]) {
                r = m;
            } else {
                l = m+1;
            }
        }
        if (l == N) b = N-1;
        else b = l-1 > i ?  i + (l-1-i)/2 : i;

        l = 1, r = i+1;
        while (l < r) {
            int m = (l + r) >> 1;
            if (st.query(i-m, i) > H[i]) {
                r = m;
            } else {
                l = m+1;
            }
        }
        if (l == i+1) a = 0;
        else a = l-1 > 0 ? i - (l-1)/2 : i;

        assert (0 <= a and  a <= b and b < N);
        D[a]++;
        D[b+1]--;
    }
    int ans = 0;
    rep(i,0,N) {
        ans += D[i];
        if (i) cout << ' ';
        cout << ans - 1;
    }
    cout << '\n';
    return 0;
}
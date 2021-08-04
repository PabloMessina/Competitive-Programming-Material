// tags: implementation, stacks, histogram, rmq
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
struct MIN {
    static const int neutro = INT_MAX;
    static int merge(int x, int y) { return min(x, y); }
};
struct MAX {
    static const int neutro = INT_MIN;
    static int merge(int x, int y) { return max(x, y); }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    vector<int> A(N);
    for (int& x : A) cin >> x;
    vector<int> L(N), R(N);
    {
        stack<ii> s;
        s.emplace(-1, 0);
        rep(i,0,N) {
            if (A[i] == -1) L[i] = -1;
            else {
                while (s.top().ss >= A[i]) s.pop();
                L[i] = s.top().ff;
                s.emplace(i, A[i]);
            }
        }
    }
    {
        stack<ii> s;
        s.emplace(N, 0);
        invrep(i,N-1,0) {
            if (A[i] == -1) R[i] = N;
            else {
                while (s.top().ss >= A[i]) s.pop();
                R[i] = s.top().ff;
                s.emplace(i, A[i]);
            }
        }
    }
    SparseTable<MIN> st_r(R);
    SparseTable<MAX> st_l(L);
    bool ans = false;
    rep(k,3,N+1) {
        if (N % k == 0 or N % k >= 3) {
            ans = true;
            for (int i = 0; i < N; i += k) {
                int j = min(i+k-1, N-1);
                int c = st_r.query(i, j) - i;
                int d = j - st_l.query(i, j);
                if (c == 1 or d == 1 or c + d <= j - i + 1) { ans = false; break; }
            }
            if (ans) break;
        }
    }
    if (ans) cout << "Y\n";
    else cout << "N\n";
}
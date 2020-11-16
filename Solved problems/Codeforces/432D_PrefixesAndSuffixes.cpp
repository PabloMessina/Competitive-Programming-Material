// tags: suffix array, sparse table, stack, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define ff first
#define ss second
typedef pair<int,int> ii;
// -------------------------------
struct SA {
    int n;
    vector<int> counts, rank, rank_, sa, sa_, lcp;
    inline int gr(int i) { return i < n ? rank[i]: 0; }
    void csort(int maxv, int k) {
        counts.assign(maxv+1, 0);
        rep(i,0,n) counts[gr(i+k)]++;
        rep(i,1,maxv+1) counts[i] += counts[i-1];
        invrep(i,n-1,0) sa_[--counts[gr(sa[i]+k)]] = sa[i];
        sa.swap(sa_);
    }
    void get_sa(vector<int>& s) {
        rep(i,0,n) sa[i] = i;
        sort(sa.begin(), sa.end(), [&s](int i, int j) { return s[i] < s[j]; });
        int r = rank[sa[0]] = 1;
        rep(i,1,n) rank[sa[i]] = (s[sa[i]] != s[sa[i-1]]) ? ++r : r;
        for (int h=1; h < n and r < n; h <<= 1) {
            csort(r, h); csort(r, 0); r = rank_[sa[0]] = 1;
            rep(i,1,n) {
                if (rank[sa[i]] != rank[sa[i-1]] or
                    gr(sa[i]+h) != gr(sa[i-1]+h)) ++r;
                rank_[sa[i]] = r;
            } rank.swap(rank_);
        }
    }
    void get_lcp(vector<int>& s) {
        lcp.assign(n, 0);
        int k = 0;
        rep(i,0,n) {
            int r = rank[i]-1;
            if (r == n-1) { k = 0; continue; }
            int j = sa[r+1];
            while (i+k<n and j+k<n and s[i+k] == s[j+k]) k++;
            lcp[r] = k;
            if (k) k--;
        }
    }
    SA(vector<int>& s) {
        n = s.size();
        rank.resize(n); rank_.resize(n);
        sa.resize(n); sa_.resize(n);
        get_sa(s); get_lcp(s);
    }
};
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
    string s; cin >> s;
    vector<int> s_; for (char c : s) s_.push_back(c);
    SA sa(s_);
    SparseTable<MIN> st_min(sa.sa);
    SparseTable<MAX> st_max(sa.sa);
    int n = s.size();
    vector<int> L(n), R(n), S;
    rep(i,0,n-1) {
        while (S.size() and sa.lcp[S.back()] >= sa.lcp[i]) S.pop_back();
        L[i] = S.size() ? S.back() + 1 : 0;
        S.push_back(i);
    }
    S.clear();
    invrep(i,n-2,0) {
        while (S.size() and sa.lcp[S.back()] >= sa.lcp[i]) S.pop_back();
        R[i] = S.size() ? S.back() - 1 : (n-2);
        S.push_back(i);
    }
    set<ii> pairs;
    rep(i,0,n-1) {
        int a = st_min.query(L[i], R[i]+1);
        int b = st_max.query(L[i], R[i]+1);
        if (a == 0 and b + sa.lcp[i] == n) {
            pairs.emplace(sa.lcp[i], R[i] - L[i] + 2);
        }
    }
    pairs.emplace(n, 1);
    cout << pairs.size() << '\n';
    for (auto& p : pairs) cout << p.ff << ' ' << p.ss << '\n';
    return 0;
}
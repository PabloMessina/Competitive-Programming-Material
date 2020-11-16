// tags: suffix array, LCP, sparse table, bitmask, stacks, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define uset unordered_set
typedef long long int ll;
// -------------------------------
struct SA {
    int n; vector<int> counts, rank, rank_, sa, sa_, lcp;
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
        get_sa(s); get_lcp(s); // lcp is optional
    }
};
template<class t> struct SparseTable {
    int n; vector<ll> memo, *arr;
    SparseTable(vector<ll>& _arr) {
        arr = &_arr; n = arr->size();
        int maxlog = 31 - __builtin_clz(n);
        memo.assign(n * (maxlog + 1), -1);
    }
    ll dp(int i, int e) {
        ll& ans = memo[e * n + i];
        if (ans != -1) return ans;
        if (e == 0) return ans = (*arr)[i];
        return ans = t::merge(dp(i, e-1), dp(i+(1<<(e-1)), e-1));
    }
    ll query(int l, int r) {
        int e = 31 - __builtin_clz(r - l + 1);
        return t::merge(dp(l,e), dp(r - (1 << e) + 1, e));
    }
};
struct OR {
    static const ll neutro = 0;
    static ll merge(ll x, ll y) { return x | y; }
};

const int MAXLEN = 60 + 10000 * 60;
int F;
vector<int> S; // stores concatenation of all strings
vector<ll> masks, masks_tmp;
int L[MAXLEN], R[MAXLEN];
vector<int> suffix_len;
vector<pair<int,int>> _stack;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    // reserve memory for worst case
    S.reserve(MAXLEN);
    masks.reserve(MAXLEN);
    masks_tmp.reserve(MAXLEN);
    suffix_len.reserve(MAXLEN);
    _stack.reserve(MAXLEN);
    // for each test case
    while (cin >> F and F) {
        // -- reset some vectors
        S.clear();
        masks_tmp.clear();
        suffix_len.clear();
        // -- read input
        rep(i,1,F+1) { // for each file
            string f; cin >> f;
            ll mask = 1LL << (i-1); // file mask
            int j = 0;
            for (char c : f) { // for each char in file
                S.push_back(F+1 + c-'a'); // append char as int (shifted by F)
                masks_tmp.push_back(mask); // append string mask
                suffix_len.push_back(f.size() - j++); // append suffix length
            }
            S.push_back(i); // append extra "separator" char (unique for each string)
            masks_tmp.push_back(mask); // append mask
            suffix_len.push_back(0); // append suffix length
        }
        // build suffix array from S (all files concatenated)
        SA sa(S);
        int n = S.size();
        // rewrite masks in suffix array order
        masks.resize(n);
        rep(i,0,n) masks[i] = masks_tmp[sa.sa[i]];
        // build sparse table on top of masks
        SparseTable<OR> st(masks);
        // uset to keep track of disctinct subsets
        uset<ll> sets;

        // *** Note: below we start from F because the first F suffixes
        // in the suffix array are the F "end of string" values we used
        // as separators (when we concatenated everything), so we ignore them

        // --- CASE 1: queries that match only a single suffix
        //  i-th suffix's length must be greater than LCP[i-1] and LCP[i]
        rep(i,F,n) {
            int slen = suffix_len[sa.sa[i]];
            if (i > F and sa.lcp[i-1] == slen) continue;
            if (sa.lcp[i] == slen) continue;
            sets.insert(masks[i]);
        }

        // ---- CASE 2: queries that match 2 or more suffixes.
        // we can think of the LCP array as heights of columns in a histogram,
        // then the range of columns matched by a query is equivalent to the range
        // of the largest rectangle that both contains and has the same height as the
        // shortest column in that range. Thus, for each column we need to find the maximum
        // range (left, right) a rectangle can be expanded horizontally from that column.
        // This can be done in O(N) with stacks:
        //  https://stackoverflow.com/questions/4311694/maximize-the-rectangular-area-under-histogram        
        //  ** good practice problem for this: https://www.spoj.com/problems/HISTOGRA/

        // 1) fill L array (left)
        _stack.clear();
        _stack.emplace_back(F, -1);
        rep(i,F,n) {
            while (_stack.back().second >= sa.lcp[i]) _stack.pop_back();
            L[i] = _stack.back().first;
            _stack.emplace_back(i+1, sa.lcp[i]);
        }
        // 2) fill R array (right)
        _stack.clear();
        _stack.emplace_back(n, -1);
        invrep(i,n-1,F) {
            while (_stack.back().second >= sa.lcp[i]) _stack.pop_back();
            R[i] = _stack.back().first;
            _stack.emplace_back(i, sa.lcp[i]);
        }
        // 3) find subsets in [L, R] ranges using sparse table
        rep(i,F,n) {
            if (sa.lcp[i] > 0) {
                ll mask = st.query(L[i], R[i]);
                sets.insert(mask);
            }
        }
        // finally: answer the number of distinct subsets found
        cout << sets.size() << '\n';
    }
    return 0;
}
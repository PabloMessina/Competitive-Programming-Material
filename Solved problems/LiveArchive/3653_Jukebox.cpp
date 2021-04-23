// Correct solution, but gets TLE :(
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define ff first
#define ss second
// -------------------------------
struct SA {
    int n; vector<int> counts, rank, rank_, sa, sa_;
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
    SA(vector<int>& s) {
        n = s.size();
        rank.resize(n); rank_.resize(n);
        sa.resize(n); sa_.resize(n);
        get_sa(s);
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
struct OR {
    static const int neutro = 0;
    static int merge(int x, int y) { return x | y; }
};
int N;
string songs[30], artists[30];
int offsets[30];
bool use_artist[30] = {};
map<string, vector<int>> a2idxs;
int lower_bound(string& s, vector<int>& sa, char c, int o, int l, int r) {
    while (l < r) {
        int m = (l+r)/2;
        char mc = o + sa[m] < s.size() ? s[o + sa[m]] : '\0';
        if (mc >= c) r = m;
        else l = m+1;
    }
    return l;
}
int upper_bound(string& s, vector<int>& sa, char c, int o, int l, int r) {
    while (l < r) {
        int m = (l+r)/2;
        char mc = o + sa[m] < s.size() ? s[o + sa[m]] : '\0';
        if (mc > c) r = m;
        else l = m+1;
    }
    return l;
}
int golden_string_size(int i, SA& sa, string& s, SparseTable<OR>& st) {
    int ans = INT_MAX;
    int n = songs[i].size();
    rep(j,0,n) {
        int l = 0, r = s.size();
        for (int k = 0; k + j < n; ++k) {
            if (k+1 >= ans) break;
            int l_next = lower_bound(s, sa.sa, songs[i][j+k], k, l, r);
            int r_next = upper_bound(s, sa.sa, songs[i][j+k], k, l, r);
            assert (l_next < r_next);
            l = l_next, r = r_next;
            int q = st.query(l, r-1);
            assert(q > 0);
            if ((q & -q) == q) { ans = min(ans, k+1); break; }
        }
    }
    if (use_artist[i]) {
        int n = artists[i].size();
        rep(j,0,n) {
            int l = 0, r = s.size();
            for (int k = 0; k + j < n; ++k) {
                if (k+1 >= ans) break;
                int l_next = lower_bound(s, sa.sa, artists[i][j+k], k, l, r);
                int r_next = upper_bound(s, sa.sa, artists[i][j+k], k, l, r);
                assert (l_next < r_next);
                l = l_next, r = r_next;
                int q = st.query(l, r-1);
                assert(q > 0);
                if ((q & -q) == q) { ans = min(ans, k+1); break; }
            }
        }
    }
    return ans;
}
vector<int> ids, ids_;
int solve() {
    string concat = "";
    ids.clear();
    rep(i,0,N) {
        int a = concat.size();
        concat += songs[i];
        if (use_artist[i]) {
            concat += '@';
            concat += artists[i];
        }
        concat += ',';
        int b = concat.size();
        rep(_,a,b) ids.push_back(1 << i);
    }
    vector<int> s; for (char c : concat) s.push_back(c);
    SA sa(s);
    ids_.resize(ids.size());
    rep(i,0,sa.sa.size()) ids_[i] = ids[sa.sa[i]];
    ids_.swap(ids);
    SparseTable<OR> st(ids);
    int ans = 0;
    rep(i,0,N) {
        int tmp = golden_string_size(i, sa, concat, st);
        if (tmp == INT_MAX) {ans = INT_MAX; break;}
        ans += tmp;
    }
    // cout << concat << " " << ans << '\n';
    return ans;
}
int final_ans;
void search(map<string,vector<int>>::iterator it) {
    if (it == a2idxs.end()) {
        final_ans = min(final_ans, solve());
        return;
    }
    search(next(it));
    for (int i : it->ss) {
        use_artist[i] = true;
        search(next(it));
        use_artist[i] = false;
    }
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ids.reserve(10000); ids_.reserve(10000);
    while (cin >> N and N) {
        a2idxs.clear();
        rep(i,0,N) {
            cin >> songs[i] >> artists[i];
            a2idxs[artists[i]].push_back(i);
            use_artist[i] = false;
        }
        final_ans = INT_MAX;
        search(a2idxs.begin());
        cout << final_ans << '\n';
    }
    return 0;
}
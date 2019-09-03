// tags: suffix array, LCP, sparse table, bitmask, stacks, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define uset unordered_set
typedef long long int ll;
// -------------------------------
struct SuffixArray {
    int n;
    vector<int> rank, rank_tmp, sa, sa_tmp;
    vector<int> lcp;
    vector<int> counts;
    int inline get_rank(int i) { return i < n ? rank[i]: 0; }
    void counting_sort(int maxv, int k) {
        counts.assign(maxv+1, 0);
        rep(i,0,n-1) counts[get_rank(i+k)]++;
        rep(i,1,maxv) counts[i] += counts[i-1];
        invrep(i,n-1,0) sa_tmp[--counts[get_rank(sa[i]+k)]] = sa[i];
        sa.swap(sa_tmp);
    }
    void compute_sa(vector<int>& s, int maxv) {
        n = s.size();
        rep(i,0,n-1) sa[i] = i, rank[i] = s[i];
        for (int h=1; h < n; h <<= 1) {
            counting_sort(maxv, h);
            counting_sort(maxv, 0);
            int r = 1;
            rank_tmp[sa[0]] = r;
            rep(i,1,n-1) {
                if (rank[sa[i]] != rank[sa[i-1]] or
                    get_rank(sa[i]+h) != get_rank(sa[i-1]+h)) r++;
                rank_tmp[sa[i]] = r;
            }
            swap(rank, rank_tmp);
            maxv = r;
        }
    }
    void compute_lcp(vector<int>& s) {
        lcp.assign(n, 0);
        int k = 0;
        rep(i,0,n-1) {
            int r = rank[i]-1;
            if (r == n-1) { k = 0; continue; }
            int j = sa[r+1];
            while (i+k<n and j+k<n and s[i+k] == s[j+k]) k++;
            lcp[r] = k;
            if (k) k--;
        }
    }
    SuffixArray(vector<int>& s) {
        n = s.size();
        rank.resize(n); rank_tmp.resize(n);
        sa.resize(n); sa_tmp.resize(n);
        int maxv = *max_element(s.begin(), s.end());
        compute_sa(s, maxv);
        compute_lcp(s);
    }
};

struct SparseTable {
    int n;
    vector<ll> memo;
    vector<ll>* arr;
    SparseTable(vector<ll>& _arr) {
        arr = &_arr;
        n = arr->size();
        int maxlog = 31 - __builtin_clz(n);
        memo.assign(n * (maxlog + 1), -1);
    }
    ll dp(int i, int e) { 
        ll& ans = memo[e * n + i];
        if (ans != -1) return ans;
        if (e == 0) return ans = (*arr)[i];
        return ans = dp(i, e-1) | dp(i+(1<<(e-1)), e-1);
    }
    ll query(int l, int r) {
        int e = 31 - __builtin_clz(r - l + 1);
        return dp(l,e) | dp(r - (1 << e) + 1, e);
    }
};

const int MAXLEN = 60 + 10000 * 60;
int F;
vector<int> S;
vector<ll> masks, masks_tmp;
int L[MAXLEN], R[MAXLEN];
vector<int> suffix_len;
vector<pair<int,int>> _stack;

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    S.reserve(MAXLEN);
    masks.reserve(MAXLEN);
    masks_tmp.reserve(MAXLEN);
    suffix_len.reserve(MAXLEN);
    _stack.reserve(MAXLEN);
    while (cin >> F and F) {
        S.clear();
        masks_tmp.clear();
        suffix_len.clear();
        rep(i,1,F) {
            string f; cin >> f;
            ll mask = 1LL << (i-1);
            int j = 0;
            for (char c : f) {
                S.push_back(F+1 + c-'a');
                masks_tmp.push_back(mask);
                suffix_len.push_back(f.size() - j++);
            }
            S.push_back(i);
            masks_tmp.push_back(mask);
            suffix_len.push_back(0);
        }
        SuffixArray sa(S);
        int n = S.size();
        masks.resize(n);
        rep(i,0,n-1) masks[i] = masks_tmp[sa.sa[i]];
        SparseTable st(masks);
        uset<ll> sets;
        rep(i,F,n-1) {
            int slen = suffix_len[sa.sa[i]];
            if (i > F and sa.lcp[i-1] == slen) continue;
            if (sa.lcp[i] == slen) continue;
            sets.insert(masks[i]);
        }
        _stack.clear();
        _stack.emplace_back(F, -1);
        rep(i,F,n-1) {
            while (_stack.back().second >= sa.lcp[i]) _stack.pop_back();
            L[i] = _stack.back().first;
            _stack.emplace_back(i+1, sa.lcp[i]);
        }
        _stack.clear();
        _stack.emplace_back(n, -1);
        invrep(i, n-1, F) {
            while (_stack.back().second >= sa.lcp[i]) _stack.pop_back();
            R[i] = _stack.back().first;
            _stack.emplace_back(i, sa.lcp[i]);
        }
        rep(i,F,n-1) {
            if (sa.lcp[i] > 0) {
                ll mask = st.query(L[i], R[i]);
                sets.insert(mask);
            }
        }
        cout << sets.size() << '\n';
    }
    return 0;
}
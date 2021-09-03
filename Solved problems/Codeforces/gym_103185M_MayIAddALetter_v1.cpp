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
const int MAXN = 200005;

struct SuffixArrayTree {
    vector<vi> g, A, rmq;
    vi P, D, L, rank, rank_, sa, log2;
    int curr, n;
    
    ll HP = 1e9+21;
    vector<ll> H;
    vector<ll> POW;
    ll B = 131;

    struct cmp {
        vi* rank;
        cmp() {}
        cmp(vi& rank) { this->rank = &rank; }
        bool operator()(int i, int j) { return (*rank)[i] < (*rank)[j]; }
    };
    set<int, cmp> act;

    SuffixArrayTree() {
        curr = 0;
        g.reserve(MAXN); g.emplace_back(26, -1);
        P.reserve(MAXN); P.push_back(0);
        D.reserve(MAXN); D.push_back(0);
        L.reserve(MAXN); L.push_back(0);
        rank.reserve(MAXN); rank.push_back(-1);
    }
    void push(int c) {
        if (g[curr][c] == -1) {
            int nxt = g.size();
            g[curr][c] = nxt;
            g.emplace_back(26, -1);
            P.push_back(curr);
            D.push_back(D[curr]+1);
            L.push_back(c+1);
            rank.push_back(c);
        }
        curr = g[curr][c];
    }
    void pop() {
        curr = P[curr];
    }    
    void compute_ancestors() {
        n = g.size();
        log2.assign(n+1, 0);
        rep(i,2,n+1) log2[i] = 1 + log2[i>>1];
        int maxe = log2[n];
        A.assign(n, vector<int>(maxe+1, 0));
        rep(i,0,n) A[i][0] = P[i];
        rep(e, 1, maxe+1) rep(i,0,n) A[i][e] = A[A[i][e-1]][e-1];
    }
    void compute_ranks() {
        n = g.size();
        int maxd = *max_element(D.begin(), D.end());
        sa.resize(n); rep(i,0,n) sa[i] = i;
        sort(sa.begin(), sa.end(), cmp(rank));
        vector<ii> rr(n); rank_.resize(n);
        for (int h = 1; h < maxd; h <<= 1) {
            rep(i,0,n) rr[i] = make_pair(rank[i], rank[raise(i,h)]);
            sort(sa.begin(), sa.end(), [&rr](int i, int j) { return rr[i] < rr[j]; });
            int r = 0;
            rank_[sa[0]] = 0;
            rep(i,1,n) {
                if (rr[sa[i-1]] < rr[sa[i]]) r++;
                rank_[sa[i]] = r;
            }
            rank.swap(rank_);
        }
    }
    void compute_hashes() {
        H.resize(n);
        POW.resize(n);
        POW[0] = 1;
        rep(j,1,n) POW[j] = (POW[j-1] * B) % HP;
        queue<int> q({0}); H[0] = 0;
        while (q.size()) {
            int u = q.front(); q.pop();
            rep(i,0,26) {
                int v = g[u][i];
                if (v != -1) {
                    H[v] = (H[u] * B + L[v]) % HP;
                    q.push(v);
                }
            }
        }
    }
    ll get_hash(int u, int pu) {
        return (H[u] + HP - (H[P[pu]] * POW[D[u] - D[pu] + 1]) % HP) % HP;
    }
    int lcp_log2(int u, int v) {
        if (u == -1 or v == -1) return 0;
        int mind = min(D[u], D[v]);
        int l = 0, r = mind;
        while (l < r) {
            int m = (l+r) >> 1;
            int pu = raise(u, m), pv = raise(v, m);
            if (get_hash(u, pu) != get_hash(v, pv)) {
                r = m;
            } else {
                l = m+1;
            }
        }
        return l;
    }
    int lcp_o1(int u, int v) {
        if (u == -1 or v == -1) return 0;
        int l = rank[u], r = rank[v];
        int e = log2[r - l];
        int tmp = min(rmq[l][e], rmq[r-(1<<e)][e]);
        return tmp;
    }
    int compute_lcp_sparse_table() {
        int maxe = log2[n];
        rmq.assign(n, vector<int>(maxe+1, 0));
        rep(i,0,n-1) rmq[i][0] = lcp_log2(sa[i], sa[i+1]);
        rep(e,1,maxe+1) {
            rep(i,0,n) {
                int j = i + (1 << (e-1));
                rmq[i][e] = j < n ? min(rmq[i][e-1], rmq[j][e-1]) : rmq[i][e-1];
            }            
        }
    }
    int calc_contrib(set<int, cmp>::iterator it) {
        auto beg = act.begin();
        auto end = act.end();
        int u = *it;
        int a, b, c, d;
        auto aux = it;
        b = it == beg ? -1 : *(--it);
        a = it == beg ? -1 : *(--it);
        it = aux;
        c = next(it) == end ? -1 : *(++it);
        d = next(it) == end ? -1 : *(++it);
        int ab = lcp_o1(a, b), bc = lcp_o1(b, c), cd = lcp_o1(c, d), bu = lcp_o1(b, u), uc = lcp_o1(u, c), ans = 0;
        ans -= max(bc - ab, 0) + max(cd - bc, 0);
        ans += max(bu - ab, 0) + max(uc - bu, 0) + max(cd - uc, 0);
        return ans;
    }
    void run(string& s, int offset) {
        int curr = 0;     
        act = set<int, cmp>(cmp(rank));
        stack<ll> ans; ans.push(0);
        rep(i,0,s.size()) {
            char c = s[i];
            if (c == '-') {
                ans.pop();
                act.erase(curr);
                curr = P[curr];
            } else {
                curr = g[curr][c - 'A'];
                ans.push(ans.top() + calc_contrib(act.insert(curr).ff));
            }
            if (i >= offset) cout << ans.top() << '\n';
        }
    }
    private:
        int raise(int u, int k) {
            for (int e = 0; k; e++, k>>=1) if (k&1) u = A[u][e];
            return u;
        }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string s, u; cin >> s >> u; s += u;
    SuffixArrayTree tree;
    for (char c : s) {
        if (c == '-') tree.pop();
        else tree.push(c - 'A');
    }
    tree.compute_ancestors();
    tree.compute_ranks();
    tree.compute_hashes();
    tree.compute_lcp_sparse_table();
    tree.run(s, s.size() - u.size() - 1);
    return 0;
}
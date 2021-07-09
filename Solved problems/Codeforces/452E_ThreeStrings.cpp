// tags: strings, suffix array, union find, implementation
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
        lcp.assign(n, 0); int k = 0;
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
struct UnionFind {
    vector<int> p, rank, setSize;
    int numSets;
    UnionFind(int n) {
        numSets = n; setSize.assign(n, 1); rank.assign(n, 0); p.resize(n);
        rep(i,0,n) p[i] = i;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j) { 
        if (!isSameSet(i, j)) {
            numSets--; 
            int x = findSet(i), y = findSet(j);
            if (rank[x] > rank[y]) {
                p[y] = x; setSize[x] += setSize[y];
            } else {
                p[x] = y; setSize[y] += setSize[x];
                if (rank[x] == rank[y]) rank[y]++;
            }
        }
    }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};
const ll MOD = 1e9 + 7;
int C[3][300005] = {};
ll count_triples(int i, int j) {
    ll ans = 1;
    rep(k,0,3) {
        ll tmp = C[k][j] - (i > 0 ? C[k][i-1] : 0);
        ans = (ans * tmp) % MOD;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string s1, s2, s3; cin >> s1 >> s2 >> s3;
    string tmp = s1 + '#' + s2 + '$' + s3;
    vector<int> s; for (char c : tmp) s.push_back(c);
    SA sa(s);
    rep(i,0,s.size()) {
        if (sa.sa[i] < s1.size()) {
            C[0][i] = 1;
        } else if (sa.sa[i] > s1.size() and sa.sa[i] < s1.size() + s2.size() + 1) {
            C[1][i] = 1;
        } else if (sa.sa[i] > s1.size() + s2.size() + 1) {
            C[2][i] = 1;
        }
    }
    rep(k,0,3) rep(i,1,s.size()) C[k][i] += C[k][i-1];
    int L = min({s1.size(), s2.size(), s3.size()});
    vector<vector<ii>> P(s.size() + 1);
    rep(i,0,s.size()-1) {
        P[sa.lcp[i]].emplace_back(i,i+1);
    }
    ll sum = 0;
    ll ans[s.size()+1] = {};
    UnionFind uf(s.size());
    vector<ii> R(s.size());
    rep(i,0,s.size()) R[i] = {i, i};
    invrep(i,s.size(),1) {
        for (auto& p : P[i]) {
            int u = uf.findSet(p.ff);
            int v = uf.findSet(p.ss);
            if (u != v) {
                sum = (sum + MOD - count_triples(R[u].ff, R[u].ss)) % MOD;
                sum = (sum + MOD - count_triples(R[v].ff, R[v].ss)) % MOD;
                ii r = {min(R[u].ff, R[v].ff), max(R[u].ss, R[v].ss)};
                uf.unionSet(u, v);
                R[uf.findSet(u)] = r;
                sum = (sum + count_triples(r.ff, r.ss)) % MOD;
            }
        }
        ans[i] = sum;
    }
    rep(i,1,L+1) {
        if (i > 1) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
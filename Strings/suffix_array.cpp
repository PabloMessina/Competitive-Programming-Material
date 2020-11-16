// ========================================================
// Suffix Array Construction : Prefix Doubling + Radix Sort
// ========================================================
// Complexity: O(N*log(N))
// references: https://www.cs.helsinki.fi/u/tpkarkka/opetus/10s/spa/lecture11.pdf
// https://youtu.be/_TUeAdu-U_k
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
using namespace std;

struct SA {
    int n; vector<int> counts, rank, rank_, sa, sa_, lcp; // lcp is optional
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
    // LCP construction in O(N) using Kasai's algorithm
    // reference: https://codeforces.com/blog/entry/12796?#comment-175287
    void get_lcp(vector<int>& s) { // lcp is optional
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

int main() { // how to use
    string test; cin >> test;
    vector<int> s;
    for (char c : test) s.push_back(c);
    SA sa(s);
    for (int i : sa.sa) cout << i << ":\t" << test.substr(i) << '\n';
    rep(i,0,s.size()) {
        printf("LCP between %d and %d is %d\n", i, i+1, sa.lcp[i]);
    }
}
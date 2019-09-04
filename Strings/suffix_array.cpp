// ========================================================
// Suffix Array Construction : Prefix Doubling + Radix Sort
// ========================================================
// Complexity: O(N*log(N))
// reference: https://www.cs.helsinki.fi/u/tpkarkka/opetus/10s/spa/lecture11.pdf
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
using namespace std;

struct SuffixArray {
    int n;
    vector<int> counts, rank, rank_tmp, sa, sa_tmp;
    vector<int> lcp; // optional: only if lcp is needed
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
            rank.swap(rank_tmp);
            maxv = r;
        }
    }
    // LCP construction in O(N) using Kasai's algorithm
    // reference: https://codeforces.com/blog/entry/12796?#comment-175287
    void compute_lcp(vector<int>& s) { // optional: only if lcp array is needed
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
        compute_lcp(s); // optional: only if lcp array is needed
    }
};

int main() { // how to use
    string test; cin >> test;
    vector<int> s;
    for (char c : test) s.push_back(c - 'a' + 1); // make sure all values are >= 1
    SuffixArray sa(s);
    for (int i : sa.sa) cout << i << ":\t" << test.substr(i) << '\n';
    rep (i, 0, s.size() - 1) {
        printf("LCP between %d and %d is %d\n", i, i+1, sa.lcp[i]);
    }
}
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
// -------------------------------

struct SuffixArray {
    int n;
    vector<int> counts, rank, rank_tmp, sa, sa_tmp;
    vector<int> lcp;
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

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    string s1, s2; cin >> s1 >> s2;
    vector<int> S; 
    S.reserve(s1.size() + s2.size() + 2);
    for (char c : s1) S.push_back(c - 'a' + 3);
    S.push_back(1);
    for (char c : s2) S.push_back(c - 'a' + 3);
    S.push_back(2);
    SuffixArray sa(S);
    int n = S.size();
    int ans = INT_MAX;
    rep(i,2,n-2) {
        int ii = sa.sa[i];
        int jj = sa.sa[i+1];
        if ( (ii <= s1.size() and jj > s1.size()) or 
             (ii > s1.size() and jj <= s1.size()) ) {
            int ref = max(sa.lcp[i-1], sa.lcp[i+1]);
            if (sa.lcp[i] > ref) {
                ans = min(ans, ref+1);
            }
        }
    }
    if (ans == INT_MAX) cout << "-1\n";
    else cout << ans << '\n';
    return 0;
}
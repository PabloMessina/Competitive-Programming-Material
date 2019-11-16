// tags: suffix array, binary search, greedy
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
// -------------------------------
struct SuffixArray {
    int n;
    vector<int> counts, rank, rank_tmp, sa, sa_tmp;
    inline int get_rank(int i) { return i < n ? rank[i]: 0; }
    void counting_sort(int maxv, int k) {
        counts.assign(maxv+1, 0);
        rep(i,0,n) counts[get_rank(i+k)]++;
        rep(i,1,maxv+1) counts[i] += counts[i-1];
        invrep(i,n-1,0) sa_tmp[--counts[get_rank(sa[i]+k)]] = sa[i];
        sa.swap(sa_tmp);
    }
    void compute_sa(vector<int>& s) {
        rep(i,0,n) sa[i] = i;
        sort(sa.begin(), sa.end(), [&s](int i, int j) { return s[i] < s[j]; });
        int r = rank[sa[0]] = 1;
        rep(i,1,n) rank[sa[i]] = (s[sa[i]] != s[sa[i-1]]) ? ++r : r;
        for (int h=1; h < n and r < n; h <<= 1) {
            counting_sort(r, h);
            counting_sort(r, 0);
            r = rank_tmp[sa[0]] = 1;
            rep(i,1,n) {
                if (rank[sa[i]] != rank[sa[i-1]] or
                    get_rank(sa[i]+h) != get_rank(sa[i-1]+h)) ++r;
                rank_tmp[sa[i]] = r;
            }
            rank.swap(rank_tmp);
        }
    }
    SuffixArray(vector<int>& s) {
        n = s.size();
        rank.resize(n); rank_tmp.resize(n);
        sa.resize(n); sa_tmp.resize(n);
        compute_sa(s);
    }
};

int lower_bound(string& word, vector<int>& sa, char c, int offset, int l, int r) {
    while (l < r) {
        int m = (l+r)/2;
        char mc = offset + sa[m] < word.size() ? word[offset + sa[m]] : '\0';
        if (mc >= c) r = m;
        else l = m+1;
    }
    return l;
}

int upper_bound(string& word, vector<int>& sa, char c, int offset, int l, int r) {
    while (l < r) {
        int m = (l+r)/2;
        char mc = offset + sa[m] < word.size() ? word[offset + sa[m]] : '\0';
        if (mc > c) r = m;
        else l = m+1;
    }
    return l;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    string word, query;
    cin >> word;
    vector<int> s; s.reserve(word.size());
    for (char c : word) s.push_back(c);
    SuffixArray sa(s);
    int q; cin >> q;
    while (q--) {
        cin >> query;
        int count = 0;
        int i = 0;
        bool possible = true;
        while (1) {
            int l = 0, r = word.size();
            int offset = 0;
            while (i < query.size()) {
                char c = query[i];
                int l_next = lower_bound(word, sa.sa, c, offset, l, r);
                int r_next = upper_bound(word, sa.sa, c, offset, l, r);
                if (l_next == r_next) break;
                else {
                    ++offset;
                    ++i;
                    l = l_next, r = r_next;
                }
            }
            if (offset == 0) {
                possible = false;
                break;
            }            
            count++;
            if (i == query.size()) break;
        }
        if (possible) cout << count << '\n';
        else cout << "-1\n";
    } 
    return 0;
}
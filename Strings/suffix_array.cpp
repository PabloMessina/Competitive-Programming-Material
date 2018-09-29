// ========================================================
// Suffix Array Construction : Prefix Doubling + Radix Sort
// ========================================================
// Complexity: O(N*log(N))
// source: https://www.cs.helsinki.fi/u/tpkarkka/opetus/10s/spa/lecture11.pdf
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
using namespace std;

namespace SA {
    const int MAXN = (int)1e6;
    int n;
    int rank[MAXN], rank_tmp[MAXN];
    int sa[MAXN], sa_tmp[MAXN];
    int inline get_rank(int i) { return i < n ? rank[i]: 0; }
    
    // stable sort suffix array based on the ranking function:
    // sa[i] -> get_rank(sa[i] + k)
    void counting_sort(int maxv, int k) {
        static int counts[MAXN];
        memset(counts, 0, sizeof(int) * (maxv+1));
        rep(i,0,n-1) counts[get_rank(i+k)]++;
        rep(i,1,maxv) counts[i] += counts[i-1];
        invrep(i,n-1,0) sa_tmp[--counts[get_rank(sa[i]+k)]] = sa[i];
        swap(sa, sa_tmp);
    }
    
    // word: sequence of values
    // maxv: maximum value in 'word'
    // suffix_indexes: suffix indexes to be sorted
    void sort_suffix_indexes(vector<int>& word, int maxv, vector<int>& suffix_indexes) {
        n = word.size();
        rep(i,0,n-1) { sa[i] = i; rank[i] = word[i]; }
        for (int h=1; h < n; h <<= 1) {
            // two counting sort passes to achieve O(n) sorting complexity
            // (i.e. 2-pass radix sort)
            counting_sort(maxv, h);
            counting_sort(maxv, 0);
            // re-compute ranking
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
        // copy suffix indexes in their final order
        suffix_indexes.resize(n);
        rep(i,0,n-1) suffix_indexes[i] = sa[i];
    }

    void sort_suffix_indexes(vector<int>& word, vector<int>& suffix_indexes) {
        int maxv = 0;
        for (int v : word) if (maxv < v) maxv = v;
        sort_suffix_indexes(word, maxv, suffix_indexes);
    }
}

int main() { // testing
    string testword; cin >> testword;
    vector<int> w;
    for (char c : testword) w.push_back(c - 'a' + 1);
    vector<int> suffix_indexes;
    SA::sort_suffix_indexes(w, suffix_indexes);
    for (int i : suffix_indexes) cout << i << ":\t" << testword.substr(i) << endl;
}
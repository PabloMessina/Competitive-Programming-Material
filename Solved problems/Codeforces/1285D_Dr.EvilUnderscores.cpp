// tags: bitwise, trie, strings
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
struct Trie {
    vector<vector<int>> g;
    vector<int> count;
    int vocab;
    Trie(int vocab, int maxdepth = 10000) : vocab(vocab) {
        g.reserve(maxdepth);
        g.emplace_back(vocab, -1);
        count.reserve(maxdepth);
        count.push_back(0);
    }
    int move_to(int u, int c) {
        assert (0 <= c and c < vocab);
        int& v = g[u][c];
        if (v == -1) {
            v = g.size();
            g.emplace_back(vocab, -1);
            count.push_back(0);
        }
        count[v]++;
        return v;
    }
    void insert(const string& s, char ref = 'a') {  // insert string
        int u = 0; for (char c : s) u = move_to(u, c - ref);
    }    
    void insert(vector<int>& s) { // insert vector<int>
        int u = 0; for (int c : s) u = move_to(u, c);
    }
    int size() { return g.size(); }

    int min_xor(int u, int i) {
        bool zero = g[u][0] != -1;
        bool one = g[u][1] != -1;
        if (zero and not one) {
            return min_xor(g[u][0], i+1);
        }
        if (one and not zero) {
            return min_xor(g[u][1], i+1);
        }
        if (one and zero) {
            return min(min_xor(g[u][0], i+1), min_xor(g[u][1], i+1)) | (1 << (29 - i)) ;
        }
        return 0;
    }
};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    Trie trie(2);
    rep(i,0,n) {
        int x; cin >> x;
        vector<int> bits(30);
        rep(i,0,30) {
            bits[i] = (x >> (30 - i - 1)) & 1;
        }
        trie.insert(bits);
    }
    cout << trie.min_xor(0, 0) << '\n';
    return 0;
}
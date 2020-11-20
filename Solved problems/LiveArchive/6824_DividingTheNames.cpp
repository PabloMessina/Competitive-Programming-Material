// tags: strings, trie, DP, implementation
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<b; i++)
struct Trie {
    vector<vector<int>> g;
    vector<int> count;
    int vocab;
    Trie(){}
    Trie(int vocab, int maxdepth = 10000) : vocab(vocab) {
        g.reserve(maxdepth);
        g.emplace_back(vocab, -1);
        count.reserve(maxdepth);
        count.push_back(0);
    }
    int move_to(int u, int c) {
        assert (0 <= c and c < vocab); // debugging
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
        int u = 0; count[0]++; for (char c : s) u = move_to(u, c - ref);        
    }    
    void insert(vector<int>& s) { // insert vector<int>
        int u = 0; count[0]++; for (int c : s) u = move_to(u, c);
    }
    int size() { return g.size(); }
};
const int MAX_NODES = 2 * 100 * 18 + 1;
const int MAXN = 200;
int N;
Trie trie;

int memo[MAX_NODES][MAXN];

int dp(int u, int n);

// Search the best split of words into streets and avenues
// among the children of node u in index range i ... 25.
// u = current trie node
// i = start index for u's child nodes
// n = numer of words to choose as streets (the rest goes to avenues)
// tot_words = total number of words to be splitted (from index i onwards)
int search(int u, int i, int n, int tot_words) {
    // find the first child node from i to the right
    while(i < 26 and trie.g[u][i] == -1) i++;
    if (i >= 26) return 0; // no more child nodes

    int v = trie.g[u][i]; // first child node found

    // find min and max number of words we can choose as streets
    // from i-th child node
    int min_k = max(0, n - (tot_words - trie.count[v]));
    int max_k = min(trie.count[v], n);
    int ans = INT_MAX;
    rep(k, min_k, max_k+1) {
        // choose optimally k words as street from node v
        // + split optimally the rest of the words to the right
        int val = dp(v,k) + search(u, i+1, n-k, tot_words - trie.count[v]);
        ans = min(ans,val);
    }
    return ans;
}

// Return the minimum total number of letters necessary to
// write the suffixes of all the words that pass through
// node u, assuming that we have to choose n words as streets
// and m = trie.count[u] - n as avenues and assuming that all letters
// until node u (inclusive) have already been properly counted.
// We assume that all the words expand at least 1 letter through any
// child branch, but if n == 1 (m == 1), we substract that
// expansion because a single street (avenue) can be shortened
// right away (no need to expand it anymore).
int dp(int u, int n) {
    int& ans = memo[u][n];
    if (ans != -1) return ans;
    int m = trie.count[u] - n;
    ans = trie.count[u];
    if (m == 1) ans--;
    if (n == 1) ans--;
    if (m >= 2 or n >= 2) ans += search(u, 0, n, trie.count[u]);
    return ans;
}

int main() {
    while (cin >> N) {
        trie = Trie(26, 100 * 18);
        string w;
        rep(i,0,2*N) { cin >> w; trie.insert(w, 'A'); }
        memset(memo, -1, sizeof memo);
        cout << (N * dp(0,N)) << '\n';
    }
    return 0;
}
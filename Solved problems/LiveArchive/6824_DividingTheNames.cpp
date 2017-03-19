// tags: trie, DP, recursive distribution
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)

const int MAX_NODES = 2 * 100 * 18 + 1;
const int MAXN = 200;
int N;
int tree[MAX_NODES][26];
int freqs[MAX_NODES];
int nodes;

// add a word to the trie
void add_word(string& word) {
    int cur = 0;
    freqs[0]++;
    for (char c : word) {
        int& nxt = tree[cur][c-'A'];
        if (nxt == -1) nxt = nodes++;
        cur = nxt;
        freqs[cur]++; // update node frequency
    }
}

int memo[MAX_NODES][MAXN];

int dp(int u, int n);

// Search the best split of words into streets and avenues
// among the children of node u in index range i ... 25.
// u = current trie node
// i = start index for u's child nodes
// n = numer of words to choose as strees (the rest goes to avenues)
// tot_words = total number of words to be splitted (from index i onwards)
int search(int u, int i, int n, int tot_words) {
    // find the first child node from i to the right
    while(i < 26 and tree[u][i] == -1) i++;
    if (i >= 26) return 0; // no more child nodes

    int v = tree[u][i]; // first child node found

    // find min and max number of words we can choose as streets
    // from i-th child node
    int min_k = max(0, n - (tot_words - freqs[v]));
    int max_k = min(freqs[v], n);
    int ans = INT_MAX;    
    rep(k, min_k, max_k) {        
        // choose optimally k words as street from node v
        // + split optimally the rest of the words to the right
        int val = dp(v,k) + search(u, i+1, n-k, tot_words - freqs[v]);
        ans = min(ans,val);
    }
    return ans;
}

// Return the minimum total number of letters necessary to
// write the suffixes of all the words that pass through
// node u, assuming that we have to choose n words as streets
// (and m = freqs[u] - n as avenues) and assuming that all letters
// until node u (inclusive) have already been properly counted.
// We assume that all the words expand at least 1 letter through any
// child branch, but if n == 1 (m == 1), we substract that
// expansion because a single street (avenue) can be shortened
// right away (no need to expand it anymore).
int dp(int u, int n) {
    if (memo[u][n] != -1) return memo[u][n];
    int m = freqs[u] - n;
    int ans = freqs[u];
    if (m == 1) ans--;
    if (n == 1) ans--;
    if (m >= 2 or n >= 2) {
        ans += search(u, 0, n, freqs[u]);
    }
    return memo[u][n] = ans;
}

int main() {
    while (scanf("%d\n", &N) == 1) {
        memset(tree, -1, sizeof tree);
        memset(freqs, 0, sizeof freqs);
        nodes = 1;
        string line;
        rep(i,1,2*N) {
            getline(cin, line);
            add_word(line);
        }
        memset(memo, -1, sizeof memo);
        printf("%d\n", N * dp(0,N));
    }
    return 0;
}
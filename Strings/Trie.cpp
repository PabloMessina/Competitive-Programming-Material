const int MAX_NODES = 1000;
int tree[MAX_NODES][26];
int freqs[MAX_NODES];
int nodes;

void init_trie() {
    memset(tree, -1, sizeof tree);
    memset(freqs, 0, sizeof freqs);
    nodes = 1;
}

void add_word(string& word) {
    int cur = 0;
    freqs[0]++;
    for (char c : word) {
        int& nxt = tree[cur][c-'a'];
        if (nxt == -1) nxt = nodes++;
        cur = nxt;
        freqs[cur]++; // update node frequency
    }
}


#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)

const int MAXN = 100;
const int MAXC = 30;
const int MAX_NODES = 2 * MAXN * 18;
int N;

// --- trie ---
int tree[MAX_NODES + 1][MAXC];
int freq[MAX_NODES + 1];
void init_trie() {
    memset(tree, -1, sizeof tree);
    memset(freq, 0, sizeof freq);
    nodes = 1;
}
void add_word(string& s) {
    int cur = 0;
    int len = s.size();
    freq[0]++;
    rep(i,0,len-1) {
        int& next = tree[cur][s[i]-'A'];
        if (next == -1) next = nodes++;
        cur = next;
        freq[cur]++;
    }
}

int memo[MAX_NODES + 1];

int dp(int node, int n);

int best_split(int node, int i, int n, int cap) {
    int child = -1;
    while (i < 26 and (child = tree[node][i]) == -1) i++;
    if (child == -1) return 0;
    int kmin = max(n - cap, 0);
    int kmax = min(freq[child], n);
    int min_v = INT_MAX;
    rep(k,kmin,kmax) {
        min_v = min(min_v, dp(child,k) + best_split(node, i+1, n-k, cap - freq[child]));
    }
    return 0;
}
int dp(int node, int n) {
    if (freq[node] == 1) return 1;
    if (memo[node][n] != -1) return memo[node][n];
    int count = 0;
    if (node != 0) count += freq[node];    
    if (n == 0) {
        rep(i,0,25) {
            int child = tree[node][i];
            if (child != -1) count += dp(child,0);
        }
    } else {
        count += best_split(node, 0, n, freq[cur]);
    }
    return memo[node][n] = count;
}

int main() {
    while (scanf("%d%", &N)) {
        init_trie();
        rep(i,1,2*N) {
            string word;
            getline(cin,word);
            add_word(word);
        }
        memset(memo, -1, sizeof memo); 
        printf("%d\n", dp(0,N));
    }
    return 0;
}
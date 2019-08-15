// tags: strings, trie, dfs
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
const int MAX_NODES = 1000001;
int P, S;
struct Trie {
    int g[MAX_NODES][26];
    int ID;
    void reset() {
        ID = 1;
        memset(g[0], -1, sizeof g[0]);
    }
    void update(string& s) {
        int u = 0;
        for (char c : s) {
            int& v = g[u][c-'a'];
            if (v == -1) {
                v = ID++;
                memset(g[v], -1, sizeof g[v]);
            }
            u = v;
        }
    }
    int size() { return ID; }
};
Trie prefix_trie, suffix_trie;
int begin_count[26];
void suffix_dfs(int u, int depth) {
    rep(i,0,25) {
        int v = suffix_trie.g[u][i];
        if (v == -1) continue;
        if (depth >= 1) begin_count[i]++;
        suffix_dfs(v, depth+1);
    }
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    while ((cin >> P >> S) and P > 0) {
        prefix_trie.reset();
        suffix_trie.reset();
        memset(begin_count, 0, sizeof begin_count);
        string word;
        while (P--) {
            cin >> word;
            prefix_trie.update(word);            
        }
        while (S--) {
            cin >> word;
            reverse(word.begin(), word.end());
            suffix_trie.update(word);
        }
        suffix_dfs(0,0);
        ll ans = (ll)(prefix_trie.size() - 1)  * (ll)(suffix_trie.size() - 1);
        rep(u,1,prefix_trie.size()-1) {
            rep(i,0,25) {
                if (prefix_trie.g[u][i] == -1) continue;
                ans -= begin_count[i];
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
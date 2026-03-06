/**
 * Aho-Corasick Automaton
 * * Purpose: Efficiently searches for multiple pattern strings simultaneously within a 
 * larger text. It acts as a Trie converted into a Deterministic Finite Automaton (DFA).
 * * Key Components:
 * - N: The Trie / DFA transition table. N[u][c] moves to the next state given char 'c'.
 * - L (Suffix Link / Fail Link): Points to the longest proper suffix of the current 
 * state that is also a prefix of some pattern in the Trie.
 * - G (Reverse Suffix Link): The "failure tree", useful for propagating match counts
 * bottom-up from longest matching suffixes to shorter ones.
 * - E: Stores the count of patterns ending at a specific node.
 * * Complexity: 
 * - Time: $O(\sum |P| + |S|)$ where $P$ are the patterns and $S$ is the queried text.
 * - Space: $O(M \times A)$ where $M$ is max nodes and $A$ is alphabet size.
 */
struct AC {
    int c = 0, ec = 0, M, A;
    vector<vi> N, G; vi L, E; // L = suffix link, G = reverse suffix link
    AC (int M, int A) : M(M), A(A), N(M, vi(A, 0)), E(M, 0), L(M, 0) {}
    int add(const string& s) {
        int p = 0;
        for (char l : s) {
            int t = l - 'a';
            if (!N[p][t]) N[p][t] = ++c;
            p = N[p][t];
        } E[p]++; return p;
    }
    void init() {
        G.assign(M, {});
        queue<int> q; q.push(0); L[0] = -1;
        while (!q.empty()) {
            int p = q.front(); q.pop();
            rep(c, 0, A) {
                int u = N[p][c]; if (!u) continue;
                L[u] = L[p] == -1 ? 0 : N[L[p]][c], q.push(u);
                G[L[u]].pb(u);
            }
            if (p) rep(c, 0, A) if (!N[p][c]) N[p][c] = N[L[p]][c];
        }
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    // Initialize AC with max expected nodes (e.g., 100) and alphabet size (26 for 'a'-'z')
    AC ac(100, 26);
    // Add dictionary words
    ac.add("he");
    ac.add("she");
    ac.add("his");
    ac.add("hers");
    // Build the suffix links and DFA transitions
    ac.init();
    // Query text: "ushers"
    string text = "ushers";
    int current_state = 0;
    int total_matches = 0;
    cout << "Matches found at ending indices:\n";
    for (int i = 0; i < text.length(); ++i) {
        current_state = ac.N[current_state][text[i] - 'a'];
        // Follow suffix links to count all matching sub-patterns ending here
        int temp = current_state;
        while (temp > 0) {
            if (ac.E[temp] > 0) {
                cout << "- Found a match ending at index " << i << "\n";
                total_matches += ac.E[temp];
            }
            temp = ac.L[temp];
        }
    }
    cout << "Total patterns matched: " << total_matches << "\n";
    return 0;
}
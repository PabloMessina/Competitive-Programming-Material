const int MAX_NODES = 1000;
struct Trie {
    int g[MAX_NODES][26];
    int count[MAX_NODES];
    int ID;
    void reset() {
        ID = 1;
        memset(g[0], -1, sizeof g[0]);
        memset()
    }
    void update(string& s) {
        int u = 0;
        for (char c : s) {
            int& v = g[u][c-'a'];
            if (v == -1) {
                v = ID++;
                memset(g[v], -1, sizeof g[v]);
                count[v] = 0;
            }
            count[v]++;
            u = v;
        }
    }
    int size() { return ID; }
};
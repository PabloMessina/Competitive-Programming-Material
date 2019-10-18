#include <bits/stdc++.h>
using namespace std;
struct Trie {
    vector<vector<int>> g;
    vector<int> count;
    int alph_size;
    Trie(int alph_size, int maxdepth = 10000)
            : alph_size(alph_size) {
        g.reserve(maxdepth);
        g.emplace_back(alph_size, -1);
        count.reserve(maxdepth);
        count.push_back(0);
    }
    int move_to(int u, int c) {
        assert (0 <= c and c < alph_size);
        int& v = g[u][c];
        if (v == -1) {
            v = g.size();
            g.emplace_back(alph_size, -1);
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
};

// example of usage
int main() {
    Trie trie(26);
    for (string s : {"hell", "hello", "hellyeah", "helpzzzz", "abcdefg"}) {
        cout << "inserting " <<  s << '\n';
        trie.insert(s);
        cout << "\ttrie size = " << trie.size() << '\n';
    }
    return 0;
}
// ToDo: finish this
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
struct AhoCorasick {
    vector<vector<int>> g, sg;
    vector<int> parent, count;
    int vocab;
    int move_to(int u, int c) {
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
        count[u]++;
    }
    void build_suffix_links() {
        queue<int> q;
        parent.assign(g.size(), -1);
        q.push(0); parent[0] = 0;
        while (q.size()) {
            int u = q.front(); q.pop();
            assert (parent[u] != -1);
            rep(v, 0, vocab) if (g[u][v] != -1) q.push(v);
        }
    }
    AhoCorasick(vector<string>& words, int vocab, char ref='a', int maxdepth=10000) : vocab(vocab) {
        g.reserve(maxdepth);
        g.emplace_back(vocab, -1);
        count.reserve(maxdepth);
        count.push_back(0);
        for (string& w : words) insert(w, ref);
    }
    int size() { return g.size(); }
};
int N, K;
vector<string> names;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> K;
    names.resize(K);
    for (string& w : names) cin >> w;

    return 0;
}
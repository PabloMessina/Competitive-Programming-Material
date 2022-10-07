// tags: strings, trie
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
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
        int& v = g[u][c];
        if (v == -1) {
            v = g.size();
            g.emplace_back(vocab, -1);
            count.push_back(0);
        }
        count[v]++;
        return v;
    }
    void insert(const string& s, char ref = 'a') {
        int u = 0; count[0]++; for (char c : s) u = move_to(u, c - ref);
    }    
    int size() { return g.size(); }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
	int N;
	while (cin >> N) {
		Trie t(26, 1000000);
		vector<string> words;
		rep(i,0,N) {
			string w; cin >> w; t.insert(w);
			words.push_back(w);
		}
		double ans = 0;
		for (string& w : words) {
			int u = 0; ans++;
			for (char c : w) {
				int v = t.move_to(u, c-'a');
				if (u > 0 and t.count[u] != t.count[v]) ans++;
				u = v;
			}
		}
		ans /= words.size();
		cout << setprecision(2) << fixed << ans << '\n';
	}
    return 0;
}
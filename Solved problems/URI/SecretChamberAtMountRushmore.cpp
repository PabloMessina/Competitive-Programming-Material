// tags: graphs, BFS
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define uset unordered_set
// -------------------------------
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int m, n; cin >> m >> n;
    vector<vector<int>> g(26);
    while (m--) {
        char a, b; cin >> a >> b;
        g[a-'a'].push_back(b-'a');
    }
    vector<uset<int>> reach(26);
    rep(s,0,26) {
        vector<bool> vis(26,false);
        vis[s] = true;
        reach[s].insert(s);
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                if (vis[v]) continue;
                vis[v] = true;
                q.push(v);
                reach[s].insert(v);
            }
        }
    }
    while (n--) {
        string a, b; cin >> a >> b;
        if (a.size() != b.size()) {
            cout << "no\n";
            continue;
        }
        bool valid = true;
        rep(i,0,a.size()) if (!reach[a[i]-'a'].count(b[i]-'a')) {
            valid = false; break;
        }
        if (valid) cout << "yes\n";
        else cout << "no\n";
    }
    return 0;
}
// tags: backtracking, pruning, implementation
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------

int K, C, B;
vector<vector<int>> g;
int occupied[16][4];

void toggle_color(int u, int c, int d) {
    for (int v : g[u]) occupied[v][c] += d;
}

bool solve(int u) {
    if (u == C) return true;
    rep(c,0,K-1) {
        if (occupied[u][c] == 0) {
            toggle_color(u,c,1);
            if (solve(u+1)) return true;
            toggle_color(u,c,-1);
        }
    }
    return false;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> C >> B;
        g.assign(C, vector<int>());
        while (B--) {
            int i, j; cin >> i >> j;
            g[i].push_back(j);
            g[j].push_back(i);
        }
        memset(occupied, 0, sizeof occupied);
        bool solved = false;
        for(K=1; K <= 4; ++K) {
            if (solved = solve(0)) break;
        }
        if (solved) cout << K << '\n';
        else cout << "many\n";
    }
    return 0;
}
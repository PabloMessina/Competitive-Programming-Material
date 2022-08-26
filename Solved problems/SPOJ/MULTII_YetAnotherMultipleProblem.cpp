// tags: BFS, modular arithmetics, math, graphs
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
const int MAXN = 10000;
int N;
struct Node {int p, d;} nodes[MAXN];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int t;
    vector<int> banned;
    vector<bool> vis;
    vis.reserve(MAXN);
    int _case = 1;
    while (cin >> N >> t) {
        vector<bool> banned(10, false);
        while (t--) { int d; cin >> d; banned[d] = true; }
        vector<int> digits;
        rep(i,0,10) if (!banned[i]) digits.push_back(i);
        vis.assign(N, false);
        queue<int> q;
        int last_u = -1;
        for (int d : digits) {
            if (d == 0) continue;
            int u = d % N;
            if (vis[u]) continue;
            vis[u] = true;
            nodes[u] = {-1, d};
            if (u == 0) {
                last_u = u;
                goto print_answer;
            }
            q.push(u);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int d : digits) {
                int v = (u * 10 + d) % N;
                if (vis[v]) continue;
                vis[v] = true;
                nodes[v] = {u, d};                
                if (v == 0) {
                    last_u = v;
                    goto print_answer;
                }
                q.push(v);
            }
        }
        print_answer:
        if (last_u == -1) {
            cout << "Case " << _case++ << ": -1\n";
        } else {
            cout << "Case " << _case++ << ": ";
            stack<int> s;
            int u = last_u;
            do { s.push(nodes[u].d); } while ((u = nodes[u].p) != -1);
            while (!s.empty()) {
                cout << s.top();
                s.pop();
            }
            cout << '\n';
        }
    }
    return 0;
}
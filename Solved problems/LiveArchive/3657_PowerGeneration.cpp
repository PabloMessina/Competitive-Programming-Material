// tags: greedy, geometry, graphs, trees, implementation
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
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int N,C;
struct P {
    int x, y, c;
    P(int x, int y, int c) : x(x), y(y), c(c) {};
};
int dist2(P& a, P& b) {
    int dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    while (cin >> N >> C and N) {
        vector<P> pts; pts.reserve(N);
        vector<int> parent(N, -1);
        vector<int> children(N, 0);
        rep(u,0,N) {
            int x, y, c; cin >> x >> y >> c;
            pts.emplace_back(x,y,c);
            int vmin = -1, dmin = INT_MAX;
            rep(v,0,u) {
                int d = dist2(pts[u], pts[v]);
                if (d < dmin) {
                    dmin = d;
                    vmin = v;
                }
            }
            if (vmin != -1) {
                parent[u] = vmin;
                children[vmin]++;
            }            
        }
        deque<int> leaves;
        rep(u,0,N) if (children[u] == 0) leaves.push_back(u);
        int ans = 0;
        while (leaves.size()) {
            int u = leaves.front();
            int p = parent[u];
            if (pts[u].c >= C) ans++;
            else if (p != -1) pts[p].c += pts[u].c;
            if (p != -1 and --children[p] == 0) leaves.push_back(p);
            leaves.pop_front();
        }
        cout << ans << '\n';
    }
    return 0;
}
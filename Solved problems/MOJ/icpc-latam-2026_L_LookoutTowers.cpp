// tags: trees, tree DP, DFS, LCA counting, counting pairs
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i) // [a, b), inclusive-exclusive
#define invrep(i,b,a) for(int i = b; i >= a; --i) // [b, a], inclusive-inclusive
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
// Idea: root the tree at 1 and count every pair of towers at its LCA, the highest node on the
// path between them. At its LCA v, a pair is either (a) two towers in different child subtrees
// of v, or (b) v itself plus a tower below it.
//
// Key observation: if (a, b) is at the GLOBAL minimum distance D with LCA v, then a is one of
// the towers closest to v within its child subtree (a closer a' would give a pair (a', b) shorter
// than D). So each subtree only needs two numbers:
//   m[u] = distance from u to the nearest tower in u's subtree (INF if none)
//   c[u] = number of towers at exactly that distance
//
// DFS: node v starts as (0, 1) if it is a tower, else (INF, 0). For each child u, once its DFS
// returns, shift it to (m[u] + 1, c[u]) and:
//   1. COUNT: pair it with what v has accumulated so far (v itself + earlier children):
//      candidate distance m[v] + m[u] + 1, with c[v] * c[u] pairs -> update the global (best, cnt)
//   2. MERGE: keep the smaller distance in (m[v], c[v]), adding the counts on a tie.
// Counting before merging pairs each child only with earlier siblings, so every pair is counted
// once: only at its LCA, and only when the later of its two branches is merged.
// Complexity: O(N).
//
// Recursion depth can reach N = 2e5 (a path), which needs about 20 MB of stack. That is fine on
// MOJ (128 MB stack), but it crashes with the default 8 MB stack on macOS / Linux: run
// `ulimit -s hard` in the terminal before testing locally.
const int INF = INT_MAX / 4; // INF + INF + 1 cannot overflow

int N;
vi W;
vector<vi> g;
vi m;           // m[v]: distance from v to the nearest tower in v's subtree
vector<ll> c;   // c[v]: number of towers at distance m[v]
int best = INF; // global minimum distance between two towers
ll cnt = 0;     // number of pairs at that distance (up to ~2e10: needs 64 bits)

void dfs(int v, int parent) {
    // v alone
    if (W[v]) { m[v] = 0; c[v] = 1; }
    else { m[v] = INF; c[v] = 0; }
    for (int u : g[v]) {
        if (u == parent) continue;
        dfs(u, v); // (m[u], c[u]) is now final
        if (m[u] == INF) continue; // no towers in u's subtree: nothing to count or merge
        int du = m[u] + 1; // distance from v to the nearest towers in u's subtree
        // 1. COUNT: pairs (tower already in v's group, nearest tower in u's subtree)
        if (m[v] != INF) {
            int d = m[v] + du;
            if (d < best) { best = d; cnt = c[v] * c[u]; }
            else if (d == best) cnt += c[v] * c[u];
        }
        // 2. MERGE: u's subtree joins v's group
        if (du < m[v]) { m[v] = du; c[v] = c[u]; }
        else if (du == m[v]) c[v] += c[u];
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    W.resize(N+1);
    rep(i,1,N+1) cin >> W[i];
    g.resize(N+1);
    rep(i,0,N-1) {
        int u, v; cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    m.resize(N+1);
    c.resize(N+1);
    dfs(1, 0); // vertices are 1..N, so 0 means "no parent"
    cout << best << ' ' << cnt << '\n';
    return 0;
}

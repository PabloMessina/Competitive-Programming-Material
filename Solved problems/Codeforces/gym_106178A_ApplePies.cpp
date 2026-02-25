// tags: graphs, eulerian path, eulerian circuit, union find
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
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int N, P, Q;
const int MAXN = 1000;
vector<int> L, R;
bool seen[MAXN+1][MAXN+1];

struct UnionFind {
    vector<int> p, rank, setSize;
    int numSets;
    UnionFind(int n) {
        numSets = n; setSize.assign(n, 1); rank.assign(n, 0); p.resize(n);
        rep(i,0,n) p[i] = i;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j) { 
        if (!isSameSet(i, j)) {
            numSets--; 
            int x = findSet(i), y = findSet(j);
            // rank is used to keep the tree short
            if (rank[x] > rank[y]) {
                p[y] = x; setSize[x] += setSize[y];
            } else {
                p[x] = y; setSize[y] += setSize[x];
                if (rank[x] == rank[y]) rank[y]++;
            }
        }
    }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    
    cin >> P;
    L.resize(P);
    rep(i,0,P) cin >> L[i];
    
    cin >> Q;
    R.resize(Q);
    rep(i,0,Q) cin >> R[i];

    int expected_length = (N * (N-1) + 2) / 2;

    if (expected_length < P + Q) {
        cout << "N\n";
        return 0;
    }
    
    rep(i,0,P-1) {
        int x = L[i], y = L[i+1];
        if (seen[x][y] or x == y) {
            cout << "N\n";
            return 0;
        }
        seen[x][y] = true;
        seen[y][x] = true;
    }
    rep(i,0,Q-1) {
        int x = R[i], y = R[i+1];
        if (seen[x][y] or x == y) {
            cout << "N\n";
            return 0;
        }
        seen[x][y] = true;
        seen[y][x] = true;
    }

    if (P + Q == expected_length) {
        if (P > 0 and Q > 0) {
            int x = L[P-1], y = R[0];
            if (seen[x][y] or x == y) {
                cout << "N\n";
                return 0;
            }
        }
        cout << "Y\n";
        return 0;
    }

    vector<vector<int>> g(N+1);
    uset<int> remaining_nodes;
    rep(u,1,N+1) {
        rep(v,1,N+1) {
            if (seen[u][v] or u == v) continue;
            g[u].pb(v);
            remaining_nodes.insert(u);
            remaining_nodes.insert(v);
        }
    }
    assert (remaining_nodes.size() > 0);

    if (P > 0) {
        if (remaining_nodes.count(L[P-1]) == 0) {
            cout << "N\n";
            return 0;
        }
    }
    if (Q > 0) {
        if (remaining_nodes.count(R[0]) == 0) {
            cout << "N\n";
            return 0;
        }
    }

    UnionFind uf(N+1);
    for (int u : remaining_nodes) {
        for (int v : g[u]) {
            uf.unionSet(u, v);
        }
    }
    int ref_set = uf.findSet(*remaining_nodes.begin());
    for (int u : remaining_nodes) {
        if (uf.findSet(u) != ref_set) {
            cout << "N\n";
            return 0;
        }
    }

    int odd_degree_nodes = 0;
    for (int u : remaining_nodes) {
        if (g[u].size() & 1) odd_degree_nodes++;
    }
    if (odd_degree_nodes > 2) {
        cout << "N\n";
        return 0;
    }

    if (P > 0 and Q > 0) {
        if (odd_degree_nodes == 0) {
            // We need an eulerian circuit, so the first and last nodes must be the same.
            if (L[P-1] == R[0]) {
                cout << "Y\n";
            } else {
                cout << "N\n";
            }
            return 0;
        } else {
            // We need an eulerian path, where the first and last nodes must be the ones with odd degree.
            if ((g[L[P-1]].size() & 1) and (g[R[0]].size() & 1) and (L[P-1] != R[0])) {
                cout << "Y\n";
            } else {
                cout << "N\n";
            }
            return 0;
        }
    } else {
        if (odd_degree_nodes == 0) {
            cout << "Y\n";
            return 0;
        } else {
            if (P > 0 and (g[L[P-1]].size() & 1) == 0) {
                cout << "N\n";
                return 0;
            }
            if (Q > 0 and (g[R[0]].size() & 1) == 0) {
                cout << "N\n";
                return 0;
            }
            cout << "Y\n";
            return 0;
        }
    }
    return 0;
}
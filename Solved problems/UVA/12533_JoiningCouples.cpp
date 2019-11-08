// tags: LCA, dfs, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
// -------------------------------
int N, Q;
vector<vector<int>> gr;
vector<int> nxt;
vector<int> stack_idx;
vector<int> cycle_index, cycle_size;
vector<int> old2newId, source;
vector<bool> is_cycle;
int ID, SOURCE_ID;

vector<vector<int>> fg;

int get_new_id(int u) {
    if (old2newId[u] != -1) return old2newId[u];
    old2newId[u] = ID;
    fg.resize(++ID);
    return old2newId[u];
}

void add_edge(int u, int v) {
    int uid = get_new_id(u);
    int vid = get_new_id(v);
    fg[uid].push_back(vid);
}

void dfs(int u) {
    source[u] = SOURCE_ID;
    for (int v : gr[u]) {
        if (source[v] == -1) {
            add_edge(u, v);
            dfs(v);
        }
    }
}

struct LCA {
    vector<int> A, D;
    vector<vector<int>> *g;
    int n, maxe;
    int& anc(int u, int e) { return A[e * n + u]; }    
    int inline log2(int x) { return 31 - __builtin_clz(x); }

    void dfs(int u, int p, int depth) {
        anc(u,0) = p;
        D[u] = depth;        
        for (int v : (*g)[u]) {
            if (D[v] == -1) {
                dfs(v, u, depth + 1);
            }
        }
    }

    LCA(vector<vector<int>>& _g, int root) {
        g = &_g;
        n = _g.size();
        maxe = log2(n);
        D.assign(n, -1);
        A.resize(n * (maxe + 1));        
        dfs(root, -1, 0);
        rep(e, 1, maxe) {
            rep (u, 0, n-1) {
                int a = anc(u,e-1);
                anc(u,e) = (a == -1 ? -1 : anc(a,e-1));
            }
        }
    }
    
    int raise(int u, int k) {
        for (int e = 0; k; e++, k>>=1) if (k&1) u = anc(u,e);
        return u;
    }

    int lca(int u, int v) {        
        if (D[u] < D[v]) swap(u, v); 
        u = raise(u, D[u] - D[v]);
        if (u == v) return u;
        invrep (e, maxe, 0) {
            if (anc(u,e) != anc(v,e)) {
                u = anc(u,e), v = anc(v,e);
            }
        }
        return anc(u,0);
    }

    int dist(int u, int v, int lca_uv) {
        return D[u] + D[v] - 2 * D[lca_uv];
    }
};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    while (cin >> N) {        
        stack_idx.assign(N, -1);
        old2newId.assign(N, -1);
        source.assign(N, -1);
        cycle_index.resize(N);
        cycle_size.resize(N);
        is_cycle.assign(N+1, false);
        gr.assign(N, vector<int>());
        nxt.resize(N);
        rep(i,0,N-1) {
            cin >> nxt[i];
            nxt[i]--;
            gr[nxt[i]].push_back(i);
        }
        vector<int> _stack;
        _stack.reserve(N);
        ID = 1;
        fg.clear();
        fg.reserve(N+1);
        fg.resize(1);
        rep(u,0,N-1) {
            if (source[u] != -1) continue;
            int v = u;
            _stack.clear();
            while (1) {
                stack_idx[v] = _stack.size();
                _stack.push_back(v);
                v = nxt[v];

                if (stack_idx[v] != -1) {
                    int csize = _stack.size() - stack_idx[v];
                    rep(i, stack_idx[v], _stack.size()-1) {
                        int z = _stack[i];
                        cycle_index[z] = i - stack_idx[v];
                        cycle_size[z] = csize;
                        old2newId[z] = ID;
                        source[z] = z;
                    }
                    fg[0].push_back(ID);
                    is_cycle[ID] = true;
                    fg.resize(++ID);
                    rep(i, stack_idx[v], _stack.size()-1) {
                        int z = _stack[i];
                        SOURCE_ID = z;
                        dfs(z);
                    }
                    break;
                }
            }
        }
        LCA lca(fg, 0);
        cin >> Q;
        while (Q--) {
            int a, b; cin >> a >> b; --a, --b;
            int aa = old2newId[a];
            int bb = old2newId[b];
            int x = lca.lca(aa, bb);
            if (x == 0){
                cout << "-1\n";
            } else if (is_cycle[x]) {
                int sa = source[a];
                int sb = source[b];
                int csize = cycle_size[sa];
                int ia = cycle_index[sa];
                int ib = cycle_index[sb];
                cout << lca.dist(aa, bb, x) + min(csize - abs(ia - ib), abs(ia - ib)) << '\n';
            } else {
                cout << lca.dist(aa, bb, x) << '\n';
            }
        }
    }
    return 0;
}
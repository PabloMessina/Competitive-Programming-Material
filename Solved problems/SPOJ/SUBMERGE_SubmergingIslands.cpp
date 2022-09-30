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

vector<int> s, D, L;
vector<bool> instack;
vector<vector<int>> g;
int n, ID;
void dfs(int u) {
    D[u] = L[u] = ID++;
    instack[u] = true;
    s.push_back(u);
    for (int v : g[u]) {
        if (D[v] == -1) {
            dfs(v);
            L[u] = min(L[v], L[u]);
        } else if (instack[v]) {
            L[u] = min(L[v], L[u]);
        }
    }
    if (L[u] == D[u]) { // u is root of a SCC
        cout << "SCC found!\n";        
        while (1) { // remove SCC from top of the stack
            int x = s.back(); s.pop_back();
            instack[x] = false;
            if (x == u) break;
        }
    }
}    
void find_sccs(vector<vector<int>>& g) {
    n = g.size(); ID = 0;
    s.reserve(n); D.assign(n, -1); L.resize(n);
    instack.assign(n, 0);
    rep(u,0,n) if (D[u] == -1) dfs(u);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N, M; cin >> N >> M;
        
    return 0;
}
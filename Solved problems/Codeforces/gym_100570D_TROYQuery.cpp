// tags: DSU, union find, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define umap unordered_map
typedef long long int ll;
// -------------------------------
struct UnionFind {
    vector<int> p, rank, setSize;
    int numSets;
    UnionFind(int n) {
        numSets = n; setSize.assign(n, 1); rank.assign(n, 0); p.resize(n);
        rep(i,0,n-1) p[i] = i;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j) { 
        if (!isSameSet(i, j)) {
            numSets--; 
            int x = findSet(i), y = findSet(j);
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

int row2id(ll x) {
    static int ID = 0;
    static umap<ll,int> x2id;
    auto it = x2id.find(x);
    if (it == x2id.end()) return x2id[x] = ID++;
    return it->second;
}
int col2id(ll x) {
    static int ID = 0;
    static umap<ll,int> x2id;
    auto it = x2id.find(x);
    if (it == x2id.end()) return x2id[x] = ID++;
    return it->second;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    UnionFind uf(4*n);
    bool possible = true;
    rep(i,1,n) {
        ll x,y; int a,b;
        cin >> x >> y >> a >> b;
        if (!possible) { cout << "No\n"; continue; }
        int xid = row2id(x);
        int yid = col2id(y);
        if (a == b) {
            uf.unionSet(xid*2, 2*n + yid*2);
            uf.unionSet(xid*2+1, 2*n + yid*2+1);
        } else {
            uf.unionSet(xid*2, 2*n + yid*2+1);
            uf.unionSet(xid*2+1, 2*n + yid*2);
        }
        if (uf.isSameSet(xid*2, xid*2+1) or uf.isSameSet(2*n + yid*2, 2*n + yid*2+1))
            possible = false;
        if (possible) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
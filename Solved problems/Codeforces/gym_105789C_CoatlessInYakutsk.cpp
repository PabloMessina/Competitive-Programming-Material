#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i < b; ++i)

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
            if (rank[x] > rank[y]) {
                p[y] = x; setSize[x] += setSize[y];
            } else {
                p[x] = y; setSize[y] += setSize[x];
                if (rank[x] == rank[y]) rank[y]++;
            }
        }
    }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

signed main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int C, N;
    cin >> C >> N;
    vector<int> T(N);
    rep(i,0,N) cin >> T[i];
    vector<int> idxs(N);
    rep(i,0,N) idxs[i] = i;
    UnionFind uf(N);
    vector<bool> with_coat(N, false);
    sort(idxs.begin(), idxs.end(), [&](int i, int j) { return T[i] < T[j]; });
    for (int idx : idxs) {
        int size = 1;
        if (idx > 0 and with_coat[idx-1]) size += uf.sizeOfSet(idx-1);
        if (idx < N-1 and with_coat[idx+1]) size += uf.sizeOfSet(idx+1);
        if (size > C) {
            cout << T[idx] << '\n';
            return 0;
        }
        if (idx > 0 and with_coat[idx-1]) uf.unionSet(idx, idx-1);
        if (idx < N-1 and with_coat[idx+1]) uf.unionSet(idx, idx+1);
        with_coat[idx] = true;
    }
    return 0;
}
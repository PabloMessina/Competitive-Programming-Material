// tags: implementation, sweep line, union find, DSU, std::set
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
typedef long long int ll;
// -------------------------------
int N, Q;
ll L, U, A[100000], X[100000], O[100000];

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
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

enum Kind { BEGIN, END };
struct Event {
    int i, idx, kind;
    Event(int i, int idx, int kind) : i(i), idx(idx), kind(kind) {}
    bool operator<(const Event& e) const {
        return tie(idx,kind) < tie(e.idx,e.kind);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N  >> L >> U;
    rep(i,0,N) cin >> A[i];
    int Q; cin >> Q;
    vector<Event> events;
    rep(i,0,Q) {
        int b, e; ll x;
        cin >> b >> e >> x;
        --b, --e;
        X[i] = x;
        events.emplace_back(i, b, BEGIN);
        events.emplace_back(i, e, END);
    }
    sort(events.begin(), events.end());
    int i = -1;
    ll offset = 0;
    auto cmp = [](int i, int j) { return tie(X[i], i) < tie(X[j], j); };
    set<int, decltype(cmp)> active(cmp);
    UnionFind uf(Q);
    for (auto& e : events) {
        while (i < e.idx) {            
            offset += A[++i];
            if (active.size() > 0) {
                if (X[*active.begin()] + offset < L) {
                    auto beg_it = active.begin();
                    auto end_it = active.end();
                    auto stop_it = beg_it;
                    while (stop_it != end_it and X[*stop_it] + offset < L) ++stop_it;
                    for (auto it = next(beg_it); it != stop_it; ++it) {
                        uf.unionSet(*beg_it, *it);
                    }
                    int s = uf.findSet(*beg_it);
                    active.erase(beg_it, stop_it);
                    X[s] = L - offset;
                    active.insert(s);
                } else if (X[*active.rbegin()] + offset > U) {
                    auto beg_it = active.rbegin();
                    auto end_it = active.rend();
                    auto stop_it = beg_it;
                    while (stop_it != end_it and X[*stop_it] + offset > U) ++stop_it;
                    for (auto it = next(beg_it); it != stop_it; ++it) {
                        uf.unionSet(*beg_it, *it);
                    }
                    int s = uf.findSet(*beg_it);
                    active.erase(stop_it.base(), beg_it.base());
                    X[s] = U - offset;
                    active.insert(s);
                }
            }
        }
        if (e.kind == BEGIN) {
            X[e.i] = max(min(X[e.i] + A[i], U), L) - offset;
            active.insert(e.i);
        } else {
            int s = uf.findSet(e.i);
            O[e.i] = X[s] + offset;
        }
    }
    rep(i,0,Q) cout << O[i] << '\n';
    return 0;
}
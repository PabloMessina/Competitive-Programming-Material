// tags: fenwick tree, sorting queries
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define umap unordered_map
// -------------------------------
const int MAXN = 30000;
const int MAXQ = 200000;
int N;
int A[MAXN+1];
int answers[MAXQ];

struct Query {
    int l, r, i;
    Query(int l, int r, int i) : l(l), r(r), i(i) {}
    bool operator<(const Query& q) const {
        return r < q.r;
    }
};

struct BIT {
    vector<int> bit;
    BIT(int n) { bit.assign(n+1, 0); }
    int psq(int k) {
        int sum = 0;
        for (; k; k -= (k & -k)) sum += bit[k];
        return sum;
    }
    int rsq(int a, int b) {
        return psq(b) - psq(a-1);
    }
    void add(int k, int v) {
        for (; k < bit.size(); k += (k & -k)) bit[k] += v;
    }
};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N;;
    rep(i,1,N+1) cin >> A[i];
    int Q; cin >> Q;
    vector<Query> queries; queries.reserve(Q);
    rep(i,0,Q) {
        int l, r; cin >> l >> r;
        queries.emplace_back(l, r, i);
    }
    sort(queries.begin(), queries.end());
    vector<int> index(1000001, -1);
    BIT bit(N);
    int r = 0;
    for (Query& q : queries) {
        while (r < q.r) {
            ++r;
            if (index[A[r]] != -1) bit.add(index[A[r]], -1);
            index[A[r]] = r;
            bit.add(r, 1);
        }
        answers[q.i] = bit.rsq(q.l, q.r);
    }
    rep(i,0,Q) cout << answers[i] << '\n';
    return 0;
}
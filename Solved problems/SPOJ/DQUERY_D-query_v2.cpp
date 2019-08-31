// tags: MO's algorithm, square root decomposition, sorting queries
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
const int MAXN = 30000;
const int MAXQ = 200000;
int N;
int N_BINS;
int A[MAXN+1];
int answers[MAXQ];
int freq[1000001];
int cnt = 0;

struct Query {
    int l, r, i, b;
    Query(int l, int r, int i) : l(l), r(r), i(i), b(l/N_BINS) {}
    bool operator<(const Query& q) const {
        if (b != q.b) return b < q.b;
        return (b&1) ? r < q.r : r > q.r;
    }
};
void add_element(int x) {
    if (++freq[x] == 1) cnt++;
}
void remove_element(int x) {
    if (--freq[x] == 0) cnt--;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N;
    N_BINS = sqrt(N);
    rep(i,1,N) cin >> A[i];
    int Q; cin >> Q;
    vector<Query> queries; queries.reserve(Q);
    rep(i,0,Q-1) {
        int l, r; cin >> l >> r;
        queries.emplace_back(l, r, i);
    }
    sort(queries.begin(), queries.end());
    int l = 1, r = 0;
    for (Query& q : queries) {
        while (r < q.r) add_element(A[++r]);
        while (r > q.r) remove_element(A[r--]);
        while (l < q.l) remove_element(A[l++]);
        while (l > q.l) add_element(A[--l]);
        answers[q.i] = cnt;
    }
    rep(i,0,Q-1) cout << answers[i] << '\n';
    return 0;
}
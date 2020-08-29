// tags: MO's algorithm, square root decomposition, sorting queries
#pragma GCC optimize("Ofast") 
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
typedef long long int ll;
// -------------------------------
const int MAXN = 200000;
const int MAXV = 1000000;
int N, Q, N_BINS;
int A[MAXN+1];
ll F[MAXV+1];
ll answers[MAXN];
struct Query {
    int l, r, i, b;
    Query(int l, int r, int i) : l(l), r(r), i(i) { b = l/N_BINS; }
    bool operator<(const Query& q) const {
        if (b != q.b) return b < q.b;
        return (b & 1) ? r < q.r : r > q.r;
    }
};
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    cin >> N >> Q;
    N_BINS = sqrt(N);
    rep(i,1,N+1) cin >> A[i];
    vector<Query> queries; queries.reserve(Q);
    rep(i,0,Q) {
        int l, r; cin >> l >> r;
        queries.emplace_back(l,r,i);
    }
    sort(queries.begin(), queries.end());
    ll ans = 0;
    int l = 0, r = 0;
    for (Query& q : queries) {
        while (l < q.l) ans -= (2*F[A[l]]-1)*A[l], F[A[l]]--, l++;
        while (l > q.l) l--, F[A[l]]++, ans += (2*F[A[l]]-1)*A[l];
        while (r < q.r) r++, F[A[r]]++, ans += (2*F[A[r]]-1)*A[r];
        while (r > q.r) ans -= (2*F[A[r]]-1)*A[r], F[A[r]]--, r--;
        answers[q.i] = ans;
    }
    rep(i,0,Q) cout << answers[i] << '\n';
    return 0;
}
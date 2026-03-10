// tags: math, modular arithmetic, sorting, geometry, greedy
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
signed main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N, L; cin >> N >> L;
    vector<ll> A(N), B(N);
    rep(i,0,N) { cin >> A[i]; A[i]--; }
    rep(i,0,N) { cin >> B[i]; B[i]--; }
    vector<int> idxs(N);
    rep(i,0,N) idxs[i] = i;
    sort(idxs.begin(), idxs.end(), [&](int i, int j) { return A[i] < A[j]; });
    rep(i,1,N) {
        int idx = idxs[i];
        int idx_prev = idxs[i-1];
        assert (A[idx_prev] < A[idx]);
        while (B[idx_prev] > B[idx]) B[idx] += L;
        assert (B[idx_prev] < B[idx]);
    }
    if (B[idxs[N-1]] - B[idxs[0]] > L) {
        cout << "*\n";
        return 0;
    }
    ll ans = LLONG_MAX;
    for (int k=-2; k <= 2; ++k) {
        ll max_diff = 0;
        rep(i,0,N) max_diff = max(max_diff, abs(B[idxs[i]]+k*L - A[idxs[i]]));
        ans = min(ans, max_diff);
    }
    cout << ans << '\n';
    return 0;
}
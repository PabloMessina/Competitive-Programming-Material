// tags: DP, divide & conquer optimization
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
const int MAXN = 1005;
int N, K;
ll X[MAXN], W[MAXN];
ll Wacc[MAXN], XWacc[MAXN];

ll cost(int i, int j) {
    return X[j] * (Wacc[j] - (i ? Wacc[i-1] : 0)) -
            (XWacc[j] - (i ? XWacc[i-1] : 0));
}

int row;
vector<ll> last, now;
void compute(int l, int r, int optl, int optr) {
    if (l > r) return;
    int m = (l + r)/2;
    pair<ll, int> best = { LLONG_MAX, -1 };    
    rep(k, max(optl, m), min(optr, N-1-row) + 1) {
        best = min(best, {cost(m, k) + last[k+1], k});
    }
    now[m] = best.ff;
    compute(l, m-1, optl, best.ss);
    compute(m+1, r, best.ss, optr);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    while (cin >> N >> K) {
        rep(i,0,N) cin >> X[i] >> W[i];
        rep(i,0,N) Wacc[i] = W[i] + (i ? Wacc[i-1] : 0);
        rep(i,0,N) XWacc[i] = X[i] * W[i] + (i ? XWacc[i-1] : 0);
        last.resize(N); now.resize(N);
        // caso base
        rep(i,0,N) last[i] = cost(i, N-1);
        // lo recursivo
        for (row=1; row < K; ++row) { compute(0, N-1-row, 0, N-1); swap(last, now); }
        cout << last[0] << '\n';
    }
    return 0;
}
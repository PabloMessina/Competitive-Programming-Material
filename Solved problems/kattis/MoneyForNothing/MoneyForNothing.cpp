// tags: geometry, divide and conquer
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

vector<pair<ll,ll>> A, B;

ll search(int l, int r, int a, int b) {
    if (l > r or a > b) return 0ll;
    ll ans = LLONG_MIN;
    int m = (l+r) >> 1;
    int best_k = -1;
    bool valid = false;
    invrep(k,b,a) {
        ll dx = B[k].ff - A[m].ff;
        ll dy = B[k].ss - A[m].ss;
        ll tmp = dx * dy;
        if (dx > 0 and dy > 0) valid = true;
        if (tmp > ans) {
            ans = tmp;
            best_k = k;
        }
    }
    if (!valid) ans = 0;
    ans = max(ans, search(l, m-1, a, best_k));
    ans = max(ans, search(m+1, r, best_k, b));
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int m, n; cin >> m >> n;
    
    A.resize(m); B.resize(n);
    for (auto& p : A) cin >> p.ff >> p.ss;
    for (auto& p : B) cin >> p.ff >> p.ss;
    
    sort(A.begin(), A.end());
    auto ref = A[0];
    int j = 1;
    rep(i,1,m) {
        if (ref.ff < A[i].ff and ref.ss > A[i].ss) {
            A[j++] = ref = A[i];
        }
    }
    A.resize(j);

    sort(B.begin(), B.end(), greater<pair<ll,ll>>());
    ref = B[0];
    j = 1;
    rep(i,1,n) {
        if (ref.ff > B[i].ff and ref.ss < B[i].ss) {
            B[j++] = ref = B[i];
        }
    }
    B.resize(j);
    reverse(B.begin(), B.end());

    cout << search(0, A.size()-1, 0, B.size()-1) << '\n';

    return 0;
}
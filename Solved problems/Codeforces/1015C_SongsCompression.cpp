// tags: implementation, greedy
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
// typedefs
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<ll> a(n), b(n);
    ll sum = 0;
    rep(i,0,n) { cin >> a[i] >> b[i]; b[i] -= a[i]; sum += a[i]; }
    vector<int> idxs(n); rep(i,0,n) idxs[i] = i;
    sort(idxs.begin(), idxs.end(), [&b](int i, int j) { return b[i] < b[j]; });
    int count = 0;
    for (int i : idxs) {
        if (sum <= m) break;
        sum += b[i], count++;
    }
    if (sum <= m) cout << count << '\n';
    else cout << "-1\n";
    return 0;
}
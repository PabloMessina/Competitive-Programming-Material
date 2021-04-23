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
    int T; cin >> T;
    rep(_case, 1, T+1) {
        int N; cin >> N;
        vector<int> L(N);
        for (int& x : L) cin >> x;
        int cost = 0;
        rep(i,0,N-1) {
            auto it = min_element(L.begin() + i, L.end());
            cost += it - (L.begin() + i) + 1;
            reverse(L.begin() + i, it + 1);
        }
        cout << "Case #" << _case << ": "  << cost << '\n';
    }
    return 0;
}
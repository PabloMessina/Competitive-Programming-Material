// tags: adhoc, implementation, stack
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,a,b) for(int i = a; i >= b; --i)
typedef long long int ll;
// -------------------------------
const int MAXN = 100000;
int N;
ll H[MAXN], L[MAXN], R[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    vector<pair<ll,ll>> s; // we use a vector to simulate a stack
    s.reserve(MAXN+1);
    while ((cin >> N) and N > 0) {
        rep(i,0,N-1) cin >> H[i];        
        ll x;
        // fill L array
        s.clear();        
        s.emplace_back(0, -1);
        x = 1;
        rep(i,0,N-1) {
            while (s.back().second >= H[i]) s.pop_back();
            L[i] = s.back().first;
            s.emplace_back(x++, H[i]);
        }
        // fill R array
        s.clear();
        s.emplace_back(N, -1);
        x = N-1;
        invrep(i,N-1,0) {
            while (s.back().second >= H[i]) s.pop_back();
            R[i] = s.back().first;
            s.emplace_back(x--, H[i]);
        }
        // find maximum area
        ll ans = 0;
        rep(i,0,N-1) {
            ans = max(ans, (R[i] - L[i]) * H[i]);
        }
        cout << ans << '\n';
    }
    return 0;
}
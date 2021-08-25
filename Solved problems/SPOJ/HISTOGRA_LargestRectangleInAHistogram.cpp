// tags: adhoc, implementation, stack
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,a,b) for(int i = a; i >= b; --i)
#define ff first
#define ss second
typedef long long int ll;
// -------------------------------
const int MAXN = 100000;
int N;
ll H[MAXN], L[MAXN], R[MAXN];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    while ((cin >> N) and N > 0) {
        rep(i,0,N) cin >> H[i];
        // fill L array        
        {
            stack<pair<ll,ll>> s; // (índice, altura)            
            s.emplace(-1, -1);
            rep(i,0,N) {
                while (s.top().ss >= H[i]) s.pop();
                L[i] = s.top().ff;
                s.emplace(i, H[i]);
            }
        }
        // fill R array
        {
            stack<pair<ll,ll>> s; // (índice, altura)
            s.emplace(N, -1);
            invrep(i,N-1,0) {
                while (s.top().ss >= H[i]) s.pop();
                R[i] = s.top().ff;
                s.emplace(i, H[i]);
            }
        }
        // find maximum area
        ll ans = 0;
        rep(i,0,N) ans = max(ans, (R[i] - L[i] - 1) * H[i]);
        cout << ans << '\n';
    }
    return 0;
}
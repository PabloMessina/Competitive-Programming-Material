// tags: implementation, geometry, greedy
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
int N, K;
vector<ll> R, C;
ll min_r, max_r, min_c, max_c;
ll initial_width, initial_height;
ll ans = 0;

void expand_sides_independently() {
    int k = K;
    ll min_side = min(initial_width, initial_height);
    ll max_side = max(initial_width, initial_height);
    ll diff = max_side - min_side;
    ll side1, side2;
    if (diff < k) {
        k -= diff;
        side1 = max_side + (k / 2);
        side2 = max_side + (k - (k / 2));
    } else {
        side1 = min_side + k;
        side2 = max_side;
    }
    ans = max(ans, side1 * side2);
}

void expand_sides_together() {
    rep(i,0,N) {
        ll r = R[i];
        ll c = C[i];
        for (int u : {-1, 1}) {
            for (int v : {-1, 1}) {
                ll nr = r + u * K;
                ll nc = c + v * K;
                ll new_min_r = min(min_r, nr);
                ll new_max_r = max(max_r, nr);
                ll new_min_c = min(min_c, nc);
                ll new_max_c = max(max_c, nc);
                ll new_width = new_max_r - new_min_r + 1;
                ll new_height = new_max_c - new_min_c + 1;
                ans = max(ans, new_width * new_height);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> K;
    R.resize(N); C.resize(N);
    rep(i,0,N) cin >> R[i] >> C[i];
    if (N == 1) {
        cout << 1 << '\n';
        return 0;
    }
    min_r = *min_element(R.begin(), R.end());
    max_r = *max_element(R.begin(), R.end());
    min_c = *min_element(C.begin(), C.end());
    max_c = *max_element(C.begin(), C.end());
    initial_width = max_r - min_r + 1;
    initial_height = max_c - min_c + 1;
    ans = initial_width * initial_height;
    // Case 1: expand sides independently
    expand_sides_independently();
    // Case 2: expand sides together
    expand_sides_together();
    cout << ans << '\n';
    return 0;
}
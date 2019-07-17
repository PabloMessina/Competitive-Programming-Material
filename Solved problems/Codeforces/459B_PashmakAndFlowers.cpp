// tags: combinatorics, math
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
typedef long long int ll;
int n;
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    vector<ll> vals;
    cin >> n;
    ll x_min = LLONG_MAX;
    ll x_max = 0;
    while (n--) {
        ll x; cin >> x; vals.push_back(x);
        x_min = min(x_min, x);
        x_max = max(x_max, x);
    }
    ll min_count = 0;
    ll max_count = 0;
    for (ll x : vals) {
        if (x == x_max) max_count++;
        if (x == x_min) min_count++;
    }
    ll ways;
    if (x_max == x_min) {
        ways = max_count * (max_count-1) / 2;
    } else {
        ways = min_count * max_count;
    }
    cout << (x_max - x_min) << ' ' << ways << '\n';
    return 0;
}
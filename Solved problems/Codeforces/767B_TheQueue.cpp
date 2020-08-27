// tags: implementation, simulation, greedy
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
// -------------------------------
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    ll ts, tf, t; int n;
    cin >> ts >> tf >> t >> n;
    priority_queue<ll, vector<ll>, greater<ll>> q;
    ll last_exit = ts;
    ll min_wait = LLONG_MAX;
    ll ans = ts;
    ll prev_x = 0;
    while (n--) {
        ll x; cin >> x;
        while (q.size() and q.top() < x) q.pop();
        if (prev_x < x) {
            if (q.empty()) {
                ll s = max(x-1, ts);
                ll wait = s - (x-1);
                if (wait < min_wait and s + t <= tf) {
                    min_wait = wait;
                    ans = x-1;
                }
            } else {
                ll wait = (q.top() - x + 1) + (q.size() - 1) * t;
                if (wait < min_wait and x-1 + wait + t <= tf) {
                    min_wait = wait;
                    ans = x-1;
                }
            }
        }
        while (q.size() and q.top() <= x) q.pop();
        last_exit = max(last_exit, x) + t;
        q.push(last_exit);
        prev_x = x;
    }
    if (last_exit + t <= tf) ans = last_exit;
    cout << ans << '\n';
    return 0;
}
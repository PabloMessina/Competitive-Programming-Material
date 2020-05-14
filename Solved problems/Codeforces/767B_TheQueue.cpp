// tags: simulation, implementation, greedy
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
enum Kind { START, FINISH, FREE, ARRIVAL, QUERY };
struct Event {
    ll t; Kind kind;
    Event(ll t, Kind kind) : t(t), kind(kind) {}
    bool operator<(const Event& o) const {
        return tie(t, kind) > tie(o.t, o.kind);
    }
};
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    ll ts, tf, ta;
    cin >> ts >> tf >> ta;
    int n; cin >> n;
    priority_queue<Event> events;
    events.emplace(ts, START);
    events.emplace(tf, FINISH);
    events.emplace(tf - ta, QUERY);
    rep(i,0,n) {
        ll t; cin >> t;
        events.emplace(t, ARRIVAL);
        if (t > 0) events.emplace(t-1, QUERY);
    }
    int inqueue = 0;
    bool free = false;
    ll t_free = ts;
    ll ans = -1, min_wait = LLONG_MAX;
    while (!events.empty()) {
        auto e = events.top(); events.pop();
        if (e.kind == START) {
            free = true;
            if (inqueue > 0 and e.t + ta <= tf) {
                free = false;
                events.emplace(e.t + ta, FREE);
                t_free = e.t + ta;
                inqueue--;
            }
        } else if (e.kind == FINISH) {
            free = false;
        } else if (e.kind == FREE) {
            free = true;
            if (inqueue > 0 and e.t + ta <= tf) {
                free = false;
                events.emplace(e.t + ta, FREE);
                t_free = e.t + ta;
                inqueue--;
            }
        } else if (e.kind == ARRIVAL) {
            if (inqueue == 0 and free and e.t + ta <= tf) {
                free = false;
                events.emplace(e.t + ta, FREE);
                t_free = e.t + ta;
            } else {
                inqueue++;
            }
        } else {
            assert (e.kind == QUERY);
            ll wait = inqueue * ta + max(t_free - e.t, 0ll);
            if (wait < min_wait and e.t + wait + ta <= tf) {
                min_wait = wait;
                ans = e.t;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
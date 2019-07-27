// tags: simulation, priority_queue, greedy
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
const int MAXN = 100005;
ll TS, TF, TA;
int N;
ll curr_time;
ll best_time;
ll min_wait;

enum EventType { START, FINISH_ATTENDING, ARRIVAL, VASYA_ARRIVAL, STOP };
enum Person { VASYA, OTHER };

struct Event {
    ll t;
    EventType et;
    Event (ll t, EventType et) : t(t), et(et) {}
    bool operator<(const Event& o) const {
        if (t != o.t) return t > o.t;
        return et > o.et;
    }
};

bool can_attend;
bool busy;
queue<pair<ll,Person>> Q;
priority_queue<Event> events;

void attend() {
    if (Q.size() > 0 and can_attend and not busy) {
        ll t; Person p;
        tie(t,p) = Q.front();
        Q.pop();
        ll delta = curr_time - t;
        if (p == VASYA) {
            if (min_wait > delta) {
                min_wait = delta;
                best_time = t;
            }
            attend();
        } else {
            busy = true;
            events.emplace(curr_time + TA, FINISH_ATTENDING);
        }
    }
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> TS >> TF >> TA;
    cin >> N;
    ll eps = TA > 0;    
    events.emplace(TS, START);
    events.emplace(TF - TA, STOP);
    events.emplace(TS, VASYA_ARRIVAL);
    rep(i,0,N-1) {
        ll t; cin >> t;
        events.emplace(t, ARRIVAL);
        events.emplace(t-eps, VASYA_ARRIVAL);
    }
    can_attend = false;
    busy = false;
    best_time = -1;
    min_wait = LLONG_MAX;
    while (!events.empty()) {
        Event e = events.top();
        events.pop();
        curr_time = e.t;
        if (e.et == START) {
            can_attend = true;
            attend();
        } else if (e.et == STOP) {
            can_attend = false;
        } else if (e.et == FINISH_ATTENDING) {
            busy = false;
            events.emplace(curr_time, VASYA_ARRIVAL);
            attend();
        } else if (e.et == ARRIVAL) {
            Q.emplace(e.t, OTHER);
            attend();
        } else if (e.et == VASYA_ARRIVAL) {
            Q.emplace(e.t, VASYA);
            attend();
        }
    }
    cout << best_time << '\n';
    return 0;
}
// tags: geometry, sweep line, std::set, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
const int MAXN = 200000;
ll rw_dist[MAXN];
ll p_dist[MAXN];
int N, Q;
enum Type { RoadworkStart, RoadworkEnd, Person };
struct Event {
    Type type;
    ll score;
    int id;
    Event(Type type, int id, ll t, ll x) : type(type), id(id) {
        score = t - x;
    }
    bool operator<(const Event& o) const {
        return tie(score, type) < tie(o.score, o.type);
    }
};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    vector<Event> events;
    rep(i,0,N) {
        ll s, t, x; cin >> s >> t >> x;
        rw_dist[i] = x;
        events.emplace_back(RoadworkStart, i, 2*s-1, 2*x);
        events.emplace_back(RoadworkEnd, i, 2*t-1, 2*x);
    }
    rep(i,0,Q) {
        ll d; cin >> d;
        events.emplace_back(Person, i, 2*d, 0);
    }
    sort(events.begin(), events.end());
    auto cmp = [](int i, int j) { return tie(rw_dist[i], i) < tie(rw_dist[j], j) };
    set<int, decltype(cmp)> active_roadworks(cmp);
    for (Event& e : events) {
        if (e.type == RoadworkStart) {
            active_roadworks.insert(e.id);
        } else if (e.type == RoadworkEnd) {
            active_roadworks.erase(e.id);
        } else { // Person
            if (active_roadworks.empty()) {
                p_dist[e.id] = -1;
            } else {
                p_dist[e.id] = rw_dist[*active_roadworks.begin()];
            }
        }
    }
    rep(i,0,Q) cout << p_dist[i] << '\n';
    return 0;
}
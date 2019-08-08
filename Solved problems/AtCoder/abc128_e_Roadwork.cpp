// tags: geometry, sweep line, std::set, implementation
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
const int MAXN = 200000;
ll rw_dist[MAXN];
ll p_dist[MAXN];
int N, Q;
enum Type { Start, End, Person };
struct Event {
    Type type;
    ll score;
    int id;
    Event(Type _type, int _id, ll t, ll x) : type(_type), id(_id) {
        score = t - x;
    }
    bool operator<(const Event& rhs) const {
        if (score == rhs.score) return type < rhs.type;
        return score < rhs.score;
    }
};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    vector<Event> events;
    rep(i,0,N-1) {
        ll s, t, x; cin >> s >> t >> x;
        rw_dist[i] = x;
        events.emplace_back(Start, i, 2*s-1, 2*x);
        events.emplace_back(End, i, 2*t-1, 2*x);
    }
    rep(i,0,Q-1) {
        ll d; cin >> d;
        events.emplace_back(Person, i, 2*d, 0);
    }
    sort(events.begin(), events.end());
    auto cmp = [](int i, int j) {
        if (rw_dist[i] == rw_dist[j]) return i < j;
        return rw_dist[i] < rw_dist[j];
    };
    set<int, decltype(cmp)> active_roadworks(cmp);
    for (Event& e : events) {
        if (e.type == Start) {
            active_roadworks.insert(e.id);
        } else if (e.type == End) {
            active_roadworks.erase(e.id);
        } else { // Person
            if (active_roadworks.empty()) {
                p_dist[e.id] = -1;
            } else {
                p_dist[e.id] = rw_dist[*active_roadworks.begin()];
            }
        }
    }
    rep (i, 0, Q-1) cout << p_dist[i] << '\n';
    return 0;
}
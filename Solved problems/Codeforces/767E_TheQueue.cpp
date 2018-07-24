// TODO: finish this
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
// -------------------------------

const int MAXN = 100000;
ll ts, tf, t;
int n;
enum Type { RECEPT_ARRIVAL, RECEPT_DEPART, CLIENT };
struct Event {
    ll time; Type type; int count;
    bool operator<(const Event& rhs) {
        return time < rhs.time || (time == rhs.time and type < rhs.type);
    }
};

int main() {
    scanf("%lld%lld%lld%d", &ts, &tf, &t, &n);
    vector<Event> events;
    events.push_back({ts, RECEPT_ARRIVAL});
    events.push_back({ts, RECEPT_DEPART});
    map<ll,int> counts;
    rep(i,0,n-1) {
        ll a; scanf("%lld", &a);
        auto it = counts.find(a);
        if (it == counts.end()) {
            counts[a] = 1;
        } else {
            it->second++;
        }
    }
    for (auto& p : counts) {
        events.push_back{p.first, CLIENT, p.second};
    }

    return 0;
}
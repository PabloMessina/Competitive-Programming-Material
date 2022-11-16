// tags: domain compression, sweep line, fenwick tree (range update & point query)
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

int P, V;
struct Point {
    ll x, y;
    Point(ll x, ll y) : x(x), y(y) {}
};

vector<Point> plants, fence;
struct Event {
    ll x, y1, y2;
    int idx;
    bool isPlant;
    Event(ll x, ll y1, ll y2, int idx, bool isPlant) : x(x), y1(y1), y2(y2), idx(idx), isPlant(isPlant) {}
};

struct FT { // fenwick tree
    vector<int> t;
    FT(int n) { t.assign(n+1, 0); }    
    int query(int i) { // sum in range 1 .. i
        int ans = 0;
        for (; i; i -= (i & -i)) ans += t[i];
        return ans;
    }
    int query(int i, int j) { return query(j) - query(i-1); } // sum in range [i .. j]
    void update(int i, int v) { // increment i'th value by v (and propagate)
        for (; i < t.size(); i += i & (-i)) t[i] += v;
    }
    void update(int i, int j, int v) { update(i, v); update(j + 1, -v); }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    while (cin >> P >> V) { // for each input case
        set<ll> yset;
        rep(i,0,P) { // read plant coordinates
            ll x, y; cin >> x >> y;
            plants.emplace_back(x, y);
            yset.insert(y);
        }
        rep(i,0,V) { // read fence's vertices coordinates
            ll x, y; cin >> x >> y;
            fence.emplace_back(x, y);
            yset.insert(y);
        }
        // create events
        vector<Event> events;
        // add plant events
        rep(i,0,P) {
            ll x = plants[i].x;
            ll y = plants[i].y;
            events.emplace_back(x, y, y, i, true);
        }
        // add segment events
        rep(i,0,V) {
            int j = (i+1) % V;
            if (fence[i].x == fence[j].x) { // vertical segment
                assert (fence[i].y != fence[j].y);
                ll miny = fence[i].y;
                ll maxy = fence[j].y;
                if (miny > maxy) swap(miny, maxy);
                events.emplace_back(fence[i].x, miny, maxy, -1, false);
            }
        }
        // sort events by x coordinate
        sort(events.begin(), events.end(), [](Event& a, Event& b) {
            return a.x < b.x;
        });
        // domain compression: map all y values to a narrower domain
        umap<ll,ll> y2idx;
        int idx = 1;
        for (ll y : yset) y2idx[y] = idx++;
        // run sweep line: left to right
        FT ft(y2idx.size()+5);
        ll ans = 0;
        for (Event& e : events) {
            if (e.isPlant) { // plant encountered
                int idx = y2idx[e.y1];
                // if outside fence -> add plant's value to sum
                if (ft.query(idx) == 0) ans += e.idx + 1;
            } else { // segment encountered
                int a = y2idx[e.y1];
                int b = y2idx[e.y2];
                assert(a < b);
                if (ft.query(a) == 0) { // nothing in range
                    // add 1 to range -> we are now inside the fence
                    ft.update(a, b-1, 1);
                } else {
                    // substract 1 to range -> we are now outside the fence
                    ft.update(a, b-1, -1);
                }
            }
        }
        // print answer
        cout << ans << '\n';
        // clear memory
        plants.clear();
        fence.clear();
    }
    return 0;
}
// tags: geometry, sweep line
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
struct Rectangle {
    ll x1, x2, y1, y2;
};
enum Kind { START, END };
struct Event {
    ll x; Kind kind; int id;
    bool operator<(const Event& o) const {
        return tie(x, kind) < tie(o.x, o.kind);
    }
};
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<Rectangle> rects;
    vector<Event> h_events, v_events;
    rects.reserve(n);
    h_events.reserve(2*n);
    v_events.reserve(2*n);
    rep(i,0,n) {
        ll x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        rects.push_back({x1, x2, y1, y2});
        h_events.push_back({x1, START, i});
        h_events.push_back({x2, END, i});
        v_events.push_back({y1, START, i});
        v_events.push_back({y2, END, i});
    }
    bool yes = true;
    // horizontal sweep line
    {
        sort(h_events.begin(), h_events.end());
        multiset<ll> S, E;
        for (auto& e : h_events) {
            if (e.kind == START) {
                S.insert(rects[e.id].y1);
                E.insert(rects[e.id].y2);
                if (*S.rbegin() > *E.begin()) {
                    yes = false; goto answer;
                }
            } else {
                S.erase(rects[e.id].y1);
                E.erase(rects[e.id].y2);
            }
        }
    }
    // vertical sweep line
    {
        sort(v_events.begin(), v_events.end());
        multiset<ll> S, E;
        for (auto& e : v_events) {
            if (e.kind == START) {
                S.insert(rects[e.id].x1);
                E.insert(rects[e.id].x2);
                if (*S.rbegin() > *E.begin()) {
                    yes = false; goto answer;
                }
            } else {
                S.erase(rects[e.id].x1);
                E.erase(rects[e.id].x2);
            }
        }
    }
    answer:
    if (yes) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}
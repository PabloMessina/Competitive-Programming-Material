// tags: geometry, sweep line, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
enum Kind { START, END };
struct Event {
    Kind kind; int x, h;
    Event(Kind kind, int x, int h) : kind(kind), x(x), h(h) {}
    bool operator<(const Event& o) const {
        if (x != o.x) return x < o.x;
        if (kind != o.kind) return kind < o.kind;
        return kind == START ? h > o.h : h < o.h;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    vector<Event> events;
    int l, h, r;
    while (cin >> l >> h >> r) {
        events.emplace_back(START, l, h);
        events.emplace_back(END, r, h);
    }
    sort(events.begin(), events.end());
    vector<int> skyline;
    multiset<int> active_hs;
    int max_h = 0;
    for (auto& e : events) {
        if (e.kind == START) {
            if (max_h < e.h) {
                skyline.push_back(e.x);
                skyline.push_back(e.h);
                max_h = e.h;
            }
            active_hs.insert(e.h);
        } else {
            auto it = active_hs.find(e.h);
            active_hs.erase(it);
            int next_max_h;            
            if (active_hs.empty()) {
                next_max_h = 0;
            } else {
                // next_max_h = *prev(active_hs.end());
                next_max_h = *active_hs.rbegin();
            }
            if (next_max_h < max_h) {
                skyline.push_back(e.x);
                skyline.push_back(next_max_h);
            }
            max_h = next_max_h;
        }
    }
    bool f = true;
    for (int x : skyline) {
        if (f) f = false;
        else cout << ' ';
        cout << x;
    }
    cout << '\n';
    return 0;
}
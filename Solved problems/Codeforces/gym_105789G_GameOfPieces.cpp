#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i < b; ++i)
typedef long long int ll;

struct Interval {
    ll l, r, h;
    Interval() {}
    Interval(ll l, ll r, ll h) : l(l), r(r), h(h) {}
    bool operator<(const Interval& o) const {
        return l < o.l;
    }
};

signed main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    multiset<Interval> intervals;
    while (N--) {
        char c; ll l, p;
        cin >> c >> l >> p;
        Interval x;
        if (c == '|') {
            x = Interval(p, p+1, l);
        } else {
            x = Interval(p, p+l, 1);
        }
        auto new_it = intervals.insert(x);
        bool intersection_found = false;
        multiset<Interval>::iterator it;
        if (new_it != intervals.begin()) {
            it = prev(new_it);
            if (max(x.l, it->l) < min(x.r, it->r)) {
                intersection_found = true;
            }
        }
        if (not intersection_found and next(new_it) != intervals.end()) {
            it = next(new_it);
            if (max(x.l, it->l) < min(x.r, it->r)) {
                intersection_found = true;
            }
        }
        bool inserted = true;
        if (intersection_found) {
            if (it->l <= x.l and x.r <= it->r) {
                if (it->l < x.l) {
                    intervals.insert(Interval(it->l, x.l, it->h));
                }
                if (x.r < it->r) {
                    intervals.insert(Interval(x.r, it->r, it->h));
                }
                intervals.erase(new_it);
                new_it = intervals.insert(Interval(x.l, x.r, x.h + it->h));
                intervals.erase(it);
                cout << "S";
            } else {
                intervals.erase(new_it); // erase invalid newly added interval
                cout << "U";
                inserted = false;
            }
        } else {
            cout << "S";
        }
        if (inserted) {
            auto prev_it = new_it;
            auto next_it = new_it;
            if (new_it != intervals.begin()) {
                auto aux = prev(new_it);
                if (aux->r == new_it->l and aux->h == new_it->h) {
                    prev_it = aux;
                }
            }
            if (next(new_it) != intervals.end()) {
                auto aux = next(new_it);
                if (aux->l == new_it->r and aux->h == new_it->h) {
                    next_it = aux;
                }
            }
            if (prev_it != next_it) {
                Interval merged(prev_it->l, next_it->r, next_it->h);
                intervals.erase(prev_it, next(next_it));
                intervals.insert(merged);
            }
        }
    }
    cout << '\n';
    return 0;
}
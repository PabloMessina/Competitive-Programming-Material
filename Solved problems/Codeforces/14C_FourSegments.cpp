// tags: implementation, geometry
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
struct Point {
    ll x, y;
    bool operator==(const Point& p) const {
        return x == p.x and y == p.y;
    }
    bool operator!=(const Point& p) const {
        return x != p.x or y != p.y;
    }
};
struct Segment {
    Point a, b;
    bool horizontal() { return a.y == b.y; }
    bool vertical() { return a.x == b.x; }
};
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    vector<Segment> segs(4);
    vector<Segment> hsegs, vsegs;
    for (auto& s : segs) {
        cin >> s.a.x >> s.a.y >> s.b.x >> s.b.y;
        if (s.a == s.b) { cout << "NO\n"; return 0; }
        if (s.horizontal()) hsegs.push_back(s);
        else if (s.vertical()) vsegs.push_back(s);
        else { cout << "NO\n"; return 0; }
    }
    if (hsegs.size() != 2 or vsegs.size() != 2) {
        { cout << "NO\n"; return 0; }
    }    
    if (vsegs[0].a.x > vsegs[1].a.x) swap(vsegs[0], vsegs[1]);
    if (vsegs[0].a.y > vsegs[0].b.y) swap(vsegs[0].a, vsegs[0].b);
    if (vsegs[1].a.y < vsegs[1].b.y) swap(vsegs[1].a, vsegs[1].b);
    if (hsegs[0].a.y < hsegs[1].a.y) swap(hsegs[0], hsegs[1]);
    if (hsegs[0].a.x > hsegs[0].b.x) swap(hsegs[0].a, hsegs[0].b);
    if (hsegs[1].a.x < hsegs[1].b.x) swap(hsegs[1].a, hsegs[1].b);
    segs[0] = vsegs[0];
    segs[1] = hsegs[0];
    segs[2] = vsegs[1];
    segs[3] = hsegs[1];
    for (int i = 3, j = 0; j < 4; i=j++) {
        if (segs[i].b != segs[j].a) {
            cout << "NO\n"; return 0;
        }
    }
    cout << "YES\n";
    return 0;
}
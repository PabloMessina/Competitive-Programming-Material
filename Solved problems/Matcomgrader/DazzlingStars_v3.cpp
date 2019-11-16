// tags: geometry, sweep line, cross product
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
int N;
struct Point {
    int x, y;
    Point rotate_ccw() { return { -y, x }; }
    Point rotate_cw() { return { y, -x }; }
    int quadrant() const {
        if (x >= 0) return y >= 0 ? 0 : 3;
        return y >= 0 ? 1 : 2;
    }
    int cross(const Point& p) const { return x * p.y - y * p.x; }
    bool operator<(const Point& p) const {
        int q = quadrant();
        int pq = p.quadrant();
        if (q != pq) return q < pq;
        return cross(p) > 0;
    }
    bool operator==(const Point& p) const {
        return quadrant() == p.quadrant() and cross(p) == 0;
    }
    Point operator-(const Point& p) const { return { x - p.x, y - p.y }; }
};
const Point pMIN = { 1, 0 };
enum Kind { START, END };
struct Event {
    Point p;
    Kind kind;
    bool operator<(const Event& e) {
        if (p < e.p) return true;
        if (p == e.p) return kind < e.kind;
        return false;
    }
};
Point pts[1000];
int B[1000];
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N;
    rep(i,0,N) cin >> pts[i].x >> pts[i].y >> B[i];
    vector<Event> events;
    int M = 0;
    rep(i,0,N) rep(j,i+1,N) {
        int u = i, v = j;
        if (B[u] == B[v]) continue;
        if (B[u] < B[v]) swap(u, v);
        Point d = pts[v] - pts[u];
        Point s = d.rotate_cw();
        Point e = d.rotate_ccw();
        events.push_back({s, START});
        events.push_back({e, END});
        if (e < s) events.push_back({pMIN, START});
        M++;
    }
    sort(events.begin(), events.end());
    int count = 0;
    for (auto& e : events) {
        if (e.kind == START) count++;
        else count--;
        if (count == M) break;
    }
    if (count == M) {
        cout << "Y\n";
    } else {
        cout << "N\n";
    }
    return 0;
}
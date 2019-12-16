// tags: geometry, radial sweep line, trigonometry
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
const double PI = acos(-1);
const double _2PI = 2 * PI;
double cos_theorem_angle(double a, double b, double c) {
    return acos((b*b + c*c - a*a)/(2*b*c));
}
double correct_angle(double a) {
    while (a > _2PI) a -= _2PI;
    while (a < 0) a += _2PI;
    return a;
}
struct Point {
    int x, y;
    Point operator-(const Point& p) const { return { x - p.x, y - p.y }; }
    int norm2() { return x * x + y * y; }
    double norm() { return sqrt(norm2()); }
    double angle() { return correct_angle(atan2(y, x)); }
};
int N, R, R2;
Point pts[2000];
bool inside[2000];

enum Kind { ENTER, EXIT };
struct Event {
    double angle;
    Kind kind;
    int id;
    bool operator<(const Event& e) { 
        return tie(angle, kind) < tie(e.angle, e.kind);
    }
};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    vector<Event> events;
    events.reserve(4000);
    while (cin >> N >> R and N) {
        R2 = R*R;
        rep(i,0,N) cin >> pts[i].x >> pts[i].y;

        int ans = 1;        
        rep(i,0,N) {
            events.clear();
            rep(j,0,N) {
                if (i == j) continue;
                Point vec = pts[j] - pts[i];
                int dist2 = vec.norm2();
                if (dist2 > 4*R2) continue;
                double angle = vec.angle();
                if (dist2 == 4*R2) {                    
                    events.push_back({angle, ENTER, j});
                    events.push_back({angle, EXIT, j});
                } else {
                    double dist = vec.norm();
                    double delta = cos_theorem_angle(R, R, dist);
                    events.push_back({ correct_angle(angle - delta), ENTER, j });
                    events.push_back({ correct_angle(angle + delta), EXIT, j });
                }
            }
            sort(events.begin(), events.end());
            Point center = {pts[i].x + R, pts[i].y};
            int count = 0;
            rep(j,0,N) {
                if ((pts[j] - center).norm2() <= R2) {
                    inside[j] = true;
                    count++;
                } else {
                    inside[j] = false;
                }
            }
            assert (count >= 1);
            assert (inside[i]);
            ans = max(ans, count);
            for (auto& e : events) {
                if (e.kind == ENTER) {
                    if (not inside[e.id]) {
                        inside[e.id] = true;
                        count++;
                        ans = max(ans, count);
                    }
                } else {
                    if (inside[e.id]) {
                        inside[e.id] = false;
                        count--;
                    }
                }
            }
        }
        cout << "It is possible to cover " << ans << " points.\n";
    }    
    return 0;
}
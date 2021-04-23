// tags: geometry, 2D, cross product, dot product
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define ff first
#define ss second
// -------------------------------
const double EPS = 1e-12;
typedef double T;
struct P { // 2D
    T x, y;
    P() {}
    P(T x, T y) : x(x), y(y) {}
    bool operator==(const P& p) const { return x==p.x && y == p.y; }
    P operator+(const P& p) const { return {x+p.x, y+p.y}; }
    P operator-(const P& p) const { return {x-p.x, y-p.y}; }
    P operator*(T d) const { return {x*d, y*d}; }
    P operator/(T d) const { return {x/d, y/d}; }
    T operator^(const P& p) const { return x*p.y - y*p.x; }
    T operator*(const P& p) const { return x*p.x + y*p.y; }
};

T turn(P &a, P &b, P &c) { return (b - a) ^ (c - a); }

double polygon_area(vector<P>& p) {
    int n = p.size(); double a = 0;
    rep(i,0,n) { int j = (i+1) % n; a += (p[i].x + p[j].x) * (p[j].y - p[i].y); }
    return a * 0.5;
}

bool above(P &a, P &p) { return p.y >= a.y; }

bool crosses_ray(P &a, P &p, P &q) { return (above(a, q) - above(a, p)) * turn(a, p, q) > 0; }

bool in_disk(P &a, P &b, P &p) { return (a-p) * (b-p) <= EPS; }

bool on_segment(P &a, P &b, P &p) { return abs(turn(a, b, p)) < EPS && in_disk(a, b, p); }

bool on_line(P &a, P &b, P &p) { return abs(turn(a, b, p)) < EPS; }

bool in_polygon(vector<P> &p, P a, bool strict = true) {
    int c = 0, n = p.size();
    rep(i,0,n) {
        int j = (i+1)%n; if (on_segment(p[i], p[j], a)) return !strict;
        c += crosses_ray(a, p[i], p[j]);
    }
    return c & 1;
}

bool intersect_lines(P& a, P& b, P& c, P& d, double& t1, double& t2) {
    double x = (b - a) ^ (c - d);
    if (abs(x) < EPS) return false;
    t1 = (c - a) ^ (c - d) / x;
    t2 = (b - a) ^ (c - a) / x;
    return true;
}

double closest_t(P& a, P& b, P& x) { return (x-a)*(b-a) / ((b-a)*(b-a)); }

double sub_segment_integral(P& a, P& b, double t1, double t2) {
    P r = a + (b-a) * t1;
    P s = a + (b-a) * t2;
    return 0.5 * (r.x + s.x) * (s.y - r.y);
}

int n;
vector<vector<P>> pols;
int main() {    
    ios::sync_with_stdio(false); cin.tie(0);
    while (cin >> n and n != -1) {
        pols.clear();
        pols.resize(n);
        double area_union = 0;
        rep(j,0,n) {
            double  i, d, h; cin >> i >> d >> h;
            pols[j].emplace_back(i, 0);
            pols[j].emplace_back(d, 0);
            pols[j].emplace_back((i+d)/2., h);
        }
        rep(i,0,n) {
            int m = pols[i].size();
            rep(j,0,m) {
                P a = pols[i][j], b = pols[i][(j+1) % m];
                vector<pair<double,int>> events;
                rep(ii,0,n) if (i != ii) {
                    if (in_polygon(pols[ii], a)) events.emplace_back(0, 0);
                    int mm = pols[ii].size();
                    vector<pair<double,int>> events_;
                    rep(jj,0,mm) {
                        P c = pols[ii][jj], d = pols[ii][(jj+1) % mm];
                        double t1, t2;
                        if (intersect_lines(a,b,c,d,t1,t2)) {
                            if (EPS < t1 and t1 < 1 - EPS and -EPS < t2 and t2 < 1. + EPS) {
                                events_.emplace_back(t1, ((b-a)^(d-c)) > 0);
                            }
                        } else if (i < ii and on_line(a,b,c) and ((b-a)*(d-c) > 0)) {
                            t1 = max(closest_t(a, b, c), 0.);
                            t2 = min(closest_t(a, b, d), 1.);
                            if (t1 + EPS < t2) {
                                events.emplace_back(t1, 0);
                                events.emplace_back(t2, 1);
                            }
                        }
                    }
                    int s = events_.size();
                    rep(k,0,s) {
                        auto e0 = events_[(k-1+s) % s];
                        auto e1 = events_[k];
                        auto e2 = events_[(k+1) % s];
                        bool b1 = abs(e0.ff - e1.ff) < EPS;
                        bool b2 = abs(e1.ff - e2.ff) < EPS;
                        if ((b1 and e0.ss == e1.ss) or (!b1 and !b2) or s == 1) events.emplace_back(e1);
                    }
                }
                if (events.size()) {                
                    sort(events.begin(), events.end());
                    int cnt = 0;
                    double t = 0;
                    for (auto& e : events) {
                        if (e.ss == 0) {
                            if (cnt++ == 0) area_union += sub_segment_integral(a, b, t, e.ff);
                        } else cnt--;
                        t = e.ff;
                    }
                    if (cnt == 0) area_union += sub_segment_integral(a, b, t, 1.);
                } else {
                    bool contained = false;
                    rep(k,0,n) if (i != k and in_polygon(pols[k], (a+b)/2)) {
                        contained = true; break;
                    }
                    if (!contained) area_union += (b.x + a.x) * (b.y - a.y) * 0.5;
                }
            }
        }
        cout << setprecision(2) << fixed << area_union << '\n';
    }
    return 0;
}
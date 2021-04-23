// TODO: pending
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

T turn(P &a, P &b, P &c) { return (b-a)^(c-a); }

double polygon_area(vector<P>& p) {
    int n = p.size(); double a = 0;
    rep(i,0,n) { int j = (i+1) % n; a += (p[i].x + p[j].x) * (p[j].y - p[i].y); }
    return a * 0.5;
}

bool on_line(P &a, P &b, P &p) { return abs(turn(a, b, p)) < EPS; }

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

double area_union(vector<vector<P>> pols) {
    double area = 0.;
    int n = pols.size();
    rep(i,0,n) {
        int m = pols[i].size();
        rep(j,0,m) {
            P a = pols[i][j], b = pols[i][(j+1) % m];
            vector<pair<double,int>> events;
            rep(ii,0,n) if (i != ii) {
                int mm = pols[ii].size();
                vector<tuple<double,int,bool>> aux, aux_;
                rep(jj,0,mm) {
                    P c = pols[ii][jj], d = pols[ii][(jj+1) % mm];
                    double t1, t2;
                    if (intersect_lines(a,b,c,d,t1,t2)) {
                        if (-EPS < t2 and t2 < 1. + EPS) {
                            aux.emplace_back(t1, ((b-a)^(d-c)) > 0, abs(t2) < EPS or abs(1. - t2) < EPS);
                        }
                    } else if (on_line(a,b,c) and ((b-a)*(d-c) > 0)) {
                        t1 = closest_t(a, b, c);
                        t2 = closest_t(a, b, d);
                        if (t1 + EPS < t2) {
                            aux.emplace_back(t1, 0, true);
                            aux.emplace_back(t2, 1, true);
                        }
                    }
                }                
                int s = aux.size();
                sort(aux.begin(), aux.end());
                // printf("*** aux.size() = %d\n", aux.size());
                // for (auto& e : aux) {
                //     printf("    e = (t=%lf, c=%d, b=%d)\n", get<0>(e), get<1>(e), get<2>(e));
                // }
                rep(k,0,s) {
                    if (k > 0 and abs(get<0>(aux[k]) - get<0>(aux[k-1])) < EPS
                        and get<1>(aux[k]) != get<1>(aux[k-1])) continue;
                    if (k < s-1 and abs(get<0>(aux[k]) - get<0>(aux[k+1])) < EPS
                        and get<1>(aux[k]) != get<1>(aux[k+1])) continue;
                    if (k > 0 and abs(get<0>(aux[k]) - get<0>(aux[k-1])) < EPS
                        and get<1>(aux[k]) == get<1>(aux[k-1])) continue;
                    aux_.emplace_back(aux[k]);
                }                
                // printf("*** aux_.size() = %d\n", aux_.size());
                // for (auto& e : aux_) {
                //     printf("    e = (t=%lf, c=%d, b=%d)\n", get<0>(e), get<1>(e), get<2>(e));
                // }
                assert (aux_.size() % 2 == 0);
                if (i < ii) for (auto& e : aux_) events.emplace_back(get<0>(e), get<1>(e));
                else {
                    int s = aux_.size();
                    rep(k,0,s) {
                        auto e = aux_[k];
                        if (not get<2>(e) or
                            (k == 0 and not get<2>(aux_[k+1])) or
                            (k == s-1 and not get<2>(aux_[k-1])) or
                            (not get<2>(aux_[k-1]) and not get<2>(aux_[k+1])))
                            events.emplace_back(get<0>(e), get<1>(e));
                    }
                }
            }
            // printf("i=%d, j=%d, a = (%lf, %lf), b = (%lf, %lf)\n", i, j, a.x, a.y, b.x, b.y);
            if (events.size()) {
                assert (events.size() % 2 == 0);
                sort(events.begin(), events.end());
                // for (auto& e : events) {
                //     printf("\t e = (%lf, %d)\n", e.ff, e.ss);
                // }
                int cnt = 0;
                double t = 0;
                for (auto& e : events) {
                    if (e.ss == 0) {
                        if (cnt++ == 0) {
                            double t1 = max(t, 0.);
                            double t2 = min(e.ff, 1.);
                            if (t1 < t2) area_union += sub_segment_integral(a, b, t1, t2);
                        }
                    } else cnt--;
                    assert(cnt >= 0);
                    t = e.ff;
                }
                assert (cnt == 0);
                if (t < 1.) area_union += sub_segment_integral(a, b, t, 1.);
            } else {
                area_union += (b.x + a.x) * (b.y - a.y) * 0.5;
            }
        }
    }
}

int n;
vector<vector<P>> pols;
int main() {    
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    pols.resize(n);
    double area_sum = 0;
    double area_union = 0;
    rep(i,0,n) {
        int m; cin >> m;
        rep(j,0,m) {
            double x, y; cin >> x >> y;
            pols[i].emplace_back(x, y);
        }
        double area = polygon_area(pols[i]);
        if (area < 0) reverse(pols[i].begin(), pols[i].end());
        area_sum += abs(area);
    }
    rep(i,0,n) {
        int m = pols[i].size();
        rep(j,0,m) {
            P a = pols[i][j], b = pols[i][(j+1) % m];
            vector<pair<double,int>> events;
            rep(ii,0,n) if (i != ii) {
                int mm = pols[ii].size();
                vector<tuple<double,int,bool>> aux, aux_;
                rep(jj,0,mm) {
                    P c = pols[ii][jj], d = pols[ii][(jj+1) % mm];
                    double t1, t2;
                    if (intersect_lines(a,b,c,d,t1,t2)) {
                        if (-EPS < t2 and t2 < 1. + EPS) {
                            aux.emplace_back(t1, ((b-a)^(d-c)) > 0, abs(t2) < EPS or abs(1. - t2) < EPS);
                        }
                    } else if (on_line(a,b,c) and ((b-a)*(d-c) > 0)) {
                        t1 = closest_t(a, b, c);
                        t2 = closest_t(a, b, d);
                        if (t1 + EPS < t2) {
                            aux.emplace_back(t1, 0, true);
                            aux.emplace_back(t2, 1, true);
                        }
                    }
                }                
                int s = aux.size();
                sort(aux.begin(), aux.end());
                // printf("*** aux.size() = %d\n", aux.size());
                // for (auto& e : aux) {
                //     printf("    e = (t=%lf, c=%d, b=%d)\n", get<0>(e), get<1>(e), get<2>(e));
                // }
                rep(k,0,s) {
                    if (k > 0 and abs(get<0>(aux[k]) - get<0>(aux[k-1])) < EPS
                        and get<1>(aux[k]) != get<1>(aux[k-1])) continue;
                    if (k < s-1 and abs(get<0>(aux[k]) - get<0>(aux[k+1])) < EPS
                        and get<1>(aux[k]) != get<1>(aux[k+1])) continue;
                    if (k > 0 and abs(get<0>(aux[k]) - get<0>(aux[k-1])) < EPS
                        and get<1>(aux[k]) == get<1>(aux[k-1])) continue;
                    aux_.emplace_back(aux[k]);
                }                
                // printf("*** aux_.size() = %d\n", aux_.size());
                // for (auto& e : aux_) {
                //     printf("    e = (t=%lf, c=%d, b=%d)\n", get<0>(e), get<1>(e), get<2>(e));
                // }
                assert (aux_.size() % 2 == 0);
                if (i < ii) for (auto& e : aux_) events.emplace_back(get<0>(e), get<1>(e));
                else {
                    int s = aux_.size();
                    rep(k,0,s) {
                        auto e = aux_[k];
                        if (not get<2>(e) or
                            (k == 0 and not get<2>(aux_[k+1])) or
                            (k == s-1 and not get<2>(aux_[k-1])) or
                            (not get<2>(aux_[k-1]) and not get<2>(aux_[k+1])))
                            events.emplace_back(get<0>(e), get<1>(e));
                    }
                }
            }
            // printf("i=%d, j=%d, a = (%lf, %lf), b = (%lf, %lf)\n", i, j, a.x, a.y, b.x, b.y);
            if (events.size()) {
                assert (events.size() % 2 == 0);
                sort(events.begin(), events.end());
                // for (auto& e : events) {
                //     printf("\t e = (%lf, %d)\n", e.ff, e.ss);
                // }
                int cnt = 0;
                double t = 0;
                for (auto& e : events) {
                    if (e.ss == 0) {
                        if (cnt++ == 0) {
                            double t1 = max(t, 0.);
                            double t2 = min(e.ff, 1.);
                            if (t1 < t2) area_union += sub_segment_integral(a, b, t1, t2);
                        }
                    } else cnt--;
                    assert(cnt >= 0);
                    t = e.ff;
                }
                assert (cnt == 0);
                if (t < 1.) area_union += sub_segment_integral(a, b, t, 1.);
            } else {
                area_union += (b.x + a.x) * (b.y - a.y) * 0.5;
            }
        }
    }
    cout << setprecision(8) << fixed << area_sum << ' ' << area_union << '\n';
    return 0;
}

/* 

2
4 1 0 3 0 3 2 1 2
3 0 0 2 0 1 1
ans = 5.0 4.5

2
4 0 0 2 0 2 2 0 2
3 0 0 2 0 1 2
ans = 6.0 4.0

2
4 0 2 2 0 4 2 2 4
3 2 0 4 2 1 3
ans = 12.0 8.0

 */
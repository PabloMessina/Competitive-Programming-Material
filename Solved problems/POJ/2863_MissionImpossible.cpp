// TODO: debug
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
// typedefs
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
const double PI = acos(-1);
const double EPS = 1e-10;
typedef double T;
struct P {
    T x, y;
    P operator+(const P& p) const { return {x+p.x, y+p.y}; }
    P operator-(const P& p) const { return {x-p.x, y-p.y}; }
    P operator*(T d) const { return {x*d, y*d}; }
    T operator^(const P& p) const { return x*p.y - y*p.x; } // cross product
    T operator*(const P& p) const { return x*p.x + y*p.y; } // dot product
    bool operator==(const P& o) const { return x == o.x and y == o.y; }
    double angle() { return atan2(y, x); } // [-PI, PI]
    T norm2() { return x*x + y*y; }
    double norm() { return sqrt(norm2()); }
};
struct Circle {
    P c; int r;
    bool operator==(const Circle& o) const { return r == o.r and c == o.c; }
};
bool circle_in_circle(Circle& a, Circle& b) {
    return (b.c - a.c).norm2() <= (b.r - a.r) * (b.r - a.r) + EPS;
}
bool do_circles_intersect(Circle& a, Circle& b) {
    return (a.c - b.c).norm2() <= (a.r + b.r) * (a.r + b.r) + EPS;
}
int B, N, M;
vector<P> border, infor, infor_;
vector<Circle> rads, rads_;
vector<vector<int>> g, g_;
set<ii> cut_edges;

vector<int> D, L;
void dfs(int u, int p, int d) {
    D[u] = L[u] = d;
    for(int v : g[u]) {
        if (v == p) continue;
        if (D[v] == -1) {
            dfs(v, u, d+1);
            if (L[v] > D[u]) { cut_edges.emplace(u, v); cut_edges.emplace(v, u); }
            L[u] = min(L[u], L[v]); 
        } else L[u] = min(L[u], D[v]);
    }
}

vector<vector<int>> comps;
vector<bool> vis;
void dfs2(int u) {
    if (vis[u]) return;
    vis[u] = true;
    comps.back().push_back(u);
    for (int v : g[u]) dfs2(v);
}

T turn(P &a, P &b, P &c) { return (b-a)^(c-a); }
bool on_line(P& a, P& b, P& p) { return abs(turn(a,b,p)) < EPS;}
bool in_disk(P &a, P &b, P &p) { return abs((a-p)*(b-p)) <= EPS; }
bool on_segment(P &a, P &b, P &p) { return on_line(a,b,p) && in_disk(a,b,p); }
bool above(P &a, P &p) { return p.y >= a.y; }
bool crosses_ray(P &a, P &p, P &q) {
    return (above(a, q) - above(a, p)) * turn(a, p, q) > 0;
}
bool in_polygon(vector<P> &p, P a, bool strict = true) {
    int c = 0, n = p.size();
    rep(i,0,n) {
        int j = (i+1)%n; if (on_segment(p[i], p[j], a)) return !strict;
        c += crosses_ray(a, p[i], p[j]);
    }
    return c & 1;
}

double point_segment_dist(P& p, P& a, P& b) {
    if (a==b) return (p-a).norm(); // segment is a single point
    P d = b-a; // direction
    double t = (d*(p-a)) / d.norm2();
    if (t <= 0) return (p-a).norm(); // truncate left
    if (t >= 1) return (p-b).norm(); // truncate right
    return (a + d * t - p).norm();
}

vector<vector<P>> polygons;

vector<P> get_polygon(vector<int>& comp) {
    assert (comp.size() >= 2);
    int s = comp[0];
    rep(i,1,comp.size()) {
        if (tie(rads[i].c.x, rads[i].c.y) < tie(rads[s].c.x, rads[s].c.y)) {
            s = i;
        }
    }
    P pc = rads[s].c;
    pc.x--;
    int p = -1;
    vector<P> poly;
    poly.push_back(rads[s].c);
    int u = s;
    while (1) {
        int nxt = -1;
        double min_angle = 999999;
        double ref_angle = (pc - rads[u].c).angle();
        for (int v : g[u]) {
            if (v == p) continue;
            double rel_angle = (rads[v].c - rads[u].c).angle() - ref_angle;
            if (rel_angle < -EPS) rel_angle += 2.*PI;
            if (abs(rel_angle) < EPS) continue;
            if (min_angle > rel_angle) {
                min_angle = rel_angle;
                nxt = v;
            }
        }
        assert (nxt != -1);
        if (nxt == s) break;
        poly.push_back(rads[nxt].c);
        p = u;
        pc = rads[u].c;
        u = nxt;
    }
    return poly;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    while (1) {
        // read input
        cin >> B; if (B == 0) break;
        border.resize(B);
        for (auto& b : border) cin >> b.x >> b.y;
        cin >> N;
        infor.resize(N);
        for (auto& i : infor) cin >> i.x >> i.y;
        cin >> M;
        rads.resize(M);
        for (auto& rad : rads) cin >> rad.c.x >> rad.c.y >> rad.r;
        // remove redundant radars
        rads_.clear();
        rep(i,0,M) {
            bool add = true;
            auto& radi = rads[i];
            rep(j,0,M) {
                if (i == j) continue;
                auto& radj = rads[j];
                if (radi == radj) { if (i < j) { add = false; break; } }
                else if (circle_in_circle(radi, radj)) { add = false; break; }
            }
            if (add) rads_.push_back(radi);
        }
        rads.swap(rads_);
        M = rads.size();
        // build radar graph
        g.assign(M, vector<int>());
        rep(i,0,M) rep(j,i+1,M) if (do_circles_intersect(rads[i], rads[j])) {
            g[i].push_back(j);
            g[j].push_back(i);
        }
        // remove cut edges 
        D.assign(M, -1);
        L.resize(M);
        cut_edges.clear();
        rep(u,0,M) if (D[u] == -1) dfs(u,-1,0);
        g_.assign(M, vector<int>());
        rep(u,0,M) for (int v : g[u]) if (cut_edges.count({u, v}) == 0) g_[u].push_back(v);
        g.swap(g_);
        // find connected components
        vis.assign(M, false);
        comps.clear();
        rep(u,0,M) if (!vis[u]) {
            comps.push_back(vector<int>());
            dfs2(u);
        }
        // find polygon for each connected component
        polygons.clear();
        for (vector<int>& comp : comps) if (comp.size() > 1) {
            polygons.push_back(get_polygon(comp));
        }
        // find informants outside all polygons
        infor_.clear();
        for (auto& i : infor) {
            bool valid = true;
            for (auto& poly : polygons) if (in_polygon(poly, i, false)) { valid = false; break; }
            if (valid) infor_.push_back(i);
        }
        infor.swap(infor_);
        //
        if (infor.empty()) cout << "Mission impossible\n";
        else {
            double maxscore = -1;
            int ans = -1;
            int i = 1;
            for (auto& inf : infor) {
                double score = 0;
                rep(j,0,border.size()) {
                    P a = border[j];
                    P b = border[(j+1) % border.size()];
                    score = min(score, point_segment_dist(inf, a, b));
                }
                if (score > maxscore + EPS) {
                    maxscore = score;
                    ans = i;
                }
                ++i;
            }
            assert (ans != -1);
            cout << "Contact informer " << ans << '\n';
        }
    }
    return 0;
}
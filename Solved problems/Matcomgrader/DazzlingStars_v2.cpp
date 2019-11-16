// tags: geometry, cross product, dot product, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
int N;
struct Point {
    int x, y;
    int cross(const Point& p) const { return x * p.y - y * p.x; }
    int dot(const Point& p) const { return x * p.x + y * p.y; }
    int quadrant() const {
        if (x >= 0) return y >= 0 ? 0 : 3;
        return y >= 0 ? 1 : 2;
    }
    Point rotate90() { return { -y, x }; }
    bool operator<(const Point& p) const {
        int q = quadrant();
        int qp = p.quadrant();
        if (q != qp) return q < qp;
        return cross(p) > 0;
    }
    bool operator<=(const Point& p) const {
        int q = quadrant();
        int qp = p.quadrant();
        if (q != qp) return q < qp;
        return cross(p) >= 0;
    }
    bool operator==(const Point& p) const {
        return quadrant() == p.quadrant() and cross(p) == 0;
    }
    Point operator-(const Point& p) const { return { x - p.x, y - p.y }; }
};
Point pts[1000];
int B[1000], idxs[1000];

int update_interval(Point& a, Point& b, Point& c, Point& d) {
    if (b == c and d == a) { return 2; }
    bool nowrap1 = a <= b;
    bool nowrap2 = c <= d;
    if (nowrap1 and nowrap2) {
        a = max(a, c);
        b = min(b, d);
        return a <= b;
    } else if (!nowrap1 and !nowrap2) {
        a = max(a, c);
        b = min(b, d);
        return true;
    } else if (!nowrap1 and nowrap2) {
        if (a <= d) {
            b = d; return true;
        } else if (c <= b) {
            a = c; return true;
        }
        return false;
    } else {
        if (c <= b) {
            a = c; return true;
        } else if (a <= d) {
            b = d; return true;
        }
        return false;
    }
}

valid_order(const Point& dir) {
    rep(i,0,N) idxs[i] = i;
    sort(idxs, idxs + N, [&dir](int i, int j) {
        return dir.dot(pts[i]) < dir.dot(pts[j]);
    });
    rep(i,0,N) {
        int ii = idxs[i];
        int score_ii = dir.dot(pts[ii]);
        rep(j,i+1,N) {
            int jj = idxs[j];
            int score_jj = dir.dot(pts[jj]);
            if (score_ii < score_jj and B[ii] > B[jj]) return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N;
    rep(i,0,N) cin >> pts[i].x >> pts[i].y >> B[i];
    bool possible = true;
    bool first = true;
    Point a, b;
    rep(i,0,N) {
        rep(j,i+1,N) {
            int u = i, v = j;
            if (B[u] == B[v]) continue;
            if (B[u] < B[v]) swap(u,v);
            Point c = pts[u] - pts[v];
            Point d = pts[v] - pts[u];
            if (first) {
                a = c, b = d;
                first = false;
            } else {
                int ret = update_interval(a, b, c, d);
                if (ret == 2) {
                    possible = valid_order(a.rotate90()) or valid_order(b.rotate90());
                    goto answer;                    
                } else if (ret == 0) {
                    possible = false; goto answer;                        
                }
            }
        }
    }
    answer:
    if (possible) cout << "Y\n";
    else cout << "N\n";
    return 0;
}
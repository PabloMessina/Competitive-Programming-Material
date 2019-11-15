// tags: geometry, cross product, dot product, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
int N;
struct Point {
    int x, y;
    Point operator-(const Point& p) const { return { x - p.x, y - p.y }; }
    Point rotate90() const { return { -y, x }; }
    int quadrant() const {
        if (x >= 0) return y >= 0 ? 0: 3;
        return y >= 0 ? 1 : 2;
    }
    int cross(const Point& p) const { return x * p.y - y * p.x; }
    int dot(const Point& p) const { return x * p.x + y * p.y; }
    bool operator<(const Point& p) const {
        int q = quadrant();
        int qp = p.quadrant();
        if (q != qp) return q < qp;
        return cross(p) > 0;
    }
    bool operator==(const Point& p) const {
        return quadrant() == p.quadrant() and cross(p) == 0;
    }
};
int B[1000], idxs[1000];
Point pts[1000];
bool conflict[1000][1000];

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N;
    rep(i,0,N) {
        cin >> pts[i].x >> pts[i].y >> B[i];
    }
    vector<tuple<Point,int,int>> arrows;
    arrows.reserve(N * N);
    rep(i,0,N) {
        rep(j,0,N) {
            if (i == j) continue;
            arrows.emplace_back(pts[j] - pts[i], i, j);
        }
    }
    sort(arrows.begin(), arrows.end());
    int inverted = 0;
    Point dir0 = get<0>(arrows[0]).rotate90();
    auto cmp = [&dir0] (int i, int j) {
        return dir0.dot(pts[i]) < dir0.dot(pts[j]);
    };
    rep(i,0,N) idxs[i] = i;
    sort(idxs, idxs + N, cmp);
    rep(i,0,N) {
        int ii = idxs[i];
        int score_ii = dir0.dot(pts[ii]);
        rep(j,i+1,N) {
            int jj = idxs[j];
            int score_jj = dir0.dot(pts[jj]);
            if (score_ii < score_jj and B[ii] > B[jj]) {
                conflict[ii][jj] = conflict[jj][ii] = true;
                inverted++;
            }
        }
    }
    if (inverted == 0) {
        cout << "Y\n";
    } else {
        int i = 0;
        int j = 1;
        while (get<0>(arrows[j]) == dir0) ++j;
        while (j < arrows.size() and inverted > 0) {
            rep(k,i,j) {
                int x = get<1>(arrows[k]);
                int y = get<2>(arrows[k]);
                if (B[x] < B[y] and not conflict[x][y]) {
                    conflict[x][y] = conflict[y][x] = true;
                    inverted++;
                } else if (B[x] > B[y] and conflict[x][y]) {
                    conflict[x][y] = conflict[y][x] = false;
                    inverted--;
                }
            }
            i = j;
            Point dir1 = get<0>(arrows[j]);
            while (j+1 < arrows.size() and get<0>(arrows[j+1]) == dir1) ++j;
            ++j;
            rep(k,i,j) {
                int x = get<1>(arrows[k]);
                int y = get<2>(arrows[k]);
                if (conflict[x][y]) {
                    conflict[x][y] = conflict[y][x] = false;
                    inverted--;
                }
            }
        }
        if (inverted == 0) {
            cout << "Y\n";
        } else {
            cout << "N\n";
        }
    }
    return 0;
}
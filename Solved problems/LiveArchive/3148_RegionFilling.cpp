// tags: geometry, point in polygon, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
struct Point {
    int x, y;
    bool operator==(const Point& p) const { return x == p.x and y == p.y; }
    Point operator-(const Point& p) const { return { x - p.x, y - p.y }; }
    int cross(const Point& p) { return x * p.y - y * p.x; }
};
int R, C, N;
int D[8][2] = {{-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};

bool inside(vector<Point>& poly, Point p) {
    int n = poly.size();
    int count = 0;
    for (int i = n-1, j = 0; j < n; i=j++) {
        Point& a = poly[i];
        Point& b = poly[j];
        if ((a.y < p.y and p.y <= b.y and (b-a).cross(p-a) >= 0)
                or (b.y < p.y and p.y <= a.y and (b-a).cross(p-a) < 0)) {
            count++;
        }
    }
    return count & 1;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);    
    while (cin >> R >> C >> N) {
        if (R == 0) break;
        vector<vector<char>> board(R, vector<char>(C, '.'));
        vector<char> path;
        rep(_,0,N) {
            char fill; int r, c, k;
            cin >> fill >> r >> c >> k;
            path.resize(k);
            rep(j,0,k) cin >> path[j];
            --r, --c;                        
            vector<Point> poly;
            bool outside = false;
            bool open = false;
            char intersected = 0;
            poly.push_back({r,c});
            if (board[r][c] != '.') {
                intersected = board[r][c];
                goto CHECK;
            }
            for (char mov : path) {
                int m = mov - 'A';
                r += D[m][0];
                c += D[m][1];
                if (not (0 <= r and r < R and 0 <= c and c < C)) {
                    outside = true;
                    goto CHECK;
                }
                if (board[r][c] != '.') {
                    intersected = board[r][c];
                    goto CHECK;
                }
                poly.push_back({r, c});
            }
            open = not (poly[0] == poly.back());
            CHECK:
            if (intersected) {
                cout << "REGION " << fill << " BOUNDARY INTERSECTS REGION " << intersected << '\n';
                continue;
            }
            if (outside) {
                cout << "REGION " << fill << " GOES OUTSIDE THE ARRAY\n";
                continue;
            }
            if (open) {
                cout << "REGION " << fill << " BOUNDARY IS NOT CLOSED\n";
                continue;
            }
            poly.pop_back();
            for (Point& p : poly) board[p.x][p.y] = fill;
            if (poly.size() > 2) {
                rep(r,0,R) rep(c,0,C) if (inside(poly, {r,c})) board[r][c] = fill;
            }
        }
        rep(r,0,R) {
            rep(c,0,C) cout << board[r][c];
            cout << '\n';
        }
        cout << '\n';
    }
    return 0;
}
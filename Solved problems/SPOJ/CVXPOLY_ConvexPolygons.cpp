// tags: DP bottom-up, angle comparison, geometry
// based on https://page.mi.fu-berlin.de/rote/Papers/pdf/Counting+convex+polygons+in+planar+point+sets.pdf

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define MAXN 100
#define MOD 1234567

int n;
int dp[MAXN][MAXN][MAXN];

enum Quadrant { UpRight, Up, UpLeft, DownLeft, Down, DownRight };

int getQuadrant(int x, int y) {
    if (x > 0) return (y >= 0) ? UpRight : DownRight;
    if (x < 0) return (y >= 0) ? UpLeft : DownLeft;
    return (y >= 0) ? Up : Down;
}

int cmpAngles(int x1, int y1, int x2, int y2) {
    int q1 = getQuadrant(x1,y1);
    int q2 = getQuadrant(x2,y2);
    if (q1 > q2) return 1;
    if (q1 < q2) return -1;
    int m1 = abs(y1 * x2);
    int m2 = abs(y2 * x1);
    switch (q1) {
        case UpRight:
        case DownLeft:
            return (m1 > m2) ? 1 : (m1 < m2) ? -1 : 0;
        case UpLeft:
        case DownRight:
            return (m1 > m2) ? -1 : (m1 < m2) ? 1 : 0;
        default: return 0;
    }
}

struct Point {
    int x, y;
    bool operator<(const Point& p) const {
        return y < p.y || (y == p.y && x < p.x);
    }
};
vector<Point> pts;

struct Ray {
    int s, t;
    bool operator<(const Ray& r) const {
        return cmpAngles(
            pts[t].x - pts[s].x,
            pts[t].y - pts[s].y,
            pts[r.t].x - pts[r.s].x,
            pts[r.t].y - pts[r.s].y
        ) > 0;
    }
};
vector<vector<Ray>> above;

int main () {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        pts.clear();
        above.assign(n, vector<Ray>());

        // collect pts
        FOR(i, 0, n-1) {
            int x, y; scanf("%d%d", &x, &y);
            pts.push_back({x, y});
        }
        sort(pts.begin(), pts.end());

        // build above sets
        FOR(i, 0, n-2) {
            FOR(j, i+1, n-1)
                above[i].push_back({ i, j });
            sort(above[i].begin(), above[i].end());
        }

        // DP
        int ans = 0;
        FOR(s, 0, n-1) { //  fix s
            if (above[s].size() >= 2) {

                FOR(i, 1, above[s].size()-1) {
                    int p = above[s][i].t; // fix p

                    FOR(j, 0, i-1) {
                        int q = above[s][j].t; // fix q
                        int sum = 1;

                        FOR(k, 0, j-1) { // iterate over r
                            int r = above[s][k].t;
                            if (cmpAngles(
                                    pts[r].x - pts[q].x,
                                    pts[r].y - pts[q].y,
                                    pts[q].x - pts[p].x,
                                    pts[q].y - pts[p].y
                                ) > 0) {
                                sum = (sum + dp[s][q][r]) % MOD;
                            }
                        }

                        dp[s][p][q] = sum;
                        ans = (ans + sum) % MOD;
                    }
                }
            }
        }
        // answer
        printf("%d\n", ans);
    }
    return 0;
}
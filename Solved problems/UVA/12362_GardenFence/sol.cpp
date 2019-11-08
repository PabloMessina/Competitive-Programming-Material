// tags: geometry, two pointers, radial sweepline, cross product, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
int P, L;
enum Kind { PINE, LARCH };
struct Point {
    ll x, y;    
    Point operator-(const Point& p) const { return { x - p.x, y - p.y }; }
    ll norm2() { return x * x + y * y; }
    ll cross(const Point& p) const { return x * p.y - y * p.x; }
    Point negative() { return { -x, -y}; }
    int get_quadrant() const {
        if (x > 0) return y >= 0 ? 0 : 3;
        return y > 0 ? 1 : 2;
    }
    bool operator<(const Point& p) const { // smaller quadrant or same quadrant and to the right
        int q = get_quadrant();
        int qp = p.get_quadrant();
        if (q != qp) return q < qp;
        return cross(p) > 0;
    }
    bool operator==(const Point& p) const { // same direction and sense
        return get_quadrant() == p.get_quadrant() and cross(p) == 0;
    }
};
Point pts[2000];
Kind kinds[2000];
int values[2000];
void add_val(int& pine_sum, int& larch_sum, int i, int coef) {
    if (kinds[i] == PINE) pine_sum += values[i] * coef;
    else larch_sum += values[i] * coef;
}
int main() { 
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    vector<tuple<Point,ll,int>> tuples;
    tuples.reserve(2000);    
    while (cin >> P >> L and P) { // for each test case
        int tot_sum_pine = 0; // sum of all pine values
        int tot_sum_larch = 0; // sum of all larch values
        rep(i,0,P-1) { // read pines
            cin >> pts[i].x >> pts[i].y >> values[i];
            kinds[i] = PINE;
            tot_sum_pine += values[i];
        }
        rep(i,P,P+L-1) { // read larches
            cin >> pts[i].x >> pts[i].y >> values[i];
            kinds[i] = LARCH;
            tot_sum_larch += values[i];
        }
        int ans = INT_MAX;
        rep(i,0,P+L-1) { // for each reference point i
            // ---------------------------------
            // 1) collect tuples for each other point (j != i)
            //  Each tuple is a triplet { p_j - p_i, norm2(p_j - p_i), j }
            //  i.e. the vector from p_i to p_j, the length squared of this vector
            //       and the index of the point
            tuples.clear();
            rep(j,0,P+L-1) {
                if (i == j) continue;
                Point d = pts[j] - pts[i];
                tuples.emplace_back(d, d.norm2(), j);
            }
            int m = tuples.size();
            // ---------------------------------
            // 2) Sort all tuples lexicographically:
            //  - first points are sorted ccw from quadrant I to quadrant IV
            //  - if two points point in the same direction, we break ties
            //      based on distance from the origin (point closer to the origin goes first)
            sort(tuples.begin(), tuples.end());
            // ---------------------------------
            // 3) Simulate all straight lines which are:
            //    - arbitrarily close to point i and to its right (imagine point i
            //       to the left of the straight line and as close to it as neccesary without touching it)
            //    - the straight line is also to the right of a second point j and almost touching it
            //   (i.e.: the line obtained by shifting  the straight line <- p_i - p_j -> an epsilon
            //    distance to the right)
            int sum_pine_left = 0; // sum of pine values to the left of straight line
            int sum_larch_left = 0; // sum of larch values to the left of straight line
            add_val(sum_pine_left, sum_larch_left, i, 1); // point i is to the left, so add it
            int k = -1;
            int j = 0;
            while (j < m) { // for each second point j
                Point& d = get<0>(tuples[j]); // d = vector p_i -> p_j
                while (1) { // find range of points ccw wich are all to the left of the current straight line
                    if (k+1 - j + 1 > m) break;
                    Point& p = get<0>(tuples[(k+1)%m]);
                    if (d.cross(p) < 0) break;
                    ++k;
                    add_val(sum_pine_left, sum_larch_left, get<2>(tuples[k%m]), 1); // update sums
                }
                // consider 2 possibles costs
                int cost1 = sum_pine_left + tot_sum_larch - sum_larch_left;
                int cost2 = sum_larch_left + tot_sum_pine - sum_pine_left;
                ans = min({ans, cost1, cost2}); // update answer
                do { // move to next second point j
                // ** corner case: we need to skip all points which are collinear and pointing to the same place
                //      (i.e.: vectors with same direction and sense)
                    add_val(sum_pine_left, sum_larch_left, get<2>(tuples[j]), -1);
                    ++j;
                } while (j < m and get<0>(tuples[j]) == d);
            }
            // ---------------------------------
            // 4) Simulate all straight lines which are:
            //    - arbitrarily close to point i and to its LEFT (imagine point i
            //       to the RIGHT of the straight line and as close to it as neccesary without touching it)
            //    - the straight line is also to the RIGHT of a second point j and almost touching it
            //   (*** in this case the line is no longer parallel to line <- p_i - p_j ->, is ALMOST parallel
            //    but infinitesimally rotated clock-wise and shifted left,
            //  so that p_i is to the right and p_j to the left of it)
            sum_pine_left = 0;
            sum_larch_left = 0;
            k = -1;
            j = 0;
            while (j < m) { // for each second point j
                Point& d = get<0>(tuples[j]);  // d = vector p_i -> p_j
                Point neg_d = d.negative();  // neg_d = -d (d rotated 180 degrees around p_i)
                while (1) {// find range of points ccw wich are all to the left of the current straight line
                    if (k+1 - j + 1 > m) break;
                    Point& p = get<0>(tuples[(k+1)%m]);
                    // ** corner cases:
                    //   - p can only be to the left of d or be collinear to d pointing with the same sense
                    //     and located above d (REASON: remember the straight line has a small inclination
                    //     with respect to vector d)
                    if (d.cross(p) < 0 or neg_d == p or (d == p and d.norm2() > p.norm2())) break;
                    ++k;
                    add_val(sum_pine_left, sum_larch_left, get<2>(tuples[k%m]), 1); // update sums
                }
                // consider 2 possibles costs
                int cost1 = sum_pine_left + tot_sum_larch - sum_larch_left;
                int cost2 = sum_larch_left + tot_sum_pine - sum_pine_left;
                ans = min({ans, cost1, cost2}); // update answer
                // only skip 1 point (we don't have to skip all collinear points because
                //  the straight line in this case has a small rotation)
                add_val(sum_pine_left, sum_larch_left, get<2>(tuples[j]), -1);
                ++j;
            }
        }
        cout << ans << '\n'; // print answer
    }
    return 0;
}
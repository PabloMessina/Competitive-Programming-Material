// tags: greedy, implementation
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long int ll;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<double, int> pdi;
typedef pair<ll, int> lli;
// -------------------------------

const int MAXN = (int)1e5 * 4;
int V;
int dirs[4][2] = {{-1,-1}, {-1,1}, {1,-1}, {1,1}};
int accmaxy[MAXN];
int accminy[MAXN];

// add 4 points around (cx, cy) making sure minx <= x <= maxx
void add_pts(vector<ii>& pts, int cx, int cy, int minx, int maxx) {
    rep(i,0,3) {
        int x = cx + dirs[i][0];
        if (minx <= x and x <= maxx) {
            int y = cy + dirs[i][1];
            pts.emplace_back(x, y);
        }
    }
}

int main() {
    while (scanf("%d", &V) == 1) {

        vector<ii> pts; // collect all points
        vector<ii> fence_pts; // collect fence points (clockwise order)

        // for finding the minimal bounding box around points
        int minx, maxx, miny, maxy;
        minx = miny = INT_MAX;
        maxx = maxy = INT_MIN;

        // read input
        rep(i,1,V) {
            int x, y; scanf("%d%d", &x, &y);
            // add 4 points for each point
            add_pts(pts, x, y, INT_MIN, INT_MAX);
            // update bounding box
            minx = min(minx, x);
            maxx = max(maxx, x);
            miny = min(miny, y);
            maxy = max(maxy, y);
        }
        // ensure 1 unit of distance around points
        minx--, miny--, maxx++, maxy++;

        // --------------------------------------------------------------------------------
        // ------ STEP 1: collect points of the upper hull of the fence (left to right) ---

        // map each unique x coordinate to its maximum y coordinate
        map<int,int> x2maxy;
        for (ii& p : pts) {
            auto it = x2maxy.find(p.first);
            if (it == x2maxy.end()) {
                x2maxy[p.first] = p.second;
            } else {
                it->second = max(it->second, p.second);
            }
        }

        // fill 'accmaxy' array
        //      where accmaxy[i] = maximum y coordinate for points
        //           with x coordinate in {x_i, x_(i+1), x_(i+2), ..., x_(n-1)}
        // intuitively: the maximum y from i to the right
        int n = x2maxy.size();
        int i = n-1;
        for (auto it = x2maxy.rbegin(); it != x2maxy.rend(); ++it) {
            accmaxy[i] = (i < n-1) ? max(accmaxy[i+1], it->second) : it->second;
            --i;
        }

        // build upper hull of the fence greedily
        i = 0;
        for (auto& it : x2maxy) {
            int x = it.first, y = it.second;
            if (i == 0) { // first point
                fence_pts.emplace_back(x, y);
            } else {
                ii& prev_p = fence_pts.back();
                if (y > prev_p.second) { // ascending
                    add_pts(pts, x, prev_p.second, minx, maxx); // --> (*)
                    fence_pts.emplace_back(x, prev_p.second);
                    fence_pts.emplace_back(x, y);
                } else if (y == accmaxy[i]) { // descending
                    add_pts(pts, prev_p.first, y, minx, maxx); // --> (*)
                    fence_pts.emplace_back(prev_p.first, y);
                    fence_pts.emplace_back(x, y);
                }
            }
            ++i;
        }
        // (*) we treat corners as new points, to make sure the lower hull of the fence
        //      doesn't touch them

        // --------------------------------------------------------------------------------
        // ------ STEP 2: collect points of the lower hull of the fence (right to left) ---

        // map each unique x coordinate to its minimum y coordinate
        map<int,int> x2miny;
        for (ii& p : pts) {
            auto it = x2miny.find(p.first);
            if (it == x2miny.end()) {
                x2miny[p.first] = p.second;
            } else {
                it->second = min(it->second, p.second);
            }
        }

        // fill 'accminy' array
        //      where accminy[i] = minimum y coordinate for points
        //           with x coordinate in {x_0, x_1, x_2, ..., x_i}
        // intuitively: the minimum y from i to the left
        n = x2miny.size();
        i = 0;
        for (auto& it : x2miny) {
            accminy[i] = (i > 0) ? min(accminy[i-1], it.second) : it.second;
            ++i;
        }

        // build lower hull of the fence greedily
        i = n-1;
        for (auto it = x2miny.rbegin(); it != x2miny.rend(); ++it) {
            int x = it->first, y = it->second;
            if (i == n-1) { // first point
                fence_pts.emplace_back(x,y);
            } else {
                ii& prev_p = fence_pts.back();
                if (y < prev_p.second) { // descending
                    fence_pts.emplace_back(x, prev_p.second);
                    fence_pts.emplace_back(x, y);
                } else if (y == accminy[i]) { // ascending
                    fence_pts.emplace_back(prev_p.first, y);
                    fence_pts.emplace_back(x, y);
                }
            }
            --i;
        }

        // ------------------------------------------------------------
        // ------ STEP 3: compute fence's Area and Perimeter ---------

        // area (Green's Theorem algorithm)
        n = fence_pts.size();
        ll A = 0;
        for (int i = n-1, j = 0; j < n; i=j++) {
            A += (ll)(fence_pts[i].first + fence_pts[j].first) * 
                   (ll)(fence_pts[j].second - fence_pts[i].second);
        }
        A = abs(A) / 2;

        // perimeter
        ll P = (maxx - minx + maxy - miny) * 2;

        // print output
        printf("%lld %lld\n", P, A);
    }
    return 0;
}
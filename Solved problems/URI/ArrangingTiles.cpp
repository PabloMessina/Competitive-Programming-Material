// tags: DP, TSP (travelling salesman problem), bitmask,
// two pointers, straight line equation, geometry
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
// -------------------------------

int N;
const int MAXK = 10000;
const int MAXN = 14;
struct Point { double x, y; };
Point pts[MAXK];

struct Tile {
    vector<Point> left_pts; // left boundary points (bottom-up)
    vector<Point> right_pts; // right boundary points (bottom-up)
    double width; // tile's width
    double min_x=0; // minimum x among all points
    double max_x=0; // maximum x among all points
} tiles[MAXN];

// Find the x-axis coordinate of the point whose y-axis coordinate is 'y'
// and is located in the straight line <-a-b->
double get_x(Point& a, Point& b, double y) {
    return a.x + (y - a.y) * (a.x - b.x) / (a.y - b.y);
}
// Find the x-axis overlap between the shadows of tiles i and j assuming
// that tile j is placed to the right of tile i and the tiles are touching
// each other in a single point/edge.
// This x-axis overlap can be computed by first finding the minimun horizontal
// distance (mind) between  tile i's right boundary and tile j's left boundary,
// which can be done in O(N) using two pointers.
// Then, the overlap can be found translating tile j 'mind' units to the left.
double overlap[MAXN][MAXN];
double get_xaxis_overlap(int i, int j) {
    Tile& ti = tiles[i];
    Tile& tj = tiles[j];
    i = ti.right_pts.size()-1;
    j = tj.left_pts.size()-1;
    double mind = 1e9;
    while(i > 0) {
        Point& pi1 = ti.right_pts[i];
        Point& pi2 = ti.right_pts[i-1];
        Point& pj1 = tj.left_pts[j];
        Point& pj2 = tj.left_pts[j-1];
        double y_up = min(pi1.y, pj1.y);
        double y_down = max(pi2.y, pj2.y);
        double xi_up = get_x(pi1, pi2, y_up);
        double xj_up = get_x(pj1, pj2, y_up);
        double xi_down = get_x(pi1, pi2, y_down);
        double xj_down = get_x(pj1, pj2, y_down);
        mind = min(mind, xj_up - xi_up);
        mind = min(mind, xj_down - xi_down);
        if (y_down == pi2.y) i--;
        if (y_down == pj2.y) j--;
    }
    return ti.max_x - tj.min_x + mind;
}

// Travelling Salesman Problem (adapted to the problem 'Arranging Tiles')
// dp(bitmask, i): find the maximum total overlap of visiting all nodes(tiles)
//   indicated by 'bitmask' in sequence, starting from node 'i'.
// 
//   * bitmask: an int whose bits indicate the nodes(tiles) to be visited next
//      ** if j-th bit in bitmask is 1, the j-th node should be visited
//         else, the j-th node should be ignored
//
//   * i: node(tile) we are starting the travel from (i is already visited,
//        so the i-th bit in bitmask should be 0)
double memo[1 << MAXN][MAXN]; // 2^MAXN x MAXN
double dp(int bitmask, int i) {
    // base case 1: nothing to visit
    if (bitmask == 0) return 0; 
    // base case 2: problem already solved
    double& ans = memo[bitmask][i];
    if (ans >= -0.5) return ans;
    // general case: try all possible next nodes
    double tmp = 0;
    for (int j=0, b=1; b <= bitmask; ++j, b <<= 1) {
        if (bitmask & b) {
            assert (i != j);
            tmp = max(tmp, overlap[i][j] + dp(bitmask & ~b, j));
        }
    }
    // return maximum overlap
    return ans = tmp;
}

int main() {
    while (scanf("%d", &N) == 1) { // for each test case
        // STEP 1: read input and define Tile instances from it
        double total_width = 0;
        rep(i,0,N-1) { // for each tile (convex polygon)
            // reset tile
            Tile& tile = tiles[i];
            tile.right_pts.clear();
            tile.left_pts.clear();
            tile.min_x = 0;
            tile.max_x = 0;
            // read points into the temporal 'pts' array
            int k; scanf("%d", &k);
            int offset = -1;
            rep(j,0,k-1) {
                double x, y; scanf("%lf%lf", &x, &y);
                pts[j] = {x,y};
                // the if below detects the position at which the 'left' boundary
                // of the polygon starts in counter clockwise order
                if (j > 2 and pts[j].y == pts[j-1].y) {
                    offset = j;
                }
                // update tile's min_x and max_x
                tile.min_x = min(tile.min_x, x);
                tile.max_x = max(tile.max_x, x);
            }
            // collect points in the tile's right boundary 
            tile.width = tile.max_x - tile.min_x;            
            total_width += tile.width;
            rep(j,1,offset-1) tile.right_pts.push_back(pts[j]);
            // collect points in the tile's left boundary
            tile.left_pts.push_back(pts[0]);
            invrep(j,k-1,offset) tile.left_pts.push_back(pts[j]);
        }
        // STEP 2: create overlap matrix in O(N^2)
        rep(i,0,N-1) rep(j,0,N-1) if (i != j) overlap[i][j] = get_xaxis_overlap(i, j);
        // STEP 3: find maximum total overlap using DP
        int M = (1 << N); // M = 2^N
        rep(i,0,M-1) rep(j,0,N-1) memo[i][j] = -1.0; // reset memo
        double maxoverlap = 0;
        rep(i,0,N-1) maxoverlap = max(maxoverlap, dp((M-1) & ~(1 << i), i));
        // STEP 4: print answer
        printf("%.3lf\n", total_width - maxoverlap);
    }
    return 0;
}
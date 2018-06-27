// tags: DP, TSP, bitmask, two pointers, straight line equation, geometry
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
// -------------------------------

int N;
const int MAXK = 10000;
const int MAXN = 14;
struct Point { double x, y; };
Point pts[MAXK];

struct Tile {
    vector<Point> left_pts;
    vector<Point> right_pts;
    double width;
    double min_x=0;
    double max_x=0;
};
Tile tiles[MAXN];

double overlap[MAXN][MAXN];
double get_x(Point& a, Point& b, double y) {
    return a.x + (y - a.y) * (a.x - b.x) / (a.y - b.y);
}
double get_overlap(int i, int j) {
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
    return ti.max_x  - tj.min_x + mind;
}

double memo[1 << MAXN][MAXN];
double dp(int mask, int curr_i) {
    if (mask == 0) return tiles[curr_i].width;
    if (memo[mask][curr_i] >= -0.5)
        return memo[mask][curr_i];
    double extra = (double)INT_MAX;
    for (int i=0, b=1; i < N; b<<=1, ++i) {
        if (mask & b) {
            extra = min(extra, dp(mask & ~b, i) - overlap[curr_i][i]);
        }
    }
    return memo[mask][curr_i] = tiles[curr_i].width + extra;
}

int main() {
    scanf("%d", &N);    
    rep(i,0,N-1) {
        Tile& tile = tiles[i];
        int k; scanf("%d", &k);
        int offset = -1;
        rep(j,0,k-1) {
            double x, y; scanf("%lf%lf", &x, &y);
            pts[j] = {x,y};
            if (j > 2 and pts[j].y == pts[j-1].y) {
                offset = j;
            }
            tile.min_x = min(tile.min_x, x);
            tile.max_x = max(tile.max_x, x);
        }
        tile.width = tile.max_x - tile.min_x;
        rep(j,1,offset-1) tile.right_pts.push_back(pts[j]);
        tile.left_pts.push_back(pts[0]);
        invrep(j,k-1,offset) tile.left_pts.push_back(pts[j]);
    }
    rep(i,0,N-1) rep(j,0,N-1) if (i != j) overlap[i][j] = get_overlap(i, j);
    int M = (1 << N);
    rep(i,0,M-1) rep(j,0,N-1) memo[i][j] = -1.0;
    double ans = 1e9;
    rep(i,0,N-1) ans = min(ans, dp((M-1) & ~(1 << i), i));
    printf("%.3lf\n", ans);
    return 0;
}
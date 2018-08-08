// tags: geometry 2D, cross product, point in convex polygon detection
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

const int MAXN = 1000;
int N,Q;
struct Point { ll x, y; };
Point pts[MAXN];

int orientation(Point& a, Point& b, Point& c) {
    ll dx0 = b.x - a.x, dy0 = b.y - a.y;
    ll dx1 = c.x - a.x, dy1 = c.y - a.y;
    ll cross = dx0 * dy1 - dx1 * dy0;
    return cross < 0 ? -1 : cross == 0 ? 0 : 1; // sign
}

bool inside(Point& p) {
    int o_min = 0, o_max = 0;
    for (int i=0, j=N-1; i < N; j=i++) {
        int o = orientation(pts[j], pts[i], p);
        if (o == 1) o_max = 1;
        else if (o == -1) o_min = -1;
        if (o_max - o_min == 2) return false;
    }
    return true;
}

int main() {
    scanf("%d%d", &N, &Q);
    rep(i,0,N-1) { ll x,y; scanf("%lld%lld",&x,&y); pts[i] = {x,y}; }
    while(Q--) {
        Point p; scanf("%lld%lld", &p.x, &p.y);
        if (inside(p)) puts("D");
        else puts("F");
    }
    return 0;
}
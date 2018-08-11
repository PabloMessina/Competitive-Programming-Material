// tags: geometry, cross product, segment intersection detection
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

const int MAXN = 50;
int n;
struct Point { double x,y; };
struct Segment { Point a, b; };
Segment segments[MAXN];

int orientation(Point& a, Point& b, Point& c) {
    double dx0 = b.x - a.x, dy0 = b.y - a.y;
    double dx1 = c.x - a.x, dy1 = c.y - a.y;
    double cross = dx0 * dy1 - dx1 * dy0;
    return cross > 0 ? 1 : cross == 0 ? 0 : -1;
}

bool do_segments_intersect(Segment& s1, Segment& s2) {
    int o11 = orientation(s1.a, s1.b, s2.a);
    int o12 = orientation(s1.a, s1.b, s2.b);
    int o21 = orientation(s2.a, s2.b, s1.a);
    int o22 = orientation(s2.a, s2.b, s1.b);
    return o11 != o12 and o21 != o22;
}

int main() {
    while(scanf("%d", &n) && n) {
        rep(i,0,n-1) {
            double x1,y1,x2,y2;
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            segments[i] = {{x1,y1},{x2,y2}};
        }
        int count = 0;
        rep(i,0,n-3) {
            Segment& si = segments[i];
            rep(j,i+1,n-2) {
                Segment& sj = segments[j];
                if (do_segments_intersect(si, sj)) {
                    rep(k,j+1,n-1) {
                        Segment& sk = segments[k];
                        if (do_segments_intersect(sj, sk) and
                            do_segments_intersect(si, sk)) {
                            count++;
                        }
                    }
                }
            }
        }
        printf("%d\n", count);
    }
    return 0;
}
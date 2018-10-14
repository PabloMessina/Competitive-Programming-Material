// TODO: finish this
#include <bits/stdc++.h> // import everything in one shot
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

int B, N, M;
ll inline square(ll x) { return x * x; }
struct Point { 
    ll x, y;
    ll dist2(Point& p) { return square(x - p.x) + square(y - p.y); }
    ll cross(const Point& p) { return x*p.y - y*p.x; }
    bool operator==(const Point& o) const {
        return x == o.x and y == o.y;
    }
};
Point border_pts[1000];
struct Informer {
    Point p; int i; double coef;
    bool contactable;
    bool operator<(const Informer& o) {
        if (coef == o.coef) return i > o.i;
        return coef < o.coef;
    }
} informers[1000];
struct Radar {
    Point p; ll r;
    bool operator<(const Rader& o) {
        if (p.x == o.p.x) return p.y < o.p.y;
        return p.x < o.px;
    }
} radars[30], radars_tmp[30];
bool to_remove[30];

vector<vector<int>> g(30);
vector<int> cycle;

bool visited[30];
bool found[30];

bool cycle_search(int u, int p) {
    assert (!visited[u]);
    assert (found[u]);
    visited[u] = true;
    if (p == -1) {
    } else {
    }
}

int main() {
    while (cin >> B) {
        if (B == 0) break;
        rep(i,0,B-1) {
            Point& p = border_pts[i];
            cin >> p.x >> p.y;
        }
        cin >> N;
        rep(i,0,N-1) {
            auto& inf = informers[i];
            inf.contactable = false;
            cin >> inf.p.x >> inf.p.y;
            inf.i = i;
        }
        cin >> M;
        rep(i,0,M-1) {
            auto& rad = radars[i];
            cin >> rad.p.x >> rad.p.y >> rad.r;
            rep(j,0,N-1) {
                auto& inf = informers[j];
                if (inf.p.dist2(rad.p) <= square(rad.r)) {
                    inf.contactable = false;
                }
            }
        }
        
        // remove redundant circles
        memset(to_remove, 0, sizeof to_remove);
        rep(i,0,M-1) {
            if (to_remove[i]) continue;
            auto& ri = radars[i];
            rep(j,0,M-1) {
                if (to_remove[j]) continue;
                auto& rj = radars[j];
                if (ri.p == rj.p and ri.r >= rj.r) {
                    to_remove[j] = true;
                }
            }
        }        
        int jj = 0;
        rep(i,0,M-1) {
            if (to_remove[i]) continue;
            radars_tmp[jj++] = radars[i];
        }
        M = jj;
        swap(radars, radars_tmp);

        sort(radars, radars + M);   
        vector<vector<int>> g(M);
        rep(i,0,M-2) {
            auto& ri = radars[i];
            rep(j,i+1,M-1) {
                auto& rj = radars[j];
                if (ri.p.dist2(rj.p) <= square(ri.r + rj.r)) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }
        }

        memset(visited, 0, sizeof visited);
        memset(found, 0, sizeof found);

    }
    return 0;
}
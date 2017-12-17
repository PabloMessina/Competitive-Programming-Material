// tags: Dijkstra modified, Fenwick Tree 2D, Divide & Conquer
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
// -------------------------------

const int MAXR = 500;
int R,C,N;
int rspans[MAXR+1][MAXR+1];
int cspans[MAXR+1][MAXR+1];
int costs[MAXR+1][MAXR+1];

namespace Solver {

    struct Cell {
        int r, c, cost;
        Cell (int r, int c, int cost) : r(r), c(c), cost(cost) {}
        bool operator<(const Cell& rhs) const {
            return cost > rhs.cost;
        }
    };

    int ft[MAXR+1][MAXR+1];
    priority_queue<Cell> q;
    int curr_cost;

    int add1(int r, int c) {
        for (int i = r; i <= R; i += (i & -i)) {
            for (int j = c; j <= C; j+= (j & -j)) {
                ft[i][j]++;
            }
        }
    }
    int count(int r, int c) {
        int sum = 0;
        for (int i = r; i; i -= (i & -i)) {
            for (int j = c; j; j -= (j & -j)) {
                sum += ft[i][j];
            }
        }
        return sum;
    }
    int count(int r1, int c1, int r2, int c2) {
        return count(r2, c2) - count(r2, c1-1) - count(r1-1, c2) + count(r1-1, c1-1);
    }
    void reset() {
        memset(ft, 0, sizeof ft);
        while (!q.empty()) q.pop();
    }
    void expand(int r1, int c1, int r2, int c2) {        
        int vis = count(r1,c1,r2,c2);
        int dr = r2 - r1;
        int dc = c2 - c1;
        int tot = (dr+1) * (dc+1);
        if (vis == tot) return;
        if (dr == 0 and dc == 0) {
            q.emplace(r1,c1,curr_cost+costs[r1][c1]);
            add1(r1,c1);
        } else if (dr > dc) {
            int rm = (r1 + r2) >> 1;
            expand(r1, c1, rm, c2);
            expand(rm+1, c1, r2, c2);
        } else {
            int cm = (c1 + c2) >> 1;
            expand(r1, c1, r2, cm);
            expand(r1, cm+1, r2, c2);
        }
    }
    int dijkstra(int sr, int sc, int er, int ec) {
        if (sr == er and sc == ec) return 0;
        q.emplace(sr, sc, costs[sr][sc]);
        add1(sr, sc);
        while (!q.empty()) {
            Cell u = q.top(); q.pop();
            int rspan = rspans[u.r][u.c];
            int cspan = cspans[u.r][u.c];
            if (abs(er - u.r) <= rspan and abs(ec - u.c) <= cspan) {
                return u.cost;
            }
            int rmin = max(u.r - rspan, 1);
            int cmin = max(u.c - cspan, 1);
            int rmax = min(u.r + rspan, R);
            int cmax = min(u.c + cspan, C);
            curr_cost = u.cost;
            expand(rmin, cmin, rmax, cmax);
        }
        return -1;
    }
}

int main() {
    scanf("%d%d%d",&R,&C,&N);
    rep(r,1,R) rep(c,1,C) scanf("%d", &costs[r][c]);
    rep(r,1,R) rep(c,1,C) scanf("%d", &rspans[r][c]);
    rep(r,1,R) rep(c,1,C) scanf("%d", &cspans[r][c]);
    int sr, sc, er, ec;
    scanf("%d%d", &sr, &sc);
    rep(i,2,N) {
        scanf("%d%d", &er, &ec);
        if (i >= 3) putchar(' ');
        Solver::reset();
        printf("%d", Solver::dijkstra(sr, sc, er, ec));
        sr = er; sc = ec;
    }
    puts("");
    return 0;
}
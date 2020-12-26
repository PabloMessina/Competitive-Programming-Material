// tags: DP, bitmasks
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)

int N; // number of objects
int xs[25], ys[25]; // coordinates
int dist2[25][25]; // distance squared

int inline calc_dist2(int x1, int y1, int x2, int y2) {
    int dx = x1-x2, dy = y1-y2;
    return dx*dx + dy*dy;
}

// dp(mask):
//    the minimum time of picking up the objects indicated by the bits of 'mask'
//    (we have to pick up the i-th object iff the i-th bit in mask is 1)
//    assuming that we are at 0 (the handbag) and at the end of the process
//    we comeback to 0 (the handbag) (** the handbag IS NOT an object)
pair<int,int> choice[1 << 24]; // to remember objects picked up in the optimal solution
int memo[1 << 24]; // to remember minimal cost of optimal solution
int dp(int mask) {
    // base case 1: no objects to pick up -> we are done
    if (mask == 0) return 0;
    // base case 2: problem already solved -> we are done
    int& ans = memo[mask];
    if (ans != -1) return ans;
    // general case:
    //   we have 2 options with the first object to pick up
    //   1) go pick up the first object and then come back
    //   2) go pick up the first object, then go pick up a 2nd object,
    //      and finally come back (swaping the order has the same cost)
    // --------
    // we find the index of the first object to pick up
    int b, i, j;
    for (b=1, i=1; i <= N; b <<= 1, ++i) if (mask & b) break;
    // option 1) pick up just the first object
    ans = 2 * dist2[0][i] + dp(mask & ~b);
    choice[mask] = {i,i}; // remember the choice made
    // option 2) try out picking up a second object (try all possibilities)
    int mask2 = mask & ~b;
    for (j = i+1, b <<= 1; j <= N; b <<= 1, ++j) {
        if (mask2 & b) {
            int tmp = dist2[0][i] + dist2[i][j] + dist2[j][0] + dp(mask2 & ~b);
            if (tmp < ans) {
                ans = tmp;
                choice[mask] = {i,j}; // remember the choice made
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    // read input
    cin >> xs[0] >> ys[0];    
    cin >> N; 
    rep(i,1,N+1) cin >> xs[i] >> ys[i];
    // compute square distances
    rep(i,0,N+1) rep(j,0,N+1) {
        dist2[i][j] = calc_dist2(xs[i], ys[i], xs[j], ys[j]);
    }
    // find optimal solution
    int mask = (1 << N) - 1;
    memset(memo, -1, sizeof(int) * (mask + 2));
    cout << dp(mask) << '\n';
    // recover the optimal path
    cout << '0';
    while (mask) {
        auto p = choice[mask];
        mask &= ~(1 << (p.first-1));
        cout << ' ' << p.first;
        if (p.first != p.second) {
            mask &= ~(1 << (p.second-1));
            cout << ' ' << p.second;
        }
        cout << " 0";
    }
    cout << '\n';
    return 0;
}
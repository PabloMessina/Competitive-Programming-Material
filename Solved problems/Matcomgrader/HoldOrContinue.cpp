// tags: dp, math, probabilities
// reference: https://codeforces.com/blog/entry/84486
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
// -------------------------------
double lo[76][76][76];
double hi[76][76][76];

double prob(int x, int y, int z) { return (lo[x][y][z] + hi[x][y][z]) / 2.0; }

bool hold(int x, int y, int z) {
    // hold
    double op1 = 1.0 - prob(y,x+z,0);
    // continue
    double op2 = 1.0 - prob(y,x,0);
    rep(i,2,7) op2 += (z+i <= 75) ? prob(x,y,z+i) : (1.0 - prob(y,x,0));
    op2 /= 6.0;
    return op1 > op2;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    rep(i,0,76) rep(j,0,76) rep(k,0,76) lo[i][j][k] = 0.;
    rep(i,0,76) rep(j,0,76) rep(k,0,76) hi[i][j][k] = 1.;

    rep(_,0,200) {
        invrep(k,150,0) {
            rep(x,max(k-75,0),min(75,k)+1) {
                int y = k - x;
                invrep(z,75,0) {
                    if (y == 75) lo[x][y][z] = 0.;
                    else if (x + z > 75) lo[x][y][z] = 1.0 - hi[y][x][0];
                    else {
                        // hold
                        double op1 = 1.0 - hi[y][x+z][0];
                        // continue
                        double op2 = 1.0 - hi[y][x][0];
                        rep(i,2,7) op2 += (z+i <= 75) ? lo[x][y][z+i] : (1.0 - hi[y][x][0]);
                        op2 /= 6.0;
                        lo[x][y][z] = max(op1, op2);
                    }
                }
            }
        }
        invrep(k,150,0) {
            rep(x,max(k-75,0),min(75,k)+1) {
                int y = k - x;
                invrep(z,75,0) {
                    if (y == 75) hi[x][y][z] = 0.;
                    else if (x + z > 75) hi[x][y][z] = 1.0 - lo[y][x][0];
                    else {
                        // hold
                        double op1 = 1.0 - lo[y][x+z][0];
                        // continue
                        double op2 = 1.0 - lo[y][x][0];
                        rep(i,2,7) op2 += (z+i <= 75) ? hi[x][y][z+i] : (1.0 - lo[y][x][0]);
                        op2 /= 6.0;
                        hi[x][y][z] = max(op1, op2);
                    }
                }
            }
        }
    }

    int Q; cin >> Q;
    while (Q--) {
        int x, y, z; cin >> x >> y >> z;
        if (hold(x,y,z)) cout << "H\n";
        else cout << "C\n";
    }
    return 0;
}
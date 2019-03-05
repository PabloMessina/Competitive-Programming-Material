// tags: backtracking, pruning, implementation
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
// -------------------------------

vector<int> sols;
int fr, fc;
int _pow8[8];
int counts[8][8] = {0};
int dirs[8][2] = {
    {1, 0},
    {1, 1},
    {1, -1},
    {-1, 0},
    {-1, 1},
    {-1, -1},
    {0, 1},
    {0, -1},
};

void add_queen(int r, int c, int d) {
    rep(i,0,7) {
        rep(x,1,7) {
            int rr = r + dirs[i][0] * x;
            int cc = c + dirs[i][1] * x;
            if (rr < 0 or rr > 7 or cc < 0 or cc > 7) break;
            counts[rr][cc] += d;
        }
    }
}

void solve(int c, int sol) {
    if (c == 8) {
        sols.push_back(sol);
    } else if (c == fc) {
        solve(c+1, sol + fr * _pow8[7-c]);
    } else {
        rep(r,0,7) {
            if (counts[r][c] == 0) {
                add_queen(r, c, 1);
                solve(c+1, sol + r * _pow8[7-c]);
                add_queen(r, c, -1);
            }
        }
    }
}

void print_sol(int i, int sol) {
    if (i > 9) cout << i << "     ";
    else cout << " " << i << "     ";
    invrep(j,7,0) {
        cout << " " << sol/_pow8[j] + 1;
        sol %= _pow8[j];
    }
    cout << '\n';
}

int main() {
    int T; cin >> T;
    _pow8[0] = 1;
    rep(i,1,7) _pow8[i] = _pow8[i-1] * 8;
    while (T--) {
        cin >> fr >> fc;
        fr--, fc--;
        cout << "SOLN       COLUMN\n";
        cout << " #      1 2 3 4 5 6 7 8\n\n";
        add_queen(fr, fc, 1);
        sols.clear();
        solve(0, 0);
        add_queen(fr, fc, -1);
        sort(sols.begin(), sols.end());
        rep(i,0,sols.size()-1) print_sol(i+1, sols[i]);
        if (T) cout << '\n';
    }
    return 0;
}
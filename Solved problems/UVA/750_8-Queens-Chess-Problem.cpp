// tags: backtracking, implementation
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
// -------------------------------
int fr, fc; // fr = fixed row, fc = fixed column
int attacks[8][8] = {0};
int movr[8] = {1,1,1,-1,-1,-1,0,0};
int movc[8] = {0,1,-1,0,1,-1,1,-1};
int queens[8];
int sol_index; // to keep track the index of the current solution
// update attacks[8][8] matrix to reflect
// the fact we are placing/removing a queen
// at/from cell (r,c).
// ** d = 1  means placing a queen
//    d = -1 means removing a queen
void place_queen(int r, int c, int d) {
    rep(i,0,8) { // for each direction (2 vertical, 2 horizotal and 4 diagonal)
        rep(x,1,8) { // for each x number of steps in the i-th direction
            int rr = r + movr[i] * x;
            int cc = c + movc[i] * x;
            if (rr < 0 or rr > 7 or cc < 0 or cc > 7) // make sure we're within the board
                break;
            attacks[rr][cc] += d; // increase/decrease the attack count of cell (rr,cc)
        }
    }
}
void print_sol() { // just print the solution currently stored in array queens[8]
    if (sol_index > 9) cout << sol_index << "     ";
    else cout << " " << sol_index << "     ";
    rep(c,0,8) cout << " " << queens[c] + 1;
    cout << '\n';
}
// c = column
void solve(int c) {
    if (c == 8) { // out of range -> we found a solution
        print_sol();
        sol_index++;
    } else if (c == fc) { // fixed column -> skip it
        solve(c+1);
    } else {
        rep(r,0,8) { // general case -> try all valid rows in lexicographic order
            if (attacks[r][c] == 0) { // no queen is attacking cell (r,c)
                // place a queen here and explore recursively
                place_queen(r, c, 1);
                queens[c] = r;
                solve(c+1);
                // backtrack
                place_queen(r, c, -1);
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int T; cin >> T; // read tests cases
    while (T--) { // for each test case
        cin >> fr >> fc; // read fixed row and fixed column
        fr--, fc--; // use 0-7 range
        queens[fc] = fr;
        place_queen(fr, fc, 1);
        cout << "SOLN       COLUMN\n";
        cout << " #      1 2 3 4 5 6 7 8\n\n";
        sol_index = 1;
        solve(0); // find all solutions with backtracking
        place_queen(fr, fc, -1);
        if (T) cout << '\n';
    }
    return 0;
}
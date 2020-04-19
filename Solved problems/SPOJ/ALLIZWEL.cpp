// tags: backtracking, implementation
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
string board[100];
bool visited[100][100]; // keep track of visited cells
int R, C; // number of rows and columns
string target = "ALLIZZWELL";
// 8 neighbour positions relative to a reference cell
int movr[8] = {1,1,1,-1,-1,-1,0,0};
int movc[8] = {0,1,-1,0,1,-1,1,-1};
// Assuming that we have traveled a partial path of length 'i' that matches the first
// 'i' characters in "ALLIZZWELL", verify if there exists a way to complete the path
// such that the next step in the path is cell (r,c)
bool solve(int i, int r, int c) {
    // already visited -> not possible
    if (visited[r][c])
        return false;
    // does not match i-th char in "ALLIZZWELL" -> not possible
    if (target[i] != board[r][c])
        return false;
    // they match and there are no more characters to match -> we are done
    if (i+1 == target.size())
        return true;
    // they match but there is still work to be done -> keep searching
    visited[r][c] = true; // remeber (r,c) is now visited
    rep(j,0,8) { // try moving to each neighbor
        int rr = r + movr[j];
        int cc = c + movc[j];
        if (0 <= rr and rr < R and 0 <= cc and cc < C
            and solve(i+1, rr, cc)) return true; // if it works -> we are done
    }
    // nothing worked -> backtrack (= undo changes)
    visited[r][c] = false;
    return false;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> R >> C;
        rep(r,0,R) cin >> board[r];
        bool path_exists = false;
        memset(visited, 0, sizeof visited);
        rep(r,0,R) rep(c,0,C) {
            if (solve(0,r,c)) {
                path_exists = true; break;
            }
        }
        if (path_exists) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
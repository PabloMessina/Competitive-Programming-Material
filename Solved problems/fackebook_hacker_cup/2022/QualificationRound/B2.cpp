#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
string board[3000];
int R, C;
int movr[4] = {0, 1, 0, -1};
int movc[4] = {1, 0, -1, 0};

bool is_invalid(int r, int c) {
    int count = 0;
    rep(i,0,4) {
        int rr = r + movr[i];
        int cc = c + movc[i];
        if (0 <= rr and rr < R and 0 <= cc and cc < C and (board[rr][cc] == '.' or board[rr][cc] == '^')) {
            count++;
        }
    }
    return count < 2;
}

void expand_from(int r, int c) {
    board[r][c] = '*';
    queue<pair<int,int>> q;
    q.emplace(r,c);
    while (q.size()) {
        tie(r, c) = q.front(); q.pop();
        rep(i,0,4) {
            int rr = r + movr[i];
            int cc = c + movc[i];
            if (0 <= rr and rr < R and 0 <= cc and cc < C and board[rr][cc] == '.' and is_invalid(rr, cc)) {
                board[rr][cc] = '*';
                q.emplace(rr, cc);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    rep(_t, 1, T+1) {
        cin >> R >> C;
        rep(i,0,R) cin >> board[i];
        rep(r,0,R) rep(c,0,C) {
            if (board[r][c] == '.' and is_invalid(r, c)) expand_from(r, c);
        }
        rep(r,0,R) rep(c,0,C) if (board[r][c] == '.') board[r][c] = '^';
        bool possible = true;
        rep(r,0,R) rep(c,0,C) if (board[r][c] == '^' and is_invalid(r, c)) {
            possible = false; break;
        }
        cout << "Case #" << _t << ": ";
        if (possible) {
            cout << "Possible\n";
            rep(r,0,R) rep(c,0,C) if (board[r][c] == '*') board[r][c] = '.';
            rep(r,0,R) cout << board[r] << '\n';
        } else {
            cout << "Impossible\n";
        }
    }
    return 0;
}
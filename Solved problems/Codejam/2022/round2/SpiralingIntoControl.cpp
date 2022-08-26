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
const int MAXN = 9999;
int board[MAXN][MAXN];
int dist[MAXN][MAXN];
int N, K;
int movr[4] = {0,1,-1,0};
int movc[4] = {1,0,0,-1};

vector<ii> get_jumps(int r, int c) {
    int tr = N/2, tc = N/2;
    vector<ii> ans;
    while (r != tr or c != tc) {
        rep(i,0,4) {
            int rr = r + movr[i];
            int cc = c + movc[i];
            if (0 <= rr and rr < N and 0 <= cc and cc < N and board[rr][cc] > board[r][c] and
                dist[rr][cc] == dist[r][c] - 1) {
                if (board[rr][cc] > board[r][c] + 1) {
                   ans.emplace_back(board[r][c], board[rr][cc]);
                }
                r = rr;
                c = cc;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    rep(_case,1,T+1) {
        cin >> N >> K;
        // fill board
        int i = 1;
        for (int side = N; side >= 1; side -= 2) {
            int delta = (N - side) / 2;
            int r, c;
            r = delta;
            for (c = delta; c < N - delta; c++) board[r][c] = i++;
            c = N - delta - 1;
            for (r = delta + 1; r < N - delta; r++) board[r][c] = i++;
            r = N - delta - 1;
            for (c = N - delta - 2; c >= delta; c--) board[r][c] = i++;
            c = delta;
            for (r = N - delta - 2; r > delta; r--) board[r][c] = i++;
        }
        // run BFS from center
        rep(r,0,N) rep(c,0,N) dist[r][c] = -1;
        int sr = N/2, sc = N/2;
        queue<ii> q;
        q.emplace(sr, sc);
        dist[sr][sc] = 0;
        while (q.size()) {
            ii p = q.front(); q.pop();            
            rep(i,0,4) {
                int rr = p.ff + movr[i];
                int cc = p.ss + movc[i];
                if (0 <= rr and rr < N and 0 <= cc and cc < N and board[rr][cc] < board[p.ff][p.ss] and
                    dist[rr][cc] == -1) {
                    dist[rr][cc] = dist[p.ff][p.ss] + 1;
                    q.emplace(rr, cc);
                }
            }
        }
        // debug board
        // rep(r,0,N) {
        //     rep(c,0,N) {
        //         cout << board[r][c] << ' ';
        //     }
        //     cout << '\n';
        // }
        // cout << "\n";
        // rep(r,0,N) {
        //     rep(c,0,N) {
        //         cout << dist[r][c] << ' ';
        //     }
        //     cout << '\n';
        // }
        // check answer
        vector<ii> jumps;
        bool possible = false;
        i = 0;
        for (int side = N; side >= 1; side -= 2) {
            int delta = (N - side) / 2;
            int r, c;
            r = delta;
            for (c = delta; c < N - delta; c++) {
                if (i + dist[r][c] == K) {
                    possible = true;
                    jumps = get_jumps(r, c);
                    goto answer;
                }
                i++;
            }
            c = N - delta - 1;
            for (r = delta + 1; r < N - delta; r++) {
                if (i + dist[r][c] == K) {
                    possible = true;
                    jumps = get_jumps(r, c);
                    goto answer;
                }
                i++;
            }
            r = N - delta - 1;
            for (c = N - delta - 2; c >= delta; c--) {
                if (i + dist[r][c] == K) {
                    possible = true;
                    jumps = get_jumps(r, c);
                    goto answer;
                }
                i++;
            }
            c = delta;
            for (r = N - delta - 2; r > delta; r--) {
                if (i + dist[r][c] == K) {
                    possible = true;
                    jumps = get_jumps(r, c);
                    goto answer;
                }
                i++;
            }
        }
        answer:;
        // print answer
        if (possible) {
            cout << "Case #" << _case << ": " << jumps.size() << "\n";
            for (ii& p : jumps) {
                cout << p.ff << " " << p.ss << '\n';
            }
        } else {
            cout << "Case #" << _case << ": IMPOSSIBLE\n";
        }
    }
    return 0;
}
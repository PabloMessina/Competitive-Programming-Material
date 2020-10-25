#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define ff first
#define ss second
typedef pair<int,int> ii;
// -------------------------------
int N, M, B;
struct Barrier {
    int r, c, k;
    int n = 0; // tot neighbors
    int ec = 0; // empty count
    int lc = 0; // lamp count
    Barrier(int r, int c, int k) : r(r), c(c), k(k) {}
};
vector<Barrier> barriers;
enum { EMPTY, BARRIER };
struct Cell {
    vector<int> nb; // neighbor barriers
    int type = EMPTY;
    int light = 0;
    int can_light = 0;
    bool instack = false;
};
vector<vector<Cell>> board;
vector<ii> cells;
int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};
int best_ans;

bool check_barriers_lamp(Cell& cell) {
    for (int i : cell.nb) if (barriers[i].lc + 1 > barriers[i].k) return false;
    return true;
}
bool check_barriers_empty(Cell& cell) {
    for (int i : cell.nb) if (barriers[i].ec + 1 > barriers[i].n - barriers[i].k) return false;
    return true;
}
bool valid_move(Cell& cell, int r, int c, bool lamp) {
    if (lamp) {
        if (cell.light) return false;
        if (not check_barriers_lamp(cell)) return false;
        rep(i,0,4) {
            rep(x,1,100) {
                int rr = r + dr[i] * x, cc = c + dc[i] * x;
                if (0 > rr or rr >= N or 0 > cc or cc >= M) break;
                if (board[rr][cc].type != EMPTY) break;
                if (board[rr][cc].instack) continue;
                if (not check_barriers_empty(board[rr][cc])) return false;
            }
        }
        return true;
    } else {
        if (not check_barriers_empty(cell)) return false;
        bool valid = false;
        rep(i,0,4) {
            rep(x,1,100) {
                int rr = r + dr[i] * x, cc = c + dc[i] * x;
                if (0 > rr or rr >= N or 0 > cc or cc >= M) break;
                if (board[rr][cc].type != EMPTY) break;
                if (board[rr][cc].can_light - 1 == 0) return false;
                if (board[rr][cc].instack) continue;
                if (not valid and check_barriers_lamp(board[rr][cc])) valid = true;
            }
        }
        return valid or cell.light;
    }
}
void toggle_move(Cell& cell, int r, int c, bool lamp, int d) {
    if (lamp) {
        for (int i : cell.nb) barriers[i].lc += d;
        cell.light += d;
        rep(i,0,4) {
            rep(x,1,100) {
                int rr = r + dr[i] * x, cc = c + dc[i] * x;
                if (0 > rr or rr >= N or 0 > cc or cc >= M) break;
                if (board[rr][cc].type != EMPTY) break;
                board[rr][cc].light += d;
            }
        }
    } else {
        for (int i : cell.nb) barriers[i].ec += d;
        cell.can_light -= d;
        rep(i,0,4) {
            rep(x,1,100) {
                int rr = r + dr[i] * x, cc = c + dc[i] * x;
                if (0 > rr or rr >= N or 0 > cc or cc >= M) break;
                if (board[rr][cc].type != EMPTY) break;
                board[rr][cc].can_light -= d;
            }
        }
    }
}

void search(int idx, int ans) {
    if (ans >= best_ans) return;
    if (idx == cells.size()) { best_ans = ans; return; }
    int r, c; tie(r,c) = cells[idx];
    Cell& cell = board[r][c];
    cell.instack = true;
    // option 1: put a lamp
    if (valid_move(cell, r, c, true)) {
        toggle_move(cell, r, c, true, 1);
        search(idx+1, ans+1);
        toggle_move(cell, r, c, true, -1);
    }
    // option 2: empty
    if (valid_move(cell, r, c, false)) {
        toggle_move(cell, r, c, false, 1);
        search(idx+1, ans);
        toggle_move(cell, r, c, false, -1);
    }
    cell.instack = false;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    nextcase:
    while (cin >> N >> M and N) {
        cin >> B;
        barriers.clear(); cells.clear();
        board.assign(N, vector<Cell>(M));
        rep(i,0,B) {
            int r,c,k; cin >> r >> c >> k; --r, --c;
            board[r][c].type = BARRIER;            
            if (k != -1) {
                int count = 0;
                barriers.emplace_back(r, c, k);                
            }
        }
        rep(i,0,barriers.size()) {
            auto& b = barriers[i];
            rep(j,0,4) {
                int rr = b.r + dr[j], cc = b.c + dc[j];
                if (0 <= rr and rr < N and 0 <= cc and cc < M and board[rr][cc].type == EMPTY) {
                    b.n++; board[rr][cc].nb.push_back(i);
                }
            }
            if (b.n < b.k) { cout << "No solution\n"; goto nextcase; }
        }
        rep(r,0,N) rep(c,0,M) if (board[r][c].type == EMPTY) {
            board[r][c].can_light++;
            rep(i,0,4) {
                rep(x,1,100) {
                    int rr = r + dr[i] * x, cc = c + dc[i] * x;
                    if (0 > rr or rr >= N or 0 > cc or cc >= M) break;
                    if (board[rr][cc].type != EMPTY) break;
                    board[r][c].can_light++;
                }
            }
        }        
        rep(r,0,N) rep(c,0,M) if (board[r][c].type == EMPTY) cells.emplace_back(r,c);
        sort(cells.begin(), cells.end(), [](ii& i, ii& j) {
            Cell& a = board[i.ff][i.ss];
            Cell& b = board[j.ff][j.ss];
            if (a.nb.size() != b.nb.size()) return a.nb.size() > b.nb.size();
            return a.can_light > b.can_light;
        });
        best_ans = INT_MAX;
        search(0, 0);
        if (best_ans == INT_MAX) cout << "No solution\n";
        else cout << best_ans << '\n';
    }
    return 0;
}
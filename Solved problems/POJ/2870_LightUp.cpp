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
// typedefs
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int N, M, B;
const int EMPTY = 5;
struct Cell {
    int k = EMPTY;
    int score = 0;
    int count = 0;
    int vg, hg; // TODO: finish this
    vector<ii> deps;
    Cell(){}
    bool operator<(const Cell& o) const { return score < o.score; }
};
vector<vector<Cell>> board;
vector<ii> cells;

int dr[4] = {1, 0, -1, 0};
int dc[4] = {0, 1, 0, -1};

bool between(int x, int a, int b) { return a <= x and x <= b; }

int ans;
void search(int i, int count) {
    if (count >= ans) return;
    if (i == cells.size()) { ans = count; return; }
    
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    while (cin >> N >> M and N) {
        board.assign(N, vector<Cell>(M, Cell()));
        cells.clear();
        ans = INT_MAX;
        cin >> B;
        rep(i,0,B) {
            int r, c, k; cin >> r >> c >> k; --r, --c;
            cell.k = k;
            if (k != -1) {
                rep(j,0,4) {
                    int rr = r + dr[j];
                    int cc = c + dc[j];
                    if (0 <= rr and rr < N and 0 <= cc and cc < M)
                }
            }
        }
        rep(r,0,N) rep(c,0,M) {
            if (between(boad[r][c].k, 1, 4)) {
                rep(i,0,4) {
                    int rr = r + dr[j];
                    int cc = c + dc[j];
                    if (0 <= rr and rr < N and 0 <= cc and cc < M and board[r][c].k == EMPTY) {
                        board[rr][cc].score += board[r][c].k;
                        board[r][c].deps.emplace_back(r,c);
                    }
                }
            }
            if (board[r][c].k == EMPTY) cells.emplace_back(r,c);
        }
        sort(cells.begin(), cells.end(), [](ii& a, ii& b) { 
            return board[a.ff][a.ss] > board[b.ff][b.ss];
        });
        search(0, 0);
        cout << ans << '\n';
    }
    return 0;
}
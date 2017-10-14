// tags: DP, bottom-up, memory optimization, path recovery
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
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<double, int> pdi;
typedef pair<ll, int> lli;
// -------------------------------

const int MAXN = 20000;
int n, m, p;
int xs[MAXN], ys[MAXN];
struct Cell { int r, c; ll score; };
vector<Cell> diagonal;

int inline prize(int c, int s) {
    return (xs[c] + ys[s]) % p;    
}

ll score_memo[MAXN];

void DP_above() {
    memset(score_memo, 0, sizeof score_memo);
    // rectangle above diagonal
    int last_r = diagonal.back().r - 1;
    rep(r, 0, last_r) {
        rep(c, 0, m-1) {
            score_memo[c] = prize(r,c) +
                (c > 0 ? max(score_memo[c-1], score_memo[c]) : score_memo[c]);
        }
    }
    // triangle above diagonal
    invrep(i, diagonal.size()-1, 0) {
        Cell& cell = diagonal[i];
        int r = cell.r;
        int last_c = cell.c;
        rep(c, 0, last_c) {
            score_memo[c] = prize(r,c) +
                (c > 0 ? max(score_memo[c-1], score_memo[c]) : score_memo[c]);
        }
        cell.score += score_memo[last_c];
    }
}

void DP_below() {
    memset(score_memo, 0, sizeof score_memo);
    // rectangle below diagonal
    int first_r = diagonal.front().r + 1;
    invrep(r, n-1, first_r) {
        invrep(c, m-1, 0) {
            score_memo[c] = prize(r,c) +
                (c < m-1 ? max(score_memo[c+1], score_memo[c]) : score_memo[c]);
        }
    }
    // triangle below diagonal
    for (Cell& cell : diagonal) {
        int r = cell.r;
        int first_c = cell.c;
        invrep(c, m-1, first_c) {
            score_memo[c] = prize(r,c) +
                (c < m-1 ? max(score_memo[c+1], score_memo[c]) : score_memo[c]);
        }
        cell.score += score_memo[first_c];
    }
}

// search the optimal path from the upper left corner to the lower right corner
// of a rectangle of dimensions (width, height) and absolute position
// (r_offset, c_offset)
void find_optimal_path(int r_offset, int c_offset, int height, int width,
    vector<char>& path) {

    // bit = 1 -> move to the right (eat a stone)
    // bit = 0 -> move downwards (eat a candy)
    static bitset<200000000> bits;
    bits.reset();
    
    // search optimal path with DP
    memset(score_memo, 0, sizeof score_memo);
    invrep(r, height-1, 0) {
        invrep(c, width-1, 0) {
            int score = prize(r_offset + r, c_offset + c);
            bool right = false;
            if (c < width-1) {
                if (score_memo[c+1] >= score_memo[c]) {
                    right = true;
                    score += score_memo[c+1];
                } else {
                    score += score_memo[c];
                }
            } else {
                score += score_memo[c];
            }
            if (right) bits.set(r * width + c);
            score_memo[c] = score;
        }
    }

    // reconstruct and collect optimal path
    int r = 0, c = 0;
    int tr = height-1, tc = width-1;
    while (r != tr || c != tc) {
        if (bits.test(r * width + c)) { // right
            path.push_back('S'); // eat a stone
            c++; // increase column
        } else { // up
            path.push_back('C'); // eat a candy
            r++; // increase row
        }
        // assert(r <= tr && c <= tc); // DEBUG
    }
}

int main() {
    scanf("%d%d%d", &n,&m,&p);
    rep(i,0,n-1) scanf("%d", xs + i);
    rep(i,0,m-1) scanf("%d", ys + i);

    int steps = n + m - 2;
    if (steps == 0) {
        printf("%d\n\n", prize(0,0));
        return 0;
    }

    // --- collect diagonal cells
    int k = steps / 2;
    if (m > k) {
        for (int r = n-1, c = m-1-k; r >= 0 && c < m; r--, c++) {
            diagonal.push_back({r,c,0});
        }
    } else {
        for (int r = n+m-2-k, c = 0; r >= 0 && c < m; r--, c++) {
            diagonal.push_back({r,c,0});
        }
    }

    // --- find cell in diagonal which is also in the optimal path
    ll max_score = -1;
    Cell best_cell;
    DP_above();
    DP_below();
    for (Cell& cell : diagonal) {
        ll score = cell.score - prize(cell.r,cell.c);
        if (max_score < score) {
            max_score = score;
            best_cell = cell;
        }
    }

    // --- find optimal path
    vector<char> optimal_path;
    // first half
    find_optimal_path(0, 0, best_cell.r+1, best_cell.c+1, optimal_path);
    // second half
    find_optimal_path(best_cell.r, best_cell.c, n-best_cell.r, m-best_cell.c, optimal_path);

    // --- print output
    printf("%lld\n", max_score);
    for (char c : optimal_path) putchar(c);
    puts("");
    
    return 0;
}
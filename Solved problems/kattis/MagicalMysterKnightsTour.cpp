// tags: backtracking, pruning, implementation
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
const int MAGIC_NUM = 260;
int board[8][8];
int row_sum[8] = {0};
int col_sum[8] = {0};
int row_free[8];
int col_free[8];
int i2row[65], i2col[65];
bool placed[80] = {0};
int n_unplaced;
int unplaced_accsum[64];
int i2index[65];
int dr[8] = {2,2,-2,-2,1,-1,1,-1};
int dc[8] = {1,-1,1,-1,2,2,-2,-2};
bool valid_jump[15][15] = {0};

void print_board() {
    rep(r,0,7) {
        rep(c,0,7) printf("%*d ", 2, board[r][c]);
        puts("");
    }
}

// place value 'i' in row 'r' and column 'c'
void make_move(int i, int r, int c) {
    i2row[i] = r;
    i2col[i] = c;
    board[r][c] = i;
    row_free[r]--;
    col_free[c]--;
    row_sum[r]+=i;
    col_sum[c]+=i;
    placed[i] = true;
}

// remove value 'i' from row 'r' and column 'c'
// ** this assumes make_move(i,r,c) was previously called
void undo_move(int i, int r, int c) {
    board[r][c] = -1;
    row_free[r]++;
    col_free[c]++;
    row_sum[r]-=i;
    col_sum[c]-=i;                                
    placed[i] = false;
}

// check that the last move (placing value 'i') does not break some rules
bool valid_update(int i) {
    // Intuition: each row r has a partial sum of row_sum[r] and still row_free[r] values not placed yet
    // This means there is a theoretical lower bound and upper bound for the sum of row r
    // The same applies to columns.
    // Here we essentially verify that
    //     for each row r:  minsum[r] <= MAGIC_NUM <= maxsum[r]
    //     for each col c:  minsum[c] <= MAGIC_NUM <= maxsum[c]
    int idx = i2index[i];
    rep(j,0,7) { // for each row and column
        // maxsum verification for row j
        int i = n_unplaced-1 - row_free[j];
        int r_maxsum = row_sum[j] + unplaced_accsum[n_unplaced-1] - (i>=0 ? unplaced_accsum[i] : 0);
        if (r_maxsum < MAGIC_NUM) return false;
        // maxsum verification for column j
        i = n_unplaced-1 - col_free[j];
        int c_maxsum = col_sum[j] + unplaced_accsum[n_unplaced-1] - (i>=0 ? unplaced_accsum[i] : 0);
        if (c_maxsum < MAGIC_NUM) return false;
        // minsum verification for row j
        int r_minsum = row_sum[j] + unplaced_accsum[idx + row_free[j]] - unplaced_accsum[idx];
        if (r_minsum > MAGIC_NUM) return false;
        // minsum verification for column j
        int c_minsum = col_sum[j] + unplaced_accsum[idx + col_free[j]] - unplaced_accsum[idx];
        if (c_minsum > MAGIC_NUM) return false;
    }
    return true;
}

bool solve(int i) {
    if (i == 65) return true; // 65 reached -> we are done
    if (placed[i]) return solve(i+1); // already placed -> move to next value
    int prev_r = i2row[i-1], prev_c = i2col[i-1]; // get row and column of previous value
    rep(j,0,7) { // for each knight jump possible
        int r = prev_r + dr[j], c = prev_c + dc[j]; // compute (r,c) of cell we jump to
        if (0 <= r and r < 8 and 0 <= c and c < 8 and board[r][c] == -1) { // if within board and empty
            // if next value already placed but there is no valid knight jump to get there -> skip
            if (placed[i+1] && !valid_jump[7 + i2row[i+1] - r][7 + i2col[i+1] - c]) continue;
            make_move(i,r,c); // try the move
            // if the move keeps everything consistent and we manage to solve the remaining problem -> we are done
            if (valid_update(i) and solve(i+1)) return true;
            undo_move(i,r,c); // it didn't work -> undo move (backtrack)
        }
    }
    return false; // nothing worked
}

int main() {
    // precompute valid_jumps
    rep(i,0,7) valid_jump[7 + dr[i]][7 + dc[i]] = true;
    // initially all rows and columns are 100% free
    rep(j,0,7) row_free[j] = col_free[j] = 8;
    // read board
    rep(r,0,7) rep(c,0,7) {
        int i; scanf("%d", &i);
        if (i != -1) make_move(i,r,c);
        else board[r][c] = i;
    }
    // for all values which have not been placed yet in the board
    //  1) we count them
    //  2) we assign indexes to them
    //  3) we compute the accumulated sum of their values
    n_unplaced = 0;
    int accsum = 0;
    rep(i,1,64) if (!placed[i]) {
        unplaced_accsum[n_unplaced] = (accsum += i);
        i2index[i] = n_unplaced;
        n_unplaced++;
    }
    // start solving from the first unplaced value
    solve(unplaced_accsum[0]);
    // print answer
    print_board();
    return 0;
}
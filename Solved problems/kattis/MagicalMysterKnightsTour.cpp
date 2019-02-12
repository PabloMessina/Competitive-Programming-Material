// tags: backtracking, pruning, implementation
#pragma GCC optimize("Ofast")
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
int movr[8] = {2,2,-2,-2,1,-1,1,-1};
int movc[8] = {1,-1,1,-1,2,2,-2,-2};
bool valid_jump[5][15][15] = {0};

void print_board() {
    rep(r,0,7) {
        rep(c,0,7) printf("%*d ", 2, board[r][c]);
        puts("");
    }
}

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

void undo_move(int i, int r, int c) {
    board[r][c] = -1;
    row_free[r]++;
    col_free[c]++;
    row_sum[r]-=i;
    col_sum[c]-=i;                                
    placed[i] = false;
}

bool valid_update(int i, int r, int c) {
    int j;

    j = n_unplaced-1 - row_free[r];
    int r_maxsum = row_sum[r] + unplaced_accsum[n_unplaced-1] - (j>=0 ? unplaced_accsum[j] : 0);
    if (r_maxsum < MAGIC_NUM) return false;

    j = n_unplaced-1 - col_free[c];
    int c_maxsum = col_sum[c] + unplaced_accsum[n_unplaced-1] - (j>=0 ? unplaced_accsum[j] : 0);
    if (c_maxsum < MAGIC_NUM) return false;

    int idx = i2index[i];

    rep(j,0,7) {
        int r_minsum = row_sum[j] + unplaced_accsum[idx + row_free[j]] - unplaced_accsum[idx];
        if (r_minsum > MAGIC_NUM) return false;
        
        int c_minsum = col_sum[j] + unplaced_accsum[idx + col_free[j]] - unplaced_accsum[idx];
        if (c_minsum > MAGIC_NUM) return false;
    }

    return true;
}

bool search(int i) {
    if (i == 65) return true;
    if (placed[i]) return search(i+1);
    int prev_r = i2row[i-1], prev_c = i2col[i-1];    
    bool next_placed = false;
    int next_r, next_c;
    int jumps;
    for (jumps=1; jumps<=4; ++jumps) {
        if (placed[i+jumps]) {
            next_placed = true;
            next_r = i2row[i+jumps];
            next_c = i2col[i+jumps];
            break;
        }
    }
    rep(j,0,7) {
        int r = prev_r + movr[j];
        int c = prev_c + movc[j];
        if (0 <= r and r < 8 and 0 <= c and c < 8 and board[r][c] == -1) {
            if (next_placed &&
                !valid_jump[jumps][7 + next_r - r][7 + next_c - c]) continue;
            make_move(i,r,c);
            if (valid_update(i,r,c) and search(i+1)) return true;
            undo_move(i,r,c);
        }
    }
    return false;
}

int main() {
    
    rep(i,0,7) {
        int dr = movr[i];
        int dc = movc[i];
        valid_jump[1][7 + dr][7 + dc] = true;
    }    
    rep(i,0,7) rep(j,0,7) {
        int dr = movr[i] + movr[j];
        int dc = movc[i] + movc[j];
        valid_jump[2][7 + dr][7 + dc] = true;
    }
    rep(i,0,7) rep(j,0,7) rep(k,0,7) {
        int dr = movr[i] + movr[j] + movr[k];
        int dc = movc[i] + movc[j] + movc[k];
        valid_jump[3][7 + dr][7 + dc] = true;
    }
    rep(i,0,7) rep(j,0,7) rep(k,0,7) rep(s,0,7) {
        int dr = movr[i] + movr[j] + movr[k] + movr[s];
        int dc = movc[i] + movc[j] + movc[k] + movc[s];
        if (abs(dr) > 7 or abs(dc) > 7) continue;
        valid_jump[4][7 + dr][7 + dc] = true;
    }

    rep(j,0,7) row_free[j] = col_free[j] = 8;
    rep(r,0,7) {
        rep(c,0,7) {
            int i; scanf("%d", &i);
            board[r][c] = i;
            if (i != -1) {
                placed[i] = true;
                row_sum[r] += i;
                col_sum[c] += i;
                row_free[r]--;
                col_free[c]--;
                i2row[i] = r;
                i2col[i] = c;
            }
        }
    }

    n_unplaced = 0;
    int accsum = 0;
    rep(i,1,64) if (!placed[i]) {
        unplaced_accsum[n_unplaced] = (accsum += i);
        i2index[i] = n_unplaced;
        n_unplaced++;
    }
    search(unplaced_accsum[0]);
    print_board();
    return 0;
}
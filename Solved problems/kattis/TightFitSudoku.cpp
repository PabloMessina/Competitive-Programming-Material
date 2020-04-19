// tags: backtracking, pruning, implementation
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
enum TYPE { SINGLE, DOUBLE };
enum OP { FIRST, SECOND }; // arriba del slash o abajo del slash
struct Cell {
    TYPE type;
    int a = 0, b = 0;
} cells[6][6];

int row_masks[6] = {0};
int col_masks[6] = {0};
int grid_masks[3][2] = {0};

// add/remove a digit from a row, column and grid section
// using XOR (^) bitwise operator.
//   r = row
//   c = column
//   b = an int with one bit = 1 and all other bits = 0
void toggle_masks(int r, int c, int b) {
    row_masks[r] ^= b;
    col_masks[c] ^= b;
    grid_masks[r/2][c/3] ^= b;
}

void read_board() {
    string tmp;
    rep(r,0,5) rep(c,0,5) {
        cin >> tmp;
        Cell& cell = cells[r][c];
        if (tmp.size() == 1) { // one digit
            cell.type = SINGLE;
            if (tmp[0] == '-') {
                cell.a = 0;
            } else {
                cell.a = tmp[0] - '0';
                toggle_masks(r, c, 1 << cell.a);
            }
        } else { // two digits
            cell.type = DOUBLE;
            if (tmp[0] == '-') {
                cell.a = 0;
            } else {
                cell.a = tmp[0] - '0';
                toggle_masks(r, c, 1 << cell.a);
            }
            if (tmp[2] == '-') {
                cell.b = 0;
            } else {
                cell.b = tmp[2] - '0';
                toggle_masks(r, c, 1 << cell.b);
            }
        }
    }
}

bool solve(int r, int c, OP op) {
    // base case: out of board -> we are done
    if (r == 6 or c == 6) return true;
    
    Cell& cell = cells[r][c]; // reference to cell at (r,c)

    // compute next_r, next_c and next_op
    int next_r, next_c;
    OP next_op;
    if (cell.type == SINGLE or (cell.type == DOUBLE and op == SECOND)) {
        if (c == 5) { next_r = r + 1; next_c = 0; }
        else { next_r = r; next_c = c + 1; }
        next_op = FIRST;
    } else {
        next_r = r; next_c = c;
        next_op = SECOND;
    }

    // easy cases: cell's values already given by the input
    if (cell.type == SINGLE and cell.a != 0)
        return solve(next_r, next_c, next_op);
    if (cell.type == DOUBLE and
            ((op == FIRST and cell.a != 0) or
            (op == SECOND and cell.b != 0)))
        return solve(next_r, next_c, next_op);
    
    // general cases: we need to try all possible values
    int gr = r/2, gc = c/3;
    int xmin, xmax;
    int* p;
    if (cell.type == SINGLE) { // SINGLE
        xmin = 1; xmax = 9; p = &cell.a;        
    } else if (op == FIRST) { // DOUBLE, FIRST
        xmin = 1;
        xmax = cell.b == 0 ? 8 : cell.b - 1;
        p = &cell.a;
    } else { // DOUBLE, SECOND
        xmin = cell.a == 0 ? 2 : cell.a + 1;
        xmax = 9;
        p = &cell.b;
    }
    rep(x,xmin,xmax+1) {
        int b = 1 << x;
        if (row_masks[r] & b) continue;
        if (col_masks[c] & b) continue;
        if (grid_masks[gr][gc] & b) continue;
        toggle_masks(r,c,b);
        *p = x;
        if (solve(next_r, next_c, next_op)) return true;
        *p = 0; // backtrack (undo changes)
        toggle_masks(r,c,b);
    }
    return false;
}

void print_board() {
    rep(r,0,5) {
        rep(c,0,5) {
            Cell& cell = cells[r][c];
            if (cell.type == SINGLE) {
                cout << cell.a;
            } else {
                cout << cell.a << '/' << cell.b;
            }
            cout << " ";
        }
        cout << '\n';
    }
}

int main() {
    // for faster input/output
    ios::sync_with_stdio(false);
    cin.tie(0);
    // ------------
    read_board();
    solve(0,0,FIRST);
    print_board();
    return 0;
}
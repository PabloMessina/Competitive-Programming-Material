#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long int ll;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;

#define MAXN 100
int N,M;
int banned[MAXN][MAXN][4];
bool assigned[MAXN][MAXN];
bool in_queue[MAXN][MAXN];
char board_orig[MAXN][MAXN];
char board_best[MAXN][MAXN];
char board[MAXN][MAXN];
vector<ii> cells;

enum CellType { FASHION, PLUS, CROSS, EMPTY };
char cell_chars[4] = {'o', '+', 'x', '.'};
int cell_scores[4] = {2, 1, 1, 0};

int best_score;
int best_future;
int acc_score;

void update_best_board() {
    rep(r,0,N-1) rep(c,0,N-1) board_best[r][c] = board[r][c];
}

int find_max_score(int r, int c) {
    int score = 0;
    rep(i,0,3) if (!banned[r][c][i]) score = max(score, cell_scores[i]);
    return score;
}

void propagate_constraints(int r, int c, int ctype, bool adding) {
    int b = adding ? 1 : -1;
    if (ctype == FASHION or ctype == CROSS) {
        rep(rr, 0, N-1) { // horizontal
            if (assigned[rr][c]) continue;
            best_future -= find_max_score(rr, c);
            banned[rr][c][CROSS] += b;
            banned[rr][c][FASHION] += b;
            best_future += find_max_score(rr, c);
        }
        rep(cc, 0, N-1) { // vertical
            if (assigned[r][cc]) continue;
            best_future -= find_max_score(r, cc);
            banned[r][cc][CROSS] += b;
            banned[r][cc][FASHION] += b;
            best_future += find_max_score(r, cc);
        }
    }
    if (ctype == FASHION or ctype == PLUS) {
        for (int tmp = min(r,c), rr = r - tmp, cc = c - tmp;
            rr < N and cc < N; rr++, cc++) { // diagonal 1
            if (assigned[rr][cc]) continue;
            best_future -= find_max_score(rr, cc);
            banned[rr][cc][PLUS] += b;
            banned[rr][cc][FASHION] += b;
            best_future += find_max_score(rr, cc);
        }        
        for (int tmp = min(c,N-1-r), rr = r + tmp, cc = c - tmp;
            rr >= 0 and cc < N; rr--, cc++) { // diagonal 2
            if (assigned[rr][cc]) continue;
            best_future -= find_max_score(rr, cc);
            banned[rr][cc][PLUS] += b;
            banned[rr][cc][FASHION] += b;
            best_future += find_max_score(rr, cc);
        }
    }
}

void search(int i) {
    if (i == cells.size()) {
        if (acc_score > best_score) {
            best_score = acc_score;
            update_best_board();
        }
        return;
    }
    if (acc_score + best_future <= best_score) return;    

    ii& cell = cells[i];
    int r = cell.first, c = cell.second;

    rep(j,0,3) {

        if (banned[r][c][j]) continue;

        int max_score = find_max_score(r,c);

        board[r][c] = cell_chars[j];
        acc_score += cell_scores[j];
        assigned[r][c] = true;
        best_future -= max_score;
        propagate_constraints(r,c,j,true);

        search(i+1);

        propagate_constraints(r,c,j,false);
        best_future += max_score;
        assigned[r][c] = false;
        acc_score -= cell_scores[j];
        board[r][c] = '.';
    }
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t,1,T) {
        scanf("%d%d\n",&N,&M);

        memset(banned, 0, sizeof(banned));
        memset(assigned, 0, sizeof(assigned));
        memset(in_queue, 0, sizeof(in_queue));
        memset(board_orig, '.', sizeof(board_orig));
        memset(board_best, '.', sizeof(board_best));
        memset(board, '.', sizeof(board));
        cells.clear();
        acc_score = 0;

        rep(i,1,M) {
            char ch; int r,c; scanf("%c%d%d\n",&ch,&r,&c);
            --r,--c;
            // printf("--> ch =  %c, r = %d, c = %d\n", ch, r+1, c+1);
            board_orig[r][c] = ch;
            banned[r][c][EMPTY]++;
            switch(ch) {
            case '+':
                banned[r][c][CROSS]++;
                cells.push_back(ii(r,c));
                in_queue[r][c] = true;
                break;
            case 'x':
                banned[r][c][PLUS]++;
                cells.push_back(ii(r,c));
                in_queue[r][c] = true;
                break;
            default: // o
                acc_score += 2;                
                board_best[r][c] = 'o';
                board[r][c] = 'o';
                assigned[r][c] = true;
                propagate_constraints(r,c,FASHION,true);
                break;
            }
        }    

        best_score = acc_score;
        best_future = 0;

        rep(r,0,N-1) rep(c,0,N-1) {
            if (assigned[r][c]) continue;
            if (!in_queue[r][c]) cells.push_back(ii(r,c));
            best_future += find_max_score(r,c);            
        }

        search(0);

        int count = 0;
        rep(r,0,N-1) rep(c,0,N-1)
            if (board_orig[r][c] != board_best[r][c])
                count++;
        printf("Case #%d: %d %d\n",t,best_score,count);
        rep(r,0,N-1) rep(c,0,N-1)
            if (board_orig[r][c] != board_best[r][c])
                printf("%c %d %d\n", board_best[r][c], r+1, c+1);
    }
    return 0;
}
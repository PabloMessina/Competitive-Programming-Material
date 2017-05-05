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
enum Piece { EMPTY, BISHOP, TOWER, QUEEN };
int orig_board[MAXN][MAXN];
int tower_board[MAXN][MAXN];
bool tower_banned[MAXN][MAXN];
int bishop_board[MAXN][MAXN];
bool bishop_banned[MAXN][MAXN];
int bishop_count;
int tower_count;

map<char,int> char2piece = {{ 'x', TOWER }, { '+', BISHOP }, { 'o', QUEEN }};
char piece2char[4] = {'.', 'x', '+', 'o'};

void propagate_tower(int x, int y) {
    tower_count++;
    tower_board[x][y] = TOWER;
    rep(xx,0,N-1) tower_banned[xx][y] = true;
    rep(yy,0,N-1) tower_banned[x][yy] = true;
}

void propagate_bishop(int x, int y) {
    bishop_count++;
    bishop_board[x][y] = BISHOP;
    // printf("\t\tpropagate_bishop(%d,%d)\n",x+1,y+1);
    for (int tmp = min(x,y), xx = x - tmp, yy = y - tmp;
        xx < N and yy < N; ++xx, ++yy) {
        bishop_banned[xx][yy] = true;
    }
    for (int tmp = min(x,N-1-y), xx = x - tmp, yy = y + tmp;
        xx < N and yy >= 0; ++xx, --yy) {
        bishop_banned[xx][yy] = true;
    }
}

void fill_towers() {
    rep(x,0,N-1) rep(y,0,N-1) {
        if (!tower_banned[x][y]) propagate_tower(x,y);
    }
}

void fill_bishops() {
    static bool inqueue[MAXN][MAXN];
    static int dirs[4][2] = {{0,-1},{0,1},{-1,0},{1,0}};
    
    queue<ii> q;

    int starts[4][2] = {{0,0}, {0,N-1}, {N-1, 0}, {N-1,N-1}};
    rep(i,0,3) {
        int x = starts[i][0], y = starts[i][1];
        if (!inqueue[x][y]) {
            q.emplace(x,y);
            inqueue[x][y] = true;
        }
    }

    while (!q.empty()) {
        ii& cur = q.front(); q.pop();
        int x = cur.first, y = cur.second;
        if (!bishop_banned[x][y]) propagate_bishop(x,y);
        rep(i,0,3) {
            int xx = x + dirs[i][0], yy = y + dirs[i][1];
            if (0 <= xx and xx < N and 0 <= yy and yy < N and !inqueue[xx][yy]) {
                q.emplace(xx,yy);
                inqueue[xx][yy] = true;
            }
        }
    }
}

int main() {
    int T;
    scanf("%d\n", &T);
    rep(_case,1,T) {
        // puts("----------------------------------");
        scanf("%d%d\n", &N, &M);
        memset(orig_board, 0, sizeof orig_board);
        memset(bishop_board, 0, sizeof bishop_board);
        memset(tower_board, 0, sizeof tower_board);
        memset(bishop_banned, 0, sizeof bishop_banned);
        memset(tower_banned, 0, sizeof tower_banned);
        bishop_count = 0;
        tower_count = 0;
        rep(i,1,M) {
            char c; int x, y;
            scanf("%c%d%d\n", &c, &x, &y);
            // printf("c = %c, x = %d, y = %d\n", c,x,y);
            --x, --y;

            int piece = orig_board[x][y] = char2piece[c];
            if (piece == BISHOP) propagate_bishop(x,y);
            else if (piece == TOWER) propagate_tower(x,y);
            else propagate_bishop(x,y), propagate_tower(x,y);
        }
        fill_bishops();
        fill_towers();


        int diff_count = 0;
        // puts("tower board:");
        // rep(x,0,N-1) {
        //     rep(y,0,N-1) {
        //         char c = piece2char[tower_board[x][y]];
        //         printf("%c", c);
        //     }
        //     puts("");
        // }
        // puts("bishop board:");
        // rep(x,0,N-1) {
        //     rep(y,0,N-1) {
        //         char c = piece2char[bishop_board[x][y]];
        //         printf("%c", c);
        //     }
        //     puts("");
        // }
        // puts("merge board:");
        // rep(x,0,N-1) {
        //     rep(y,0,N-1) {
        //         int piece = bishop_board[x][y] + tower_board[x][y];
        //         char c = piece2char[piece];
        //         printf("%c", c);
        //     }
        //     puts("");
        // }


        rep(x,0,N-1) {
            rep(y,0,N-1) {
                int piece = bishop_board[x][y] + tower_board[x][y];
                if (piece != orig_board[x][y]) diff_count++;
            }
        }

        // puts("-------------");
        printf("Case #%d: %d %d\n", _case, bishop_count + tower_count, diff_count);
        rep(x,0,N-1) rep(y,0,N-1) {
            int piece = bishop_board[x][y] + tower_board[x][y];
            if (piece != orig_board[x][y]) {
                printf("%c %d %d\n", piece2char[piece], x+1, y+1);
            }
        }
    }
    return 0;
}
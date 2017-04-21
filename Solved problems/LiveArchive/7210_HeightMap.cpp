// tags: adhoc, bfs/dfs, implementation
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)
#define invrep(i,a,b) for(int i=a; i>=b; i--)
typedef pair<int,int> ii;

#define MAXR 100
#define MAXC 100
int R,C;
int board[MAXR][MAXC];
bool visited[MAXR][MAXC];
int shifts[4][2] = {
    {1, 0},
    {-1, 0},
    {0, -1},
    {0, 1}
};

void bfs(int r, int c) {
    int h = board[r][c];
    queue<ii> q;
    q.push(ii(r,c));
    visited[r][c] = true;
    while (!q.empty()) {
        ii u = q.front(); q.pop();
        rep(i,0,3) {
            int rr = u.first + shifts[i][0];
            int cc = u.second + shifts[i][1];
            if (0 <= rr && rr < R && 0 <= cc && cc < C &&
            !visited[rr][cc] && board[rr][cc] == h) {
                q.push(ii(rr,cc));
                visited[rr][cc] = true;
            }
        }
    }
}

int main() {
    while(scanf("%d%d",&R,&C)==2) {
        rep(r,0,R-1) rep(c,0,C-1) scanf("%d", &board[r][c]);
        memset(visited, 0, sizeof visited);

        int faces = 5; // always there are at least 5 faces

        // top
        rep(r,0,R-1) rep(c,0,C-1) if (!visited[r][c]) faces++, bfs(r,c);

        int prev_up, prev_down, up, down;
        // north -> south
        rep(r,1,R-1) {
            prev_up = prev_down = 0;
            rep(c,0,C-1) {
                up = board[r][c];
                down = board[r-1][c];
                if (up > down) {
                    if (min(prev_up, up) - max(prev_down, down) < 1)
                        faces++;
                }
                prev_up = up;
                prev_down = down;
            }
        }
        // south -> north
        invrep(r,R-2,0) {
            prev_up = prev_down = 0;
            rep(c,0,C-1) {
                up = board[r][c];
                down = board[r+1][c];
                if (up > down) {
                    if (min(prev_up, up) - max(prev_down, down) < 1)
                        faces++;
                }
                prev_up = up;
                prev_down = down;
            }
        }
        // west -> east
        rep(c,1,C-1) {
            prev_up = prev_down = 0;
            rep(r,0,R-1) {
                up = board[r][c];
                down = board[r][c-1];
                if (up > down) {
                    if (min(prev_up, up) - max(prev_down, down) < 1)
                        faces++;
                }
                prev_up = up;
                prev_down = down;
            }
        }
        // east -> west
        invrep(c,C-2,0) {
            prev_up = prev_down = 0;
            rep(r,0,R-1) {
                up = board[r][c];
                down = board[r][c+1];
                if (up > down) {
                    if (min(prev_up, up) - max(prev_down, down) < 1)
                        faces++;
                }
                prev_up = up;
                prev_down = down;
            }
        }
        
        printf("%d\n", faces);
    }
    return 0;
}
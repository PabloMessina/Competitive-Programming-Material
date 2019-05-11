// tags: dijkstra
#include <cstdio>
#include <queue>
using namespace std;

#define FOR(i,i0,n) for(int i=i0; i < n; ++i)
#define INF 1e9

int costs[5][5] = {
    {7,6,5,6,7},
    {6,3,2,3,6},
    {5,2,0,2,5},
    {6,3,2,3,6},
    {7,6,5,6,7},
};

int C,R;
int sc, sr, tc, tr;
int board[1000][1000];
int W;
int wflag = 1;

int dist[1000][1000];

struct Tuple {
    int row;
    int col;
    int dist;
    Tuple (int r, int c, int d) : row(r), col(c), dist(d) {}
    bool operator<(const Tuple& t) const {
        return dist > t.dist;
    }
};

int main() {
    while(scanf("%d %d",&C,&R) && C && R) {
        // read input
        scanf("%d %d %d %d",&sc,&sr,&tc,&tr);
        sc--; sr--; tc--; tr--;
        scanf("%d",&W);
        FOR(i,0,W) {
            int c1,r1,c2,r2;
            scanf("%d %d %d %d",&c1,&r1,&c2,&r2);
            c1--; r1--; c2--; r2--;
            FOR(r,r1,r2+1) FOR(c,c1,c2+1) board[r][c] = wflag;
        }
        // dijkstra
        FOR(r,0,R) FOR(c,0,C) dist[r][c] = INF;
        dist[sr][sc] = 0;
        priority_queue<Tuple> pq;
        pq.push(Tuple(sr,sc,0));
        while (!pq.empty()) {
            Tuple t = pq.top(); pq.pop();
            if (t.dist > dist[t.row][t.col]) continue;
            if (tr == t.row && tc == t.col) break; // optimization
            FOR(x,-2,3) FOR(y,-2,3) {
                if (x == 0 && y == 0) continue;
                int r = t.row + x;
                int c = t.col + y;
                if (0 <= r && r < R && 0 <= c && c < C && board[r][c] != wflag) {
                    int alt = t.dist + costs[2 + x][2 + y];
                    if (alt < dist[r][c]) {
                        dist[r][c] = alt;
                        pq.push(Tuple(r,c,alt));
                    }
                }
            }
        }
        // print answer
        if (dist[tr][tc] == INF) puts("impossible");
        else printf("%d\n", dist[tr][tc]);
        wflag++; // increase water flag
    }
    return 0;
}
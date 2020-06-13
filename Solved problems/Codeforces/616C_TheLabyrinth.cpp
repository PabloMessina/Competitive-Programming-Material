// tags: BFS / DFS, flood fill, graphs
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define uset unordered_set
// -------------------------------
enum { EMPTY = -2, IMP = -1 };
int R,C;
int board[1000][1000];
int movr[4] = {0, 0, 1, -1};
int movc[4] = {1, -1, 0, 0};
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    cin >> R >> C;
    rep(r,0,R) {
        string line; cin >> line;
        rep(c,0,C) board[r][c] =  line[c] == '*' ? IMP : EMPTY;
    }
    int ID = 0;
    vector<int> counts;
    queue<pair<int,int>> q;
    rep(r,0,R) rep(c,0,C) {
        if (board[r][c] == EMPTY) {
            q.emplace(r,c);
            board[r][c] = ID;
            int count = 1;
            while(!q.empty()) {
                auto p = q.front(); q.pop();
                rep(i,0,4) {
                    int rr = p.first + movr[i];
                    int cc = p.second + movc[i];
                    if (0 <= rr and rr < R and 0 <= cc and cc < C and
                            board[rr][cc] == EMPTY) {
                        board[rr][cc] = ID;
                        count++;    
                        q.emplace(rr,cc);
                    }
                }
            }
            counts.push_back(count);
            ID++;
        }
    }
    uset<int> used;
    rep(r,0,R) {
        rep(c,0,C) {
            if (board[r][c] == IMP) {
                int count = 1;
                rep(i,0,4) {
                    int rr = r + movr[i];
                    int cc = c + movc[i];
                    int id = board[rr][cc];
                    if (0 <= rr and rr < R and 0 <= cc and cc < C and
                             id != IMP and used.count(id) == 0) {
                        count += counts[id];
                        used.insert(id);
                    }
                }
                used.clear();
                cout << (count % 10);
            } else {
                cout << '.';
            }
        }
        cout << '\n';
    }
    return 0;
}
#include <cstdio>
#include <vector>
#include <queue>
#include <bitset>
#include <cstring>
using namespace std;

typedef vector<int> vi;

#define MAX_R 60
#define MAX_C 60
#define MAX_V 3602
#define WHITE 1
#define BLACK 2
#define INF 1000000000

int R, C, V;

char board[MAX_R][MAX_C + 1]; //+1 to store \0 (end of string)
int coloration[MAX_R][MAX_C];
int res[MAX_V][MAX_V];
int shifts[2][4] = { { 0, 0, -1, 1 }, { -1, 1, 0, 0 } };

vector<vi> AdjList;
vi p;

int s = 3600; //source
int t = 3601; //target
int mf, f;

int main() {

	int _case = 1;
	while (true) {
		READ_INPUT: scanf("%d %d", &R, &C);
		if (R == 0 && C == 0)
			break;

		for (int r = 0; r < R; ++r)
			scanf("%s", board[r]);

		//==================================
		//perform bi-coloration check and
		//build graph at the same time

		memset(coloration, -1, sizeof coloration);
		AdjList.assign(MAX_V, vi());
		V = 0;

		for (int r = 0; r < R; ++r) {
			for (int c = 0; c < C; ++c) {
				//make sure it's a not-yet-colored # cell
				if (board[r][c] != '#' || coloration[r][c] != -1)
					continue;

				queue<pair<int, int>> q;
				q.push(std::make_pair(r, c));
				coloration[r][c] = WHITE;
				int wcount = 0;
				int bcount = 0;

				while (!q.empty()) { //BFS
					pair<int, int> u = q.front();
					q.pop();
					int u_row = u.first;
					int u_col = u.second;
					int ui = u_row * C + u_col; // (r,c) to index
					int color = coloration[u_row][u_col];
					int child_color;

					//count color and set child color
					if (color == WHITE)
						wcount++, child_color = BLACK;
					else
						bcount++, child_color = WHITE;

					for (int i = 0; i < 4; ++i) {
						int v_row = u_row + shifts[0][i];
						int v_col = u_col + shifts[1][i];
						if (v_row < 0 || v_row >= R || v_col < 0 || v_col >= C
								|| board[v_row][v_col] != '#')
							continue;
						int vi = v_row * C + v_col;
						AdjList[ui].push_back(vi);

						if (coloration[v_row][v_col] == -1) {
							coloration[v_row][v_col] = child_color;
							q.push(std::make_pair(v_row, v_col));
						}
					}

					if (color == WHITE) {
						//make residual capacity 1 from White to Black
						//and 0 backwards
						for (int i = 0; i < (int) AdjList[ui].size(); ++i) {
							int vi = AdjList[ui][i];
							res[ui][vi] = 1;
							res[vi][ui] = 0;
						}
						//add connection between source and white
						AdjList[s].push_back(ui);
						res[s][ui] = 1;
						AdjList[ui].push_back(s);
						res[ui][s] = 0;
					} else {
						//add connection between black and target
						AdjList[ui].push_back(t);
						res[ui][t] = 1;
						AdjList[t].push_back(ui);
						res[t][ui] = 0;
					}
				}

				//check same number of blacks and whites
				if (wcount != bcount) {
					printf("Case %d: Impossible\n", _case);
					_case++;
					goto READ_INPUT;
				}

				V += wcount + bcount; //count visited nodes
			}
		}

		// ========================================
		// run Edmonds Karp's algorithm (MAX FLOW)
		// to get the maximum bipartite matching

		mf = 0;
		while (true) {
			// run BFS to find aumenting path
			f = 0;
			bitset<MAX_V> vis;
			vis[s] = true;
			queue<int> q;
			q.push(s);
			p.assign(MAX_V, -1); //reset parents
			while (!q.empty()) {
				int u = q.front();
				q.pop();
				for (int j = 0; j < (int) AdjList[u].size(); ++j) {
					int v = AdjList[u][j];
					if (res[u][v] > 0 && !vis[v]) {
						vis[v] = true, q.push(v), p[v] = u;
						if (v == t) { //target found, we are done
							goto end_bfs;
						}
					}
				}
			}
			end_bfs:

			//augment along the path
			if (p[t] != -1) {
				int n = t;
				while (n != s) {
					res[p[n]][n]--;
					res[n][p[n]]++;
					n = p[n];
				}
				mf++;
			} else
				break;
		}

		if (mf == V / 2)
			printf("Case %d: Possible\n", _case);
		else
			printf("Case %d: Impossible\n", _case);

		_case++;
	}

	return 0;
}

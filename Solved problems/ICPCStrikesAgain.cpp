#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <queue>
using namespace std;
typedef unsigned long long int ull;
int T, E;
int S[1000];
ull TS[1000];
vector<vector<int>> g(1000, vector<int>());
vector<vector<int>> W(1000, vector<int>());
vector<set<int>> Waux(1000, set<int>());
bool deleted[1000];

ull totalSignif(int t) {
	if (TS[t] > 0)
		return TS[t];
	ull ans = S[t];
	for (int i = 0; i < g[t].size(); ++i)
		ans += totalSignif(g[t][i]);
	return TS[t] = ans;
}

int main() {
	while (true) {
		scanf("%d %d", &T, &E);
		if (T == 0 && E == 0)
			break;
		for (int e = 0; e < E; ++e) {
			W[e].clear();
			Waux[e].clear();
		}
		for (int t = 0; t < T; ++t) {
			int bs, nd, ne;
			scanf("%d %d %d", &bs, &nd, &ne);
			S[t] = bs;
			TS[t] = 0;
			g[t].clear();
			for (int i = 0; i < nd; ++i) {
				int dt;
				scanf("%d", &dt);
				dt--;
				g[t].push_back(dt);
			}
			for (int i = 0; i < ne; ++i) {
				int e;
				scanf("%d", &e);
				e--;
				W[e].push_back(t);
				Waux[e].insert(t);
			}
		}
		for (int t = 0; t < T; ++t)
			totalSignif(t);
		printf("*****\n");
		for (int e = 0; e < E; ++e) {
			memset(deleted, 0, sizeof deleted);
			for (int i = 0; i < W[e].size(); ++i) {
				int t = W[e][i];
				if (deleted[t])
					continue;
				queue<int> q;
				q.push(t);
				while (!q.empty()) {
					t = q.front();
					q.pop();
					for (int j = 0; j < g[t].size(); ++j) {
						int dt = g[t][j];
						if (!deleted[dt]) {
							Waux[e].erase(dt);
							deleted[dt] = true;
							q.push(dt);
						}
					}
				}
			}
			ull salary = 0;
			for (set<int>::iterator it = Waux[e].begin(); it != Waux[e].end();
					++it)
				salary += TS[*it];
			printf("%d %llu\n", e + 1, salary);
		}
	}
	return 0;
}

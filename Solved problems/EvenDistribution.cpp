#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
int I, S;
int C[10005];
vector<int> g[10005];
set<int> memo[10005];
queue<pair<int, int> > states;
int solve() {
	set<int> global_memo;
	for (int i = 0; i < I; ++i) {
		states.push(make_pair(i, C[i]));
		memo[i].insert(C[i]);
		global_memo.insert(C[i]);
	}
	while (!states.empty()) {
		pair<int, int> s = states.front();
		states.pop();
		int u = s.first;
		int c = s.second;
		for (int j = 0; j < (int) g[u].size(); ++j) {
			int v = g[u][j];
			int c2 = __gcd(c, C[v]);
			if (memo[v].find(c2) == memo[v].end()) {
				memo[v].insert(c2);
				global_memo.insert(c2);
				states.push(make_pair(v, c2));
			}
		}
	}
	return global_memo.size();
}
int main() {
	while (scanf("%d %d", &I, &S) == 2) {
		for (int i = 0; i < I; ++i) {
			scanf("%d", &C[i]);
			g[i].clear();
			memo[i].clear();
		}
		for (int i = 0; i < S; ++i) {
			int a, b;
			scanf("%d %d", &a, &b);
			a--, b--;
			g[a].push_back(b);
			g[b].push_back(a);
		}
		printf("%d\n", solve());
	}
	return 0;
}

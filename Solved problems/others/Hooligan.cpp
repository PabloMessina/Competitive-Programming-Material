#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <queue>
using namespace std;

#define MAX_V 800
#define INF 1000000

int n, m, g;
int flow;
int source;
int target;

int scores[40];
int matchesCount[40][40];
vector<int> p;

// source, matches: 39*19, teams: 39, target
int res[MAX_V][MAX_V];
vector<vector<int> > AdjList;

int getIndex(int i, int j, int n) {
	if (0 <= i && i < j && j < n)
		return (n - 1) * i - i * (i - 1) / 2 + j - i - 1;
	return -1;
}

void augment(int v, int minEdge) {
	if (v == source) {
		flow = minEdge;
		return;
	} else if (p[v] != -1) {
		augment(p[v], min(minEdge, res[p[v]][v]));
		res[p[v]][v] -= flow;
		res[v][p[v]] += flow;
	}
}

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	loop: while (true) {

		scanf("%d %d %d", &n, &m, &g);
		if (!(n || m || g))
			break;

		memset(scores, 0, sizeof scores);
		memset(matchesCount, 0, sizeof matchesCount);

		for (int i = 0; i < g; ++i) {
			int t1, t2;
			char c;
			scanf("%d %c %d", &t1, &c, &t2);
			if (c == '<')
				scores[t2] += 2;
			else {
				scores[t1]++;
				scores[t2]++;
			}
			matchesCount[t1][t2]++;
			matchesCount[t2][t1]++;
		}

		//make 0 win all the available matches
		for (int i = 1; i < n; ++i) {
			scores[0] += (m - matchesCount[0][i]) * 2;
			matchesCount[0][i] = m;
			matchesCount[i][0] = m;
		}

		//check that 0 is greater than everybody else
		for (int i = 1; i < n; ++i) {
			if (scores[0] <= scores[i]) {
				printf("N\n");
				goto loop;
			}
		}

		//calculate remaining score
		int remainingScore = m * n * (n - 1);
		for (int i = 0; i < n; ++i) {
			remainingScore -= scores[i];
		}

		// source, matches: 39*19, teams: 39, target
		int V = 1 + (n - 1) * (n - 2) / 2 + (n - 1) + 1;
		int source = 0;
		int target = V - 1;
		memset(res, 0, sizeof res);
		AdjList.assign(V, vector<int>());

		int teams_offset = 1 + (n - 1) * (n - 2) / 2;

		//from source to matches and matches to teams
		for (int i = 1; i < n - 1; ++i) {
			for (int j = i + 1; j < n; ++j) {
				//source to match
				int index = getIndex(i - 1, j - 1, n - 1) + 1;
				res[source][index] = (m - matchesCount[i][j]) * 2;
				AdjList[source].push_back(index);
				AdjList[index].push_back(source);

				//match to teams
				int t1 = teams_offset + i - 1;
				int t2 = teams_offset + j - 1;
				res[index][t1] = INF;
				res[index][t2] = INF;
				AdjList[index].push_back(t1);
				AdjList[index].push_back(t2);
				AdjList[t1].push_back(index);
				AdjList[t2].push_back(index);
			}
		}

		//from teams to target
		for (int i = 1; i < n; ++i) {
			int t = teams_offset + i - 1;
			res[t][target] = scores[0] - 1 - scores[i];
			AdjList[t].push_back(target);
			AdjList[target].push_back(t);
		}

		int mf = 0;
		while (true) {
			flow = 0;
			bitset<MAX_V> vis;
			vis[source] = true;
			queue<int> q;
			q.push(source);
			p.assign(V, -1);
			while (!q.empty()) {
				int u = q.front();
				q.pop();
				if (u == target)
					break;
				for (int j = 0; j < (int) AdjList[u].size(); j++) {
					int v = AdjList[u][j];
					if (res[u][v] > 0 && !vis[v])
						vis[v] = true, q.push(v), p[v] = u;
				}
			}
			augment(target, INF);
			if (flow == 0)
				break;
			mf += flow;
		}

		if (mf == remainingScore)
			printf("Y\n");
		else
			printf("N\n");

	}

	return 0;
}
#include <cstdio>
#include <tr1/unordered_map>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

typedef std::tr1::unordered_map<int, int> nested_hash;
typedef std::tr1::unordered_map<int, nested_hash> double_hash;

int N;
#define MAXN 50005
std::pair<int, int> points[MAXN];

vector<vector<int> > adjList(MAXN);
bool visited[MAXN];

int getIndex(double_hash& hash, int x, int y) {
	double_hash::iterator it = hash.find(x);
	if (it == hash.end())
		return -1;
	nested_hash::iterator it2 = it->second.find(y);
	if (it2 == it->second.end())
		return -1;
	return it2->second;
}

int bfs(int i) {
	queue<pair<int, int> > q;
	int count[2] = { };
	q.push(make_pair(i, 0));
	while (!q.empty()) {
		pair<int, int> p = q.back();
		q.pop();
		int u = p.first;
		count[p.second]++;
		visited[u] = true;
		for (int j = 0; j < (int) adjList[u].size(); ++j) {
			int v = adjList[u][j];
			if (visited[v])
				continue;
			q.push(make_pair(v, 1 - p.second));
		}
	}
	return min(count[0], count[1]);
}

int main() {

	//setvbuf(stdout, NULL, _IONBF, 0);

	while (scanf("%d", &N) == 1) {

		double_hash pointToIndexMap;

		memset(visited, false, sizeof(bool) * N);

		//build double hash map
		for (int i = 0; i < N; ++i) {
			int x, y;
			scanf("%d %d", &x, &y);
			points[i].first = x;
			points[i].second = y;

			double_hash::iterator it = pointToIndexMap.find(x);
			if (it == pointToIndexMap.end()) {
				pointToIndexMap[x] = nested_hash();
				pointToIndexMap[x][y] = i;
			} else {
				it->second[y] = i;
			}
		}

		//build graph
		for (int i = 0; i < N; ++i) {
			adjList[i].clear();
			int x = points[i].first;
			int y = points[i].second;
			for (int h = -5; h <= 5; ++h) {
				int hh = h * h;
				for (int v = -5; v <= 5; ++v) {
					int vv = v * v;
					if (h == 0 && v == 0)
						continue;
					if (hh + vv > 25)
						continue;
					int j = getIndex(pointToIndexMap, x + h, y + v);
					if (j == -1)
						continue;
					adjList[i].push_back(j);
				}
			}
		}

		//bfs's
		int sum = 0;
		for (int i = 0; i < N; ++i) {
			if (visited[i])
				continue;
			sum += bfs(i);
		}

		printf("%d\n", sum);
	}

	return 0;
}
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int N, Q;

int dN[40000];
int dQ[40000];
long long accum_dQ[40000];

bool visited[40000];

int deepestDepth;
int diameterEndNode;

void dfs(int curr, int depth, vector<vector<int> > &adjList, int* distances) {

	if (deepestDepth < depth) {
		diameterEndNode = curr;
		deepestDepth = depth;
	}

	for (int i = 0; i < (int) adjList[curr].size(); ++i) {
		int v = adjList[curr][i];
		if (visited[v])
			continue;
		visited[v] = true;
		if (distances[v] < depth)
			distances[v] = depth;
		dfs(v, depth + 1, adjList, distances);
	}
}

void dfsBase(int root, vector<vector<int> >& adjList, int* distances) {

	memset(visited, 0, sizeof(bool) * adjList.size());

	deepestDepth = -1;
	visited[root] = true;
	dfs(root, 0, adjList, distances);

}

int binSearch(int val, int l, int r, int* array) {
	if (val > array[r])
		return r + 1;
	while (l < r) {
		int m = (l + r) / 2;
		if (array[m] < val)
			l = m + 1;
		else
			r = m;
	}
	return l;
}

int main() {
	while (scanf("%d %d", &N, &Q) == 2) {

		vector<vector<int> > adjList_N(N, vector<int>());
		vector<vector<int> > adjList_Q(Q, vector<int>());

		for (int i = 1; i < N; ++i) {
			int a, b;
			scanf("%d %d", &a, &b);
			a--;
			b--;
			adjList_N[a].push_back(b);
			adjList_N[b].push_back(a);
		}

		for (int i = 1; i < Q; ++i) {
			int a, b;
			scanf("%d %d", &a, &b);
			a--;
			b--;
			adjList_Q[a].push_back(b);
			adjList_Q[b].push_back(a);
		}

		//find Nlogonia's diameter
		memset(dN, 0, sizeof(int) * N);
		dfsBase(0, adjList_N, dN);
		int diamEnd1_N = diameterEndNode;
		dfsBase(diamEnd1_N, adjList_N, dN);
		int diamEnd2_N = diameterEndNode;
		dfsBase(diamEnd2_N, adjList_N, dN);
		int diamN = dN[diamEnd1_N];

		//find Quadradonia's diameter
		memset(dQ, 0, sizeof(int) * Q);
		dfsBase(0, adjList_Q, dQ);
		int diamEnd1_Q = diameterEndNode;
		dfsBase(diamEnd1_Q, adjList_Q, dQ);
		int diamEnd2_Q = diameterEndNode;
		dfsBase(diamEnd2_Q, adjList_Q, dQ);
		int diamQ = dQ[diamEnd1_Q];

		//get max diameter
		int maxDiam = max(diamN, diamQ);

		//sort dQ and get  accumulated sum
		sort(dQ, dQ + Q);
		accum_dQ[0] = dQ[0];
		for (int i = 1; i < Q; ++i)
			accum_dQ[i] = dQ[i] + accum_dQ[i - 1];

		//calculate average in O(NlogQ)
		long long sum = 0;
		for (int i = 0; i < N; ++i) {
			int delta = maxDiam - dN[i];
			int index = binSearch(delta, 0, Q - 1, dQ);
			sum += index * maxDiam;
			sum += (accum_dQ[Q - 1] - accum_dQ[index - 1])
					+ (dN[i] + 1) * (Q - index);
		}
		double average = sum / (double) (Q * N);

		printf("%.3f\n", average);
	}
	return 0;
}
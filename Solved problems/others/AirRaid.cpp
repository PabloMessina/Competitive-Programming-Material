#include <cstdio>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;

int indegree[121];
bool explored[121];
stack<int> next_nodes;
vector<vector<int> > adjNodes;

void travelGraph(int source) {
	explored[source] = true;
	int selected_child = -1;
	for (int i = 0; i < (int) adjNodes[source].size(); ++i) {
		int child = adjNodes[source][i];
		if (explored[child])
			continue;
		if (selected_child == -1)
			selected_child = child;
		else {
			indegree[child]--;
			if (indegree[child] == 0)
				next_nodes.push(child);
		}
	}
	if (selected_child != -1)
		travelGraph(selected_child);
}

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	int NI, NS;
	int ncases;

	scanf("%d", &ncases);
	printf("ncases = %d\n",ncases);
	while (ncases--) {

		scanf("%d %d", &NI, &NS);

		adjNodes.assign(NI+1, vector<int>());
		memset(indegree, 0, sizeof(indegree));
		memset(explored, 0, sizeof(explored));

		for (int i = 0; i < NS; ++i) {
			int s, e;
			scanf("%d %d", &s, &e);
			adjNodes[s].push_back(e);
			indegree[e]++;
		}

		next_nodes = stack<int>();

		for (int i = 1; i <= NI; ++i) {
			if (indegree[i] == 0)
				next_nodes.push(i);
		}

		int count = 0;

		while (next_nodes.size() > 0) {
			int source = next_nodes.top();
			next_nodes.pop();
			count++;
			travelGraph(source);
		}

		printf("%d\n",count);	

	}

	return 0;
}

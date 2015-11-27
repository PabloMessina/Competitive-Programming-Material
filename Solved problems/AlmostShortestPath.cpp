#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

const int INFINITY = 99999999;
using namespace std;

struct edge {
	int cost;
};

struct priorityData {
public:
	int node;
	int parent;
	int travelCost;

	bool operator>(priorityData const& x) const {
		return this->travelCost > x.travelCost;
	}

	bool operator<(const priorityData & x) const {
		return this->travelCost < x.travelCost;
	}
};

vector<vector<edge> > edges(500, vector<edge>(500));
vector<vector<int> > adjLists(500);
vector<int> minCosts(500);
vector<vector<int> > parents(500);


void printAdjList(int n) {
	for(int i = 0; i < n; ++i) {
		printf("%d:",i);
		for(int j = 0; j < (int)adjLists[i].size(); ++j) {
			printf("\t%d",adjLists[i][j]);
		}
		printf("\n");
	}
}


int main() {
	while (true) {
		int n, m, s, d;

		scanf("%d %d", &n, &m);
		if (n == 0 && m == 0)
			break;

		scanf("%d %d", &s, &d);

		adjLists.assign(n, vector<int>());

		//read all the edges
		for (int i = 0; i < m; ++i) {
			int u, v, p;
			scanf("%d %d %d", &u, &v, &p);
			adjLists[u].push_back(v);
			edges[u][v].cost = p;
		}

		//DEBUG
//		printf("--------------------\n");
//		printf("printing adjlist first time\n");
//		printAdjList(n);

		//first Dijkstra
		priority_queue<priorityData, vector<priorityData>, greater<priorityData> > pq;
		parents.assign(n, vector<int>());
		minCosts.assign(n, INFINITY);

		priorityData pdata;
		pdata.node = s;
		pdata.travelCost = 0;
		pq.push(pdata);

//		printf("=====================\n");
//		printf("executing disktra (1)\n");


		while (!pq.empty()) {


//			printf("\tpopping from queue\n");

			pdata = pq.top();
			pq.pop();
			int node = pdata.node;
			int parent = pdata.parent;
			int travelCost = pdata.travelCost;

//			printf("\t node = %d\n",node);
//			printf("\t parent = %d\n",parent);
//			printf("\t travelCost = %d\n",travelCost);
//			printf("\t minCosts[%d] = %d\n",node,minCosts[node]);

			if (travelCost > minCosts[node])
				continue;
			if (travelCost == minCosts[node]) {
				parents[node].push_back(parent);
				continue;
			}

			if(node != s) parents[node].push_back(parent);
			minCosts[node] = travelCost;
			//printf("\t\t--------\n");
			for (int i = 0; i < (int) adjLists[node].size(); ++i) {
				int child = adjLists[node][i];
				int childCost = travelCost + edges[node][child].cost;
				if (childCost <= minCosts[child]) {
					pdata.travelCost = childCost;
					pdata.parent = node;
					pdata.node = child;
					pq.push(pdata);

					//printf("\t\tchild = %d, childCost = %d\n",child,childCost);

				}
			}
		}

		//printf("=====================\n");

		//remove edges in shortest paths toward the destination
		//DEBUG
		//printf("--------------------\n");
		//printf("removing edges\n");


		queue<int> toDelete;
		toDelete.push(d);
		while (toDelete.size() > 0) {
			int node = toDelete.back();
			toDelete.pop();

			//printf("removing parents of node = %d\n",node);

			for (int i = 0; i < (int) parents[node].size(); ++i) {
				int parent = parents[node][i];
				for (int j = 0; j < (int) adjLists[parent].size(); ++j) {
					if (adjLists[parent][j] == node) {
						adjLists[parent].erase(adjLists[parent].begin() + j);

						//printf("\tparent = %d\n",parent);

						break;
					}
				}
				toDelete.push(parent);
			}
		}

		//DEBUG
		//printf("--------------------\n");
		//printf("printing adjlist second time\n");
//		printAdjList(n);

		//second Dijkstra

		minCosts.assign(n, INFINITY);

		pdata.node = s;
		pdata.travelCost = 0;
		pq.push(pdata);

		while (!pq.empty()) {
			pdata = pq.top();
			pq.pop();
			int node = pdata.node;
			int travelCost = pdata.travelCost;

			if (travelCost > minCosts[node])
				continue;

			minCosts[node] = travelCost;

			for (int i = 0; i < (int) adjLists[node].size(); ++i) {
				int child = adjLists[node][i];
				int childCost = travelCost + edges[node][child].cost;
				if (childCost < minCosts[child]) {
					pdata.travelCost = childCost;
					pdata.parent = node;
					pdata.node = child;
					pq.push(pdata);
				}
			}
		}

		// print result
		if (minCosts[d] != INFINITY)
			printf("%d\n", minCosts[d]);
		else
			printf("-1\n");

	}

	return 0;
}

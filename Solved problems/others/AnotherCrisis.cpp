#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct node {
	int employee;
	int cost;
	bool operator<(const node& x) const
	{
		return cost < x.cost;
	}
};

int n, t;
vector<vector<node> > employee (100001);


int getFileCost(int boss) {
	if(employee[boss].size() == 0)
		return 1;

	for(int i = 0; i < (int)employee[boss].size(); ++i) {
		employee[boss][i].cost = getFileCost(employee[boss][i].employee);
	}

	sort(employee[boss].begin(), employee[boss].end());

	int threshold = ceil((double)employee[boss].size() * (double)t / 100.0);

	int cost = 0;

	for(int i = 0; i < threshold; ++i) {
		cost+= employee[boss][i].cost;
	}

	return cost;
}

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	while(true) {

		scanf("%d %d",&n,&t);
		if(n == 0 && t == 0)
			break;

		employee.assign(n+1,vector<node>());

		node _node;
		for(int i = 1; i <= n; ++i) {
			int boss;
			scanf("%d",&boss);
			_node.employee = i;
			employee[boss].push_back(_node);
		}

		printf("%d\n",getFileCost(0));

	}


	return 0;
}
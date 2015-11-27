#include <cstdio>
#include <vector>
using namespace std;

int N, F;

struct node {
	int cost;
	int index;
	vector<node*> children;
	node* parent;
	bool hasFriends;
};

#define MAXN 100005

node nodes[MAXN];
int costForward[MAXN];
int costBackward[MAXN];

void computeCosts(node* x) {

//	printf("x->index = %d, cost = %d\n", x->index, x->cost);
	if (!x->hasFriends || x->children.empty()) {
		costForward[x->index] = 0;
		costBackward[x->index] = 0;
//		printf("\t_____base case\n");
	} else {
//		printf("\tchildren.size() = %d\n", x->children.size());
		int costbackward = 0;
		for (int i = 0; i < x->children.size(); ++i) {
			node* y = x->children[i];
			if(!y->hasFriends)
				continue;
			computeCosts(y);
			costbackward += costBackward[y->index] + y->cost;
		}
		costBackward[x->index] = costbackward;

		int costforward = costbackward;

		for (int i = 0; i < x->children.size(); ++i) {
			node* y = x->children[i];
			if (!y->hasFriends)
				continue;
			int cf = costbackward + costForward[y->index]
					- costBackward[y->index] - y->cost;
			if (costforward > cf)
				costforward = cf;
		}
		costForward[x->index] = costforward;

//		printf("\tcostforward = %d, costbackward = %d\n", costforward,
//				costbackward);
	}
}

int main() {

	nodes[0].parent = NULL;

	for (int i = 0; i < MAXN; ++i) {
		nodes[i].index = i;
	}

	while (scanf("%d %d", &N, &F) == 2) {

		for (int i = 0; i < N; ++i) {
			nodes[i].children.clear();
			nodes[i].hasFriends = false;
		}

		for (int i = 1; i < N; ++i) {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			a--, b--;
			nodes[a].children.push_back(&nodes[b]);
			nodes[b].parent = &nodes[a];
			nodes[b].cost = c;
		}

		for (int i = 0; i < F; ++i) {
			int f;
			scanf("%d", &f);
			f--;
			node* aux = &nodes[f];
			aux->hasFriends = true;
			while (aux->parent != NULL && !aux->parent->hasFriends) {
				aux = aux->parent;
				aux->hasFriends = true;
			}
		}

		computeCosts(&nodes[0]);
		printf("%d\n", costForward[0]);

	}

	return 0;
}
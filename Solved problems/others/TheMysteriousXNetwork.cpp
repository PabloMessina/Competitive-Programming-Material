#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

#define MAXN 100000
#define INF 1000000000

vector<vii> AdjList(MAXN, vii());
vi dist(MAXN);

int main() {

	 setvbuf(stdout, 0, _IONBF, 0);

	int tests;
	scanf("%d",&tests);
//	printf("tests = %d\n",tests);

	bool first = true;
	while(tests--) {

		int N;
		scanf("%d",&N);
//		printf("N = %d\n",N);

		AdjList.assign(N,vii());

		for(int i = 0; i < N; ++i) {
			int c, n;
			scanf("%d %d",&c, &n);
			for(int j = 0; j < n; ++j) {
				int k;
				scanf("%d",&k);
				AdjList[c].push_back(ii(k,1)); //node and weight
				AdjList[k].push_back(ii(c,1)); //node and weight
			}
		}

		int source, target;
		scanf("%d %d",&source,&target);

		dist.assign(N,INF);
		dist[source] = 0;

		priority_queue<ii,vector<ii>,greater<ii> > pq;
		pq.push(ii(source,0));

		while(!pq.empty()) {
			ii current = pq.top(); pq.pop();
			int u = current.first; //node index
			int d = current.second; //distance
			if(d > dist[u]) continue;
			for(int j = 0; j < (int)AdjList[u].size(); ++j) {
				ii v = AdjList[u][j];
				if (dist[u] + v.second < dist[v.first]) {
					dist[v.first] = dist[u] + v.second;
					pq.push(ii(v.first, dist[v.first]));
				}
			}
		}

		if(first) first = false;
		else printf("\n");
		printf("%d %d %d\n",source,target,dist[target]-1);

	}

	return 0;
}
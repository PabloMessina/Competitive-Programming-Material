// tags: BFS / DFS, diameter of trees, binary search
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
typedef long long int ll;
typedef vector<int> vi;
// -------------------------------
const int MAXN = 40000;
int N1, N2; // numbers of nodes
vector<vi> g1, g2; // graphs (in this problem they are always trees)
int maxdist1[MAXN], maxdist2[MAXN]; // store the distance from each node
// to its farthes node in the graph
ll accsum2[MAXN]; // to accumulate maxdist2 (explained later on)

// find node farthest from starting node 's' using BFS
// (assuming edges have length = 1)
int farthest_from(vector<vi>& g, int s) {
	static int dist[MAXN];
	memset(dist, -1, sizeof(int) * g.size());
	int f = s;
	queue<int> q;
	q.push(s);
	dist[s] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v : g[u]) {
			if (dist[v] == -1) {
				q.push(v);
				dist[v] = dist[u] + 1;
				if (dist[v] > dist[f]) f = v;
			}
		}
	}
	return f;
}

// update maxdist array with the distance from reference node 's' using BFS
void update_maxdist(vector<vi>& g, int* maxdist, int s) {
	static int dist[MAXN];
	memset(dist, -1, sizeof(int) * g.size());
	queue<int> q;
	q.push(s);
	dist[s] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v : g[u]) {
			if (dist[v] == -1) {
				q.push(v);
				dist[v] = dist[u] + 1;
				maxdist[v] = max(maxdist[v], dist[v]); // update if bigger
			}
		}
	}
}

// set the maxdist array for tree 'g' and return its diameter
int set_maxdist_and_get_diameter(vector<vi>& g, int* maxdist) {
	// 1) find the end nodes of a diameter of 'g'
	int e1 = farthest_from(g, 0);
	int e2 = farthest_from(g, e1);
	// 2) fill maxdist array
	memset(maxdist, 0, sizeof(int) * g.size()); // init with 0s
	update_maxdist(g, maxdist, e1); // first update considering distance from e1
	update_maxdist(g, maxdist, e2); // second update considering distance from e2
	// At this point, maxdist has for each node of 'g'
	// its distance to its farthest node, which is either e1 or e2. Why?
	// It turns out this is a property of the extreme nodes of a diameter of a tree :)
	// 3) finally, we return the diameter of 'g', which is exactly the farthest
	// distance from any end node of the diameter
	assert(maxdist[e1] == maxdist[e2]); // this should be true
	return maxdist[e1];
}

int main() {
	while(scanf("%d%d", &N1, &N2) == 2) { // read each case header
		// read and build graphs
		g1.assign(N1, vi());
		g2.assign(N2, vi());
		rep(i,2,N1) {
			int u,v; scanf("%d%d", &u, &v); --u, --v;
			g1[u].push_back(v);
			g1[v].push_back(u);
		}
		rep(i,2,N2) {
			int u,v; scanf("%d%d", &u, &v); --u, --v;
			g2[u].push_back(v);
			g2[v].push_back(u);
		}
		// set maxdist and find diameter for each graph
		int diam1 = set_maxdist_and_get_diameter(g1, maxdist1);
		int diam2 = set_maxdist_and_get_diameter(g2, maxdist2);
		// remember the maximum between both diameters
		int max_diameter = max(diam1, diam2);
		// sort maxdist2 and fill accsum2
		sort(maxdist2, maxdist2 + N2);
		ll acc = 0;
		rep(i,0,N2-1) acc = accsum2[i] = maxdist2[i] + acc;
		// --- tricky part -----
		// IDEA: given node 'u' from 'g1' and node 'v' from 'g2'
		// the diamater of the new tree that results from adding an edge
		// u-v connecting g1 with g2 is either:
		// (1) max_diameter = max {diameter(g1), diameter(g2)}
		// (2) maxdist1[u] + maxdist2[v] + 1
		// So, notice that if we fix 'u', and if we sort all v's by their maxdist's
		// then if there is a v such that (2) > (1), then from that point onwards
		// all v's to the right will make (2) > (1).
		// Therefore, for each 'u' from g1 we can do binary search to find the first
		// 'v' from g2 such that (2) > (1).
		// Then, we can easily compute in O(1) the contribution of all 'u'-pairs 
		// (pairs whose node from g1 is 'u') to the numerator of the answer
		ll totsum = 0;
		rep(u,0,N1-1) {
			int i = 0, j = N2;
			// binary search
			while (i < j) {
				int m = (i+j) >> 1;
				if (maxdist2[m] + maxdist1[u] + 1 > max_diameter) {
					j = m;
				} else {
					i = m+1;
				}
			}
			// add u-pairs contribution to numerator in O(1)
			totsum += (ll)max_diameter * (ll)i;
			if (i < N2) {
				totsum += (N2 - i) * ((ll)maxdist1[u] + 1);
				totsum += accsum2[N2-1];
				if (i > 0) totsum -= accsum2[i-1];
			}
		}
		// print answer
		double ans = (double)totsum/(double)(N1 * N2);
		printf("%.3lf\n", ans);
	}
    return 0;
}
// tags: Dijkstra, Ternary Search
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define MAXN 1000
typedef pair<double, int> pdi;

int N,M;
int A[MAXN][MAXN];
int B[MAXN][MAXN];
vector<vector<int>> g;

// -- Dijkstra --
double mincost[MAXN];
double find_mincost(double t) {
	rep(i,0,N-1) mincost[i] = -1.0;
	priority_queue<pdi, vector<pdi>, greater<pdi>> q;
	q.push(pdi(0, 0));
	mincost[0] = 0;
	while (!q.empty()) {
		pdi curr = q.top(); q.pop();
		double cost = curr.first;
		int u = curr.second;
		if (mincost[u] < cost)
			continue;
		if (u == N-1)
			break;
		for (int v : g[u]) {
			double c = cost + A[u][v] * t + B[u][v];
			if (mincost[v] < -0.5 or mincost[v] > c) {
				mincost[v] = c;
				q.push(pdi(c, v));
			}
		}
	}
	return mincost[N-1];
}

int main() {
	while (scanf("%d%d",&N,&M) == 2) {

		// -- read input and build graph --
		g.assign(N, vector<int>());
		rep(i,1,M) {
			int u,v,a,b; scanf("%d%d%d%d",&u,&v,&a,&b); --u, --v;
			g[u].push_back(v);
			g[v].push_back(u);
			A[u][v] = a;
			A[v][u] = a;
			B[u][v] = b;
			B[v][u] = b;
		}

		// --- ternary search ---
		double left = 0;
		double right = 24 * 60;
		double ans;
		double c1, c2, t1, t2, third;
		int times = 100;
		while (times--) {
			third = (right - left) / 3.0;
			t1 = left + third;
			t2 = right - third;
			c1 = find_mincost(t1);
			c2 = find_mincost(t2);
			if (c1 < c2) {
				left = t1;
			} else if (c1 > c2) {
				right = t2;
			} else {
				left = t1;
				right = t2;
			}
		}

		// -- print answer --
		ans = (c1+c2) * 0.5;
		printf("%.5lf\n", ans);
	}
	return 0;
}
// tags: binary search, union find, disjoint set
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)
#define MAXN 300
typedef long long ll;

struct UnionFind {
	int p[MAXN+2];
	int rank[MAXN+2];	
	void reset(int N) {
		memset(rank, 0, (N+2) * sizeof(int));
		rep(i,0,N+1) p[i] = i;
	}
	int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
	bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
	void unionSet(int i, int j) {
		if (!isSameSet(i, j)) {
			int x = findSet(i), y = findSet(j);
			if (rank[x] > rank[y]) {
				p[y] = x;
			} else {
				p[x] = y;
				if (rank[x] == rank[y]) rank[y]++;
			}
		}
	}
};

int N, W, H;
double R;
int dist2UpperLeft[MAXN];
int dist2LowerRight[MAXN];
ll squareDist[MAXN][MAXN];
struct Coord { int x, y; };
Coord dinCoords[MAXN];
UnionFind uf;
int source, target;

int main() {
	while (true) {
		scanf("%d %d %d", &N, &W, &H);
		if (N == -1) break;
		source = N;
		target = N+1;
		
		// read coordinates
		rep(i,0,N-1) {
			int x, y; scanf("%d %d", &x, &y);
			dinCoords[i] = {x, y};
			// set distances to margins
			dist2UpperLeft[i] = min(x, H - y);
			dist2LowerRight[i] = min(W - x, y);
		}
		// save square distance between each pair of dinosaurs
		rep(i,0,N-2) rep(j,i+1,N-1) {
			ll dx = dinCoords[i].x - dinCoords[j].x;
			ll dy = dinCoords[i].y - dinCoords[j].y;
			ll dist2 = dx * dx + dy * dy;
			squareDist[i][j] = squareDist[j][i] = dist2;
		}

		//================
		// Binary Search
		double minR = 0;
		double maxR = max(W, H);
		double _4R2;
		rep(times, 1, 40) {
			R = (minR + maxR) * 0.5;
			_4R2 = 4 * R * R;

			bool marginsConnected = false;
			uf.reset(N); // reset union-find set
			// upper left vs dinosaurs
			rep(i, 0, N-1) {
				if (dist2UpperLeft[i] >= R) continue; // make sure it's reachable
				if (dist2LowerRight[i] < R) { // optimization: check if it reaches the other margin
					marginsConnected = true;
					goto updateBounds;
				}
				uf.unionSet(source, i);
			}
			// bottom right vs dinousaurs
			rep(i, 0, N-1) {
				if (dist2LowerRight[i] >= R) continue; // make sure it's reachable
				uf.unionSet(target, i);
			}
			// dinosaurs vs dinousaurs
			rep(i,0,N-2) rep(j,i+1,N-1) {
				if (squareDist[i][j] < _4R2) {
					uf.unionSet(i, j);
					if (uf.isSameSet(source, target)) {
						marginsConnected = true;
						goto updateBounds;
					}
				}				
			}
			// update range
			updateBounds:
			if (marginsConnected) maxR = R;
			else minR = R;
		}
		printf("%.3f\n", (minR + maxR) * 0.5);
	}
	return 0;
}
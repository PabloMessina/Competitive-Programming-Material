#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

typedef struct {
	int x;
	int y;
} Coord;

#define MAXN 302
#define SOURCE_NODE 300
#define TARGET_NODE 301

class UnionFind {
private:
	int p[MAXN];
	int rank[MAXN];
public:
	UnionFind() {
	}
	void reset(int N) {
		memset(rank, 0, N * sizeof(int));
		for (int i = 0; i < N; ++i)
			p[i] = i;
		p[SOURCE_NODE] = SOURCE_NODE;
		p[TARGET_NODE] = TARGET_NODE;
	}
	int findSet(int i) {
		return (p[i] == i) ? i : (p[i] = findSet(p[i]));
	}
	bool isSameSet(int i, int j) {
		return findSet(i) == findSet(j);
	}
	void unionSet(int i, int j) {
		if (!isSameSet(i, j)) {
			int x = findSet(i), y = findSet(j);
			if (rank[x] > rank[y])
				p[y] = x;
			else {
				p[x] = y;
				if (rank[x] == rank[y])
					rank[y]++;
			}
		}
	}
};

int N, W, H; //inputs

double R; //radius we will binary search
double _4R2;
int dist2UpperLeft[300];
int dist2LowerRight[300];
long long squareDist[300][300];
Coord dinCoords[300];

//union-find set
UnionFind uf; //dinosaur nodes go from 0 to 299

//compare nodes based on distance from lower right margin
bool CompareByLowerRightDistance(int i, int j) {
//	printf("\nDEBUG: i = %d, j = %d, dist2LowerRight[i] = %d, dist2LowerRight[j] = %d\n",i,j,dist2LowerRight[i],dist2LowerRight[j]);
	return dist2LowerRight[i] < dist2LowerRight[j];
}

//compare nodes based on distance from upper left margin
bool CompareByUpperLeftDistance(int i, int j) {
	return dist2UpperLeft[i] < dist2UpperLeft[j];
}

//compare by distance from a third dinosaur
int currDinIndex;
bool CompareByThirdDinoDistance(int i, int j) {
	return squareDist[currDinIndex][i] < squareDist[currDinIndex][j];
}

typedef bool (*comp)(int, int);

int main() {
	while (true) {
		scanf("%d %d %d", &N, &W, &H);
		if (N == -1)
			break;

		//read coordinates
		for (int i = 0; i < N; ++i) {
			int x, y;
			scanf("%d %d", &x, &y);
			dinCoords[i].x = x;
			dinCoords[i].y = y;

			//set distances to margins
			dist2UpperLeft[i] = min(x, H - y);
			dist2LowerRight[i] = min(W - x, y);
		}

		//save square distance between each pair of dinosaurs
		for (int i = 0; i < N; ++i) {
			for (int j = i; j < N; ++j) {
				long long aux1 = (dinCoords[i].x - dinCoords[j].x);
				long long aux2 = (dinCoords[i].y - dinCoords[j].y);
				long long dist2 = aux1 * aux1 + aux2 * aux2;
				squareDist[i][j] = dist2;
				squareDist[j][i] = dist2;
			}
		}

		//=============================
		//Binary Search

		double minR = 1.0;
		double maxR = min(W, H);

		for (int it = 0; it < 40; ++it) {

			R = (minR + maxR) / 2;
			_4R2 = 4 * R * R;

			//reset union-find set
			uf.reset(N);

			bool marginsConnected = false;

			for (int i = 0; i < N; ++i) {

				if (dist2UpperLeft[i] > R) //make sure it's reachable
					continue;

				if (dist2LowerRight[i] <= R) { //check if it reaches the other margin
					marginsConnected = true;
					goto updateBounds;
				}

				uf.unionSet(SOURCE_NODE, i);
			}

			for (int i = 0; i < N; ++i) {
				if (dist2LowerRight[i] > R) //make sure it's reachable
					continue;

				if (dist2UpperLeft[i] <= R) { //check if it reaches the other margin
					marginsConnected = true;
					goto updateBounds;
				}

				uf.unionSet(TARGET_NODE, i);
			}

			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					if (i == j || squareDist[i][j] > _4R2)
						continue;
					uf.unionSet(i, j);
					if (uf.isSameSet(SOURCE_NODE, TARGET_NODE)) {
						marginsConnected = true;
						goto updateBounds;
					}
				}
			}

			updateBounds: if (marginsConnected)
				maxR = R;
			else
				minR = R;
		}

		printf("%.3f\n", R);

	}
	return 0;
}

//*/

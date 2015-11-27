#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdlib>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
using namespace std;

int K, W;

struct Kid {
	int id;
	set<int> wishes;
};

bool success;
bool visited[200001];
Kid kids[200001];
map<int, int> id2index;
int h[200001], cycle;
bool done[200001];

void dfs(int cur, int prev, int curh) {
//	printf("parent = %d, kid = %d\n", parentID, kid.id);
	if (visited[cur])
		return;
	visited[cur] = true;
	h[cur] = curh;
	Kid& kid = kids[cur];
	for (set<int>::iterator it = kid.wishes.begin(); it != kid.wishes.end();
			++it) {
		int to = *it;
		if (!visited[to])
			dfs(to, cur, curh + 1);
		else if (to != prev && !done[to])
			cycle = curh - h[to] + 1;
	}
	done[cur] = true;
}

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

//	ofstream myfile;
//	myfile.open("example.txt");
//
//
//	for (int cas = 0; cas < 10; ++cas) {
//		int _W = rand() % 100001;
//		int _K = 2 * _W + rand() % (1000000000 - 2 * _W + 1);
//
//		map<int, int> counter;
//		myfile << _K << " " << _W << endl;
//
//		for (int w = 0; w < _W; ++w) {
//			int k1, k2;
//			while (true) {
//				k1 = 1 + rand() % (_K);
//				map<int, int>::iterator it;
//				it = counter.find(k1);
//				if (it == counter.end()) {
//					counter[k1] = 0;
//					break;
//				} else if (it->second < 2)
//					break;
//			}
//			while (true) {
//				k2 = 1 + rand() % (_K);
//				map<int, int>::iterator it;
//				it = counter.find(k2);
//				if (it == counter.end()) {
//					counter[k2] = 0;
//					break;
//				} else if (it->second < 2)
//					break;
//			}
//			counter[k1]++;
//			counter[k2]++;
//			myfile << k1 << " " << k2 << endl;
//		}
//		myfile << endl << endl;
//
//	}
//	myfile << "0 0";
//	myfile.close();

	mainloop: while (true) {

		scanf("%d %d", &K, &W);
		if (K == 0 && W == 0)
			break;

//		printf("K == %d, W == %d", K, W);

		int index = 0;
		id2index.clear();

		success = true;

		for (int i = 0; i < W; ++i) {
			int a, b;
			scanf("%d %d", &a, &b);

			int i1, i2;
			if (id2index.find(a) == id2index.end()) {
				kids[index].id = a;
				kids[index].wishes.clear();
				i1 = id2index[a] = index++;
			} else {
				i1 = id2index[a];
			}
			if (id2index.find(b) == id2index.end()) {
				kids[index].id = b;
				kids[index].wishes.clear();
				i2 = id2index[b] = index++;
			} else {
				i2 = id2index[b];
			}

			Kid& kid1 = kids[i1];
			kid1.wishes.insert(i2);
			if (kid1.wishes.size() > 2) {
				success = false;
			}

			Kid& kid2 = kids[i2];
			kid2.wishes.insert(i1);
			if (kid2.wishes.size() > 2) {
				success = false;
			}
		}

		if (!success) {
			puts("N");
			goto mainloop;
		}

		memset(visited, false, sizeof visited);
		memset(done, false, sizeof done);
		cycle = -1;

		for (int count = index, i = 0; i < count; ++i)
			if (!visited[i])
				dfs(i, -1, 0);

		if (cycle == -1 || cycle == K)
			puts("Y");
		else
			puts("N");

	}

	return 0;
}
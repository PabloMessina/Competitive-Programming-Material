#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,i0,n) for(int i = i0; i < n; ++i)
typedef vector<int> vi;
typedef vector<vi> vii;

int m, p, k;
char volume[50][50][51];
int groupCount;
int shifts[6][3] = {
	{-1, 0, 0},
	{1, 0, 0},
	{0, -1, 0},
	{0, 1, 0},
	{0, 0, -1},
	{0, 0, 1}
};

void dfs(int i, int x, int y, char c) {
	if (0 <= i && i < m && 0 <= x && x < p && 0 <= y && y < k && volume[i][x][y] == c) {
		groupCount++;
		volume[i][x][y] = '*';
		FOR(d,0,6) dfs(i + shifts[d][0], x + shifts[d][1], y + shifts[d][2], c);
	}
}

int main() {
	int _case = 1;
	while(scanf("%d %d %d", &p, &k, &m) == 3) {
		// read layers
		FOR(i,0,m) FOR(x,0,p) scanf("%s",volume[i][x]);
		// collect groups
		vii groups(4);
		FOR(i,0,m) FOR(x,0,p) FOR(y,0,k) {
			char c = volume[i][x][y];
			if (c == '*') continue;
			groupCount = 0;
			dfs(i,x,y,c);
			groups[c-'a'].push_back(groupCount);
		}
		// sort groups
		FOR(i,0,4) sort(groups[i].begin(),groups[i].end());
		// print answer
		if (_case > 1) puts("");
		printf("Case %d:\n",_case);
		for(char c = 'a'; c <= 'd'; ++c) {
			printf("%c",c);
			vi& cgroups = groups[c-'a'];
			if (cgroups.size()) {
				for(int i = cgroups.size() - 1; i >= 0; --i) printf(" %d", cgroups[i]);
			} else {
				printf(" 0");
			}
			puts("");
		}
		_case++;
	}
	return 0;
}
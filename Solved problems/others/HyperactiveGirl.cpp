#include <cstdio>
#include <set>
#include <algorithm>
#include <cstring>
#include <map>
#include <stack>
#include <string>
#include <vector>
using namespace std;

#define MAXN 100
#define MOD 100000000
int M, N;

struct Activity {
	int S;
	int F;
};

Activity activities[MAXN];
int times[2 * MAXN];
map<int, int> time2IndexMap;
int DP[MAXN][2 * MAXN][2 * MAXN];

bool compByS(const Activity& x, const Activity& y) {
	return x.S < y.S;
}

int solve(int i, int ti_1, int ti_2) {
	if (i == N)
		return 0;
	if (ti_2 != -1 && DP[i][ti_1][ti_2] != -1)
		return DP[i][ti_1][ti_2];
	int ans = 0;
	Activity& act = activities[i];
	bool parentCond = (act.S <= times[ti_1] && act.F > times[ti_1]);
	bool gparentCond = (ti_2 == -1) || (act.S > times[ti_2]);
	if (parentCond && gparentCond) {
		if (act.F == M)
			ans++;
		else {
			int next_ti = time2IndexMap[act.F];
			ans += solve(i + 1, next_ti, ti_1);
		}
	}
	ans += solve(i + 1, ti_1, ti_2);
	ans %= MOD;
	if(ti_2 != -1) DP[i][ti_1][ti_2] = ans;
	return ans;
}

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	mainloop: while (true) {
		int i;
		scanf("%d %d", &M, &N);
		if (M == 0 && N == 0)
			break;
		set<int> timesSet;
		for (i = 0; i < N; ++i) {
			int s, f;
			scanf("%d %d", &s, &f);
			activities[i].S = s;
			activities[i].F = f;
			timesSet.insert(s);
			timesSet.insert(f);
		}
		i = 0;
		time2IndexMap.clear();
		for (set<int>::iterator it = timesSet.begin(); it != timesSet.end();
				++it) {
			int t = *it;
			time2IndexMap[t] = i;
			times[i] = t;
			++i;
		}
		if (times[0] > 0 || times[timesSet.size() - 1] < M) {
			puts("0");
			goto mainloop;
		}
		sort(activities, activities + N, compByS);
		memset(DP, -1, sizeof DP);
		printf("%d\n", solve(0, 0, -1));

	}

	return 0;
}
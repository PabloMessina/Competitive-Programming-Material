/**
 * Algorithm used: DP (top-down / memo)
 */
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define FOR(i,i0,n) for(int i = i0; i < n; ++i)
#define INF 1e8

int S,B;
int s_last;
int b_last;
int slots[250];
int balls[125];
int memo[255][125];

int dp(int s_from, int b_from) {
	if (memo[s_from][b_from] != -1)
		return memo[s_from][b_from];

	int b_left = b_last - b_from + 1;
	int s_req = b_left * 2;
	int s_limit = (s_last - s_req + 2 + S) % S;
	int minval;

	if (b_left == 1) {
		minval = INF;
		for (int slot = s_from; slot != s_limit; slot = (slot + 1) % S) {
			int val = balls[b_from] * (slots[slot] + slots[(slot + 1) % S]);
			if (val < minval) minval = val;
		}
	} else {
		int s_next = (s_from + 1) % S;
		minval = balls[b_from] * (slots[s_from] + slots[s_next])
			+ dp((s_from + 2) % S, b_from + 1);
		if (s_next != s_limit) {
			minval = min(minval, dp(s_next, b_from));
		}
	}
	return (memo[s_from][b_from] = minval);
}

int main() {
	while(scanf("%d %d", &S, &B) && S && B) {
		b_last = B - 1;
		FOR(i,0,S) scanf("%d", &slots[i]);
		FOR(i,0,B) scanf("%d", &balls[i]);
		int minval = INF;
		FOR(s,0,S) {
			memset(memo, -1, sizeof memo);
			s_last = (s + S - 1) % S;
			minval = min(minval, dp(s,0));
		}
		printf("%d\n",-minval);
	}
	return 0;
}
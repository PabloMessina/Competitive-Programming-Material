#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i =a; i<=b; ++i)
#define MAXN 100000

typedef pair<int,int> pii;
typedef vector<pii> vii;

int N;
vector<vii> g;
int thresh[MAXN];
int input[MAXN];
bool dead[MAXN];

int survivors() {
	queue<int> q;
	q.push(0);
	dead[0] = true;
	int dcount = 0;	
	while (!q.empty()) {
		int u = q.front(); q.pop();
		dcount++;
		for (pii& p : g[u]) {
			int v = p.first;
			int c = p.second;
			input[v] -= c;
			if (!dead[v] && input[v] < thresh[v]) {
				dead[v] = true;
				q.push(v);
			}
		}
	}
	return N - dcount;
}

int main() {
	scanf("%d", &N);

	g.assign(N,vii());
	memset(dead, 0, sizeof(dead[0]) * N);	
	memset(input, 0, sizeof(input[0]) * N);

	rep(i,0,N-1) {
		int k;
		scanf("%d%d",&thresh[i],&k);
		rep(j,1,k) {
			int s,v;
			scanf("%d%d",&s,&v); --s;
			g[s].push_back({i, v});
			input[i] += v;
		}
	}

	printf("%d", survivors());

	return 0;
}
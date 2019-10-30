#include<bits/stdc++.h>
 
using namespace std;
#define ll long long
 
const int N = 1000005, P = 1000000007;
int r, n, m, now, num, ans[N], h[N], e[N], w[N], pre[N];
bool vis[N];
vector<int> q[N];
void add(int x, int y, int z){ e[++num]=y, w[num]=z, pre[num]=h[x], h[x]=num;}
void Add(int x, int y, int z){
	int last=y;
	while(z>9) add(++now, last, z%10), last=now, z/=10;
	add(x, last, z);
}
int main() {
	scanf("%d%d", &n, &m), now=n;
	for(int i=1; i<=m; ++i){
		int x, y;
		scanf("%d%d", &x, &y);
		Add(x, y, i), Add(y, x, i);
	}
	q[r=1]={1};
	for(int l=1; l<=r; ++l){
		for(int i=0; i<10; ++i){
			vector<int> a;
			for(int u:q[l]) for(int v=h[u]; v; v=pre[v])
				if(w[v]==i && !vis[e[v]])
					vis[e[v]]=1, a.push_back(e[v]),
					ans[e[v]]=(ans[u]*10ll+w[v])%P;
			if(!a.empty()) q[++r]=a;
		}
	}
	for(int i=2; i<=n; ++i) printf("%d\n", ans[i]);
	return 0;
}
// Tags: EdmondsKarp, max-flow, min-cut
#include <cstdio>
#include <vector>
#include <queue>
#include <bitset>
using namespace std;

#define FOR(i,a,b) for(int i=a; i<=b; ++i)
#define MAXV 310
#define INF 1000000000
typedef vector<int> vi;

vector<vi> g;
vi p;
int res[MAXV][MAXV];
int n,m;
int s, t;
int mf, f;

void add_edge(int u, int v, int c) {
  g[u].push_back(v);
  res[u][v] = c;
}

void augment(int v, int minEdge) {
  if (v == s)
    f = minEdge;
  else if (p[v] != -1) {
    augment(p[v], min(minEdge, res[p[v]][v]));
    res[p[v]][v] -= f;
    res[v][p[v]] += f;
  }
}

int main() {
  while (scanf("%d%d", &n, &m), n || m) {
    s = n;
    t = n + 1;
    g.assign(n+2,vi());

    // read preferences
    FOR(i,0,n-1) {
      int pref; scanf("%d", &pref);
      if (pref == 1)
        add_edge(s,i,1), add_edge(i,s,0);
      else 
        add_edge(i,t,1), add_edge(t,i,0);
    }

    // read friendships
    FOR(i,1,m) {
      int u, v; scanf("%d%d",&u,&v); --u, --v;
      add_edge(u, v, 1);
      add_edge(v, u, 1);
    }

    // max flow
    p.assign(n+2, -1);
    mf = 0;
    while (true) {
      f = 0;
      bitset<MAXV> vis; vis[s] = true;
      queue<int> q; q.push(s);
      while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
          if (res[u][v] > 0 && !vis[v]) {
            vis[v] = true, q.push(v), p[v] = u;
            if (v == t) goto endbfs;
          }
        }
      }
      endbfs:
      augment(t, INF);
      if (f == 0) break;
      mf += f;
    }

    printf("%d\n", mf);
  }
  return 0;
}
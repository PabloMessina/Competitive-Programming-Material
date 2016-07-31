// Tags: max flow, edmonds karp

#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <bitset>
using namespace std;

typedef vector<int> vi;

#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define MAXV 300
#define INF 1000000000

int N,Q;
int V;
int sid, tid;
int rid, oid;
inline int pid(int i) { return i + 1; }
inline int aid(int i) { return i + 1 + N; }

vector<vi> g;
int res[MAXV][MAXV];
int res0[MAXV][MAXV];
int mf, f;
vi p;

void augment(int v, int minEdge) {
  if (v == sid) { f = minEdge; return; }
  if (p[v] != -1) {
    augment(p[v], min(minEdge, res[p[v]][v]));
    res[p[v]][v] -= f; res[v][p[v]] += f; 
  }
}

void add_edge(int u, int v, int c) {
  g[u].push_back(v);
  g[v].push_back(u);
  res0[u][v] = c;
  res0[v][u] = 0;
}

int main() {
  int B;
  while (scanf("%d%d",&N,&Q) == 2) {
    sid = 0;
    rid = 1 + N + (N+1) + 5;
    oid = rid + 1;
    tid = oid + 1;
    V = tid + 1;
    g.assign(V, vi());
    memset(res0, 0, sizeof res0);

    FOR(i,0,N-1) {
      // source to parent
      add_edge(sid, pid(i), 1);

      scanf("%d",&B);
      FOR(j, 1, B) {
        int x; scanf("%d", &x);
        // parent to antigent
        add_edge(pid(i), aid(x), 1);
      }
      if (B < N) { // default 0 antigent
        add_edge(pid(i), aid(0), 1);
      }
    }

    // antigents to required/optional
    FOR(x,0,N) {
      add_edge(aid(x), rid, 0);
      add_edge(aid(x), oid, 0);
    }

    // required/optional to target
    add_edge(rid, tid, 0);
    add_edge(oid, tid, 0);

    FOR(i,0,Q-1) {
      // reset initial weights
      memcpy(res, res0, sizeof res0);
      // read query
      scanf("%d",&B);
      FOR(j, 1, B) {
        int x; scanf("%d", &x);
        // antigen to required
        res[aid(x)][rid] = 1;
        // antigen to optional
        res[aid(x)][oid] = N;
      }
      // antigen 0 to optional
      res[aid(0)][oid] = N;
      // required to target
      res[rid][tid] = B;
      // optional to target
      res[oid][tid] = N-B;

      // ================
      // MAX FLOW
      mf = 0;
      while (1) {
        f = 0;
        bitset<MAXV> vis; vis[sid] = true;
        queue<int> q; q.push(sid);
        p.assign(MAXV, -1);
        while (!q.empty()) {
          int u = q.front(); q.pop();
          for (int v : g[u]) {
            if (res[u][v] > 0 && !vis[v]) {
              vis[v] = true, q.push(v), p[v] = u;
              if(v == tid) goto end_bfs;
            }
          }
        }
        end_bfs:
        augment(tid, INF);
        if (f == 0) break;
        mf += f;
      }

      if (mf == N)
        puts("Y");
      else
        puts("N");
    }
  }
  return 0;
}
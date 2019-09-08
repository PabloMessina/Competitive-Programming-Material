// tags: max flow
#include <algorithm>
#include <bitset>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <utility>
using namespace std;
#define FOR(i,a,b) for(int i=a; i<=b; ++i)

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long int ll;

#define MAX_V 700
#define INF 1000000000

int np, nt;
ll speed, maxtime;
vvi adjList;
vi pa;
int res[MAX_V][MAX_V];
int mf, f, s, t;
vector<pair<ll,ll> > taxis;
vector<pair<ll,ll> > persons;

void augment(int v, int minEdge) {
  if (v == s) { f = minEdge; return; }
  if (pa[v] != -1) {
    augment(pa[v], min(minEdge, res[pa[v]][v]));
    res[pa[v]][v] -= f; res[v][pa[v]] += f;
  }
}

inline int manhattan(int p, int t) {
  return abs(persons[p].first - taxis[t].first) 
    + abs(persons[p].second - taxis[t].second);
}

inline int personToId(int p) { return 2 + nt + p; }
inline int taxiToId(int t) { return 2 + t; }

int main() {
  int k;
  s = 0, t = 1;
  scanf("%d", &k);
  while (k--) {
    scanf("%d %d %lld %lld", &np, &nt, &speed, &maxtime);
    
    persons.resize(np);
    taxis.resize(nt);
    adjList.assign(2 + np + nt, vi());
    memset(res, 0, sizeof res);

    ll maxsteps = speed * maxtime / 200;

    ll x, y;
    FOR(i,0,np-1) {
      scanf("%lld %lld",&x,&y), persons[i] = make_pair(x,y);
      int pid = personToId(i);
      adjList[pid].push_back(t);
      adjList[t].push_back(pid);
      res[pid][t] = 1;
    }
    FOR(i,0,nt-1) {
      scanf("%lld %lld",&x,&y), taxis[i] = make_pair(x,y);
      int tid = taxiToId(i);
      adjList[s].push_back(tid);
      adjList[tid].push_back(s);
      res[s][tid] = 1;
    }
    FOR(p,0,np-1) {
      int pid = personToId(p);
      FOR(t,0,nt-1) {
        int d = manhattan(p,t);
        if (d <= maxsteps) {
          int tid = taxiToId(t);
          adjList[tid].push_back(pid);
          adjList[pid].push_back(tid);
          res[tid][pid] = 1;
        }
      }
    }

    mf = 0;
    while (true) {
      f = 0;
      bitset<MAX_V> vis; vis[s] = true;
      queue<int> q; q.push(s);
      pa.assign(MAX_V, -1);
      while (!q.empty()) {
        int u = q.front(); q.pop();
        FOR(j, 0, (int)adjList[u].size() - 1) {
          int v = adjList[u][j];
          if (res[u][v] > 0 && !vis[v]) {
            vis[v] = true, q.push(v), pa[v] = u;
            if (v == t) goto end_bfs;
          }
        }
      }
      end_bfs:
      augment(t, INF);
      if (f == 0) break;
      mf += f;
    } 
    printf("%d\n", mf);
  }
  return 0;
}
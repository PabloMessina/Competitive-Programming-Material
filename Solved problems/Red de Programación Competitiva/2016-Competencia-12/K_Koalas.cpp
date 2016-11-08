// tags: BFS, DFS, DP top down, minimax

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXN 100000

int N,M,P;
int scores[MAXN];
int path_ids[MAXN];
int path_len;
int parent[MAXN];
int treescores[MAXN];
int pathscores[MAXN];
int scoresums[MAXN];

vector<vector<int>> g;

void find_path() {
  memset(parent, -1, sizeof(int)*N);
  queue<int> q;
  q.push(P);
  parent[P] = -2;

  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : g[u]) {
      if (parent[v] == -1) {
        parent[v] = u;
        if (v == M)
          goto outside_loop;
        q.push(v);
      }
    }
  }
  outside_loop:

  int curr = M;
  int i = 0;
  while (true) {
    path_ids[i++] = curr;
    if (curr == P) break;
    curr = parent[curr];
  }
  path_len = i;
}

int dfs(int u, int p) {
  int tot = 0;
  for (int v : g[u]) {
    if (v == p)
      continue;
    tot = max(tot, dfs(v, u));
  }
  tot += scores[u];
  return tot;
}

void find_treescores() {
  rep (i, 0, path_len-1) {
    int score = 0;
    int u = path_ids[i];
    for (int v : g[u]) {
      if (i-1 >= 0 && path_ids[i-1] == v)
        continue;
      if (i+1 < path_len && path_ids[i+1] == v)
        continue;
      score = max(score, dfs(v, u));
    }
    treescores[i] = score;
  }
}

int get_scoresum(int i, int j) {
  if (i == 0) return scoresums[j];
  return scoresums[j] - scoresums[i-1];
}

int maxscores1[MAXN];

int get_maxscore1(int i, int j) {
  if (maxscores1[i] != -1)
    return maxscores1[i];
  int ans;
  if (i+1 <= j-1) {
    ans = max(
      max(treescores[i], pathscores[i+1] + get_maxscore1(i+1, j-1)),
      get_scoresum(i+1, j) + treescores[j]
    );
  } else {
    ans = treescores[i];
    if (i+1 == j) {
      ans = max(ans, pathscores[i+1] + treescores[i+1]);
    }
  }

  return maxscores1[i] = ans;
}

int maxscores2[MAXN];

int get_maxscore2(int i, int j) {
  if (maxscores2[j] != -1)
    return maxscores2[j];
  int ans;
  if (i+1 <= j-1) {
    ans = max(
      max(treescores[j], pathscores[j-1] + get_maxscore2(i+1, j-1)),
      get_scoresum(i, j-1) + treescores[i]
    );
  } else {
    ans = treescores[j];
    if (i == j-1) {
      ans = max(ans, pathscores[j-1] + treescores[j-1]);
    }
  }

  return maxscores2[j] = ans;
}

int maxdiff(int i, int j) {
  if (i + 1 == j) return treescores[i] - treescores[j];
  if (i + 2 == j) {
    return max(
      treescores[i] - max(treescores[j], pathscores[j-1] + treescores[j-1]),
      pathscores[i+1] + treescores[i+1] - treescores[j]
    );
  }

  return max(
    treescores[i] - get_maxscore2(i+1, j),
    pathscores[i+1] - max(
      treescores[j] - get_maxscore1(i+1, j-1),
      pathscores[j-1] - maxdiff(i+1, j-1)
    )
  );
}


int main() {
  while (scanf("%d%d%d",&N,&M,&P) == 3) {
    --M; --P;

    g.assign(N, vector<int>());

    rep(i, 0, N-1) {
      scanf("%d", &scores[i]);
    }
    rep(i,2,N) {
      int u, v; scanf("%d%d",&u,&v); --u; --v;
      g[u].push_back(v);
      g[v].push_back(u);
    }

    find_path();
    find_treescores();

    rep(i, 0, path_len-1) {
      pathscores[i] = scores[path_ids[i]];
    }

    scoresums[0] = pathscores[0];
    rep(i, 1, path_len-1) {
      scoresums[i] = scoresums[i-1] + pathscores[i];
    }

    memset(maxscores1, -1, sizeof(int) * N);
    memset(maxscores2, -1, sizeof(int) * N);
    printf("%d\n", maxdiff(0, path_len-1) + pathscores[0] - pathscores[path_len-1]);
  }

  return 0;
}
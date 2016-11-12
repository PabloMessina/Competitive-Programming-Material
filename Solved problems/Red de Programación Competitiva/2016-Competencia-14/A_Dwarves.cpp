#include <bits/stdc++.h>
#include <tr1/unordered_set>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define umap tr1::unordered_map
typedef long long int ll;
typedef pair<int,int> pii;
typedef tr1::unordered_set<int> useti;

#define MAXN 100000

int n;
int n_nodes;
int ID = 0;
map<string, int> name_to_id;
vector<int> g[MAXN];
int indegree[MAXN];

int get_id(string& name) {
  auto it = name_to_id.find(name);
  if (it == name_to_id.end()) {
    name_to_id[name] = ID++;
    return ID-1;
  }
  return it->second;
}

int main() {
  scanf("%d\n", &n);
  string line, name1, name2, op;
  int id1, id2;

  memset(indegree, 0, sizeof indegree);

  rep(i,0,n-1) {
    getline(cin, line);

    stringstream ss(line);
    getline(ss,name1,' ');
    getline(ss,op,' ');
    getline(ss,name2,' ');

    id1 = get_id(name1);
    id2 = get_id(name2);

    if (op == "<") {
      g[id1].push_back(id2);
      indegree[id2]++;
    } else {
      g[id2].push_back(id1);
      indegree[id1]++;
    }
  }

  n_nodes = ID;

  // printf("n_nodes = %d\n", n_nodes);

  queue<int> q;
  rep(i, 0, n_nodes-1) {
    if (indegree[i] == 0)
      q.push(i);
  }

  int count = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    count++;
    indegree[u] = -1;

    for (int v : g[u]) {
      if (indegree[v] == -1)
        continue;
      if (--indegree[v] == 0) {
        q.push(v);
      }
    }
  }

  if (count == n_nodes) {
    puts("possible");
  } else {
    puts("impossible");
  }

  return 0;
}
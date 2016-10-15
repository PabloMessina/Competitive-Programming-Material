// tags: parse input, bfs

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i <= b; ++i)
#define invrep(i,a,b) for(int i=a; i>= b; --i)

typedef vector<int> vi;

int n;
map<int, vi> g;
map<string,int> name2id;
map<int,string> id2name;
int id;
vector<int> parent;
vector<bool> visited;

void split(string& s, vector<string>& tokens) {
  stringstream ss(s);
  string tok;
  while(getline(ss, tok, ' '))
    tokens.push_back(tok);
}

int get_id(string& name) {
  auto it = name2id.find(name);
  if (it == name2id.end()) {
    id2name[id] = name;
    return name2id[name] = id++;
  }
  return it->second;
}

bool try_find_path(int s, int t) {
  parent.assign(id, -1);
  visited.assign(id, false);
  queue<int> q;
  q.push(s);
  visited[s] = true;
  while(!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : g[u]) {
      if (visited[v])
        continue;
      if (v == t) {
        parent[t] = u;
        return true;
      }
      parent[v] = u;
      visited[v] = true;
      q.push(v);
    }
  }
  return false;
}

int main() {
  scanf("%d\n", &n);

  id = 0;
  string line;
  vector<string> tokens;

  rep(i, 1, n) {
    getline(cin, line);
    tokens.clear();
    split(line, tokens);
    int u = get_id(tokens[0]);
    for (int j = 1; j < tokens.size(); ++j) {
      int v = get_id(tokens[j]);
      g[u].push_back(v);
      g[v].push_back(u);
    }
  }

  getline(cin, line);
  tokens.clear();
  split(line, tokens);

  int s = get_id(tokens[0]);
  int t = get_id(tokens[1]);

  if (try_find_path(s, t)) {
    int x = t;
    vector<int> path;
    while(true) {
      path.push_back(x);
      if (x == s)
        break;
      x = parent[x];
    }
    bool first = true;
    invrep(i, (int)path.size()-1, 0) {
      if (first) first = false;
      else printf(" ");
      printf("%s", id2name[path[i]].c_str());
    }
    puts("");
  } else {
    puts("no route found");
  }

  return 0;
}
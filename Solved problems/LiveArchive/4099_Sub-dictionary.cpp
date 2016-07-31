#include <cstdio>
#include <tr1/unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=a; i<=b; ++i)
typedef vector<int> vi;
typedef vector<vi> vii;

void split(const string& s, vector<string>& tokens) {
  stringstream ss(s);
  string token;
  while(getline(ss, token, ' ')) tokens.push_back(token);
}

int n;
int main() {
  string line;
  while (scanf("%d\n", &n) && n) {
    int id = 0;
    std::tr1::unordered_map<string, int> name2idMap;
    std::tr1::unordered_map<int, string> id2nameMap;
    vii adjList(n);
    vi indegree(n, 0);
    // process each line
    FOR(i,1,n) {
      getline(cin, line);
      vector<string> names;
      split(line, names);
      // collect / define ids
      vi ids;
      for (string& name : names) {
        auto it = name2idMap.find(name);
        if (it == name2idMap.end()) {
          name2idMap[name] = id;
          id2nameMap[id] = name;
          ids.push_back(id);
          id++;
        } else {
          ids.push_back(it->second);
        }
      }
      // add edges
      FOR(j,1,ids.size()-1) {
        adjList[ids[0]].push_back(ids[j]);
        indegree[ids[j]]++;
      }
    }
    // collect nodes with indegree = 0
    queue<int> zeroes;
    FOR(i,0,n-1)
      if (indegree[i] == 0)
        zeroes.push(i);
    // remove with propagation
    while (!zeroes.empty()) {
      int node = zeroes.front(); zeroes.pop();
      for (int next : adjList[node])
        if (--indegree[next] == 0)
          zeroes.push(next);
    }
    // collect remaining nodes
    vector<string> ansNames;
    FOR(i,0,n-1)
      if (indegree[i] > 0)
        ansNames.push_back(id2nameMap[i]);
    // print answer
    sort(ansNames.begin(), ansNames.end());
    printf("%d\n", ansNames.size());
    FOR(i,0,ansNames.size()-1) {
      if (i>0) printf(" ");
      printf(ansNames[i].c_str());
    }
    puts("");
  }
  return 0;
}

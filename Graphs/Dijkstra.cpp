// complexity: (|E| + |V|) * log |V|
#include <bits/stdc++.h>
#define ff first
#define ss second
using namespace std;
typedef pair<int, int> ii;
vector<vector<ii>> g; // graph
int N; // number of nodes
vector<int> mindist; // min distance from source to each node
vector<int> parent; // parent of each node in shortest path from source
void dijkstra(int s) {
    parent.assign(N, -1);
    mindist.assign(N, INT_MAX);
    mindist[s] = 0;
    priority_queue<ii, vector<ii>, greater<ii>> q; // minheap
    q.emplace(0, s);
    while (q.size()) {
        int d, u; tie(d, u) = q.top(); q.pop(); // u = node, d = mindist from s to u
        if (mindist[u] < d) continue; // skip outdated improvements
        for (auto& e : g[u]) {
            if (mindist[e.ff] > d + e.ss) {
                mindist[e.ff] = d + e.ss;
                parent[e.ff] = u;
                q.emplace(mindist[e.ff], e.ff);
            }
        }
    }
}
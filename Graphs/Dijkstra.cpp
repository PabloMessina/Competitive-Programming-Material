// complexity: (|E| + |V|) * log |V|
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii; // (weight, node), in that order

vector<vector<pii>> g; // graph
int N; // number of nodes
vector<int> mindist; // min distance from source to each node
vector<int> parent; // parent of each node in shortest path from source

void dijkstra(int source) {
    parent.assign(N, -1);
    mindist.assign(N, INT_MAX);
    mindist[source] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push(pii(0, source));
    while (!q.empty()) {
        pii p = q.top(); q.pop();
        int u = p.second, dist = p.first;
        if (mindist[u] < dist) continue; // skip outdated improvements
        for (pii& e : g[u]) {
            int v = e.second, w = e.first;
            if (mindist[v] > dist + w) {
                mindist[v] = dist + w;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}
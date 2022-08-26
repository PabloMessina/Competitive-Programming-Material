#include "../c++_template.cpp"
// complexity: (|E| + |V|) * log |V|
int N; // number of nodes
vector<vector<ii>> g; // graph
vector<int> D, P; // D: min distance from source to each node
// P: parent of each node in shortest path from source
void dijkstra(int s) {
    P.assign(N, -1);
    D.assign(N, INT_MAX);
    D[s] = 0;
    priority_queue<ii, vector<ii>, greater<ii>> q; // minheap
    q.emplace(0, s);
    while (q.size()) {
        int d, u; tie(d, u) = q.top(); q.pop(); // u = node, d = mindist from s to u
        if (D[u] < d) continue; // skip outdated improvements
        for (auto& e : g[u]) {
            if (D[e.ff] > d + e.ss) {
                D[e.ff] = d + e.ss;
                P[e.ff] = u;
                q.emplace(D[e.ff], e.ff);
            }
        }
    }
}
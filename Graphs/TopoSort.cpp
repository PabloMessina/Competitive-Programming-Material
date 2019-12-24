#define rep(i,a,b) for(int i = a; i < b; ++i)
// ----------------------------
// option 1: tarjan's algorithm
// ----------------------------
// Note: nodes are sorted in reversed order
vector<vector<int>> g; // graph
int n; // num of nodes
bool vis[MAXN]; // track visited nodes
vector<int> sorted;
void dfs(int u) {
    vis[u] = true;
    for (int v : g[u]) if (!vis[v]) dfs(v);
    sorted.push_back(u);
}
void topo_sort() {  
    memset(vis, false, sizeof(bool) * n);
    sorted.clear(); 
    rep(i,0,n) if (!vis[i]) dfs(i);
}

// ---------------------------
// option 2: Kahn's algorithm
// ---------------------------
vector<int> topoSort(vector<vector<int>>& g) {
    int n = g.size();
    vector<int> indegree(n,0);
    rep(u,0,n) for (int v : g[u]) indegree[v]++;
    queue<int> q;
    int count = 0;
    rep(u,0,n) if (indegree[u] == 0) q.push(u);
    vector<int> sorted;
    sorted.reserve(n);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        sorted.push_back(u);
        for (int v : g[u]) if (--indegree[v] == 0) q.push(v);        
    }
    return sorted;
}
// special variant: check if a directed graph is a DAG
bool isDAG(vector<vector<int>>& g) {
    int n = g.size();
    vector<int> indegree(n,0);
    rep(u,0,n) for (int v : g[u]) indegree[v]++;
    queue<int> q;
    int count = 0;
    rep(u,0,n) if (indegree[u] == 0) q.push(u);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        count++;
        for (int v : g[u]) if (--indegree[v] == 0) q.push(v);        
    }
    return count == n;
}
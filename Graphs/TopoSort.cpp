typedef vector<int> vi;

// ----------------------------
// option 1: tarjan's algorithm
// ----------------------------
// Note: nodes are sorted in reversed order

vector<vi> g; // graph
int n; // num of nodes
bool visited[MAXN]; // track visited nodes
vi sorted;

void dfs(int u) {
    visited[u] = true;
    for (int v : g[u]) {
        if (!visited[v])
            dfs(v);
    }
    sorted.push_back(u);
}

void topo_sort() {  
    memset(visited, false, sizeof(bool) * n);
    sorted.clear(); 
    rep(i,0,n-1)
        if (!visited[i])
            dfs(i);
}

// ---------------------------
// option 2: Kahn's algorithm
// ---------------------------

vector<vi> g;
int n;
vi indegree;
vi sorted;

void compute_indegree() {
    indegree.assign(n, 0);
    rep(u,0,n-1)
        rep(int v : g[u])
            indegree[v]++;
}

void topoSort() {
    sorted.clear();
    compute_indegree();

    queue<int> q;
    rep(i,0,n-1)
        if (indegree[i] == 0)
            q.push(i);
         
    while(!q.empty()) {
        int u = q.front(); q.pop();
        sorted.push_back(u);
        for (int v : g[u]) {
            if(--indegree[v] == 0)
                q.push(v);
        }
    }
}
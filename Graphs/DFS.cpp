#include "../c++_template.cpp"

// =========================
// Depth First Search (DFS)
// =========================
const int MAXN = 1000;
vector<int> g[MAXN];
bool visited[MAXN];
int n;

//recursive
void dfs(int u) {
    visited[u] = true;
    for(int v : g[u]) {
        if(!visited[v]) {
            dfs(v);
        }
    }
}

//recursive, using depth
int depth[MAXN];
void dfs(int u, int d) {
    depth[u] = d;
    for(int v : g[u]) { 
        if(depth[v] == -1) { // not visited yet
            dfs(v, d+1);
        }
    }
}

//iterative
void dfs(int root) {
    stack<int> s;
    s.push(root);
    visited[root] = true;
    while (!s.empty()) {
        int u = s.top(); s.pop();
        for (int v : g[u]) {
            if (!visited[v]) {
                visited[u] = true;
                s.push(v);
            }
        }
    }
}

//-----------------------------
// Finding connected components
//-----------------------------
int count_cc() {
    int count = 0;
    memset(visited, 0, sizeof(bool)*n);
    rep(i,0,n) {
        if (!visited[i]) {
            count++, dfs(i);
        }
    }
    return count;
}

//------------------------------
// Flood Fill
//------------------------------

//explicit graph
const int DFS_WHITE = -1;
vector<int> dfs_num(DFS_WHITE,n);
void floodfill(int u, int color) {
    dfs_num[u] = color;
    for (int v : g[u]) {
        if (dfs_num[v] == DFS_WHITE) {
            floodfill(v, color);
        }
    }
}

//implicit graph
int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const char EMPTY = '*';
int floodfill(int r, int c, char color) {
    if (r < 0 || r >= R || c < 0 || c >= C) return 0; // outside grid
    if (grid[r][c] != EMPTY) return 0; // cannot be colored
    grid[r][c] = color;
    int ans = 1;
    rep(i,0,4) ans += floodfill(r + dirs[i][0], c + dirs[i][1], color);
    return ans;
}
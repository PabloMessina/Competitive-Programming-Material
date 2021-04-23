// -------------------
// Tarjan's Algorithm
// -------------------
//references:
//https://www.youtube.com/watch?v=jFZsDDB0-vo
//https://www.hackerearth.com/practice/algorithms/graphs/articulation-points-and-bridges/tutorial/
//https://www.hackerearth.com/practice/algorithms/graphs/biconnected-components/tutorial/
//http://web.iitd.ac.in/~bspanda/biconnectedMTL776.pdf
#define ff first
#define ss second
typedef pair<int,int> ii;
vector<int> D, L;
vector<vector<int>> g;
stack<ii> s; int root;

void print_and_remove_bicomp(int u, int v) {
    puts("biconnected component found:");
    ii uv(u,v);
    while (true) {
        ii top = s.top(); s.pop();
        printf("(%d, %d)\n", top.ff, top.ss);
        if (top == uv) break;
    }
}

// general version: find everything
int root_children = 0;    
void dfs(int u, int p, int d) { // (node, parent, depth)    
    D[u] = L[u] = d; // u at least can reach itself (ignoring u-p edge)
    for(int v : g[u]) {
        if (v == p) continue; // direct edge to parent -> ignore
        if (D[v] == -1) { // exploring a new, unvisited child node            
            s.emplace(u,v); // add edge to stack
            dfs(v, u, d+1); // explore recursively v's subtree
            // 1) detect articulation points and biconnected components
            if (p == -1) { // 1.1) special case: if u is root
                if (++root_children == 2) {
                    // we detected that root has AT LEAST 2 children
                    // therefore root is an articulation point
                    printf("root = %d is articulation point\n", root);
                }
                // whenever we come back to the root, we just finished
                // exploring a whole biconnected component
                print_and_remove_bicomp(u,v);
            } else if (L[v] >= d) { // 1.2) general case: non-root
                printf("u = %d is articulation point\n",  u);
                // we entered through and came back to an AP,
                // so we just finished exploring a whole biconnected component
                print_and_remove_bicomp(u,v);
            }
            // 2) detect cut edges (a.k.a. bridges)
            if (L[v] > D[u]) {
                printf("(u,v) = (%d, %d) is cut edge\n", u, v);
            }
            // propagate low
            L[u] = min(L[u], L[v]); 
        } else if (D[v] < d) { // back-edge to proper ancestor
            s.emplace(u,v); // add edge to stack
            L[u] = min(L[u], D[v]); // propagate low
        } else { // forward-edge to an already visited descendant
            // => do nothing, because this edge was already considered as a
            // back-edge from v -> u
        }
    }
}

// find cut edges
void dfs(int u, int p, int d) {
    D[u] = L[u] = d;
    for(int v : g[u]) {
        if (v == p) continue;
        if (D[v] == -1) {
            dfs(v, u, d+1);
            if (L[v] > D[u]) printf("(u,v) = (%d, %d) is cut edge\n", u, v);
            L[u] = min(L[u], L[v]); 
        } else L[u] = min(L[u], D[v]);
    }
}

// find articulation points
int root_children = 0;
void dfs(int u, int p, int d) {
    D[u] = L[u] = d;
    for(int v : g[u]) {
        if (v == p) continue;
        if (D[v] == -1) {
            dfs(v, u, d+1);
            if (p == -1) { if (++root_children == 2) printf("root = %d is AP\n", root); }
            else if (L[v] >= d) printf("u = %d is AP\n",  u);
            L[u] = min(L[u], L[v]); 
        } else if (D[v] < d) L[u] = min(L[u], D[v]);
    }
}

// find biconnected components
void dfs(int u, int p, int d) {
    D[u] = L[u] = d;
    for(int v : g[u]) {
        if (v == p) continue;
        if (D[v] == -1) {
            s.emplace(u,v);
            dfs(v, u, d+1);
            if (p == -1 or L[v] >= d) print_and_remove_bicomp(u,v);
            L[u] = min(L[u], L[v]); 
        } else if (D[v] < d) {
            s.emplace(u,v);
            L[u] = min(L[u], D[v]);
        }
    }
}
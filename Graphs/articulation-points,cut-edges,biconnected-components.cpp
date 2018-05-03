//sources:
//https://www.youtube.com/watch?v=jFZsDDB0-vo
//https://www.hackerearth.com/practice/algorithms/graphs/articulation-points-and-bridges/tutorial/
//https://www.hackerearth.com/practice/algorithms/graphs/biconnected-components/tutorial/
//http://web.iitd.ac.in/~bspanda/biconnectedMTL776.pdf
typedef pair<int,int> ii;
const int MAXN = 1000;
int depth[MAXN];
int low[MAXN];
vector<int> g[MAXN];
stack<ii> edge_stack;

void print_and_remove_bicomp(int u, int v) {
    puts("biconnected component found:");
    ii uv(u,v);
    while (true) {
        ii top = edge_stack.top();
        edge_stack.pop();
        printf("(%d, %d)\n", top.first, top.second);
        if (top == uv) break;
    }
}

void dfs(int u, int p, int d) { // (node, parent, depth)
    static num_root_children = 0;    
    depth[u] = d;
    low[u] = d; // u at least can reach itself (ignoring u-p edge)
    for(int v : g[u]) {
        if (v == p) continue; // direct edge to parent -> ignore
        if (depth[v] == -1) { // exploring a new, unvisited child node            
            edge_stack.emplace(u,v); // add edge to stack
            dfs(v, u, d + 1); // explore recursively v's subtree
            // 1) detect articulation points and biconnected components
            if (p == -1) { // 1.1) special case: if u is root
                if (++num_root_children == 2) {
                    // we detected that root has AT LEAST 2 children
                    // therefore root is an articulation point
                    printf("root = %d is articulation point\n", root);
                }
                // whenever we come back to the root, we just finished
                // exploring a whole biconnected component
                print_and_remove_bicomp(u,v);
            } else if (low[v] >= d) { // 1.2) general case: non-root
                printf("u = %d is articulation point\n",  u);
                // we entered through and came back to an AP,
                // so we just finished exploring a whole biconnected component
                print_and_remove_bicomp(u,v);
            }
            // 2) detect cut edges (a.k.a. bridges)
            if (low[v] > depth[u]) {
                printf("(u,v) = (%d, %d) is cut edge\n", u, v);
            }
            // propagate low
            low[u] = min(low[u], low[v]); 
        } else if (depth[v] < d) { // back-edge to proper ancestor
            edge_stack.emplace(u,v); // add edge to stack
            low[u] = min(low[u], depth[v]); // propagate low
        } else { // forward-edge to an already visited descendant
            // => do nothing, because this edge was already considered as a
            // back-edge from v -> u
        }
    }
}


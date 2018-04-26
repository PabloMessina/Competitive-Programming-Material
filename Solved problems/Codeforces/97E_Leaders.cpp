// tags: DFS, articulation points, biconnected components, bicoloration
// recommended reads:
//https://www.hackerearth.com/practice/algorithms/graphs/articulation-points-and-bridges/tutorial/
//https://www.hackerearth.com/practice/algorithms/graphs/biconnected-components/tutorial/
//http://web.iitd.ac.in/~bspanda/biconnectedMTL776.pdf
//http://codeforces.com/blog/entry/55824
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
// -------------------------------

const int MAXN = 100000;
int n, m; 
uset<int> g[MAXN]; // graph modeled as an array of unordered_sets

int color[MAXN]; // color of nodes -> used in bicoloration
int low[MAXN]; // low array, the typical one used to find Articulation Points
int depth[MAXN]; // to store node depths as they are encountered in DFS traversal
stack<ii> edge_stack; // stack of edges, the typical one used to find Biconnected Components
vector<ii> edges_to_remove; // here we store the edges of those biconnected components
// containing at least 1 odd cycle
int COMP_ID; // to assign different IDs to connected components
int comp_before[MAXN]; // which connected component does this node belong to (before edge deletion)
int comp_after[MAXN]; // which connected component does this node belong to (after edge deletion)

// remove from top of the stack all edges of the last biconnected component found
// if the biconnected component has an odd cycle, remember those edges for future deletion
void remove_comp(int u, int v, bool odd) {
    ii uv(u,v);
    while (true) {
        ii top = edge_stack.top();
        edge_stack.pop();
        if (odd) edges_to_remove.push_back(top);
        if (top == uv) break;
    }
}

// * AP = Articulation Point
// First DFS. Here we do many things:
// 1) bi-colorate the whole graph
// 2) assign COMP_IDs to all nodes
// 3) detect biconnected componentes
// 4) particularly, detect  biconnected components with odd cycles
bool dfs_before(int u, int p, int d) {
    comp_before[u] = COMP_ID;        
    depth[u] = d;
    color[u] = d % 2;
    low[u] = d-1; // at least u can reach its parent
    bool u_odd = false;
    for (int v: g[u]) {
        if (v == p) continue; // parent -> ignore
        if (depth[v] == -1) { // exploring a new, unvisited child node
            edge_stack.emplace(u, v); // add edge to stack
            bool v_odd = dfs_before(v, u, d+1);
            if (low[v] >= d) { // u is an AP for subtree rooted at v
                // => remove the top of the stack until the edge (u,v) is encountered
                // because the union of all these edges [(u,v) inclusive] is another
                // biconnected component of the original graph
                // => additionally, if v's biconnected component has an odd-loop, we remember
                // these edges because we will remove them later on
                remove_comp(u, v, v_odd);
            } else { // u is NOT an AP for subtree rooted at v
                // => there is a back-edge from v's subtree connecting to a node above u
                // => due to this back-edge, u and v are in a common loop
                // => u and v are in the same biconnected component
                // => THEREFORE, if v's biconnected component has an odd-loop
                //      THEN u's biconnected component ALSO has an odd-loop (because
                //      they are one and the same biconnected component)
                // => We can safely propagate "oddness"
                u_odd = u_odd or v_odd;
                // And don't forget to propagate low as well
                low[u] = min(low[u], low[v]);
            }
        } else if (depth[v] < d) { // back edge to a proper ancestor
            // => we are in the presence of a loop
            edge_stack.emplace(u, v); // add edge to stack
            low[u] = min(low[u], depth[v]); // update u's low
            if (color[u] == color[v]) { // same colors
                // => this means we were not able to properly bi-colorate
                // the loop we just found
                // => we are in the presence of an ODD loop!
                // => u's biconnected component has an ODD loop
                u_odd = true;
            }
        } else { // forward-edge to an already visited descendant
            // => do nothing, because this edge was already considered as a
            // back-edge from v -> u
        }        
    }
    return u_odd;
}

// Second DFS: here we only assign COMP_IDs to all nodes
// assuming the edges of all biconnected components with odd cycles
// have already been removed
void dfs_after(int u, int p) {
    comp_after[u] = COMP_ID;
    for (int v : g[u]) {
        if (v == p or comp_after[v] != -1) continue;
        dfs_after(v, u);
    }
}

int main() {
    // read and build graph
    scanf("%d%d", &n, &m);
    while(m--) {
        int a, b; scanf("%d%d", &a, &b); --a, --b;
        g[a].insert(b);
        g[b].insert(a);
    }
    // run first DFS
    memset(depth, -1, sizeof(depth[0]) * n);
    COMP_ID = 0;
    rep(u,0,n-1) {
        if (depth[u] == -1) {
            dfs_before(u, -1, 0);
            COMP_ID++;
        }
    }
    // remove edges of biconnected components with odd cyles
    for (auto& e : edges_to_remove) {
        g[e.first].erase(e.second);
        g[e.second].erase(e.first);
    }
    // run second DFS
    memset(comp_after, -1, sizeof(comp_after[0]) * n);
    rep(u,0,n-1) {
        if (comp_after[u] == -1) {
            dfs_after(u, -1);
            COMP_ID++;
        }
    }
    // answer queries
    int q; scanf("%d", &q);
    while (q--) {
        int a, b; scanf("%d%d", &a, &b); --a, --b;
        // case 1) different connected components:
        // => there is no path connecting a and b at all -> trivially NO
        if (comp_before[a] != comp_before[b])
            puts("No");
        // case 2) same connected component BUT different components AFTER edge deletion:
        // => this means ALL paths from "a" to "b" MUST NECESSARILY go through at least
        // 1 biconnected component with an odd cycle. It's not hard to see that if a
        // biconnected component has an odd cycle, then ALL edges within that component
        // are part of an odd cycle (http://codeforces.com/blog/entry/49386?#comment-334100)
        // Hence, we can always modify the PARITY of any path
        // that goes through any such component as we wish. So the answer is YES.
        else if (comp_after[a] != comp_after[b])
            puts("Yes");
        // case 3) same connected component BEFORE and AFTER edge deletion.
        // This means both "a" and "b" lie in the same connected cluster of biconnected components
        // WITHOUT odd cycles. This means all biconnected components are bipartites (only have
        // even length cycles), so no matter how many cycles we use, the parity of any path will
        // never change. Therefore, we can use the DFS bi-coloration to anwer:
        // if different colores -> YES, otherwise -> NO
        else if (color[a] != color[b])
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
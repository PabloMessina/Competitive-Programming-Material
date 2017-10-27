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
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<double, int> pdi;
typedef pair<ll, int> lli;
// -------------------------------

const int MAXM = 10000;
const int MAX_NODES = MAXM * 2;
int M,Q;

int ID = 0;
umap<int,int> num2id;
int get_id(int x) {
    auto it = num2id.find(x);
    if (it == num2id.end())
        return num2id[x] = ID++;
    return it->second;
}

vector<vector<ii>> g(MAX_NODES);
int values[MAX_NODES];

int OFFSET = 10000000;
umap<int,int> key2anomalie;
int get_anomalie(int u, int v) {
    if (u > v) swap(u, v);
    int key = u * MAX_NODES + v;
    return key2anomalie[key];
}
void set_anomalie(int u, int v, int a) {
    if (u > v) swap(u, v);
    int key = u * MAX_NODES + v;
    key2anomalie[key] = a;
}

bfs(int s) {
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& p : g[u]) {
            int v = p.first;
            int a = p.second;
            if (values[v] == INT_MIN) {
                values[v] = a - values[u];
                q.push(v);
            }
        }
    }
}

int depth[MAX_NODES];
int parent[MAX_NODES];
bool dfs(int u, int p, int d) {
    parent[u] = p;
    depth[u] = d;
    for (auto& x : g[u]) {
        int v = x.first;
        if (v == p) continue;
        if (depth[v] == -1) {
            if (dfs(v, u, d+1)) return true;
        } else { // loop found
            if ((d - depth[v]) % 2 == 0) { // odd loop
                // we solve a local equation system and propagate
                // to the whole connected component with BFS
                int val = get_anomalie(u, v);
                int coef = -1;
                while (u != v) {
                    val += coef * get_anomalie(u, parent[u]);
                    coef *= -1;
                    u = parent[u];
                }
                val /= 2;
                values[v] = val;
                bfs(v);
                return true;
            }
        }
    }
    return false;
}

int main() {
    while (true) {
        scanf("%d%d", &M, &Q);
        if (M == 0 and Q == 0) break;

        puts("-----------------");
        printf("M=%d,Q=%d\n",M,Q);

        // reset global variables
        rep(i,0,2*M-1) values[i] = INT_MIN;
        num2id.clear();
        key2anomalie.clear();        
        // build graph and collect trivially assigned nodes
        queue<int> q;
        rep(i,1,M) {
            int x,y,a; scanf("%d%d%d", &x,&y,&a);
            if (x == y) {
                int u = get_id(x);
                values[u] = a;
                q.push(u);
            } else {
                int u = get_id(x);
                int v = get_id(y);
                g[u].emplace_back(v, a);
                g[v].emplace_back(u, a);
                set_anomalie(u, v, a);
            }
            printf("x=%d -> u=%d\n", x, get_id(x));
            printf("y=%d -> u=%d\n", y, get_id(y));
            printf("a = %d\n", a);
            puts("-");
        }
        // propagate from trivially assigned nodes
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto& p : g[u]) {
                int v = p.first;
                int a = p.second;
                if (values[v] == INT_MIN) {
                    values[v] = a - values[u];
                    q.push(v);
                }
            }
        }
        // deduce node values by finding loops of odd length
        memset(depth, -1, sizeof depth);
        memset(parent, -1, sizeof parent);
        rep(u, 0, ID-1) {
            if (depth[u] == -1 and values[u] == INT_MIN) {
                dfs(u, -1, 0);
            }
        }
        // answer queries
        int ID_orig = ID;
        while (Q--) {
            int x, y; scanf("%d%d", &x, &y);
            if (x == y) {
                int u = get_id(x);
                if (u < ID_orig and values[u] != INT_MIN) printf("%d\n", values[u]);
                else puts("*");
            } else {
                int u = get_id(x);
                int v = get_id(y);
                if (u < ID_orig and v < ID_orig and values[u] != INT_MIN and values[v] != INT_MIN) {
                    printf("%d\n", values[u] + values[v]);
                } else {
                    puts("*");
                }
            }
        }
        puts("-");
    }
    return 0;
}
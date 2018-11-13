// ----------------------------------------------
// Travelling Salesman Problem (TSP) - Variant 1
// ----------------------------------------------
// Variant 1: find the minimum cost of visiting all nodes WITHOUT returning to the initial node
// complexity: O(2^N * N)

const int MAXN = 14; // maximum number of nodes in the problem statement
int cost[MAXN][MAXN]; // cost[i][j]: cost to travel from node i to node j

// dp(bitmask, i): find the minimum cost of visiting all nodes indicated by 'bitmask'
// starting from node 'i'.
// 
//   * bitmask: an int whose bits indicate the nodes to be visited next
//      ** if j-th bit in bitmask is 1, the j-th node should be visited
//         else, the j-th node should be ignored
//
//   * i: node we are starting the travel from (i is already visited,
//        so the i-th bit in bitmask should be 0)
int memo[1 << MAXN][MAXN]; // 2^MAXN x MAXN
int dp(int bitmask, int i) {
    // base case 1: nothing visit
    if (bitmask == 0) return 0; 
    // base case 2: problem already solved
    int& ans = memo[bitmask][i];
    if (ans != -1) return ans;
    // general case: try all possible next nodes
    int tmp = INT_MAX;
    for (int j=0, b=1; b <= bitmask; ++j, b <<= 1) {
        if (bitmask & b) {
            assert (i != j);
            tmp = min(tmp, cost[i][j] + dp(bitmask & ~b, j));
        }
    }
    // return best answer
    return ans = tmp;
}

int tsp(int n) {
    memset(memo, -1, sizeof memo);
    int ans = INT_MAX;
    int mask = (1 << n) - 1;
    rep(i, 0, n-1) {
        ans = min(ans, dp(mask & ~(1 << i), i));
    }
    cout << ans << endl;
}

// ----------------------------------------------
// Travelling Salesman Problem (TSP) - Variant 2
// ----------------------------------------------
// find the minimum cost of visiting all nodes RETURNING to the initial node
// complexity: O(2^N * N)

const int MAXN = 14; // maximum number of nodes in the problem statement
int cost[MAXN][MAXN]; // cost[i][j]: cost to travel from node i to node j
int initial_i; // we will use this global variable to remember the initial node

// dp(bitmask, i): find the minimum cost of visiting all nodes indicated by 'bitmask'
// starting from node 'i'.
// 
//   * bitmask: an int whose bits indicate the nodes to be visited next
//      if j-th bit in bitmask is 1, the j-th node should be visited
//
//   * i: node we are starting the travel from (i is already visited,
//        so the i-th bit in bitmask should be 0)
int memo[1 << MAXN][MAXN]; // 2^MAXN x MAXN
int dp(int bitmask, int i) {
    // base case 1: nothing to visit, come back to initial node
    if (bitmask == 0) return cost[i][initial_i];
    // base case 2: problem already solved
    int& ans = memo[bitmask][i];
    if (ans != -1) return ans;
    // general case: try all possible next nodes
    int tmp = INT_MAX;
    for (int j=0, b=1; b <= bitmask; ++j, b <<= 1) {
        if (bitmask & b) {
            assert (i != j);
            tmp = min(tmp, cost[i][j] + dp(bitmask & ~b, j));
        }
    }
    // return best answer
    return ans = tmp;
}

int tsp(int n) {
    initial_i = 0;
    memset(memo, -1, sizeof memo); 
    ans = dp((1 << n) - 2, 0);
    cout << ans << endl;
}
// ----------------------------------
// Travelling Salesman Problem (TSP)
// ----------------------------------
// complexity: O(2^N * N)

const int MAXN = 14; // maximum number of nodes in the problem statement
int cost[MAXN][MAXN]; // cost[i][j]: cost to travel from node i to node j
// make sure cost[i][j] >= 0
int start_index; // OPTIONAL: if you need to remember the start node

// dp(mask, i): find the minimum cost of visiting all nodes indicated by 'mask'
// starting from node 'i'.
//  *** OPTIONAL VARIANT: include the cost of returning back to the start node at the end
// 
//   * mask: an int whose bits indicate the nodes we want to visit
//      ** if j-th bit in mask is 1, the j-th node should be visited
//         else, the j-th node should be ignored
//
//   * i: node we are starting the travel from (i'th bit should be 1 in mask)
int memo[1 << MAXN][MAXN]; // 2^MAXN x MAXN
int dp(int mask, int i) {
    // base case 1: problem already solved
    int& ans = memo[mask][i];
    if (ans != -1) return ans;
    
    // mark i-th node as visited
    int mask2 = mask & ~(1 << i);
    
    // base case 2: nothing else to visit
    if (mask2 == 0) return ans = 0;
    // if (mask2 == 0) return ans = cost[i][start_index]; // <--- if returning back to start

    // general case: try all possible next nodes
    ans = INT_MAX;
    for (int j = 0, tmp=mask2; tmp; ++j, tmp>>=1) {
        if (tmp & 1) ans = min(ans, cost[i][j] + dp(mask2, j));
    }

    // return answer
    return ans;
}

int main() { // usage
    memset(memo, -1, sizeof memo);
    start_index = 0;
    cout << dp((1 << N)-1, start_index); // <-- mincost of visiting all N nodes starting from 0
}
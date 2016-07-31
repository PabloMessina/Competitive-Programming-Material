#include <queue>
#include <stack>
#include <vector>
#define MAXN 1000
vector<int> adjList[MAXN];
bool visited[MAXN];


//iterative
void dfs(int root) {
	stack<int> s;
	s.push(root);
  visited[root] = true;
	while (!s.empty()) {
		int u = s.top();
		s.pop();
		for (int i = 0; i < adjList[u].size(); ++i) {
			int v = adjList[u][i];
			if (visited[v])
				continue;
      visited[u] = true;
			s.push(v);
		}
	}
}

//recursive
void dfs(int u) {
	visited[u] = true;
	for(int i = 0; i < adjList[i].size(); ++i) {
		int v = adjList[u][i];
		if(!visited[v]) 
			dfs(v);
	}
}

//-----------------------------
// Finding connected components
//-----------------------------
int numCC = 0;
memset(visited,false,sizeof visited)
for (int i = 0; i < V; i++)                
  if (!visited[i])          
    printf("Component %d:", ++numCC), dfs(i), printf("\n");   // 3 lines here!
printf("There are %d connected components\n", numCC);

//------------------------------
// Flood Fill
//------------------------------

//explicit graph
#define DFS_WHITE (-1)
vector<int> dfs_num(DFS_WHITE,n);
void floodfill(int u, int color) {
  dfs_num[u] = color;                            // not just a generic DFS_BLACK
  for (int j = 0; j < (int)AdjList[u].size(); j++) {
    int v = AdjList[u][j];
    if (dfs_num[v] == DFS_WHITE)
      floodfill(v, color);
  }
}

//implicit graph
int dr[] = {1,1,0,-1,-1,-1, 0, 1}; // trick to explore an implicit 2D grid
int dc[] = {0,1,1, 1, 0,-1,-1,-1}; // S,SE,E,NE,N,NW,W,SW neighbors
int floodfill(int r, int c, char c1, char c2) { // returns the size of CC
	if (r < 0 || r >= R || c < 0 || c >= C) return 0; // outside grid
	if (grid[r][c] != c1) return 0; // does not have color c1
	int ans = 1; // adds 1 to ans because vertex (r, c) has c1 as its color
	grid[r][c] = c2; // now recolors vertex (r, c) to c2 to avoid cycling!
	for (int d = 0; d < 8; d++)
		ans += floodfill(r + dr[d], c + dc[d], c1, c2);
	return ans; // the code is neat due to dr[] and dc[]
}


//------------------------------
// Topo Sort
//------------------------------

//option 1: tarjan's algorithm

vector<int> topoSort;
void dfs2(int u) {    
  visited[u] = true;
  for (int j = 0; j < (int)AdjList[u].size(); j++) {
    int v = AdjList[u][j];
    if (!visited[v])
      dfs2(v);
  }
  topoSort.push_back(u); //only change with respect to dfs()
} 
//in main
topoSort.clear();
memset(visited, false, sizeof visited);
for (int i = 0; i < V; i++)            // this part is the same as finding CCs
  if (!visited[i])
      dfs2(i);
for (int i = topoSort.size()-1; i >= 0; i--)       // we need to print in reverse order
  printf(" %d", topoSort[i]);          


//option 2: Kahn's algorithm

//pseudo-code
// L ← Empty list that will contain the sorted elements
// S ← Set of all nodes with no incoming edges
// while S is non-empty do
//     remove a node n from S
//     add n to tail of L
//     for each node m with an edge e from n to m do
//         remove edge e from the graph
//         if m has no other incoming edges then
//             insert m into S
// if graph has edges then
//     return error (graph has at least one cycle)
// else 
//     return L (a topologically sorted order)

//c++ version
//Input : adj_list ->Adjacency list; indegree : indegrees of all nodes .....
void topoSort(vii & adj_list,  vi &indegree) {

  queue<int> tsort_queue;  
  vector<int> sorted;     

  for(int i = 0; i < (signed)indegree.size(); i++) 
    if(indegree[i] == 0)
    	tsort_queue.push(i);      
     
  while(!tsort_queue.empty()) {
    int u = tsort_queue.front();
    tsort_queue.pop();
    sorted.push_back(u);
    for(int i = 0; i <  adj_list[u].size(); ++i) {
    	int v = adj_list[u][i];      
      if(--indegree[v] == 0)
        tsort_queue.push(v);
    }
  }

  printf("Top Sorted Order : ");
  for(int i = 0; i < (signed)sorted.size(); i++)
    printf("%d ",sorted[i]);
  printf("\n");
}

/* =============================== */
/* Articulation Points & Cut Edges */
/* =============================== */
vi depth(N,-1);
vi low(N);
vii graph(N,vi());
int rootChildren = 0;

void dfs(int u, int p, int d) { // (node, parent, depth)
  depth[u] = d;
  low[u] = d;
  for(int v : graph[u]) {
    if (v == p) continue; // direct edge to parent is not back edge
    if (depth[v] == -1) {
      if (p == -1 && ++rootChildren > 1) // root
          printf("root = %d is articulation point\n", root);

      dfs(v, u, d + 1);

      if (low[v] >= depth[u] && p != -1)
        printf("u = %d is articulation point\n",  u);

      if (low[v] > depth[u])
        printf("(u,v) = (%d, %d) is cut edge\n", u, v);

      if (low[v] < low[u]) low[u] = low[v];

    } else if (depth[v] < low[u]) {
      low[u] = depth[v];
    }
  }
}



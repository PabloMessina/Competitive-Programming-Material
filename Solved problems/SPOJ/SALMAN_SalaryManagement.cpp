// Algorithms: DFS + segment tree sum + segment tree min
#include <vector>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <queue>
using namespace std;

#define FOR(i,a,b) for(int i=a; i<=b; ++i)

typedef vector<int> vi;
typedef long long int ll;

const ll INF = (ll)1e18;

vector<queue<int>> g;
vector<ll> sal;
vi in;
vi out;

// segment tree
vector<ll> realsal;
vector<ll> sumtree;
vector<ll> mintree;
vector<ll> tree;
vector<ll> lazy;
vector<ll> leaves;

inline int left(int node) { return node << 1; }
inline int right(int node) { return (node << 1) + 1; }

void build_tree(int node, int a, int b) {
  if (a > b) return;
  if (a == b) { // leaf node
    mintree[node] = realsal[a];
    sumtree[node] = realsal[a];
    leaves[node] = 1;
    return;
  }
  int l = left(node), r = right(node);
  build_tree(l, a, (a+b)/2); // left child
  build_tree(r, (a+b)/2+1, b); // left child
  // sum tree
  sumtree[node] = sumtree[l] + sumtree[r];
  // min tree
  mintree[node] = min(mintree[l], mintree[r]);
  // leaves
  leaves[node] = leaves[l] + leaves[r];
}

void update_tree(int node, int a, int b, int i, int j, ll value) {
  if (lazy[node] != 0) {
    mintree[node] += lazy[node];
    sumtree[node] += lazy[node] * leaves[node];
    if (a < b) {
      lazy[left(node)] += lazy[node];
      lazy[right(node)] += lazy[node];
    }
    lazy[node] = 0;
  }

  if (a > b || a > j || b < i)
    return;

  if (a >= i && b <= j) {
    mintree[node] += value;
    sumtree[node] += leaves[node] * value;
    if (a < b) {
      lazy[left(node)] += value;
      lazy[right(node)] += value;
    }
    return;
  }

  int l = left(node), r = right(node);
  update_tree(l, a, (a+b)/2, i, j, value);
  update_tree(r, (a+b)/2+1, b, i, j, value);
  mintree[node] = min(mintree[l], mintree[r]);
  sumtree[node] = sumtree[l] + sumtree[r];
}

enum QuertyType { MIN, SUM };
ll query_tree(QuertyType qt, int node, int a, int b, int i, int j) {
  if (a > b || a > j || b < i)
    return (qt == MIN) ? INF : 0;

  if (lazy[node] != 0) {
    mintree[node] += lazy[node];
    sumtree[node] += lazy[node] * leaves[node];
    if (a < b) {
      lazy[left(node)] += lazy[node];
      lazy[right(node)] += lazy[node];
    }
    lazy[node] = 0;
  }

  if (a >= i && b <= j)
    return (qt == MIN) ? mintree[node] : sumtree[node];

  ll q1 = query_tree(qt, left(node), a, (a+b)/2, i, j);
  ll q2 = query_tree(qt, right(node), (a+b)/2+1, b, i, j);
  ll res = (qt == MIN) ? min(q1, q2) : (q1 + q2);
  return res;
}

int main() {
  setvbuf(stdout, NULL, 0, _IONBF);
  int T, n, Q;
  scanf("%d", &T);
  FOR(caso, 1, T) {
    scanf("%d %d", &n, &Q);
    sal.resize(n);
    g.assign(n, queue<int>());

    FOR(i,0,n-1) {
      int p; scanf("%d %lld", &p, &sal[i]), --p;
      if (p >= 0) g[p].push(i);
    }

    // dfs
    in.resize(n);
    out.resize(n);
    int val = 0;
    stack<int> stck;
    stck.push(0), in[0] = val++;
    while (!stck.empty()) {
      int u = stck.top();
      if (!g[u].empty()) {
        int v = g[u].front(); g[u].pop();
        stck.push(v), in[v] = val++;
      } else {
        stck.pop(); out[u] = val-1;
      }
    }

    // segment trees
    realsal.resize(n);
    sumtree.resize(n*4+5);
    mintree.resize(n*4+5);
    lazy.assign(n*4+5, 0);
    leaves.assign(n*4+5, 0);
    FOR(i,0,n-1) realsal[in[i]] = sal[i];
    build_tree(1,0,n-1);

    printf("Case %d: \n", caso);
    FOR(i,1,Q) {
      int q, v; scanf("%d%d", &q, &v), v--;
      if (q == 1)
        printf("%lld\n", query_tree(SUM, 1, 0, n-1, in[v], out[v]));
      else {
        ll m = query_tree(MIN, 1, 0, n-1, in[v], out[v]);
        if (m > 1000) m = 1000;
        update_tree(1, 0, n-1, in[v], out[v], m);
      }
    }
  }
  return 0;
}
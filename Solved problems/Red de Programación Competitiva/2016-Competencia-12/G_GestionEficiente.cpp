#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a;i<=b;++i)
#define invrep(i,a,b) for(int i=a;i>=b;--i)
typedef pair<int,int> pii;
typedef vector<pii> vii;

struct Node {
  Node* children[2];
  Node() {
    children[0] = NULL;
    children[1] = NULL;
  }
};

int N;
vector<vii> g;
vector<int> D;
Node* root = new Node();

void dfs(int u, int p, int d) {
  D[u] = d;
  for (pii& i : g[u])
    if (i.first != p)
      dfs(i.first, u, d xor i.second);
}

void expand_trie(int bits) {
  Node* curr = root;
  invrep(i,30,0) {
    int b = (bits >> i) & 1;
    if (curr->children[b] == NULL) {
      curr->children[b] = new Node();
    }
    curr = curr->children[b];
  }
}

int find_max(int target) {
  int ans = 0;
  Node* curr = root;
  invrep(i, 30, 0) {
    int b = (target >> i) & 1;
    if (curr->children[b] != NULL) {
      ans |= (1 << i);
      curr = curr->children[b];
    } else if (curr->children[1-b] != NULL) {
      curr = curr->children[1-b];
    } else {
      break;
    }
  }
  return ans;
}

int main() {
  scanf("%d", &N);
  g.assign(N, vii());
  D.resize(N);
  rep(i,2,N) {
    int a, b, c;
    scanf("%d%d%d",&a,&b,&c);
    --a; --b;
    g[a].push_back(pii(b, c));
    g[b].push_back(pii(a, c));
  }

  dfs(0, -1, 0);

  rep (i, 0, N-1)
    expand_trie(D[i]);

  rep (i, 0, N-1)
    printf("%d\n", find_max(D[i] xor INT_MAX));

  return 0;
}
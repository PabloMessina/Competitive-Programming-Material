/**
 * Algorithms used:
 *  DFS + DP (memo)
 */

#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
#define FOR(i,i0,n) for (int i = i0; i < n; ++i)
typedef vector<vector<int> > vii;
typedef vector<int> vi;

struct Range {
  int start;
  int end;
};
Range ranges[1000];

int memo[1000];
int bestChild[1000];

int longestPath(int s, vii& adjList) {
  if (memo[s] != -1) return memo[s];
  int maxLength = 0;
  vi& children = adjList[s];
  FOR(i,0,children.size()) {
    int length = longestPath(children[i], adjList);
    if (length > maxLength) {
      maxLength = length;
      bestChild[s] = children[i];
    }
  }
  return (memo[s] = maxLength + 1);
}

int main() {
  int n;
  while(scanf("%d", &n) && n > 0) {
    vii adjList(n);
    FOR(i,0,n) {
      Range& r = ranges[i];
      scanf("%d %d", &r.start, &r.end);
    }
    FOR(i,0,n) {
      Range& r1 = ranges[i];
      FOR(j,i+1,n) {
        Range& r2 = ranges[j];
        if (r1.end < r2.start) {
          adjList[i].push_back(j);
        } else if (r2.end < r1.start) {
          adjList[j].push_back(i);
        }
      }
    }
    memset(memo, -1, sizeof memo);
    memset(bestChild, -1, sizeof bestChild);
    int maxLength = 0;
    int s;
    FOR(i,0,n) {
      int length = longestPath(i, adjList);
      if (length > maxLength) {
        maxLength = length;
        s = i;
      }
    }
    printf("%d",s+1);
    while((s = bestChild[s]) >= 0) printf(" %d", s+1);
    puts("");
  }
  return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i <= b; ++i)
#define invrep(i,a,b) for(int i=a; i>= b; --i)

char matrix[101][101];
int min_side(int n) {
  int i = 1, j = n;
  while (i < j) {
    int m = (i + j) / 2;
    if (m*m >= n) j = m;
    else i = m+1;
  }
  return i;
}

int main() {
  int n;
  scanf("%d\n", &n);
  string line;
  while(n--) {
    getline(cin, line);
    int k = min_side(line.size());
    int i = 0;
    invrep (c, k-1, 0) {
      rep(r, 0, k-1) {
        if (i < line.size())
          matrix[r][c] = line[i++];
        else
          matrix[r][c] = '*';
      }
    }
    rep(r, 0, k-1) {
      rep(c, 0, k-1) {
        if (matrix[r][c] != '*')
          printf("%c", matrix[r][c]);
      }
    }
    puts("");
  }
  return 0;
}
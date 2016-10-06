#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define invrep(i,a,b) for(int i=a; i>=b; --i)
#define MAXC 100
#define MAXR 100

int R,C;
int sr,sc,tr,tc;
int minr, minc, maxr, maxc;
int board[MAXR][MAXC];
int memo[MAXR][MAXC];

void split(string& s, char delim, vector<string>& tokens) {
  stringstream ss(s);
  string item;
  while(getline(ss, item, delim)) {
    if (item.size())
      tokens.push_back(item);
  }
}

int main() {
  int n; scanf("%d\n", &n);
  string line;
  rep(gb, 1, n) {
    scanf("%d%d\n",&R,&C);

    rep(r, 0, R-1) {
      getline(cin, line);
      vector<string> tokens;
      split(line, ' ', tokens);

      rep(c,0,C-1) {
        // printf("r = %d, tokens[c = %d] = %s\n", r, c, tokens[c].c_str());
        if (tokens[c] == "P") {
          sr = r, sc = c;
          board[r][c] = 0;
        } else if (tokens[c] == "E") {
          tr = r, tc = c;
          board[r][c] = 0;
        } else {
          board[r][c] = atoi(tokens[c].c_str());
        }
      }      
    }

    // bottom-up dp
    memo[tr][tc] = 0;
    invrep(c,tc-1,0) {
      memo[tr][c] = board[tr][c] + memo[tr][c+1];
    }
    invrep(r,tr-1,0) {
      memo[r][tc] = board[r][tc] + memo[r+1][tc];
    } 
    while (--tr >= sr && --tc >= sc) {
      memo[tr][tc] = board[tr][tc] + max(memo[tr+1][tc], memo[tr][tc+1]);
      invrep(c,tc-1,0) {
        memo[tr][c] = board[tr][c] + max(memo[tr][c+1], memo[tr+1][c]);
      }
      invrep(r,tr-1,0) {
        memo[r][tc] = board[r][tc] + max(memo[r+1][tc], memo[r][tc+1]);
      } 
    }
    printf("Game Board #%d: %d\n", gb, memo[sr][sc]);
  }
  return 0;
}
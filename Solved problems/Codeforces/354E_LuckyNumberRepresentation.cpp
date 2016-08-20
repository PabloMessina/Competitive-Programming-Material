// tags: backtracking, pruning, DP (memoization)

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXN 20

typedef long long int ll;

int N;
int sumDigits[MAXN];
int addDigits[6][MAXN];
vector<int> options = {0, 4, 7};

int memo[MAXN][6][50];

inline bool check(int i, int sum) {
  if (i == N-1)
    return (sum == sumDigits[i]);
  else
    return ((sum % 10) == sumDigits[i]);
}

// digit i, addend j, carry sum
int solve(int i, int j, int sum) {
  if (i == N) return true;

  if (memo[i][j][sum] != -1)
    return memo[i][j][sum];

  for (int op : options) {    
    addDigits[j][i] = op;
    sum += op;
    if (j == 5) {
      if (check(i, sum) && solve(i+1, 0, sum / 10) == 1)
        return memo[i][j][sum] = 1;
    } else {
      if (solve(i, j+1, sum))
        return memo[i][j][sum] = 1;
    }
    // backtrack
    sum -= op;
  }
  return memo[i][j][sum] = 0;
}

ll getNum(int i) {
  ll num = 0;
  for (int j = N-1; j >= 0; --j) {
    num = num * 10 + addDigits[i][j];
  }
  return num;
}

int main() {
  int t;
  scanf("%d\n", &t);
  string line;
  while (t--) {
    getline(cin, line);
    N = line.size();
    rep(i,0, N-1) {
      sumDigits[N-1-i] = line[i]-'0';
    }
    memset(memo, -1, sizeof memo);
    if (solve(0,0,0)) {
      rep(i,0,5) {
        if (i) printf(" ");
        printf("%I64d", getNum(i));
      }
      puts("");
    } else {
      puts("-1");
    }
  }
  return 0;
}
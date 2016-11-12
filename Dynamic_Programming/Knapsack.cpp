/* ===================== */
/* Knapsack problem : DP */
/* ===================== */

// --------------------------------------
// VARIANT 1: without reposition of items
// ---------------------------------------

// ---------------------------------
// TOP-DOWN RECURSION (pseudo-code)

function DP(i, c)
  if i == first
    if c >= weight[i] && value[i] > 0 // enough space and worth it
      return value[i]
    else
      return 0
  else
    ans = DP(i-1, c)
    if c >= weight[i] && value[i] > 0 // enough space and worth it
      ans = max(ans, value[i] + DP(i-1, c - weight[i]))
    return ans

// -----------
// BOTTOM-UP

#define MAXN 1000 // max num items
#define MAXC 500 // max capacity
int value[MAXN];
int weight[MAXN];
int memo[MAXC+1]; // 0 ... MAXC
int N, C;

int dp() {
  // first item (i = 0)
  memset(memo, 0, sizeof(memo[0]) * (C+1));
  if (value[0] > 0) { // worth it
    rep (c, weight[0], C) {
      memo[c] = value[0];
    }
  }
  // other items (i = 1 .. N-1)
  rep (i, 1, N-1) {
    if (value[i] > 0) { // worth it
      invrep(c, C, weight[i]) { // <--- REVERSE ORDER !!
        memo[c] = max(memo[c], value[i] + memo[c - weight[i]]);
      }
    }
  }
  return memo[C];
}

// --------------------------------------
// VARIANT 2: with reposition of items
// -------------------------------------

// ---------------------------------
// TOP-DOWN RECURSION (pseudo-code)

function DP(i, c)
  if i == first
    if c >= weight[i] && value[i] > 0 // enough space and worth it
      return value[i]
    else
      return 0
  else
    ans = DP(i-1, c)
    if c >= weight[i] && value[i] > 0 // enough space and worth it
      ans = max(ans, value[i] + DP(i, c - weight[i])) // << i instead of i-1
    return ans

// -----------
// BOTTOM-UP

#define MAXN 1000 // max num items
#define MAXC 500 // max capacity
int value[MAXN];
int weight[MAXN];
int memo[2][MAXC + 1]; // 0 .. MAXC
int N, C;

int dp() {
  // first item (i = 0)
  memset(memo, 0, sizeof(memo[0]) * (C+1));
  if (value[0] > 0) { // worth it
    rep (c, weight[0], C) {
      memo[0][c] = value[0] * (c / weight[0]); // collect it as many times as you can
    }
  }
  // other items (i = 1 .. N-1)
  int prev = 0, curr = 1;
  rep (i, 1, N-1) {
    rep(c, 0, C) { // <--- INCREASING ORDER !!
      if (c >= weight[i] && value[i] > 0) { // if fits in && worth it
        memo[curr][c] = max(
          memo[prev][c], // option 1: don't take it
          value[i] + memo[curr][c - weight[i]] // option 2: take it
        );        
      } else {
        memo[curr][c] = memo[prev][c]; // only option is to skip it
      }
    }
    // update prev, curr
    prev = curr;
    curr = 1-curr;
  }
  return memo[(N-1)&1][C]; // last item + full capacity
}

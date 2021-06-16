int fib(int i) {
    if (i < 2) return i;
    return fib(i-1) + fib(i-2);
}

int memo[1000000];
memset(memo, -1, sizeof memo);
int fib_dp_topdown(int i) { // memoization
    int& ans = memo[i];
    if (ans != -1) return ans;
    if (i < 2) return ans = i;
    return ans = fib_dp_topdown(i-1) + fib_dp_topdown(i-2);
}

const int MAXN = 1000000;
int memo[MAXN + 1];
void init_memo() {
    memo[0] = 0;
    memo[1] = 1;
    for (int k = 2; k <= MAXN; ++k) memo[k] = memo[k-1] + memo[k-2];
}
int fib_dp_bottomup(int i) { return memo[i]; }

int fib_dp_bottomup_o1_memory(int i) {
    if (i < 2) return i;
    int a = 0;
    int b = 1;
    for (int k = 2; k <= i; ++k) { a = a + b; swap(a, b); }
    return b;
}
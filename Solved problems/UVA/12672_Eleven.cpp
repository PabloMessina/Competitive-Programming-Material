// tags: DP, combinatorics, math, modular binomial coefficient
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------

const ll MOD = (ll)1e9 + 7;
int f[10];
ll inline mul(ll x, ll y) { return (x * y) % MOD; }
ll inline add(ll x, ll y) { return (x + y) % MOD; }

// choose(n,k) = choose(n-1,k) + choose(n-1,k-1)
// so we can apply DP to it
ll choose_memo[102][102];
ll choose(int n, int k) {
    ll& ans = choose_memo[n][k];
    if (ans != -1) return ans;
    if (n == k) return ans = 1;
    if (k == 0) return ans = 1;
    if (n < k) return ans = 0;
    return ans = add(choose(n-1, k), choose(n-1, k-1));
}

// dp(i, s, p, n):
//    number of distinct ways of arranging the digits i, i+1, ..., 9
//    (with frequencies f[i], f[i+1], ..., f[9]) such that
//    a total of 'p' digits go to positive positions (even index) and 
//    a total of 'n' digits go to negative positions (odd index) and
//    ((sum of positive digits) - (sum of negative digits)) % 11 == s
ll memo[10][11][52][52];
ll dp(int i, int s, int p, int n) {
    // base case 1: i out of range, if s == 0 return 1, else 0
    if (i == 10) return s == 0;
    // base case 2: already solved
    ll& ans = memo[i][s][p][n];
    if (ans != -1) return ans;
    // base case 3: digit 'i' has frequency 0 -> move to next digit
    if (f[i] == 0) return ans = dp(i+1, s, p, n);
    // general case:
    //   we can partition all possible arrangements as follows:
    //   let mink = max(f[i] - n, 0) be minimum number of 'i's that go to positives
    //   let maxk = min(f[i], p) be maximum number of 'i's that go to positives
    //   Then we can ask this question: how many 'i's go to positives?
    //   we have the following options: k = mink, mink+1, mink+2, ..., maxk
    //   In each case, we send k i's to positives and f[i] - k i's to negatives.
    //   If we send k i's to positives and f[i] - k i's to negatives, then the target sum 's'
    //      now changes to ss(k) = s - ((i * k) - (i * (f[i] - k))  (mod 11)
    //   if we send k i's to positives, we have C(p,k) ways of choosing k positions
    //   from p options and likewise C(n, f[i] - k) ways of choosing f[i] - k positions
    //   from n options.
    //   So, for each k, we have these combinations:
    //      C(p,k) * C(n, f[i]-k) * DP(i+1, ss(k), p-k, n-(f[i]-k))
    //   we add up all these combinations and this is the answer for DP(i,s,p,n)
    int mink = max(f[i] - n, 0);
    int maxk = min(f[i], p);
    ll tmp = 0;
    rep(k,mink,maxk) {
        int ss = (11 + ((s - i * (2 * k - f[i])) % 11)) % 11;
        tmp = add(tmp, mul(mul(choose(p, k), choose(n, f[i] - k)),
            dp(i+1, ss, p - k, n - f[i] + k)));
    }
    return ans = tmp;
}

int main() {
    // faster input/output
    ios::sync_with_stdio(false);
    cin.tie(0);
    // fill choose_memo with -1
    memset(choose_memo, -1, sizeof choose_memo);
    // read input
    string line;
    while (cin >> line) { // for each line
        memset(f, 0, sizeof f); // init with 0s
        for (char c : line) f[c-'0']++; // count digit frequencies
        ll ans = 0;
        int len = line.size();
        int n = len>>1; // half to negatives
        int p = len-n; // rest to positives
        memset(memo, -1, sizeof memo); // fill memo with -1
        ans = dp(0, 0, p, n); // solve problem
        if (f[0] > 0) { // if there are 0's, substract all combinations
            // with leading 0's. We can do that assuming there is a 0
            // fixed at the first position, we substract 1 from f[0] and
            // count all combinations to solve the remaining subproblem.
            // Then we substract that from the original answer.
            memset(memo, -1, sizeof memo);
            f[0]--;
            ans = add(ans, MOD - dp(0, 0, p-1, n));
        }
        cout << ans << '\n'; // print answer
    }
    return 0;
}
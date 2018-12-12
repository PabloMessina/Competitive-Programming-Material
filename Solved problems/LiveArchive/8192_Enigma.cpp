// tags: greedy, backtracking + memoization (DP), modular arithmetics, math
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
int N, M;
string digits;
int modpow10[1000];


// possible(i,mod) = whether it is possible to fill in all missing digits ('?') in suffix[i .. M-1]
// such that suffix[i .. M-1] % N == mod.
// If it is possible, find the smallest number possible.
// Notice the solution to the original problem is given by possible(0,0)
int memo[1000][1000];
int possible(int i, int mod) {
    if (i == M) return mod == 0;
    int& ans = memo[i][mod];
    if (ans != -1) return ans;
    int p = modpow10[M-1-i];
    if (digits[i] != '?') { // no choice
        int val = ((digits[i] - '0') * p) % N;
        return ans = possible(i+1, (mod + N - val) % N);
    }
    int mink = i == 0 ? 1 : 0;
    rep(k, mink, 9) { // greedily try from smallest to largest
        int val = (k * p) % N;
        if (possible(i+1, (mod + N - val) % N)) {
            digits[i] = (char)(k + '0');
            return ans = 1;
        }
    }
    return ans = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while(cin >> digits >> N) {
        M = digits.size();
        memset(memo, -1, sizeof memo);
        modpow10[0] = 1;
        rep(i,1,M-1) modpow10[i] = (modpow10[i-1] * 10) % N;
        if (possible(0, 0)) cout << digits << endl;
        else cout << "*\n";
    }
    return 0;
}
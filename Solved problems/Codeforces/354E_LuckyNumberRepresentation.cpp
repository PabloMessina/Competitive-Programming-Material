// tags: backtracking + memoization, top-down DP
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long int ll;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<double, int> pdi;
typedef pair<ll, int> lli;
// -------------------------------

const int MAXN = 19;
int N;
int sum_digits[MAXN];
int lucky_digits[3] = {0, 4, 7};

int digits[6][MAXN];
int memo[6][MAXN][48];

// try to find a valid assignment of digits to the six numbers assuming that
// - digits d+1, d+2, ..., N-1 for the 6 numbers have been already placed and
//   match correctly the corresponding digits of the sum
// - digit d for numbers 0, 1, ..., n-1  in the current column have been placed too
// - we are standing at number n and digit d in the number/digit matrix
// - we have a propagated sum of carry
int solve(int n, int d, int carry) {
    if (d == -1) { // base case: we already covered the whole number/digit matrix
        return carry == 0;    
    }
    if (memo[n][d][carry] != -1) // base case: subproblem already solved
        return memo[n][d][carry];
    
    if (n == 5) { // special case: last number, we next switch to digit d-1 and number 0
        for (int x : lucky_digits) {
            int c = carry + x;
            if (c % 10 == sum_digits[d] and solve(0, d-1, c/10)) {
                digits[n][d] = x;
                return memo[n][d][carry] = 1;
            }
        }
    } else { // general case: we move to the next number n+1 for the same digit d
        for (int x : lucky_digits) {
            int c = carry + x;
            if (solve(n+1, d, c)) {                
                digits[n][d] = x;
                return memo[n][d][carry] = 1;
            }
        }
    }
    return memo[n][d][carry] = 0;
}

// reconstruct number from n-th row's digits
ll get_num(int n) {
    ll num = 0;
    rep(d,0,N-1) num = num * 10 + digits[n][d];
    return num;
}

int main() {
    int t; scanf("%d\n", &t);
    while (t--) {
        
        // read and save sum digits
        string line; getline(cin, line);
        N = line.size();
        rep(i,0,N-1) sum_digits[i] = line[i] - '0';

        // find solution with backtracking + memoization
        memset(memo, -1, sizeof memo);
        if (solve(0, N-1, 0)) {
            rep(i,0,5) {
                if (i) printf(" ");
                printf("%I64d", get_num(i));
            }
            puts("");
        } else {
            puts("-1");
        }

    }
    return 0;
}
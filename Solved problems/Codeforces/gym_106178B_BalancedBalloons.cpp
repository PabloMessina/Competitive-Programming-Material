// tags: DP, top-down, memoization, counting, math, harmonic sum
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
// Idea: after i people the total is divisible by i, so track the integer AVERAGE a = total / i
// (always in [1, K]) instead of the total. The next contribution x = (i+1)*a' - i*a determines
// the next average a' and vice versa, so counting contribution sequences = counting average
// sequences. 1 <= x <= K becomes
//   ceil((i*a + 1) / (i+1)) <= a' <= floor((i*a + K) / (i+1)),
// a range that always contains a' = a (bring x = a).
//
// Key observation: the range has real length (K-1)/(i+1), so it shrinks as people join.
//   - Once i+1 > K-1 only a' = a fits: the rest is forced, so N (up to 1e9) can be capped at ~K.
//   - Relative to a, the next range is the current one scaled toward a, so if the range is a
//     single value now, it stays a single value forever: return 1 early.
//
// DP: dp(i, a) = number of ways to finish with i people joined and average a.
//   dp(0, 0) is the answer (i*a = 0, so the first range is [1, K])
//   dp(i, a) = sum_{a' = a_min}^{a_max} dp(i+1, a'),  dp(actual_N, a) = 1
// Complexity: ~K*K states, each looping ~(K-1)/(i+1) + 1 values -> ~K^2 ln K ~ 3e7 operations.
int N, K;
int actual_N;
const ll MOD = 998244353;

ll memo[2003][2003]; // memo[i][a]: i <= actual_N <= 2002, a <= K <= 2000
// i = people joined so far, a = current (integer) average, so the total so far is a * i
ll dp(int i, int a) {
    ll& ans = memo[i][a];
    if (ans != -1) return ans;
    if (i == actual_N) return ans = 1; // all N joined, or past ~K people where the rest is forced
    ans = 0;
    int aux;
    // next person brings x = (i+1)*a' - i*a balloons; 1 <= x <= K gives the range of a'
    aux = a * i + 1; // smallest new total (x = 1)
    int a_min = (aux + i) / (i+1); // ceil(aux / (i+1)) = floor((aux + (i+1) - 1) / (i+1))
    aux = a * i + K; // largest new total (x = K)
    int a_max = aux / (i+1); // floor(aux / (i+1))
    assert (a_min <= a_max); // a' = a (x = a) is always valid
    if (a_min == a_max) {
        // later ranges are nested inside this one, so they stay single-valued
        return ans = 1; // from this point on, there is only one way to go
    }
    rep(next_a, a_min, a_max + 1) { // each next_a corresponds to exactly one contribution x
        ans = (ans + dp(i+1, next_a)) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> K;
    // the range of a' has length (K-1)/(i+1), so beyond ~K people every step is forced
    actual_N = min(N, 2002);
    memset(memo, -1, sizeof memo); // every byte 0xFF, so each ll is -1 ("not computed")
    cout << dp(0, 0) << '\n'; // i*a = 0 for any a, so a = 0 just means "no one yet"
    return 0;
}
// tags: dp
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
int N, K;
int actual_N;
const ll MOD = 998244353;

ll memo[2003][2003];
ll dp(int i, int a) {
    ll& ans = memo[i][a];
    if (ans != -1) return ans;
    if (i == actual_N) return ans = 1;
    ans = 0;
    int aux;
    aux = a * i + 1;
    int a_min = (aux % (i+1) == 0) ? aux / (i+1) : aux / (i+1) + 1;
    aux = a * i + K;
    int a_max = aux / (i+1);
    assert (a_min <= a_max);
    if (a_min == a_max) {
        return ans = 1; // from this point on, there is only one way to go
    }
    rep(next_a, a_min, a_max + 1) {
        ans = (ans + dp(i+1, next_a)) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> K;
    actual_N = min(N, 2002);
    memset(memo, -1, sizeof memo);
    cout << dp(0, 0) << '\n';
    return 0;
}
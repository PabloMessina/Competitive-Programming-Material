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

const int MAXN = 50;
const int MAXK = 50;

int memo[MAXN][MAXN][MAXK];

// dp(i,j,k) = the maximum number of prefix sum queries we might need to ask
// to find the exact position of k ones in a binary array of length (j-i+1), assuming
// we make queries optimally but the answers are adversarial.
int dp(int i, int j, int k) {
    assert (i <= j);
    assert (0 <= k && k <= j-i+1);
    if (k == 0) return 0;
    if (k == j-i+1) return 0;
    int &ans = memo[i][j][k];
    if (ans != -1) return ans;
    ans = INT_MAX;
    // Try all possible queries
    rep(m,i,j+1) {
        int worst = -1;
        rep(x,0,k+1) {
            if (x > m-i+1) break;
            if (k-x > j-m) continue;
            worst = max(worst, 1 + dp(i,m,x) + dp(m+1,j,k-x));
        }
        assert (worst != -1);
        ans = min(ans, worst);
    }
    assert (ans != INT_MAX);
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, k; cin >> n >> k;
    memset(memo,-1,sizeof(memo));
    cout << dp(0,n-1,k) << endl;
    return 0;
}
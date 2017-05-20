// tags: DP
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

int M,N;
const int MAXN = 100000;
ll candies[MAXN];
ll memo[MAXN+1];
ll row_max[MAXN+1];

// find maximum total score using DP.
// rule: if score[i] is picked, then score[i-1] and score[i+1] cannot be picked
ll find_max(int n, ll scores[]) {
    memo[n] = 0;
    memo[n-1] = scores[n-1];
    invrep(c,n-2,0) memo[c] = max(scores[c] + memo[c+2], memo[c+1]);
    return memo[0];
}

int main() {
    while(true) {
        scanf("%d%d", &M, &N);
        if (M == 0 and N == 0) break;
        // process each row
        rep(r,0,M-1) {
            // read current row's candies
            rep(c,0,N-1) scanf("%lld", &candies[c]);
            // find current row's maximum with DP
            row_max[r] = find_max(N, candies);
        }
        // find global maximun using row_max as candies
        // of a new row
        row_max[M] = 0;
        printf("%lld\n", find_max(M, row_max));
    }
    return 0;
}
// tags: DP, domain compression
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

int N,M;
ii act[100];
ll memo[100][200];
const ll MOD = 100000000;

// count all the ways to cover the interval [start, M] with minimal subsets
// assuming that we start by placing the i-th activity first.
// we use top-down DP
ll solve(int i, int start) {
    if (memo[i][start] != -1) return memo[i][start];
    if (act[i].second == M) return 1;
    ll count = 0;
    rep(j,i+1,N-1) {
        // make sure that:
        //   1) the next activity does not leave a gap with the i-th activity
        //   2) the next activity does not cover 100% de interval [start, activity_i.end]
        if (start < act[j].first and act[j].first <= act[i].second and act[j].second > act[i].second) {
            count = (count + solve(j, act[i].second)) % MOD;
        }
    }
    return memo[i][start] = count;
}

int main() {
    while (true) {
        scanf("%d%d", &M, &N);
        if (N == 0 and M == 0) break;

        // - read activities (start, end)
        // - insert 0, M and all start's and end's into a set
        set<int> nums;
        nums.insert(0);
        nums.insert(M);
        rep(i,0,N-1) {
            scanf("%d%d", &act[i].first, &act[i].second);
            nums.insert(act[i].first);
            nums.insert(act[i].second);        
        }

        // perform domain compression:
        // - map all original values to smaller values
        // - there are at most 100 * 2 = 200 distinct values
        //   so we can map to the range [0, ..., 199]
        umap<int,int> num2idx;
        int i = 0;
        for (int num : nums) num2idx[num] = i++;
        M = num2idx[M];
        rep(i,0,N-1) {
            act[i].first = num2idx[act[i].first];
            act[i].second = num2idx[act[i].second];
        }

        // sort activities
        sort(act, act + N);

        // reset memo
        rep(i,0,N-1) rep(j,0,M) memo[i][j] = -1;

        // count all the ways to cover the whole range with
        // minimal subset of activities
        ll ans = 0;
        rep(i, 0, N-1) {
            // make sure we add the solutions of subproblems
            // starting from activities that begin exactly at 0
            if (act[i].first > 0) break;
            ans = (ans + solve(i, 0)) % MOD;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
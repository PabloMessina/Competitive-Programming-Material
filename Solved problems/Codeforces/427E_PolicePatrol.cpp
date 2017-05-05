// tags: greedy, ternary search
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long int ll;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<double, int> pdi;
typedef pair<ll, int> lli;

const int MAXN = 1000000;

int n,m;
ll xs[MAXN];
int uniq_idxs[MAXN];
int n_uniq;

ll tot_dist(int i) {
    int idx = uniq_idxs[i];
    ll dist = 0;
    ll ref_x = xs[idx];
    for (int j = 0; j < idx; j+=m) dist += ref_x - xs[j];
    for (int j = n-1; j > idx; j-=m) dist += xs[j] - ref_x;
    return dist * 2;
}

int main() {
    scanf("%d%d", &n, &m);
    n_uniq = 0;
    rep(i,0,n-1) {
        scanf("%I64d", &xs[i]);
        if (i==0 or xs[i] > xs[i-1])
            uniq_idxs[n_uniq++] = i;
    }
    int low = 0, high = n_uniq - 1;
    while (low < high) {
        int mid = (low + high) >> 1;
        ll slope = tot_dist(mid+1) - tot_dist(mid);
        if (slope >= 0) high = mid;
        else low = mid + 1;
    }
    printf("%I64d\n", tot_dist(low));
    return 0;
}
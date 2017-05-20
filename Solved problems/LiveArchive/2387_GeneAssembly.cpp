// tags: DP, binary search, sequence recovery
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

const int MAXN = 1000;
int n;
iii ranges[MAXN]; // store ranges
int memo[MAXN]; // remember subproblem solutions
int _next[MAXN]; // remember index of the next range in the optimal sequence of this subproblem

int main() {
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        // collect triples (start, end, original index)
        rep(i,0,n-1) {
            int a, b;
            scanf("%d%d", &a, &b);
            ranges[i] =  iii(a, b, i+1);
        }
        sort(ranges, ranges + n); // sort the triples

        int best = 0;
        int start;
        invrep(i, n-1, 0) {

            // binary search first range to the right whose start
            // is > the current range's end
            int low = i+1, high = n;            
            while (low < high) {
                int mid = (low + high) >> 1;
                if (get<1>(ranges[i]) < get<0>(ranges[mid])) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            // find the optimal next range with DP
            _next[i] = -1;
            memo[i] = 1;
            rep(j, low, n-1) {
                if (memo[i] < 1 + memo[j]) {
                    memo[i] = 1 + memo[j];
                    _next[i] = j;
                }                
            }
            // check if this range is the current best to
            // start the optimal range sequence
            if (memo[i] > best) {
                best = memo[i];
                start = i;
            }
        }

        // reconstruct and print the optimal range sequence
        int curr = start;
        while(curr != -1) {
            if (curr != start) printf(" ");
            printf("%d", get<2>(ranges[curr]));
            curr = _next[curr];
        }
        puts("");
    }
    return 0;
}
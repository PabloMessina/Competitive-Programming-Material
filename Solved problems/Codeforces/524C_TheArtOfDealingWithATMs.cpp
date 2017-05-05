// tags: greedy, math, implementation
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

const int MAXN = 5000;
int a[MAXN];
int N,K;
uset<int> bills;

int solve(int money) {
    int ans = INT_MAX;
    invrep(i,N-1,0) {
        int x_max = money / a[i];
        if (money % a[i] == 0) {
            if (x_max <= K) ans = min(ans, x_max);
            break;
        } else if (x_max + 1 > K) {
            break;
        }
        invrep(x, x_max, 1) {
            int rest = money - x * a[i];
            rep(y, 1, K - x) {
                if (rest % y == 0 and bills.count(rest / y)) {
                    ans = min(ans, x + y);
                    break;
                }
            }
        }        
    }
    return ans == INT_MAX ? -1 : ans;
}

int main() {
    scanf("%d%d", &N, &K);
    rep(i,0,N-1) scanf("%d", &a[i]), bills.insert(a[i]);
    int q; scanf("%d", &q);
    while (q--) {
        int x; scanf("%d", &x);
        printf("%d\n", solve(x));
    }
    return 0;
}
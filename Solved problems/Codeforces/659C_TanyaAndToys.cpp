// tags: greedy, implementation
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

int n, m;

int main() {
    scanf("%d%d", &n, &m);
    uset<int> old_types;
    rep(i,0,n-1) {
        int x; scanf("%d", &x);
        old_types.insert(x);
    }

    vector<int> new_types;
    for (int k =1;;++k) {
        if (k > m) break;
        if (old_types.count(k)) continue;
        new_types.push_back(k);
        m -= k;
    }

    printf("%d\n", new_types.size());
    bool first = true;
    for (int x : new_types) {
        if (first) {
            printf("%d", x);
            first = false;
        } else {
            printf(" %d", x);
        }
    }
    puts("");
    return 0;
}
// tags: bit, fenwick tree, range query
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

const int MAXR = 100000;

struct BIT {
    int n; vi f;
    BIT (int n) {
        this->n = n;
        this->f.assign(n+1, 0);
    }
    void add(int x, int d) {
        while (x <= n) {
            f[x] += d;
            x += x & -x;
        }
    }
    void range_add(int i, int j, int d) {
        add(i, d); add(j+1, -d);
    }
    int psq(int x) {
        if (x < 1 or x > n)
            return 0;
        int sum = 0;
        while (x > 0) {
            sum += f[x];
            x -= x & -x;
        }
        return sum;
    }
};

int main() {
    BIT ft(MAXR);
    int n; scanf("%d", &n);
    while(n--) {
        // read stem's horizontal coordinates
        int l, r; scanf("%d%d", &l, &r);

        // count all new intersections
        int flowers_left = ft.psq(l);
        int flowers_right = ft.psq(r);
        printf("%d\n", flowers_left + flowers_right);

        // remove intersections to prevent duplicate flowers
        ft.range_add(l,l, -flowers_left);
        ft.range_add(r,r, -flowers_right);
        
        // add 1 (a new potential intersection) to the
        // coordinate range [l+1, r-1]
        if (l + 1 <= r - 1) ft.range_add(l+1, r-1, 1);
    }
    return 0;
}
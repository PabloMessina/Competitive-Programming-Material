// tags: BIT, Fenwick Tree, Range Sum Query
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

struct BIT {
    int n;
    vector<ll> f;
    BIT(int n) {
        this->n = n;
        this->f.assign(n+1, 0);
    }
    void add(int x, ll d) {
        while (x <= n) {
            f[x] += d;
            x += x & -x;
        }
    }
    ll psq(int x) {
        ll sum = 0;
        while (x) {
            sum += f[x];
            x -= x & -x;
        }
        return sum;
    }
    ll rsq(int i, int j) {
        return psq(j) - psq(i-1);
    }
};

int main() {
    int n; scanf("%d", &n);
    BIT ft(n);
    rep(i,1,n) {
        int a; scanf("%d", &a);
        ft.add(i, a);
    }
    int q; scanf("%d\n", &q);
    while(q--) {
        char c = getchar();
        if (c == 'q') {
            int l, r; scanf("%d%d\n", &l, &r);
            printf("%lld\n", ft.rsq(l, r));
        } else {
            int i, x; scanf("%d%d\n", &i, &x);
            ft.add(i, x);
        }
    }
    return 0;
}
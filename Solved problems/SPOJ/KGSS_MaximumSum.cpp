// tags: segment tree, maximum sum
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

struct ST {
    int n;
    vi arr;
    vi leaf;
    vector<ii> tree;

    int inline left(int u) { return u << 1; }
    int inline right(int u) { return (u << 1) + 1; }

    ST(int n) {
        this->n = n;
        this->arr.resize(n);
        this->leaf.resize(n);
        this->tree.resize(4*n+5);
    }

    ii merge(ii& a, ii& b) {
        int vals[4] = {a.first, a.second, b.first, b.second };
        sort(vals, vals + 4);
        return ii(vals[2], vals[3]);
    }

    void build(int u, int i, int j) {
        if (i == j) {
            leaf[i] = u;
            tree[u] = ii(arr[i],0);
        } else {
            int lu = left(u), ru = right(u), m = (i+j)/2;
            build(lu, i, m);
            build(ru, m+1, j);
            tree[u] = merge(tree[lu], tree[ru]);
        }
    }

    void update(int i, int newval) {
        arr[i] = newval;
        int u = leaf[i];
        tree[u] = ii(newval, 0);
        u >>= 1;
        while (u) {
            int lu = left(u), ru = right(u);
            tree[u] = merge(tree[lu], tree[ru]);
            u >>= 1;
        }
    }

    ii query(int a, int b, int u, int i, int j) {
        if (i > b or j < a)
            return ii(0,0);
        if (a <= i and j <= b)
            return tree[u];
        int lu = left(u), ru = right(u), m = (i+j)/2;
        ii lq = query(a, b, lu, i, m);
        ii rq = query(a, b, ru, m+1, j);
        return merge(lq, rq);
    }

    ii query(int a, int b) {
        return query(a, b, 1, 0, n-1);
    }
};

int main() {
    int n, q;
    scanf("%d", &n);
    ST st(n);
    rep(i,0,n-1) scanf("%d", &st.arr[i]);
    st.build(1,0,n-1);
    scanf("%d\n", &q);
    while (q--) {
        if (getchar() == 'U') {
            int i, x; scanf("%d%d\n", &i, &x); --i;
            st.update(i, x);
        } else {
            int x, y; scanf("%d%d\n", &x, &y); --x, --y;
            ii ans = st.query(x, y);
            printf("%d\n", ans.first + ans.second);
        }
    }
    return 0;
}
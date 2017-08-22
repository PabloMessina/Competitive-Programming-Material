// tags: binary tree / segment tree, bitwise operations
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

enum { OR, XOR };
struct ST {
    vector<unsigned int> arr;
    vector<unsigned int> tree;
    vector<int> op;
    vector<int> leaf;
    int n;

    ST(int n) {
        this->n = n;
        arr.resize(n);
        leaf.resize(n);
        tree.resize(4*n+5);
        op.resize(4*n+5);        
    }

    inline int left(int u) { return u << 1; }
    inline int right(int u) { return (u << 1) + 1; }

    void build(int u, int i, int j) {
        if (i == j) {
            tree[u] = arr[i];
            op[u] = XOR;
            leaf[i] = u;            
        } else {
            int lu = left(u), ru = right(u), m = (i+j)/2;
            build(lu, i, m);
            build(ru, m+1, j);
            int type = 1 - op[lu];
            tree[u] = (type == OR) ? (tree[lu] | tree[ru]) : (tree[lu] ^ tree[ru]);
            op[u] = type;
        }
    }

    void update(int i, unsigned int newval) {
        int u = leaf[i];
        arr[i] = newval;
        tree[u] = newval;
        u >>= 1;
        while (u) {
            int lu = left(u), ru = right(u);
            tree[u] = (op[u] == OR) ? (tree[lu] | tree[ru]) : (tree[lu] ^ tree[ru]);
            u >>= 1;            
        }
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    n = 1 << n;    
    ST st(n);
    rep(i,0,n-1) scanf("%u", &st.arr[i]);
    st.build(1,0,n-1);
    while (m--) {
        int p; unsigned int b; scanf("%d %u", &p, &b); --p;
        st.update(p, b);
        printf("%u\n", st.tree[1]);
    }
    return 0;
}
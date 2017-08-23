// tags: modular arithmetics, segment tree
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

ll B, P;
int L, N;
ll B_power[100001];

struct Node {
    ll val;
    int start;
    int end;
};

struct ST {
    vector<Node> tree;
    vector<ll> arr;
    vector<int> leaf;
    int n;

    int inline left(int u) { return u << 1; }
    int inline right(int u) { return (u << 1) + 1; }

    void build(int u, int i, int j) {
        tree[u].val = 0;
        tree[u].start = i;
        tree[u].end = j;
        if (i == j) {
            leaf[i] = u;
        } else {
            int lu = left(u), ru = right(u), m = (i+j)/2;
            build(lu, i, m);
            build(ru, m+1, j);
        }
    }

    void update(int i, ll v) {
        ll old_v = arr[i];
        arr[i] = v;
        int u = leaf[i];        
        tree[u].val = v;

        u >>= 1;
        
        while (u) {
            tree[u].val = (tree[u].val + (B_power[tree[u].end - i] * (v - old_v + P)) % P ) % P;
            u >>= 1;
        }
    }

    ll query(int a, int b, int u, int i, int j) {
        if (i > b or j < a) {
            return -1;
        }
        if (a <= i and j <= b) {
            return tree[u].val;
        }
        
        int lu = left(u), ru = right(u), m = (i+j)/2;
        ll lq = query(a, b, lu, i, m);
        ll rq = query(a, b, ru, m+1, j);
        if (lq == -1) return rq;
        if (rq == -1) return lq;
        int exp = min(tree[ru].end, b) - tree[lu].end;
        ll ans = (rq + (B_power[exp] * lq) % P) % P;
        return ans;
    }

    ST(int n) {
        this->n = n;
        tree.resize(4*n+5);
        arr.assign(n, 0);
        leaf.resize(n);
        build(1, 0, n-1);
    }
};

int main() {

    while(true) {

        scanf("%lld %lld %d %d\n", &B, &P, &L, &N);

        if (B == 0 and P == 0 and L == 0 and N == 0)
            break;
    
        B_power[0] = 1;
        rep(i, 1, L-1) B_power[i] = (B * B_power[i-1]) % P;
    
        ST st(L);
    
        while(N--) {
            if (getchar() == 'E') {
                int i, v; scanf("%d%d\n", &i, &v); --i;
                st.update(i, v);
            } else {
                int i, j; scanf("%d%d\n", &i, &j); --i, --j;
                printf("%lld\n", st.query(i,j,1,0,L-1));
            }
        }
        puts("-");
    }

    return 0;
}
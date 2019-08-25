// tags: segment tree, bitwise operations
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
template<class node> struct ST {
    vector<node> t; int n;
    ST(vector<node> &arr) {
        n = arr.size();
        t.resize(n*2);
        copy(arr.begin(), arr.end(), t.begin() + n);
        for (int i = n-1; i > 0; --i)
            t[i] = node(t[i<<1], t[i<<1|1]);
    }
    void set_point(int p, const node &value) {
        for (t[p += n] = value; p > 1; p >>= 1)
            t[p>>1] = node(t[p], t[p^1]);
    }
    node query(int l, int r) {
        node ansl, ansr;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) ansl = node(ansl, t[l++]);
            if (r&1) ansr = node(t[--r], ansr);
        }
        return node(ansl, ansr);
    }
};
enum { OR, XOR };
struct Node {
    int x, kind;
    Node() { kind = -1; }
    Node(int x) : x(x), kind(OR) {}
    Node(const Node& l, const Node& r) {
        if (l.kind == -1) { x = r.x, kind = r.kind; return; }
        if (r.kind == -1) { x = l.x, kind = l.kind; return; }
        if (l.kind == OR) {
            x = l.x | r.x;
            kind = XOR;
        } else {
            x = l.x ^ r.x;
            kind = OR;
        }
    }
};
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<Node> arr;
    n = 1 << n;
    rep(i,1,n) { int x; cin >> x; arr.emplace_back(x); }
    ST<Node> st(arr);
    while (m--) {
        int p, b; cin >> p >> b; --p;
        st.set_point(p, Node(b));
        cout << st.query(0, n).x << '\n';
    }
    return 0;
}
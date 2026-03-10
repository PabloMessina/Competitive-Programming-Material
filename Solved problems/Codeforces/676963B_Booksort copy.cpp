// tags: implementation, greedy, segment tree
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i) // [a, b), inclusive-exclusive
#define invrep(i,b,a) for(int i = b; i >= a; --i) // [b, a], inclusive-inclusive
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
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
    // 0-indexed
    void set_point(int p, const node &value) {
        for (t[p += n] = value; p > 1; p >>= 1)
            t[p>>1] = node(t[p], t[p^1]);
    }
    // inclusive exclusive, 0-indexed
    node query(int l, int r) {
        node ansl, ansr;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) ansl = node(ansl, t[l++]);
            if (r&1) ansr = node(t[--r], ansr);
        }
        return node(ansl, ansr);
    }
};

struct Node {
    int i, v;
    Node() {i = -1; v = INT_MIN; }
    Node(int i, int v) : i(i), v(v) {}
    Node(const Node& a, const Node& b) {
        if (a.v < b.v) {
            i = b.i;
            v = b.v;
        } else {
            i = a.i;
            v = a.v;
        }
    }
};

signed main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    vector<int> A(N);
    rep(i,0,N) cin >> A[i];
    vector<ii> commands;
    vector<Node> nodes(N);
    rep(i,0,N) nodes[i] = Node(i, A[i]);
    ST<Node> st(nodes);
    for (int i = N-1; i > 0; --i) {
        while (true) {
            Node q = st.query(0, i);
            // cout << "q.i: " << q.i << ", q.v: " << q.v << ", i: " << i << '\n';
            // assert (q.i < i);
            if (A[q.i] > A[i]) {
                commands.eb(q.i+1, i+1);
                int sum = A[q.i] + A[i];
                A[q.i] = sum / 2;
                A[i] = sum - A[q.i];
                st.set_point(q.i, Node(q.i, A[q.i]));
            } else {
                break;
            }
        }
    }
    cout << commands.size() << '\n';
    for (auto& c : commands) cout << c.first << ' ' << c.second << '\n';
    return 0;
}
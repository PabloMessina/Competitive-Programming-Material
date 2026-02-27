// tags: geometry, math, quadratic equation, segment tree, sweep line, coordinate compression
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
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
int N;
const int MAXN = 1e5 + 5;
ll A, B;
ll M[MAXN], C[MAXN];

double EPS = 1e-12;

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
    int count;
    Node() { count = 0; }
    Node(int count) : count(count) {}
    Node(const Node& a, const Node& b) { count = a.count + b.count; }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> A >> B;
    vector<pair<double,double>> intervals;
    vector<double> x_values;
    rep(i,0,N) {
        cin >> M[i] >> C[i];
        ll a = A;
        ll b = -M[i];
        ll c = B - C[i];
        ll delta = b*b - 4*a*c;
        if (delta > 0) {
            double sqrt_delta = sqrt(delta);
            double start = (double)(-b - sqrt_delta) / (double)(2*a);
            double end = (double)(-b + sqrt_delta) / (double)(2*a);
            intervals.emplace_back(start, end);
            x_values.push_back(start);
            x_values.push_back(end);
        }
    }
    sort(x_values.begin(), x_values.end());
    umap<double,int> x2i;
    int id = 0;
    rep(i,0,x_values.size()) {
        if (i > 0 and abs(x_values[i] - x_values[i-1]) > EPS) id++;
        x2i[x_values[i]] = id;
    }
    vector<pair<int,int>> int_intervals;
    for (auto& p : intervals) {
        int_intervals.emplace_back(x2i[p.first], x2i[p.second]);
    }
    if (int_intervals.empty()) {
        cout << "0\n";
        return 0;
    }
    sort(int_intervals.begin(), int_intervals.end());
    vector<Node> nodes(id+1);
    ST<Node> st(nodes);
    ll count = 0;
    int i = 0;
    while (i < int_intervals.size()) {
        int j = i;
        while (j+1 < int_intervals.size() and int_intervals[j+1].first == int_intervals[i].first) ++j;
        rep(k,i,j+1) {
            int inbetween_count = st.query(int_intervals[k].first+1, int_intervals[k].second).count;
            count += inbetween_count;
        }
        rep(k,i,j+1) {
            int x = int_intervals[k].second;
            st.set_point(x, Node(st.query(x, x+1).count + 1));
        }
        i = j+1;
    }
    cout << count << '\n';
    return 0;
}
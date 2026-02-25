// tags: segment tree, fractions, binary search, sweep line, implementation
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
int N, S;
ll K;
const int MAXN = 1e5 + 5;
ll H[MAXN], L[MAXN], U[MAXN];

template<typename T> struct Fraction {
    T x, y; // x / y
    Fraction() : x(0), y(1) {}
    Fraction(T x_, T y_) : x(x_), y(y_) {
        if (y < 0) x = -x, y = -y;
        simplify();
    }
    bool operator<(const Fraction& o) const { return x * o.y < y * o.x; }
    bool operator==(const Fraction& o) const { return x * o.y == y * o.x; }
    bool operator<=(const Fraction& o) const { return x * o.y <= y * o.x;}
    Fraction operator+(const Fraction& o) const {
        Fraction ans = {x * o.y + y * o.x, y * o.y};
        ans.simplify();
        return ans;
    }
    Fraction operator-(const Fraction& o) const {
        Fraction ans = {x * o.y - y * o.x, y * o.y};
        ans.simplify();
        return ans;
    }
    Fraction operator*(const Fraction& o) const {
        Fraction ans = {x * o.x, y * o.y};
        ans.simplify();
        return ans;
    }
    void simplify() {
        T g = __gcd(x, y);
        x /= g;
        y /= g;
    }
};

struct Event {
    int type; // 0: start, 1: end
    Fraction<ll> r; // price per hour rate
    int cid; // id of the cleaner
    Event(int type, Fraction<ll> r, int cid) : type(type), r(r), cid(cid) {}
    bool operator<(const Event& o) const { return tie(r, type) < tie(o.r, o.type);}
};
enum Kind { START, END };

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

// Range Sum
struct Node {
    ll streets, hours;
    Node() { streets = 0, hours = 0; }
    Node(ll streets, ll hours) : streets(streets), hours(hours) {}
    Node(const Node& a, const Node& b) { 
        streets = a.streets + b.streets;
        hours = a.hours + b.hours;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> S >> K;
    vector<Event> events;
    rep(i,0,N) {
        cin >> H[i] >> L[i] >> U[i];
        events.emplace_back(START, Fraction<ll>(L[i], H[i]), i);
        events.emplace_back(END, Fraction<ll>(U[i], H[i]), i);
    }
    sort(events.begin(), events.end());
    int max_h = *max_element(H, H+N);
    vector<Node> nodes(max_h+1);
    ST<Node> st(nodes);
    Fraction<ll> min_cost;
    bool possible = false;
    for (auto& e : events) {
        int cid = e.cid;
        int h = H[cid];
        if (e.type == START) {
            Node old_node = st.query(h, h+1);
            Node new_node(old_node.streets + (K / h), old_node.hours + (K / h) * h);
            st.set_point(h, new_node);
            int l = 1, r = max_h+1;
            while (l < r) {
                int m = (l+r) >> 1;
                if (st.query(0, m+1).streets >= S) r = m;
                else l = m+1;
            }   
            if (l < max_h+1) { // it is possible to clean all the streets
                Node before_node = st.query(0, l);
                ll streets_before = before_node.streets;
                ll hours_before = before_node.hours;
                ll delta_streets = S - streets_before;
                ll total_hours = hours_before + delta_streets * l;
                Fraction<ll> cost = Fraction<ll>(e.r.x * total_hours, e.r.y);
                if (!possible || cost < min_cost) {
                    possible = true;
                    min_cost = cost;
                }
            }
        } else {
            Node old_node = st.query(h, h+1);
            Node new_node(old_node.streets - (K / h), old_node.hours - (K / h) * h);
            assert (new_node.streets >= 0);
            assert (new_node.hours >= 0);
            st.set_point(h, new_node);
        }
    }
    if (possible) cout << min_cost.x << ' ' << min_cost.y << '\n';
    else cout << "*\n";
    return 0;
}
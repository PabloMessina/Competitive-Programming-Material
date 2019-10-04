// tags: geometry, straight line equation hashing, counting,
// modular inverse, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
const ll MOD = 1000000007;
int N;
struct Point {
    ll x, y; 
    bool operator<(const Point& o) const {
        if (x == o.x) return y < o.y;
        return x < o.x;
    }
};

inline ll mul(ll x, ll y) { return (x * y) % MOD; }
inline ll add(ll x, ll y) { return (x + y) % MOD; }
inline ll mod(ll x, ll m) { return ((x %= m) < 0) ? x+m : x; }

ll gcdext(ll a, ll b, ll& x, ll& y) {
    ll r2, x2, y2, r1, x1, y1, r0, x0, y0, q;
    r2 = a, x2 = 1, y2 = 0;
    r1 = b, x1 = 0, y1 = 1;
    while (r1) {
        q = r2 / r1;
        r0 = r2 % r1;
        x0 = x2 - q * x1;
        y0 = y2 - q * y1;
        r2 = r1, x2 = x1, y2 = y1;
        r1 = r0, x1 = x0, y1 = y0;        
    }
    ll g = r2; x = x2, y = y2;
    if (g < 0) g = -g, x = -x, y = -y;
    return g;
}

ll mulinv(ll a, ll m) {
    ll x, y;
    if (gcdext(a, m, x, y) == 1) return mod(x, m);
    return -1;
}

tuple<ll,ll,ll> hash_line(const Point& p1, const Point& p2) {
    ll a = p1.y - p2.y;
    ll b = p2.x - p1.x;
    ll c = p1.x * (p2.y - p1.y) - p1.y * (p2.x - p1.x);
    ll sgn = (a < 0 or (a == 0 and b < 0)) ? -1 : 1;
    ll g = __gcd(abs(a), __gcd(abs(b), abs(c))) * sgn;
    return make_tuple(a/g, b/g, c/g);
}

pair<ll,ll> hash_slope(const Point& p1, const Point& p2) {
    ll dx = p2.x - p1.x;
    ll dy = p2.y - p1.y;
    ll sgn = (dx < 0 or (dx == 0 and dy < 0)) ? -1 : 1;
    ll g = __gcd(abs(dx), abs(dy)) * sgn;
    return {dx/g, dy/g};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;    
    vector<Point> pts(N);
    map<Point, int> pt2f;
    rep(i,0,N-1) {
        cin >> pts[i].x >> pts[i].y;
        pt2f[pts[i]]++;
    }
    
    vector<ll> fact(N + 1);
    fact[0] = 1;
    rep(i, 1, N) fact[i] = mul(i, fact[i-1]);
    
    ll default_ways = 1;
    for (auto& p : pt2f) {
        default_ways = mul(default_ways, fact[p.second]);
    };

    map<pair<ll,ll>, map<tuple<ll,ll,ll>, set<Point>>> m;
    for (auto it1 = pt2f.begin(); it1 != pt2f.end(); ++it1) {
        const Point& p1 = it1->first;
        for (auto it2 = next(it1); it2 != pt2f.end(); ++it2) {
            const Point& p2 = it2->first;
            auto slope_hash = hash_slope(p1, p2);
            if (slope_hash.first > 0 and slope_hash.second < 0) {
                auto line_hash = hash_line(p1, p2);
                auto& tmp = m[slope_hash][line_hash];
                tmp.insert(p1);
                tmp.insert(p2);
            }
        }
    }

    ll ways;
    int n_slopes = m.size();
    if (n_slopes == 0) {
        ways = default_ways;
    } else {
        ways = 0;
        for (auto& i : m) {
            ll tmp = default_ways;
            for (auto& j : i.second) {
                int count = 0;
                for (const Point& pt : j.second) {
                    int f = pt2f[pt];
                    count += pt2f[pt];
                    tmp = mul(tmp, mulinv(fact[f], MOD));
                }
                tmp = mul(tmp, fact[count]);
            }
            ways = add(ways, tmp);
        }
        if (n_slopes >= 2) {
            ways = add(ways, MOD - mul(n_slopes - 1, default_ways));
        }
    }
    cout << ways << '\n';
    return 0;
}
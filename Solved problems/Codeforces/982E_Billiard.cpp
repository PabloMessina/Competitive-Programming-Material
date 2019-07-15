// tags: linear congruence equation, 
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
typedef long long int ll;

ll inline mod(ll x, ll m) { return ((x %= m) < 0) ? x+m : x; }

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
    if (g < 0) g = -g, x = -x, y = -y; // make sure g > 0
    return g;
}

// linear congruence equation: a*x = b (mod m)
bool lincongeq(ll a, ll b, ll m, ll& x) {
    a = mod(a,m);
    b = mod(b,m);    
    ll s, t;
    ll g = gcdext(a,m,s,t);
    if (b % g == 0) {
        ll bb = b/g;
        ll mm = m/g;
        ll n = -s*bb/mm;
        x = s*bb + n*mm;
        if (x < 0) x += mm;
        return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    ll w, h, x0, y0, vx, vy;
    cin >> w >> h >> x0 >> y0 >> vx >> vy;
    ll a, b, k;
    ll xf, yf, t_min = LLONG_MAX;
    if (vx != 0) {
        ll hsteps20, hsteps2w;
        if (vx > 0) {
            hsteps20 = 2*w-x0;
            hsteps2w = w-x0;
        } else {
            hsteps20 = x0;
            hsteps2w = x0+w;
        }
        // 1) x = x0 + 2wk + hsteps20 = 0 (mod 2w)
        //----------------------------------------
        // 1.1) y0 + vy*(2wk + hsteps20) = 0 (mod 2h)
        // => (vy*2w) * k = -y0 - vy*hsteps20 (mod 2h)
        a = vy*2*w;
        b = -y0 - vy*(hsteps20);
        if (lincongeq(a, b, 2*h, k)) {
            ll t = 2*w*k + hsteps20;
            if (t_min > t) { t_min = t; xf = 0, yf = 0; }
        }
        //----------------------------------------
        // 1.2) y0 + vy*(2wk + hsteps20) = h (mod 2h)
        // => (vy*2*w) * k = h - y0 - vy*hsteps20
        a = vy*2*w;
        b = h - y0 - vy*(hsteps20);
        if (lincongeq(a, b, 2*h, k)) {
            ll t = 2*w*k + hsteps20;
            if (t_min > t) { t_min = t; xf = 0, yf = h; }
        }

        // 2) x = x0 + 2wk + hsteps2w = w (mod 2w)
        //----------------------------------------
        // 2.1) y0 + vy*(2wk + hsteps2w) = 0 (mod 2h)
        // => (vy*2w) * k = -y0 - vy*(hsteps2w) (mod 2h)
        a = vy*2*w;
        b = -y0 - vy*(hsteps2w);
        if (lincongeq(a, b, 2*h, k)) {
            ll t = 2*w*k + hsteps2w;
            if (t_min > t) { t_min = t; xf = w, yf = 0; }
        }
        //----------------------------------------
        // 2.2) y0 + vy*(2wk + hsteps2w) = h (mod 2h)
        // => (vy*2*w) * k = h - y0 - vy*(hsteps2w)
        a = vy*2*w;
        b = h - y0 - vy*(hsteps2w);
        if (lincongeq(a, b, 2*h, k)) {
            ll t = 2*w*k + hsteps2w;
            if (t_min > t) { t_min = t; xf = w, yf = h; }
        }
    } else if ((x0 == 0 or x0 == w) and vy != 0) { // vx == 0
        t_min = 0;
        xf = x0;
        yf = vy > 0 ? h : 0;
    }
    if (t_min == LLONG_MAX) {
        cout << "-1\n";
    } else {
        cout << xf << ' ' << yf << '\n';
    }
    return 0;
}
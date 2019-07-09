// tags: CRT, implementation, number theory, modular arithmetic, math
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a; i<=b; ++i)
using namespace std;
typedef long long int ll;

int B,Z;
int cur_zoo[10];
int next_zoo[10][100];
int cycle_index[10][100];
int zoo_count[100];
ll remainders[10];
ll cycle_size[10];

ll inline mod(ll x, ll m) { return ((x %= m) < 0) ? x+m : x; }
ll inline mult(ll x, ll y, ll m) { return (x * y) % m; }
ll inline add(ll x, ll y, ll m) { return (x + y) % m; }

void xgcd(ll a, ll b, ll& g, ll& x, ll& y) {
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
    g = r2, x = x2, y = y2;
}

ll CRT(ll* r, ll* m, int n) {
    // assert (n > 1);
    ll r1 = r[0], m1 = m[0];
    rep(i,1,n-1) {
        ll r2 = r[i], m2 = m[i];
        ll g, x, y; xgcd(m1, m2, g, x, y);
        if ((r1 - r2) % g != 0) return -1; // no solution
        ll z = m2/g;
        ll lcm = m1 * z;
        ll sol = add(mod(r1, lcm), m1*mult(mod(x,z),mod((r2-r1)/g,z),z), lcm);
        r1 = sol;
        m1 = lcm;
    }
    // rep(i,0,n-1) assert (r1 % m[i] == r[i]);
    return r1;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> B >> Z;
    rep(i,0,B-1) {
        cin >> [i];
        cur_zoo[i]--;
        rep(j,0,Z-1) {
            cin >> next_zoo[i][j];
            next_zoo[i][j]--;
        }
    }
    rep(t,0,Z) {        
        // check if everyone is in the same zoo
        int tmp = cur_zoo[0];
        bool same = true;
        rep(i,1,B-1) {
            if (cur_zoo[i] != tmp) {
                same = false; break;
            }
        }
        if (same) {
            cout << tmp+1 << ' ' << t << '\n';
            return 0;
        }        
        if (t == Z) break;
        // move every bear one step further
        rep(i,0,B-1) {
            cur_zoo[i] = next_zoo[i][cur_zoo[i]];
        }
    }
    // find cycles for each bear
    memset(cycle_index, -1, sizeof cycle_index);
    memset(zoo_count, 0, sizeof zoo_count);
    rep(i,0,B-1) {
        int u = cur_zoo[i];
        int index = 0;
        while (cycle_index[i][u] == -1) {
            zoo_count[u]++;
            cycle_index[i][u] = index++;
            u = next_zoo[i][u];
        }
        cycle_size[i] = index;
    }
    // use CRT to find the answer
    ll t_min = LLONG_MAX;
    int z_min = -1;
    rep(z,0,Z-1) {
        if (zoo_count[z] == B) {
            rep(i,0,B-1) {
                remainders[i] = cycle_index[i][z];
                // assert (remainders[i] != -1);
            }
            ll t = CRT(remainders, cycle_size, B);
            if (t != -1 and t < t_min) {
                t_min = t;
                z_min = z;
            }
        }
    }
    if (z_min != -1) {
        cout << (z_min+1) << ' ' << (t_min+Z) << '\n';
    } else {
        cout << "*\n";
    }
    return 0;
}
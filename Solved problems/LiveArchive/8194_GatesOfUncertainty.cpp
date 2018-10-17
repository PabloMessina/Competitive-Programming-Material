// tags: DP, modular arithmetics, math
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------

const int MAXN = (int)1e5 + 1;
int N;
ll MOD = (ll)1e9 + 7;
struct Gate {
    int x, y, f;
} gates[MAXN];

inline ll mod(ll x) { return x % MOD; }
inline ll mul(ll x, ll y) { return mod(x*y); }
inline ll add(ll x, ll y) { return mod(x+y); }

ll memo[MAXN][2][2];
// number of value assignments (mod 1e9+7) so that node i
// should output u (theory) but instead outputs v (reality)
ll dp(int i, int u, int v) {
    ll& ans = memo[i][u][v];
    if (ans != -1) return ans;
    if (i == 0) return ans = (u == v);
    Gate& gate = gates[i];
    ll a = dp(gate.x, 0, 0); // x c0
    ll b = dp(gate.x, 0, 1); // x i1
    ll c = dp(gate.x, 1, 0); // x i0
    ll d = dp(gate.x, 1, 1); // x c1
    ll e = dp(gate.y, 0, 0); // y c0
    ll f = dp(gate.y, 0, 1); // y i1
    ll g = dp(gate.y, 1, 0); // y i0
    ll h = dp(gate.y, 1, 1); // y c1
    ll tmp = 0;    
    if (gate.f == -1) { // normal        
        /* c0 */if (u == 0 && v == 0) tmp = mul(d,h);
        /* i1 */if (u == 0 && v == 1) tmp = mod(mul(d,g)+mul(c,h)+mul(c,g));
        /* i0 */if (u == 1 && v == 0) tmp = mod(mul(b,h)+mul(b,f)+mul(d,f));
        /* c1 */if (u == 1 && v == 1) tmp = mod(mul(a, e+f+g+h) + mul(b,e+g) + mul(d,e) + mul(c,e+f));
    } else if (gate.f == 0) { // stuck 0
        /* c0 */if (u == 0 && v == 0) tmp = mul(c+d,g+h);
        /* i0 */if (u == 1 && v == 0) tmp = mod(mul(a+b, e+f+g+h) + mul(c+d,e+f));
    } else { // stuck 1
        /* i1 */if (u == 0 && v == 1) tmp = mul(c+d,g+h);
        /* c1 */if (u == 1 && v == 1) tmp = mod(mul(a+b, e+f+g+h) + mul(c+d,e+f));
    }
    return ans = tmp;
}

int main() {
    while (cin >> N) {
        rep(i,1,N) {
            Gate& g = gates[i];
            cin >> g.x >> g.y >> g.f;
        }
        memset(memo, -1, sizeof memo);
        cout << add(dp(1,0,1),dp(1,1,0)) << endl;
    }
    return 0;
}
// TODO: finish this
// #pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;

ll N; int R,K;
ll cur_pos[200];
ll start_pos[200];
ll acc[200][201];
bool sick[200];
ll t_sick[200];

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
    if (g < 0) g = -g, x = -x, y = -y;
    // for debugging (in case you think you might have bugs)
    assert (g == a * x + b * y);
    assert (g == __gcd(abs(a),abs(b)));
    assert (g >= 0);
}

// a * x = b (mod m)
ll lincongeq__first_nonneg(ll a, ll b, ll m) {
    assert (m > 0);
    a %= m; b %= m;
    if (a == 0) return b == 0 ? 0 : -1;
    if (b == 0) return 0;
    ll g, x, y; xgcd(a, m, g, x, y);
    assert (a * x + m * y == g);
    assert (g >= 0);
    if (b % g != 0) return -1;
    ll k = -x*b / m;
    ll sol = x * (b/g) + k * (m/g);
    if (sol < 0) {
        sol += m/g;
        assert (sol >= 0);
    } else {
        assert (sol - (m/g) < 0);
    }
    // assert (x * b + m * k >= 0);
    // assert (x * b + m * (k-1) < 0);
    return sol;
}

ll shifted_acc(int i, int r, int offset) {
    // assert (0 <= r and r < K);
    // assert (0 <= offset and offset < K);
    int ret;
    if (offset + r <= K) {
        ret = acc[i][offset + r];
    } else {
        ret = acc[i][K] + acc[i][offset + r - K];
    }
    ret -= acc[i][offset];
    // assert (0 <= ret and ret < acc[i][K]);
    return ret;
}

ll inline mul(ll a, ll b, ll m) { return (a*b) % m; }
ll inline add(ll a, ll b, ll m) { return (a+b) % m; }

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    while (cin >> N >> R >> K) {
        assert (2 <= N and N <= 1000000000);
        assert (2 <= R and R <= 200);
        assert (1 <= K and K <= 200);
        rep(i,0,R-1) {
            cin >> start_pos[i];
            cur_pos[i] = --start_pos[i];
        }
        rep(i,0,R-1) {
            acc[i][0] = 0;
            rep(j,1,K) {
                cin >> acc[i][j];
                acc[i][j] += acc[i][j-1];
            }
        }
        memset(sick, 0, sizeof(bool)*R);
        rep(i,1,R-1) t_sick[i] = LLONG_MAX;
        t_sick[0] = 0;
        sick[0] = true;
        int sick_count = 1;
        ll t = 0;
        while (true) {
            int offset = t % K;
            ll t_next = LLONG_MAX;
            int debug_j = -1;
            rep(i,0,R-1) if (sick[i]) {
                rep(j,0,R-1) if (!sick[j]) {
                    ll dt_min = LLONG_MAX;
                    ll a = acc[i][K] - acc[j][K];
                    rep(r,0,K-1) {
                        ll ri = shifted_acc(i, r, offset);
                        ll rj = shifted_acc(j, r, offset);                    
                        ll b = cur_pos[j] - cur_pos[i] + rj - ri;
                        ll n = lincongeq__first_nonneg(a,b,N);                        
                        if (n != -1) {
                            assert (n >= 0);
                            ll dt = n * K + r;
                            assert (dt >= 0);
                            dt_min = min(dt_min, dt);
                        }
                    }
                    if (dt_min < LLONG_MAX) {
                        assert (dt_min >= 0);
                        t_sick[j] = t + dt_min;
                        if (t_sick[j] < t_next) {
                            t_next = t_sick[j];
                            debug_j = j;
                            assert (sick[debug_j] == false);
                            assert (t_sick[debug_j] == t_next);
                        }                        
                    }
                }
            }
            if (t_next < LLONG_MAX) {
                assert (debug_j != -1);
                assert (0 <= debug_j and debug_j < R);
                assert (sick[debug_j] == false);
                assert (t_sick[debug_j] == t_next);
                bool new_sick = false;
                rep(i,0,R-1) if (sick[i] == false and t_sick[i] == t_next) {
                    sick[i] = true;
                    sick_count++;
                    new_sick = true;
                }
                assert (new_sick);
                // assert (t_next > t);
                t = t_next;
                rep(i,0,R-1) {
                    cur_pos[i] = add(add(start_pos[i],
                                    mul(acc[i][K], (t/K), N), N),
                                    acc[i][t%K], N);
                }
            } else {
                break;
            }
        }
        cout << sick_count << ' ' << t << '\n';
    }
    return 0;
}
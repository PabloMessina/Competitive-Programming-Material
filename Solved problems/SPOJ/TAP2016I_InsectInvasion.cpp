// tags: linear congruence equation, gcdext, euclidean algorithm,
// dijkstra, modular arithmetics, math
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
typedef pair<ll,int> ll_i;

ll N; int R,K;
ll start[200];
ll acc[200][200];
ll sick_time[200];

ll inline mul(ll a, ll b, ll m) { return (a*b) % m; }
ll inline add(ll a, ll b, ll m) { return (a+b) % m; }
ll inline mod(ll x, ll m) { return ((x %= m) < 0) ? x + m : x; }

// position of frog u at time t
// the position is given by the initial position + total distance traveled (mod N)
ll pos(int u, ll t) {
    ll q = t / K;
    int r = t % K;
    ll x = add(start[u],mul(mod(q,N),acc[u][K-1],N),N);
    if (r > 0) x = add(x, acc[u][r-1], N);
    return x;
}

// extended euclidean algorithm, iterative version
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
    g = r2, x = x2, y = y2;
    if (g < 0) g = -g, x = -x, y = -y;
    return g;
}


// Find minimum instant t >= t0 such that frog u reaches frog v.
// t can be broken down into t = t0 + c * K + k, where
//     c = number of full cycles of jumps (c * K jumps in total)
//     k = number of jumps after the last full cycle (0 <= k < K)
// We can derive the following equation for c and k:
//     pos(u,t0) + c * acc[u][K-1] + dist(u,t0,k) = 
//     pos(v,t0) + c * acc[v][K-1] + dist(v,t0,k)  (mod N)
// Where dist(u,t0,k) = the sum of first k jumps frog u makes
//   right after time t0
// The equation can be simplified to:
//     pos(u,t0+k) + c * acc[u][K-1] = pos(v,t0+k) + c * acc[v][K-1] (mod N)
//     => (acc[u][K-1] - acc[v][K-1]) * c = pos(v,t0+k) - pos(u,t0+k) (mod N)
//     => A * c = B(k) (mod N)
// For a fixed k, A * c = B(k) (mod N) is just a linear congruence equation,
//    which is equivalent to solving a linear diophantine equation, which can
//    be done using the extended euclidean algorithm
// Then we simply try out all k's (k = 0 ... K-1) and choose the minimum
//    non-negative c we find
// For more details about linear congruence equations, check out these lectures:
//   http://gauss.math.luc.edu/greicius/Math201/Fall2012/Lectures/linear-congruences.article.pdf
//   http://gauss.math.luc.edu/greicius/Math201/Fall2012/Lectures/linear-diophantine.article.pdf
ll get_reach_time(ll t0, int u, int v) {
    int offset = t0 % K; // the last jump made = the index of the next jump
    ll A = acc[u][K-1] - acc[v][K-1]; // the A in the equation A * c = B(k)
    ll t = LLONG_MAX; // the answer
    if (A == 0) { // special case: 0 * c = B(k), only solution when B(k) == 0
    // for some k, in which case we pick c = 0 for the smallest k possible
        rep(k,0,K-1) {
            ll B = pos(v, t0+k) - pos(u, t0+k);
            if (B==0) { t = t0+k; break; }
        }
    } else { // general case: A * c =  B(k), k = 0 ... K-1
        A = mod(A, N); // make sure 0 <= A < N
        ll g,x0,y0;
        g = gcdext(A,N,x0,y0); // run gcdext just once (shared computation)
        rep(k,0,K-1) {
            ll B = mod(pos(v, t0+k) - pos(u, t0+k), N); // make sure 0 <= B < N
            if (B % g == 0) {
                // c = x0*(B/g) + n*(N/g) >= 0,  where n is any integer
                // => n >= -x0*B/N
                // => n = ceil(-x0*B/N), because we want the smallest integer n
                ll n = -x0*B / N;
                ll c = x0 * (B/g) + n * (N/g);
                if (c < 0) c += N/g;
                t = min(t, t0 + c * K + k);
            }
        }
    }
    return t;
}

int main() {
    while (scanf("%lld %d %d", &N, &R, &K) == 3) {
        // read initial positions
        rep(i,0,R-1) {
            scanf("%d", start + i);
            start[i]--;
        }
        // read and compute accumulated sums of jumps
        rep(i,0,R-1) {
            ll sum = 0;
            rep(j,0,K-1) {
                ll x; scanf("%d", &x);
                sum += x;
                acc[i][j] = sum;
            }
        }
        // run a "dijkstra-like" search of the minimum cotagion time for each frog
        fill(sick_time, sick_time+R, LLONG_MAX);                
        priority_queue<ll_i, vector<ll_i>, greater<ll_i>> q;
        sick_time[0] = 0;
        q.emplace(0,0);
        while (!q.empty()) {
            auto p = q.top(); q.pop();
            ll t = p.first;
            int u = p.second;
            if (t > sick_time[u]) // ignore outdated updates
                continue;
            rep(v,0,R-1) {
                if (sick_time[v] > t) { // if there is margin for improvement
                    ll tt = get_reach_time(t, u, v); // compute time after t when u reaches v
                    if (tt < sick_time[v]) { // if there is an actual improvement
                        sick_time[v] = tt;
                        q.emplace(tt, v);
                    }
                }
            }
        }
        // calculate and print answer
        int sick_count = 0;
        ll t_last_sick = 0;
        rep(i,0,R-1) {
            if (sick_time[i] < LLONG_MAX) {
                sick_count++;
                t_last_sick = max(t_last_sick, sick_time[i]);
            }
        }
        printf("%d %lld\n", sick_count, t_last_sick);
    }
    return 0;
}
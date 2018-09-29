// tags: concurrent BFS's, implicit graph, flood fill,
// math, prime numbers, sieve of eratosthenes,
// implementation
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
// -------------------------------

struct Cell {
    int x,y;
    Cell() {}
    Cell(int x, int y) : x(x), y(y) {}
};

// unitary vectors: up, left, down, right
int dirs[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

// return the number of cells up to level 'n', i.e.
// the area of a square of side = 2 * n + 1
inline int count_up_to_level(int n) {
    int tmp = (2 * n + 1); return tmp * tmp;
}

// given Cell c = {x,y}, return its corresponding number
// according to the spiral pattern
int cell2num(Cell p) {
    int n = max(abs(p.x), abs(p.y));
    int ans = count_up_to_level(n-1);
    if (p.x == n) {
        if (p.y == -n) return count_up_to_level(n);
        return ans + p.y + n;
    }
    int _2n = 2 * n;
    ans += _2n;
    if (p.y == n) return ans + n - p.x;
    ans += _2n;
    if (p.x == -n) return ans + n - p.y;
    ans += _2n;
    // assert(p.y == -n); // debugging
    return ans + p.x + n;
}

// given number k, return its corresponding cell {x, y}
// according to the spiral pattern
// * we assume that 1 maps to {0, 0}
Cell num2cell(int k) {
    if (k == 1) return {0, 0};
    int n = (int)ceil((sqrt(k) - 1.) / 2.);
    // assert(count_up_to_level(n-1) < k); // debugging
    // assert(count_up_to_level(n) >= k); // debugging
    int delta = k - count_up_to_level(n-1);
    int x = n, y = -n;
    int _2n = 2 * n;
    rep(i,0,3) {
        if (delta <= _2n) {
            x += dirs[i][0] * delta;
            y += dirs[i][1] * delta;
            break;
        }
        x += dirs[i][0] * _2n;
        y += dirs[i][1] * _2n;
        delta -= _2n;
    }
    return {x,y};
}

// we anotate in 'is_prime' all numbers that are primes
// up to a large enough position, using the well known
// "Sieve of Eratosthenes" algorithm
const int MAXK = 1000000;
vector<bool> is_prime;
void init_primes() {
    is_prime.assign(MAXK + 1, true);
    is_prime[1] = false;
    int limit = (int) floor(sqrt(MAXK));
    rep (i,2,limit)
        if (is_prime[i])
            for (int j = i * i; j <= MAXK; j += i)
                is_prime[j] = false;
}

// we run 2 BFS's simultaneously, one from 'x' and one from 'y'
// If either of the two BFS's gets stuck (say, either 'x' or 'y' is surrounded by
// prime numbers), then we return -1
// Else, the two BFS's will eventually collide, and the first collision
// will give us the shortest distance between 'x' and 'y'
// * notice we don't use an explicit graph, instead we assume each cell is a node
// and cells up, down, left and right (4) are neighbors (like a flood fill
// https://en.wikipedia.org/wiki/Flood_fill), except for those cells
// corresponding to prime numbers
int shortest_path(int x, int y) {
    static int dist1[300000], dist2[300000];

    // init variables for each BFS
    memset(dist1, -1, sizeof dist1);
    memset(dist2, -1, sizeof dist2);
    queue<pair<int,Cell>> q1, q2;
    q1.emplace(x, num2cell(x));
    q2.emplace(y, num2cell(y));
    dist1[x] = 0;
    dist2[y] = 0;

    // run 2 BFS's simultaneously
    while (!q1.empty() and !q2.empty()) {
        // BFS 1: expand
        auto u1 = q1.front(); q1.pop();
        int k1 = u1.first;
        Cell c1 = u1.second;
        rep(i,0,3) {
            int xx = c1.x + dirs[i][0];
            int yy = c1.y + dirs[i][1];
            int kk = cell2num({xx,yy});
            if (dist2[kk] != -1) {
                return dist1[k1] + dist2[kk] + 1;
            }
            if (dist1[kk] != -1 or is_prime[kk]) continue;
            q1.push({kk, {xx, yy}});
            dist1[kk] = dist1[k1] + 1;
        }

        // BFS 2: expand
        auto u2 = q2.front(); q2.pop();
        int k2 = u2.first;
        Cell c2 = u2.second;
        rep(i,0,3) {
            int xx = c2.x + dirs[i][0];
            int yy = c2.y + dirs[i][1];
            int kk = cell2num({xx,yy});
            if (dist1[kk] != -1) {
                return dist2[k2] + dist1[kk] + 1;
            }            
            if (dist2[kk] != -1 or is_prime[kk]) continue;
            q2.push({kk, {xx, yy}});
            dist2[kk] = dist2[k2] + 1;
        }
    }
    return -1;
}

int main() {
    init_primes();
    int x, y;
    int _case = 1;
    while (cin >> x >> y) {
        int d = shortest_path(x,y);
        cout << "Case " << _case++ << ": ";
        if (d == -1) cout << "impossible\n";
        else cout << d << '\n';
    }
    return 0;
}
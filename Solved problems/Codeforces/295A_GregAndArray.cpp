// tags: implementation, lazy updates
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

const int MAXN = 100000 + 5;
int n,m,k;
ll values[MAXN] = {0};
ll deltas[MAXN] = {0};
ll op_times[MAXN] = {0};
tuple<int,int,ll> ops[MAXN];

void lazy_range_increment(ll d, int i, int j, ll* arr) {
    arr[i] += d;
    arr[j+1] -= d;
}

void update_array(ll* arr, int size) {
    ll acc = 0;
    rep(i,0,size-1) { acc = arr[i] = arr[i] + acc; }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    rep(i,0,n-1) cin >> values[i];
    rep(i,0,m-1) {
        int l, r; ll d; cin >> l >> r >> d;
        ops[i] = make_tuple(l-1, r-1, d);
    }
    rep(i,1,k) {
        int x, y; cin >> x >> y;
        lazy_range_increment(1, x-1, y-1, op_times);
    }
    update_array(op_times, m);
    rep(i, 0, m-1) {
        int l, r; ll d; tie(l,r,d) = ops[i];
        lazy_range_increment(d * op_times[i], l, r, deltas);
    }
    update_array(deltas, n);
    rep(i,0,n-1) {
        if (i) cout << ' ';
        cout << values[i] + deltas[i];
    }
    cout << '\n';
    return 0;
}
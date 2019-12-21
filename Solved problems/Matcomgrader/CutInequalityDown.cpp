// tags: data structures, implementation, sparse table, binary lifting, binary search
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
typedef long long int ll;
// -------------------------------
int N;
ll L, U;
vector<ll> A, accA;
enum { UP, DOWN };

template<class t> class SparseTable {
    int n;
    vector<ll> memo, *arr;    
public:
    SparseTable(vector<ll>& _arr) {
        arr = &_arr;
        n = arr->size();
        int maxlog = 31 - __builtin_clz(n);
        memo.assign(n * (maxlog + 1), -1);
    }
    ll dp(int i, int e) { 
        ll& ans = memo[e * n + i];
        if (ans != -1) return ans;
        if (e == 0) return ans = (*arr)[i];
        return ans = t::merge(dp(i, e-1), dp(i+(1<<(e-1)), e-1));
    }
    ll query(int l, int r) {
        int e = 31 - __builtin_clz(r - l + 1);
        return t::merge(dp(l,e), dp(r - (1 << e) + 1, e));
    }
};

struct RMinQ {
    static ll merge(ll x, ll y) { return min(x, y); }
};
struct RMaxQ {
    static ll merge(ll x, ll y) { return max(x, y); }
};

int next_up(int i, ll x, SparseTable<RMaxQ>& st_max) {
    if (i+1 == N) return -1;
    int l = i+1, r = N;
    ll ref = i >= 0 ? accA[i] : 0;
    while (l < r) {
        int m = (l+r)>>1;
        if (x + st_max.query(l, m) - ref >= U) {
            r = m;             
        } else {
            l = m+1;
        }
    }
    return l == N ? -1 : l;
}

int next_down(int i, ll x, SparseTable<RMinQ>& st_min) {
    if (i+1 == N) return -1;
    int l = i+1, r = N;
    ll ref = i >= 0 ? accA[i] : 0;
    while (l < r) {
        int m = (l+r)>>1;
        if (x + st_min.query(l, m) - ref <= L) {
            r = m;             
        } else {
            l = m+1;
        }
    }
    return l == N ? -1 : l;
}

pair<int,int> next_event(int i, ll x, SparseTable<RMinQ>& st_min, SparseTable<RMaxQ>& st_max) {
    int j1 = next_up(i, x, st_max);
    int j2 = next_down(i, x, st_min);
    if (j1 == -1) return {j2, DOWN};
    if (j2 == -1) return {j1, UP};
    return j1 < j2 ? make_pair(j1, UP) : make_pair(j2, DOWN);
}

struct NextSparseTable {
    int n, maxlog;
    vector<pair<int,int>> memo[2], *arr[2];
    NextSparseTable(
            vector<pair<int,int>>& arr_up,
            vector<pair<int,int>>& arr_down) {
        arr[UP] = &arr_up;
        arr[DOWN] = &arr_down;
        n = arr_up.size();
        maxlog = 31 - __builtin_clz(n);
        memo[UP].assign(n * (maxlog + 1), make_pair(-1,-1));
        memo[DOWN].assign(n * (maxlog + 1), make_pair(-1,-1));
    }
    pair<int,int>& dp(int p, int i, int e) {
        auto& ans = memo[p][e * n + i];
        if (ans.second != -1) return ans;
        if (e == 0) return ans = (*arr[p])[i];
        auto& tmp = dp(p, i, e-1);
        if (tmp.first == -1) return ans = tmp;
        return ans = dp(tmp.second, tmp.first, e-1);
    }
    pair<int,int> query(int p, int l, int r) {
        pair<int,int> ans = {l, p};
        invrep(e, maxlog, 0) {
            auto& tmp = dp(ans.second, ans.first, e);
            if (tmp.first != -1 and tmp.first <= r) ans = tmp;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> L >> U;
    A.resize(N);
    accA.resize(N);
    ll _sum = 0;
    rep(i,0,N) {
        cin >> A[i];
        _sum += A[i];
        accA[i] = _sum;
    }
    SparseTable<RMaxQ> st_max(accA);
    SparseTable<RMinQ> st_min(accA);
    vector<pair<int,int>> next_if_up(N);
    vector<pair<int,int>> next_if_down(N);
    rep(i,0,N) {
        next_if_up[i] = next_event(i, U, st_min, st_max);
        next_if_down[i] = next_event(i, L, st_min, st_max);
    }
    NextSparseTable st_next(next_if_up, next_if_down);

    int Q; cin >> Q;
    while (Q--) {
        int b, e; ll x; cin >> b >> e >> x;
        --b, --e;        
        auto tmp = next_event(b-1, x, st_min, st_max);
        if (tmp.first != -1 and tmp.first <= e) {
            tmp = st_next.query(tmp.second, tmp.first, e);
            b = tmp.first + 1;
            x = tmp.second == UP ? U : L;
        }
        ll ans = x + accA[e] - (b > 0 ? accA[b-1] : 0);
        cout << ans << '\n';
    }
    return 0;
}
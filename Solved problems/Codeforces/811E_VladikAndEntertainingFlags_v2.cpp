// tags: sparse table, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
const int MAXM = 100000;
int N, M, Q;
int mat[10][MAXM];

struct Interval {
    int l, r;
    int left[10], right[10];
    int n_comp = -1;
};

Interval merge(Interval a, Interval b) {
    Interval m;
    m.n_comp = a.n_comp + b.n_comp;
    rep(j,0,N) {       
        int new_id = a.right[j];
        int old_id = b.left[j];
        if (mat[j][a.r] == mat[j][b.l] and old_id != new_id) {
            m.n_comp--;
            rep(k,0,N) {
                if (b.left[k] == old_id) b.left[k] = new_id;
                if (b.right[k] == old_id) b.right[k] = new_id;
                if (a.left[k] == old_id) a.left[k] = new_id;
                if (a.right[k] == old_id) a.right[k] = new_id;
            }
        }
    }
    m.l = a.l;
    m.r = b.r;    
    rep(j,0,N) {
        m.left[j] = a.left[j];
        m.right[j] = b.right[j];
    }
    return m;
}

struct SparseTable {
    vector<Interval> intervals;
    int ID = 0;
    SparseTable() {
        int max_log = 31 - __builtin_clz(M);
        intervals.resize(M * (max_log+1));
    }
    Interval dp(int i, int e) {
        auto& tmp = intervals[e * M + i];
        if (tmp.n_comp == -1) {
            if (e == 0) {
                tmp.n_comp = 0;
                tmp.l = i;
                tmp.r = i;
                rep(j,0,N) {
                    tmp.left[j] = ID;
                    tmp.right[j] = ID;
                    if (j+1 >= N or mat[j][i] != mat[j+1][i]) {
                        ID++;
                        tmp.n_comp++;
                    }
                }
            } else {
                tmp = merge(dp(i, e-1), dp(i+(1 << (e-1)), e-1));
            }
        }
        return tmp;
    }
    int query(int l, int r) {
        int d = r - l + 1;
        Interval ans;
        for (int e = 0; d; e++, d>>=1) {
            if (d & 1) {
                Interval i = dp(l, e);
                if (ans.n_comp == -1) ans = i;
                else ans = merge(ans, i);
                l += 1 << e;
            }
        }        
        return ans.n_comp;
    }    
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> M >> Q;
    SparseTable st;
    rep(i,0,N) rep(j,0,M) cin >> mat[i][j];
    while (Q--) {
        int l, r; cin >> l >> r; --l, --r;
        cout << st.query(l, r) << '\n';
    }
    return 0;
}
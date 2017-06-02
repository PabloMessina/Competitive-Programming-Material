// tags: divide and conquer, range minimum query (rmq) (segment tree)
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long int ll;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<double, int> pdi;
typedef pair<ll, int> lli;
// -------------------------------

const int MAXN = 5000;
int N;
vi a;

// segment tree for range minimum query
struct SegmentTree {
    vi st, A;
    int n;
    int left(int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; } 

    SegmentTree(const vi &_A) {
        A = _A;
        n = A.size();
        st.resize(4 * n, 0);
        build(1,0,n-1);
    }

    void build(int p, int l, int r) {
        if (l == r) {
            st[p] = l;
        } else {
            int lp = left(p), rp = right(p);
            build(lp, l, (l+r)/2);
            build(rp, (l+r)/2+1, r);
            int i = st[lp], j = st[rp];
            st[p] = (A[i] <= A[j]) ? i : j;
        }
    }

    int rmq(int p, int l, int r, int i, int j) {
        if (i > r or j < l) return -1;
        if (i <= l and r <= j) return st[p];
        int ii = rmq(left(p), l, (l+r)/2, i, j);
        int jj = rmq(right(p), (l+r)/2+1, r, i, j);
        if (ii == -1) return jj;
        if (jj == -1) return ii;
        return (A[ii] <= A[jj]) ? ii : jj;
    }

    // return the index of the leftmost position
    // with minimum value within range [i, j]
    int rmq(int i, int j) {
        return rmq(1,0,n-1,i,j);
    }
};

// find minimum number of strokes to paint
// from column i to column j and above height h
int solve(int i, int j, int h, SegmentTree& st) {
    int l, r;
    l = i;
    r = st.rmq(i,j);
    int minh = a[r];
    int ans = minh - h;
    while (true) {
        if (l < r) {
            ans += solve(l, r-1, minh, st);
        }
        l = r + 1;
        if (l > j) break;
        r = st.rmq(l, j);
        if (a[r] > minh) r = j + 1;
    }
    return min(ans, j - i + 1); 
}

int main() {
    scanf("%d", &N);
    a.resize(N);
    rep(i,0,N-1) scanf("%d", &a[i]);
    SegmentTree st(a);
    printf("%d\n", solve(0, N-1, 0, st));
    return 0;
}
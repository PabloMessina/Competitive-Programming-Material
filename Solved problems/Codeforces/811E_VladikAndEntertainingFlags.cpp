// tags: Segment Tree

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

const int MAXM = (int)1e5;
int n,m,q;
int mat[10][MAXM];

// ----- SEGMENT TREE -----
int ID = 0;
struct segment {
    int lc, rc;
    int left[10], right[10];
    int comp = 0;
};
segment st[MAXM * 4];
void merge(const segment &a, const segment& b, segment& c) {
    static int midleft[10], midright[10];
    c.lc = a.lc;
    c.rc = b.rc;
    rep(i,0,n-1) {
        c.left[i] = a.left[i];        
        c.right[i] = b.right[i];
        midleft[i] = a.right[i];
        midright[i] = b.left[i];
    }
    c.comp = a.comp + b.comp;
    rep(i,0,n-1) {            
        if (mat[i][a.rc] == mat[i][b.lc] and midleft[i] != midright[i]) {
            int old_id = midleft[i];
            int new_id = midright[i];
            c.comp--;
            rep(j,0,n-1) {                
                if (c.left[j] == old_id) c.left[j] = new_id;
                if (c.right[j] == old_id) c.right[j] = new_id;
                if (midleft[j] == old_id) midleft[j] = new_id;
                if (midright[j] == old_id) midright[j] = new_id;
            }
        }
    }
}

int inline left(int p) { return p << 1; }
int inline right(int p) { return (p << 1) + 1; }

void build(int p, int l, int r) {    
    segment& s = st[p];
    if (l == r) {
        s.lc = s.rc = l;
        s.comp = 0;
        rep(i,0,n-1) {
            if (i == 0 or mat[i][l] != mat[i-1][l]) {
                s.left[i] = s.right[i] = ID++;
                s.comp++;
            } else {
                s.left[i] = s.right[i] = s.left[i-1];
            }
        }
    } else {
        int lp = left(p), rp = right(p);
        build(lp, l, (l+r)/2);
        build(rp, (l+r)/2+1, r);
        merge(st[lp], st[rp], s);
    }
}

segment* query(int p, int l, int r, int i, int j, bool& should_delete) {
    should_delete = false;
    if (i > r or j < l) return NULL; // no overlap
    if (i <= l and r <= j) return &st[p]; // full overlap

    // partial overlap
    int lp = left(p), rp = right(p);
    bool dell, delr;
    segment* lseg = query(lp, l, (l+r)/2, i, j, dell);
    segment* rseg = query(rp, (l+r)/2+1, r, i, j, delr);
    if (lseg == NULL) return rseg;
    if (rseg == NULL) return lseg;

    should_delete = true;
    segment* new_seg = new segment();
    merge(*lseg, *rseg, *new_seg);
    if (dell) delete lseg;
    if (delr) delete rseg;
    return new_seg;
}


// ---- MAIN --------

int main() {
    scanf("%d%d%d", &n, &m, &q);
    rep(i,0,n-1) rep(j,0,m-1) scanf("%d", mat[i] + j);
    build(1,0,m-1);
    while (q--) {
        int l, r; scanf("%d%d", &l, &r); --l, --r;
        bool should_delete;
        segment* seg = query(1, 0, m-1, l, r, should_delete);
        printf("%d\n", seg->comp);
        if (should_delete) delete seg;
    }
    return 0;
}
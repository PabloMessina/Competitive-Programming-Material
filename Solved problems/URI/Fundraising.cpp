// tags: DP, HIV (heaviest increasing subsequence), RMQ, fenwick tree,
// domain compression
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
// -------------------------------

struct BeautyGroup {
    int b;
    vector<int> fs;
    vector<ll> ds;
};

struct FenwickTree {
    vector<ll> ft;
    FenwickTree(int n) {
        ft.assign(n+1,0);
    }
    ll rmq(int b) {
        ll ans = 0;
        for (; b; b -= (b & -b)) ans = max(ans, ft[b]);
        return ans;
    }
    void update(int b, ll new_val) {
        for(; b < ft.size(); b += (b & -b)) ft[b] = max(ft[b], new_val);
    }
};

int main() {
    int N;
    scanf("%d", &N);
    map<ii,ll> bf2d; // map (b,f) -> d, notice this is an ordered map
    set<int> fset; // set of unique f values
    while (N--) {
        int b,f,d;
        scanf("%d%d%d",&b,&f,&d);
        fset.insert(f); // add f to fset
        // merge all (b,f) pairs with the same b and f
        // into single points
        ii q(b,f);
        auto it = bf2d.find(q);
        if (it == bf2d.end()) {
            bf2d[q] = d;
        } else {
            it->second += d;
        }
    }

    // reassign f values in a compact domain
    // making sure to preserve order
    umap<int,int> compact_f_map;
    int maxf = 0;
    for (auto& f : fset) {
        compact_f_map[f] = ++maxf;
    }

    // re-collect points into 'beauty' groups, i.e.,
    // groups such that all points within a group
    // have the same beauty
    vector<BeautyGroup*> bgroups;
    BeautyGroup *bg;
    int prevb = -1;
    for (auto& it : bf2d) {
        int b = it.first.first;
        int f = it.first.second;
        f = compact_f_map[f];
        ll d = it.second;
        if (prevb != b) { // new b value -> spawn new group
            bg = new BeautyGroup();
            bg->b = b;
            bgroups.push_back(bg);
            prevb = b;
        }        
        bg->fs.push_back(f);
        bg->ds.push_back(d);
    }

    // FT to keep track of maximum subsequence weight
    // seen so far such that it ends in value f,
    // for 1 <= f <= maxf
    FenwickTree ft(maxf);

    // stack to keep track of pairs (f, max_weight)
    // we use this stack to remember optimum values for the
    // current BeautyGroup and perform updates to the Fenwick Tree
    // afterwards
    vector<pair<int,ll>> stack;
    stack.reserve(maxf);
    
    // Iterate over beauty groups and calculate maximum subsequence
    // weights using DP (dynamic programming): we reuse maximum
    // subsequence weights from previous iterations, which are
    // stored in the fenwick tree.
    for (BeautyGroup* bg : bgroups) {
        // iterate over points of the current beauty group
        int n = bg->fs.size();        
        rep(i,0,n-1) {
            int f = bg->fs[i];
            ll d = bg->ds[i];
            // max subsequence weight ending in f at this position
            // = (max subsequence weight ending in some value < f
            // at some position to the left) + d
            stack.emplace_back(f, ft.rmq(f-1)+d);
        }
        // update fenwick tree with the optimum values found
        // for the current group (stored in the stack)
        while (!stack.empty()) {
            auto p = stack.back();
            ft.update(p.first,p.second);
            stack.pop_back();
        }
    }

    // print global maximum
    printf("%lld\n", ft.rmq(maxf));
    return 0;
}
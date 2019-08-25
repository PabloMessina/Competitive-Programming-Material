// tags: DP, HIV (heaviest increasing subsequence), RMQ, fenwick tree,
// domain compression
#include <bits/stdc++.h>
using namespace std;
#define umap unordered_map
typedef pair<int,int> ii;
// -------------------------------

struct Triplet {
    int b; int f; ll d;
    bool operator<(const Triplet& o) const {
        return (b < o.b) or (b == o.b and f > o.f);
    }
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
    while (scanf("%d", &N) == 1) {
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

        // collect all b,f,d in triplets and sort them
        // lexicographically: increasing in b, decreasing in f
        vector<Triplet> triplet_list(bf2d.size());
        int i = 0;
        for (auto& it : bf2d) {
            Triplet& t = triplet_list[i++];
            t.b = it.first.first;
            t.f = compact_f_map[it.first.second];
            t.d = it.second;
        }
        sort(triplet_list.begin(), triplet_list.end());

        // FT to keep track of maximum subsequence weight
        // seen so far such that it ends in value f,
        // for 1 <= f <= maxf
        FenwickTree ft(maxf);

        // Find HIS for each point, from left to right,
        // reusing stored HIS of previous points by quering
        // the fenwick tree. Then update the fenwick tree
        // with this new value.
        for (Triplet& t : triplet_list) {
            ft.update(t.f, ft.rmq(t.f-1) + t.d);
        }

        // print global maximum
        printf("%lld\n", ft.rmq(maxf));
    }
    return 0;
}
// tags: implementation, ordered sets
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

struct Interval {
    int start;
    int end;
    int color;
    bool operator<(const Interval& o) const {
        return start < o.start;
    }
};

const int MAXC = 100005;
ll color_counts[MAXC] = {0}; // color_counts initialized filled with 0s

int main() {
    int L,C,N;
    while (scanf("%d%d%d", &L,&C,&N) == 3) {
        set<Interval> intervals;
        memset(color_counts, 0, sizeof color_counts);

        // insert first interval
        Interval aux = {0,L-1,1};
        intervals.insert(aux);    
        color_counts[1] = L; // update counter for color 1

        while(N--) {
            int P,X;
            ll A,B;
            scanf("%d%d%lld%lld", &P, &X, &A, &B);
            ll s = color_counts[P];
            int m1 = (A + s * s) % (ll)L;
            int m2 = (A + (s + B) * (s + B)) % (ll)L;
            if (m1 > m2) swap(m1, m2);

            // iterators pointing to the first and last intervals
            // that intersect with the range [m1, m2]
            set<Interval>::iterator it_first, it_last;
            // Interval instances to copy the Intervals pointed to by the
            // previous iterators
            Interval in_first, in_last;

            // -------------------------------------
            // STEP 1) Find the first iterator in O(log(L)) by inserting a "fake" interval
            aux.start = m1;
            // check out the documentation of set::insert
            // http://www.cplusplus.com/reference/set/set/insert/
            auto ret = intervals.insert(aux);
            if (ret.second == true) { // succesful insertion, it_first should be set to the previous one
                it_first = std::prev(ret.first);
                intervals.erase(ret.first); // remove "fake" interval
            } else { // no insertion, just set "it_first" to the already existing interval's iterator
                it_first = ret.first;
            }
            in_first = *it_first; // copy Interval pointed to by "it_first"

            // -------------------------------------
            // STEP 2) iterate from "it_first" until we find the last interval that intersects with [m1, m2],
            // and remove the whole range from the intervals set
            for(auto it = it_first; it != intervals.end(); ++it) {
                aux = *it;
                if (aux.start <= m2) {
                    it_last = it;
                    // substract from corresponding color count
                    color_counts[aux.color] -= aux.end - aux.start + 1;
                } else {
                    break;
                }
            }
            
            in_last = *it_last; // copy Interval pointed to by "it_last"

            // remove range [it_first, it_last]
            // check out the documentation of set::erase
            // http://www.cplusplus.com/reference/set/set/erase/
            intervals.erase(it_first, std::next(it_last));

            // -------------------------------------
            // STEP 3) insert new Interval(s)

            // check if there is a merge (same color) or split (different colors) at the left
            if (in_first.start < m1) {
                if (in_first.color == X) { // same color -> merge
                    m1 = in_first.start;
                } else { // different colors -> split
                    in_first.end = m1 - 1;
                    color_counts[in_first.color] += in_first.end - in_first.start + 1;
                    intervals.insert(in_first);
                }
            }

            // check if there is a merge (same color) or split (different colors) at the right
            if (in_last.end > m2) {
                if (in_last.color == X) { // same color -> merge
                    m2 = in_last.end;
                } else { // different colors -> split
                    in_last.start = m2 + 1;
                    color_counts[in_last.color] += in_last.end - in_last.start + 1;
                    intervals.insert(in_last);
                }
            }

            // insert new interval (this already considers possible merges at both ends)
            aux = {m1, m2, X};
            color_counts[aux.color] += aux.end - aux.start + 1;
            intervals.insert(aux);
        }
        // find maximum color count from 1 to C
        ll ans = 0;
        rep(i,1,C) {
            ans = max(ans, color_counts[i]);
        }
        // print answer
        printf("%lld\n", ans);
    }
    return 0;
}
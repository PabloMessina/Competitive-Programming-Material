// tags: domain compression, sweep line, fenwick tree (range update & point query)
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define umap unordered_map
typedef long long int ll;
typedef pair<int,int> ii;
// -------------------------------
int P, V;

// define 2 structs: Plant and Vertical Segment
// both inheriting from struct X, in order to use
// polymorphism
enum Type { PLANT, VSEGMENT };
struct X { int x; Type type; }; // keep track of x coordinate and type
struct Plant : X {
	int y, val;
	Plant(int x, int y, int val) {
		this->x = x; this->y = y; this->val = val;
		this->type = PLANT;
	}
};
struct VerticalSegment : X {
	int miny, maxy;
	VerticalSegment(int x, int miny, int maxy) {
		this->x = x; this->miny = miny; this->maxy = maxy;
		this->type = VSEGMENT;
	}	
};
// custom comparator used later on for sorting
bool cmp(const X* a, const X* b) { return a->x < b->x; }


// data structure used for range updates and single point queries
struct FenwickTree {
	vector<int> ft;
	FenwickTree(int n) { ft.assign(n+1, 0); }	
	// prefix sum query
	int psq(int b) {
		int sum = 0;
		for (; b; b -= (b & -b)) sum += ft[b];
		return sum;
	}
	// range sum query
	int rsq(int a, int b) { return psq(b) - psq(a-1); }
	// add v to k'th position (and propagate)
	void add(int k, int v) {
		for (; k < ft.size(); k += (k & -k)) ft[k] += v;
	}
	// add v to range [i..j] (and propagate)
	void range_add(int i, int j, int v) {
		add(i, v); add(j+1, -v);
	}
};

int main() {
    while (scanf("%d%d", &P, &V) == 2) { // for each input case

		set<int> ys; // use ordered set to keep track of y coordinates in increasing order
		vector<X*> xs; // polymorphic list of X objects

		// read plant coordinates
		rep(i,1,P) {
			int x, y; scanf("%d%d", &x, &y);
			xs.push_back(new Plant(x, y, i));
			ys.insert(y);
		}

		// read fence's vertices coordinates
		vector<ii> vcoords;
		rep(i,1,V) {
			int x,y; scanf("%d%d", &x, &y); vcoords.emplace_back(x,y);
			ys.insert(y);
		}
		rep(i,0,V-1) {
			int j = (i+1) % V;
			if (vcoords[i].first == vcoords[j].first) { // vertical segment
				int miny = vcoords[i].second;
				int maxy = vcoords[j].second;
				if (miny > maxy) swap(miny, maxy);
				xs.push_back(new VerticalSegment(vcoords[i].first, miny, maxy));
			}
		}
		
		// sort X objects using custom comparator
		sort(xs.begin(), xs.end(), cmp);

		// domain compression: map all y values to a narrower domain
		int idx = 1;
		umap<int,int> y2idx;
		for (int y : ys) y2idx[y] = idx++;

		// ---------------------------------
		// run sweep line: left to right
		FenwickTree ft(y2idx.size());
		ll sum = 0; // use long long (avoid int overflow)
		for (X* p : xs) {
			if (p->type == VSEGMENT) { // vertical segment encountered
				VerticalSegment* vseg = static_cast<VerticalSegment*>(p);
				int a = y2idx[vseg->miny];
				int b = y2idx[vseg->maxy];
				if (ft.psq(a) == 0) { // nothing in range
					// add 1 to range -> we are now inside the fence
					ft.range_add(a, b-1, 1);
				} else {
					// substract 1 to range -> we are now outside the fence
					ft.range_add(a, b-1, -1);
				}
			} else { // plant encountered
				Plant* plant = static_cast<Plant*>(p);
				int idx = y2idx[plant->y];
				// if outside fence -> add plant's value to sum
				if (ft.psq(idx) == 0) sum += plant->val;
			}
			delete p; // clear memory
		}
		// print answer
		printf("%lld\n", sum);

	}
    return 0;
}
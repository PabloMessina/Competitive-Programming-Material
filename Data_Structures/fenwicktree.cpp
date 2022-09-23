#include "../c++_template.cpp"

struct FT { // fenwick tree
    vector<int> t;
    FT(int n) { t.assign(n+1, 0); }    
    int query(int i) { // sum in range 1 .. i
        int ans = 0;
        for (; i; i -= (i & -i)) ans += t[i];
        return ans;
    }
    int query(int i, int j) { return query(j) - query(i-1); } // sum in range [i .. j]
    void update(int i, int v) { // increment i'th value by v (and propagate)
        for (; i < t.size(); i += i & (-i)) t[i] += v;
    }
    void update(int i, int j, int v) { update(i, v); update(j + 1, -v); }
};
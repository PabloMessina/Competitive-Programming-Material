#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

// Example of SegmentTree for rmq (range minimum query)
// Note: instead of storing the minimum value, each node will store 
//  the index of the leftmost position of the range in which the minimum
//  value of that range is found

struct SegmentTreeRMQ {
    vi arr; // store original array values
    vi tree; // store rmq for each node in segment tree
    vi leaf; // store index of leaf nodes in segment tree
    int n; // number of leaf nodes (length of arr)
    
    inline int left (int u) { return u << 1; } // index of left child
    inline int right(int u) { return (u << 1) + 1; } // index of right child

    // u = node, [a, b] = u's range
    void build(int u, int a, int b) {
        if (a == b) { // base case: a leaf node
            tree[u] = a; // u's rmq = a
            leaf[a] = u;
        } else { // recursive case
            int lu = left(u), ru = right(u), m = (a+b)/2;
            build(lu, a, m); // build left child, range = [a, m]
            build(ru, m+1, b); // build right child, range = [m+1, b]
            // store the index of the minimum value,
            // in case of draw choose the leftmost
            int min_i = tree[lu], min_j = tree[ru];
            tree[u] = (arr[min_i] <= arr[min_j]) ? min_i : min_j;
        }        
    }

    // update arr[i] with new_val, and propagate updates in the tree
    // from leaf[i] upwards
    void update(int i, int new_val) {
        arr[i] = new_val;
        int u = leaf[i] >> 1;
        while (u) {
            int lu = left(u), ru = right(u);
            int min_i = (arr[tree[lu]] <= arr[tree[ru]]) ? tree[lu] : tree[ru];
            if (min_i == tree[u]) break; // optimization: no changes, interrupt updates
            // update and move to next parent
            tree[u] = min_i;
            u >>= 1;
        }
    }

    // query the leftmost index of the minimun in range [i,j],
    // considering that we are at node u which is in charge of range [a, b]
    int query(int u, int a, int b, int i, int j) {
        // case 1: no overlap -> return some neutral / invalid value
        if (j < a or b < i) return -1;
        // case 2: full overlap -> return cached answer
        if (i <= a and b <= j) return tree[u];

        // case 3: partial overlap -> need recursion and merge of answers
        int lu = left(u), ru = right(u), m = (a+b)/2;
        int min_i = query(lu, a, m, i, j);
        int min_j = query(ru, m+1, b, i, j);
        if (min_i == -1) return min_j;
        if (min_j == -1) return min_i;
        return (arr[min_i] <= arr[min_j]) ? min_i : min_j;
    }

    // overloading for easier use
    int query(int i, int j) { return query(1, 0, n - 1, i, j); }

    SegmentTreeRMQ(const vi& _arr) {
        arr = _arr; // copy content for local usage
        n = arr.size();
        leaf.resize(n);
        tree.resize(4 * n + 5); // reserve enough space for the worst case
        build(1, 0, n - 1); // recursive build from root node (root == 1)
    }

};
  
// usage
int main() {
    vi arr = { 18, 17, 13, 19, 15, 11, 20 };
    SegmentTreeRMQ st(arr);
    st.query(1, 3);
    st.update(5, 100);
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

struct SegmentTreeLazy {
    vi arr, tree, lazy;
    int n;
    inline int left (int p) { return p << 1; }
    inline int right(int p) { return (p << 1) + 1; }
     
    // u = node, [i, j] = u's range
    void build(int u, int i, int j) {
        if(i == j) { // base case: a leaf node
            tree[u] = arr[i]; // init value
            return;
        }
        int lu = left(u), ru = right(u), m = (i+j)/2;
        build(lu, i, m); // init left child
        build(ru, m+1, j); // init right child
        tree[u] = max(tree[lu], tree[ru]); // set u's value
    }
     
    // increment elements within range [i, j] with value
    void range_update(int u, int a, int b, int i, int j, int value) {
        if(lazy[u] != 0) { // this u needs to be updated
            tree[u] += lazy[u]; // update it 
            if(a != b) {
                lazy[left(u)] += lazy[u]; // mark left child as lazy
                lazy[right(u)] += lazy[u]; // mark right child as lazy  
            }   
            lazy[u] = 0; // Reset it
        }
        
        if(a > j or b < i) // current segment is not within range [i, j]
            return;
            
        if(a >= i and b <= j) { // segment is fully within range
            tree[u] += value;
            if(a != b) { // not leaf
                lazy[left(u)] += value;
                lazy[right(u)] += value;
            } 
            return;
        }
        int lu = left(u), ru = right(u), m = (a+b)/2;
        range_update(lu, a, m, i, j, value); // update left child
        range_update(ru, m+1, b, i, j, value); // update right child 
        tree[u] = max(tree[lu], tree[ru]); // update u
    }
     
    // query tree to get max element value within range [i, j]
    int range_query(int u, int a, int b, int i, int j) {  
        if(a > j or b < i) return INT_MIN; // out of range 
        if(lazy[u] != 0) { // this u needs to be updated
            tree[u] += lazy[u]; // update it 
            if(a != b) {
                lazy[left(u)] += lazy[u]; // mark child as lazy
                lazy[right(u)] += lazy[u]; // mark child as lazy
            } 
            lazy[u] = 0; // reset it
        } 
        if(a >= i and b <= j) // current segment is totally within range [i, j]
            return tree[u];
        int m = (a+b)/2;
        int q1 = range_query(left(u), a, m, i, j); // query left child
        int q2 = range_query(right(u), m+1, b, i, j); // query right child
        return = max(q1, q2); // return final result
    }

    SegmentTreeLazy(const vi& A) {
        arr = A; n = (int)A.size();           // copy content for local usage
        tree.assign(4 * n + 5, 0);            // create large enough vector of zeroes
        lazy.assign(4 * n + 5, 0);
        build(1, 0, n - 1);                   // recursive build
    }
    // overloading
    int range_update(int i, int j, int value) { return range_update(1, 0, n - 1, i, j, value); }
    int range_query(int i, int j) { return range_query(1, 0, n - 1, i, j); }
};

// usage
int main() {
    vi A = { 18, 17, 13, 19, 15, 11, 20 };
    SegmentTreeLazy stl(A);
    stl.range_update(1, 5, 100);
    stl.range_query(1, 3);
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

struct SegmentTreeLazy {
  vi arr, tree, lazy;
  int n;
  inline int left (int p) { return p << 1; }
  inline int right(int p) { return (p << 1) + 1; }
   
  // build the tree
  void build(int node, int a, int b) {
    if(a > b) return; // out of range 
    if(a == b) { // leaf node
      tree[node] = arr[a]; // init value
      return;
    }
    int lnode = left(node), rnode = right(node);
    build(lnode, a, (a+b)/2); // init left child
    build(rnode, (a+b)/2 + 1, b); // init right child 
    tree[node] = max(tree[lnode], tree[rnode]); // init root value
  }
   
  // increment elements within range [i, j] with value
  void range_update(int node, int a, int b, int i, int j, int value) {
    if(lazy[node] != 0) { // this node needs to be updated
      tree[node] += lazy[node]; // update it 
      if(a != b) {
        lazy[left(node)] += lazy[node]; // mark left child as lazy
        lazy[right(node)] += lazy[node]; // mark right child as lazy  
      }   
      lazy[node] = 0; // Reset it
    }
    
    if(a > b || a > j || b < i) // current segment is not within range [i, j]
      return;
      
    if(a >= i && b <= j) { // segment is fully within range
      tree[node] += value; 
      if(a != b) { // not leaf node
        lazy[left(node)] += value;
        lazy[right(node)] += value;
      } 
      return;
    }
   
    range_update(left(node), a, (a+b)/2, i, j, value); // updating left child
    range_update(right(node), 1+(a+b)/2, b, i, j, value); // updating right child 
    tree[node] = max(tree[left(node)], tree[right(node)]); // Updating root with max value
  }
   
  // query tree to get max element value within range [i, j]
  int range_query(int node, int a, int b, int i, int j) {  
    if(a > b || a > j || b < i) return INT_MIN; // out of range 
    if(lazy[node] != 0) { // this node needs to be updated
      tree[node] += lazy[node]; // update it 
      if(a != b) {
        lazy[left(node)] += lazy[node]; // mark child as lazy
        lazy[right(node)] += lazy[node]; // mark child as lazy
      } 
      lazy[node] = 0; // reset it
    } 
    if(a >= i && b <= j) // current segment is totally within range [i, j]
      return tree[node]; 
    int q1 = range_query(left(node), a, (a+b)/2, i, j); // Query left child
    int q2 = range_query(right(node), 1+(a+b)/2, b, i, j); // Query right child 
    return = max(q1, q2); // Return final result  
  }

  SegmentTree(const vi& A) {
    arr = A; n = (int)A.size();              // copy content for local usage
    tree.assign(4 * n, 0);            // create large enough vector of zeroes
    lazy.assign(4 * n, 0);
    build(1, 0, n - 1);                                  // recursive build
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
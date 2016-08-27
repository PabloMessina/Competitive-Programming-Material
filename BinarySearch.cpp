/* ============= */
/* BINARY SEARCH */
/* ============= */

// Find the index of the first item that satisfies a predicate.
// If no such index exists, retuns -1
// Pseudo-code:
function binsearch(array, i, j) {
  while (i < j) {
    m = (i+j)/2
    if (predicate(array[m]))
      j = m
    else
      i = m + 1
  }
  return (predicate(array[i]) ? i : -1)
}

// -----------------------------
// EXAMPLE 1: Integer Lowerbound
// predicate(a, i, key) = (a[i] >= key)
// i.e. "first element >= key"
int lowerbound(vector<int> a, int key, int i, int j) {
  while (i < j) {
    int m = (i + j) / 2;
    if (a[m] >= key)
      j = m;
    else
      i = m + 1;
  }
  return a[i] >= key ? i : -1;
}

// -----------------------------
// EXAMPLE 2: Integer Upperbound
// predicate(a, i, key) = (a[i] > key)
// i.e. "first element > key"
int upperbound(vector<int> a, int key, int i, int j) {
  while (i < j) {
    int m = (i + j) / 2;
    if (a[m] > key)
      j = m;
    else
      i = m + 1;
  }
  return a[i] > key ? i : -1;
}

/* ============================= */
/*  upper_bound(), lower_bound() */
/* ============================= */

// search between [first, last)
// if no value is >= key (lb) / > key (ub), return last

#include <algorithm>
#include <iostream>     // std::cout
#include <algorithm>    // std::lower_bound, std::upper_bound, std::sort
#include <vector>       // std::vector

int main () {
  int myints[] = {10,20,30,30,20,10,10,20};
  std::vector<int> v(myints,myints+8);           // 10 20 30 30 20 10 10 20

  std::sort (v.begin(), v.end());                // 10 10 10 20 20 20 30 30

  std::vector<int>::iterator low,up;
  low=std::lower_bound (v.begin(), v.end(), 20); //          ^
  up= std::upper_bound (v.begin(), v.end(), 20); //                   ^

  std::cout << "lower_bound at position " << (low- v.begin()) << '\n';
  std::cout << "upper_bound at position " << (up - v.begin()) << '\n';

  return 0;
}

// ------------------------------------------------
// Query: how many items are LESS THAN (<) value x

lower_bound(v.begin(), v.end(), x) - v.begin();

// ------------------------------------------------
// Query: how many items are GREATER THAN (>) value x

v.end() - upper_bound(v.begin(), v.end(), x);

//=================
// binary_search()
//=================
bool myfunction (int i,int j) { return (i<j); }
int myints[] = {1,2,3,4,5,4,3,2,1};
std::vector<int> v(myints,myints+9);  
bool found = std::binary_search (v.begin(), v.end(), 6, myfunction)
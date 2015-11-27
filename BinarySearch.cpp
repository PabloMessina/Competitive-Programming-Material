//#####################################################
//################## BINARY SEARCH ####################
//#####################################################

int binsearch(int a[], int key, int i, int j) {
  if(key < a[i] || key > a[j]) return -1;
  while (i <= j) {
    int m = (i + j) / 2;
    if (a[m] == key)
      return m;
    if (key > a[m])
      i = m + 1;
    else
      j = m - 1;
  }
  return -1;
}

//first element's index with value >= key
//if no element has value >= key, return -1
//example:
//key = 5
//array: 1 2 3 4 (5) 5 5 6 7 8
//----------------^
int lowerbound(int a[], int key, int i, int j) {
  while (i < j) {
    int m = (i + j) / 2;
    if (a[m] < key)
      i = m + 1;
    else
      j = m;
  }
  return (a[i] >= key) ? i : -1;
}

//first element's index with value > key
//if no element has value > key, return -1
//example:
//key = 5
//array: 1 2 3 4 5 5 5 (6) 7 8
//----------------------^
int upperbound(int a[], int key, int i, int j) {
  while (i < j) {
    int m = (i + j) / 2;
    if (a[m] <= key)
      i = m + 1;
    else
      j = m;
  }
  return (a[i] > key) ? i : -1;
}


//----------------------------
//Using c++ libraries

//================================
// upper_bound(), lower_bound()
//================================

//search between [first, last)
//if no value is >= key (lb) / > key (ub), return last

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

//=================
// binary_search()
//=================
bool myfunction (int i,int j) { return (i<j); }
int myints[] = {1,2,3,4,5,4,3,2,1};
std::vector<int> v(myints,myints+9);  
bool found = std::binary_search (v.begin(), v.end(), 6, myfunction)
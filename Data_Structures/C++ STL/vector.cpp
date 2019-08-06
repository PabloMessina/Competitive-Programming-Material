// references:
// http://www.cplusplus.com/reference/vector/vector/
// https://www.geeksforgeeks.org/vector-in-cpp-stl/
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a; i<=b; i++)
using namespace std;

// ----------------------------
// DECLARATION & INITIALIZATION
// ----------------------------

// vector of ints
vector<int> v; // empty
vector<int> v(100); // size 100
vector<int> v(N); // size N, make sure N is defined
vector<int> v(N, 2); // size N filled with 2's
vector<int> v = { 1, 2, 3, 5, 6 }; // list initialization (since C++11)
v[0] = -8; // v = { -8, 2, 3, 5, 6 }
v[1] = 0; // v = { -8, 0, 3, 5, 6 }

// vector of vector of ints
// a matrix of R rows by C columns filled with -1
vector<vector<int>> matrix(R, vector<int>(C,-1));

// ---------------------------------------------------
// MODIFYING A VECTOR (capacity, size, adding elements)
// ---------------------------------------------------

vector<int> v; //  v = {}, v.size() == 0
v.reserve(1000); // reserve 1000 x sizeof(int) bytes of contiguous memory in advance
// ** we use v.reserve(MAXN) when we when we know the maximum memory we will ever
//    need to prevent unnecessary memory reallocations

rep(i, 1, 10) v.push_back(i); // v = { 1, 2, 3, ..., 10 }, v.size() == 10
int x = v.front(); // x = 1
int y = v.back(); // y = 10
v.pop_back(); // remove last element -> v = { 1, 2, 3, ..., 9 }, v.size() == 9

// clearing
v.clear(); // v = {}, v.size() == 0

// -------
// RESIZE
// -------
rep(i,1,10) v.push_back(i); // v = { 1, 2, ..., 10 }
v.resize(5); // v = { 1, 2, 3, 4, 5 }
v.resize(8,100); // v = { 1, 2, 3, 4, 5, 100, 100, 100 }
v.resize(12); // v = { 1, 2, 3, 4, 5, 100, 100, 100, 0, 0, 0, 0 }

// -------
// ASSIGN
// -------
v.assign(N, 4); // v = { 4, 4, ..., 4 } (N times)

vector<int> v2;
v2.assign(v.begin(), v.end()); // v2 = v
v2.assign(v.begin() + 1, v.end() - 1); // v2 = v[1:-1]

int arr[5] = {1, 2, 3, 4, 5};
v2.assign(arr, arr + 5); // v2 = {1, 2, 3, 4, 5}
v2.assign(arr, arr + 3); // v2 = {1, 2, 3}

// --------------------------
// EMPLACE_BACK VS PUSH_BACK
// -------------------------
struct CustomData {
    int x; double y; string z;
    CustomData(int x, double y, string z) : x(x), y(y), z(z) {}
};
vector<CustomData> v;
// option 1: with push_back() -> object is created and then copied
v.push_back(CustomData(1,2.32,"foo")); // using constructor
v.push_back({1, 2.32,"bar"}); // c++11: using curly braces
// option 2: with emplace_back() -> object is created in its final location ;)
v.emplace_back(1, 2.32, "foo");
// ** NOTE: for emplace_back() make sure your custom struct/class has a constructor
//          for push_back(), no need to define a constructor


// -----------------------
// ITERATING OVER VECTORS
// -----------------------
// reference:
// https://stackoverflow.com/questions/15176104/c11-range-based-loop-get-item-by-value-or-reference-to-const

// 1) foward direction

vector<CustomData> v(100); // vector of custom type
// option 1: iterate over element copies (slower)
for (auto x : v) { /* do something */ }
// option 2: iterate over references (faster)
for (auto& x : v) { /* do something */ }
// option 3: iterate over const references (equally fast)
// * the const keyword is just to prevent unintended modifications
for (const auto& x : v) { /* do something */ }

vector<int> v {1, 2, 3, 4, 5, 6}; // vector of ints
for (int x : v) { /* do something */ }
for (int& x : v) { /* do something */ }
for (const int& x : v) { /* do something */ }

// using iterators
for (auto it = v.begin(); it != v.end(); ++it) {
    const auto& x = *it; // use *it to access original element pointed by it
    /* do something with x */
}

// 2) backward direction
for (auto it = v.rbegin(); it != v.rend(); ++it) {
    const auto& x = *it;
}

// -------------------
// SWAPPING 2 VECTORS 
// -------------------
vector<int> v1 = {1, 1, 1, 1};
vector<int> v2 = {2, 2, 2};
v1.swap(v2); // v1 = {2, 2, 2}, v2 = {1, 1, 1, 1}
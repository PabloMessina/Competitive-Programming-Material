// Find the index of the first item that satisfies a predicate
// over a range [i,j), i.e., from i to j-1
// If no such index exists, j is returned
function binsearch(array, i, j) {
    assert(i < j) // since the range is [i,j), then j must be > i
    while (i < j) {
        m = (i+j) >> 1;
        if (predicate(array[m]))
            j = m
        else
            i = m + 1
    }
    return i; // notice that i == j if the predicate is false for the whole range
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
    return i;
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
    return i
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


/* ======================= */
/* Discrete Ternary Search */
/* ======================= */

int min_search(int i, int j) {
    while (i < j) {
        int m = (i+j)/2;
        int slope = eval(m+1) - eval(m);
        if (slope >= 0)
            j = m;
        else
            i = m+1;
    }
    return i;
}

int max_search(int i, int j) {
    while (i < j) {
        int m = (i+j)/2;
        int slope = eval(m+1) - eval(m);
        if (slope <= 0)
            j = m;
        else
            i = m+1;
    }
    return i;
}
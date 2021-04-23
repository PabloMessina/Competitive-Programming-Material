// Find the index of the first item that satisfies a predicate
// over a range [i,j), i.e., from i to j-1
// If no such index exists, j is returned
function binsearch(array, i, j) {
    // assert(i < j) // since the range is [i,j), then j must be > i
    while (i < j) {
        m = (i+j) / 2;
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
int lowerbound(vector<int>& a, int key, int i, int j) {
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
int upperbound(vector<int>& a, int key, int i, int j) {
    while (i < j) {
        int m = (i + j) / 2;
        if (a[m] > key)
            j = m;
        else
            i = m + 1;
    }
    return i
}

/* ======================================= */
/*  std::upper_bound(), std::lower_bound() */
/* ======================================= */

// search between [first, last)
// if no value is >= key (lb) / > key (ub), return last

#include <bits/stdc++.h>

int main () {
    vector<int> v{10,20,30,30,20,10,10,20};          // 10 20 30 30 20 10 10 20
    sort (v.begin(), v.end());                       // 10 10 10 20 20 20 30 30
    auto low = lower_bound (v.begin(), v.end(), 20); //          ^
    auto up  = upper_bound (v.begin(), v.end(), 20); //                    ^
    cout << "lower_bound at position " << (low- v.begin()) << '\n';
    cout << "upper_bound at position " << (up - v.begin()) << '\n';
    return 0;
}

// ------------------------------------------------
// Query: how many items are LESS THAN (<) value x

lower_bound(v.begin(), v.end(), x) - v.begin();

// ------------------------------------------------
// Query: how many items are GREATER THAN (>) value x

v.end() - upper_bound(v.begin(), v.end(), x);

//======================
// std::binary_search()
//======================
bool myfunction (int i,int j) { return (i<j); }
std::vector<int> v{1,2,3,4,5,4,3,2,1};  
sort(v.begin(), v.end());
bool found = std::binary_search (v.begin(), v.end(), 6, myfunction)


/* ======================= */
/* Discrete Ternary Search */
/* ======================= */

int cost(int i) { ... }

int min_search(int l, int r) { // convex cost function
    while (l < r) {
        int m = (i+j) >> 1;
        int slope = cost(m+1) - cost(m);
        if (slope >= 0) r = m;
        else l = m+1;
    }
    return l;
}

int max_search(int l, int r) { // concave cost function
    while (l < r) {
        int m = (i+j) >> 1;
        int slope = cost(m+1) - cost(m);
        if (slope <= 0) r = m;
        else l = m+1;
    }
    return l;
}
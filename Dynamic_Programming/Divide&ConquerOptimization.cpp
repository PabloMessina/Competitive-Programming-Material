#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long int ll;

#define MAXG 1000
#define MAXL 1000
int G,L;
ll DP[MAXG+1][MAXL+1];

// return cost of forming a group with items in the range i .. j
ll group_cost(int i, int j) { ... }

/**
 Calculates the values of DP[g][l] for l1 <= l <= l2 (a range of cells in row 'g')
 using divide & conquer optimization

 DP[g][l] means: given a list of the first 'l' items, partition them into 'g' groups,
 each group consisting of consecutive items (left to right), so that the total
 cost of forming those groups is the minimum possible.

 If we form one group at a time, from right to left, this leads to the following
 recursion:

 DP[g][l] = min { DP[g-1][k] + group_cost(k,l-1) for k = g-1 .. l-1 }
 DP[1][l] = group_cost(0, l-1)

 in other words:

 DP[g][l] = DP[g-1][best_k] + group_cost(best_k,l-1)
    where best_k is the left most value of k where the minimum is reached

Now, for a given 'g':

    If best_k(g,0) <= best_k(g,1) <= best_k(g,2) <= ... <= best_k(g,L-1) holds

    Then, we can propagate those best_k's recursively to reduce the range of 
    candidate k's for each DP[g][l] problem we solve.
    Using Divide & Conquer, we fill the whole row 'g' recursively with
    recursion depth O(log(L)), and each recursion layer taking O(L) time.

Doing this for G groups, the total computation cost is O(G*L*log(L))

*/
void fill_row(int g, int l1, int l2, int k1, int k2) {
    if (l1 > l2) return; // ensure valid range
    int lm = (l1+l2)/2; // solve middle case
    int kmin = max(g-1, k1);
    int kmax = min(lm-1, k2);
    int best_k = -1;
    ll mincost = LLONG_MAX;
    rep(k,kmin,kmax+1) {
        ll tmp = DP[g-1][k] + group_cost(k, lm-1);    
        if (mincost > tmp) mincost = tmp, best_k = k;    
    }
    DP[g][lm] = mincost;
    fill_row(g, l1, lm-1, k1, best_k); // solve left cases
    fill_row(g, lm+1, l2, best_k, k2); // solve right cases
}

void fill_dp() {
    // base: g = 1
    rep(l,1,L+1) DP[1][l] = group_cost(0,l-1);
    // other: g >= 2
    rep(g,2,G+1) fill_row(g,g,L,0,L);
}
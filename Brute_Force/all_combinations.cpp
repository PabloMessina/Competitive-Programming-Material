/* =============================== */
/*  Try all 2^n subsets of n items */
/* =============================== */
void all_subsets(vector<int> items) {
    int n = vals.size();
    int times = (1 << n);
    vector<int> bits(n, 0)
    while(times-- > 0) {
        do_something(bits)
        // generate next set's bit representation
        int i = 0, carry = 1;
        while (i < n) {
            in[i] += carry;
            if (in[i] <= 1)
                carry = 0;
            else
                in[i] = 0;
            i++;
        }
    }
}

/* ========================================= */
/* Split n items into k containers optimally */
/* ========================================= */
int capacities[MAXN];
int N;
// Return cost of storing n items in i-th container
storage_cost(int i, int n);
// Find best way to split n items among containers
// from index i to N-1. For simplicity, the total
// remaining capacity is carried along.
int search_splits(int i, int n, int tot_cap) {
    if (i >= N) return 0;
    int min_k = max(0, n - (tot_cap - capacities[i]));
    int max_k = min(n, capacities[i]);
    int min_cost = INT_MAX;
    rep(k, min_k, max_k) {
        min_cost = min(min_cost,
            storage_cost(i, k) +
            search_splits(i+1, n-k, tot_cap - capacities[i]);
        )
        
    }
}
int best_split(int n) {
    int tot_cap = 0;
    rep(i,0,N-1) tot_cap += capacities[i];
    return search_splits(0,n,tot_cap);
}
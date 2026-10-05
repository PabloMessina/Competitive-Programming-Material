#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'countSubarraysWithSumAndMaxAtMost' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY nums
 *  2. LONG_INTEGER k
 *  3. LONG_INTEGER M
 */

// defines
#define rep(i,a,b) for(int i = a; i < b; ++i) // [a, b), inclusive-exclusive
#define invrep(i,b,a) for(int i = b; i >= a; --i) // [b, a], inclusive-inclusive
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;

template<class t> struct SparseTable {
    int n; vector<int> memo, log2, *arr;
    SparseTable(vector<int>& _arr) {
        arr = &_arr; n = arr->size(); log2.resize(n+1);
        rep(i,2,n+1) log2[i] = 1 + log2[i >> 1];
        memo.assign(n * (log2[n] + 1), -1);
    }
    int dp(int i, int e) {
        int& ans = memo[e * n + i];
        if (ans != -1) return ans;
        if (e == 0) return ans = (*arr)[i];
        return ans = t::merge(dp(i, e-1), dp(i+(1<<(e-1)), e-1));
    }
    // option 1: complexity O(1)
    // ** only works if queries can overlap (e.g. max, min, or, and)
    int query_O1(int l, int r) {
        int e = log2[r - l + 1];
        return t::merge(dp(l,e), dp(r - (1 << e) + 1, e));
    }
};
struct MAX {
    static const int neutro = INT_MIN;
    static int merge(int x, int y) { return max(x, y); }
};

long countSubarraysWithSumAndMaxAtMost(vector<int> nums, long k, long M) {

    if (nums.size() == 0) return 0;

    // Prepare for max queries: build SparseTable to answer max in any subarray
    SparseTable<MAX> st_max(nums);

    // Calculate prefix sums array to allow O(1) sum queries
    vector<ll> prefix_sums(nums.size());
    prefix_sums[0] = nums[0];
    rep(i,1,nums.size()) {
        prefix_sums[i] = prefix_sums[i-1] + nums[i];
    }

    int count = 0;

    // Map from prefix_sum value to index/indices where it occurs (to find subarrays with given sum)
    umap<ll,vector<int>> sum_indices;
    sum_indices[0].pb(-1); // to handle the case where the subarray starts at index 0

    // Iterate through all end indices of subarrays
    rep(i,0,nums.size()) {
        // Look for possible starting indices j, such that sum of nums[j+1..i] == k
        auto it = sum_indices.find(prefix_sums[i] - k);
        if (it != sum_indices.end()) {
            // For each candidate starting index j, check if max in [j+1, i] is <= M
            for (int j : it->second) {
                if (st_max.query_O1(j+1, i) <= M) {
                    count++;
                }
            }
        }
        // Store current prefix sum and index for later queries
        sum_indices[prefix_sums[i]].pb(i);
    }
    
    return count;
}

int main()
{
    string nums_count_temp;
    getline(cin, nums_count_temp);

    int nums_count = stoi(ltrim(rtrim(nums_count_temp)));

    vector<int> nums(nums_count);

    for (int i = 0; i < nums_count; i++) {
        string nums_item_temp;
        getline(cin, nums_item_temp);

        int nums_item = stoi(ltrim(rtrim(nums_item_temp)));

        nums[i] = nums_item;
    }

    string k_temp;
    getline(cin, k_temp);

    long k = stol(ltrim(rtrim(k_temp)));

    string M_temp;
    getline(cin, M_temp);

    long M = stol(ltrim(rtrim(M_temp)));

    long result = countSubarraysWithSumAndMaxAtMost(nums, k, M);

    cout << result << "\n";

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
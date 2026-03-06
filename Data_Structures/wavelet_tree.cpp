/**
 * Wavelet Tree
 * * Purpose: Efficiently answers queries on an array of integers over an alphabet [0, sigma).
 * Space Complexity: O(N log(sigma))
 * Time Complexity (per query): O(log(sigma))
 * * Core Operations:
 * - rank(x, k): Counts occurrences of value x in arr[0...k-1].
 * - quantile(k, a, b): Finds the k-th smallest element in arr[a...b-1] (k is 1-indexed).
 * - range(x, y, a, b): Counts elements with values in [x, y] that are located in arr[a...b-1].
 * - push_back / pop_back: Dynamic insertion/deletion at the end of the array.
 * - swap_adj(i): Swaps arr[i] with arr[i+1].
 */
typedef vector<int>::iterator iter;
struct WaveletTree {
    vector<vector<int>> r0; int n, s;
    vector<int> arrCopy;

    void build(iter b, iter e, int l, int r, int u) {
        if (l == r)
            return;
        int m = (l+r)/2;
        r0[u].reserve(e-b+1); r0[u].push_back(0);
        for (iter it = b; it != e; ++it)
            r0[u].push_back(r0[u].back() + (*it<=m));
        iter p = stable_partition(b, e, [=](int i){return i<=m;});
        build(b, p, l, m, u*2);
        build(p, e, m+1, r, u*2+1);
    }

    int q, w;
    int range(int a, int b, int l, int r, int u) {
        if (r < q or w < l)
            return 0;
        if (q <= l and r <= w)
            return b-a;
        int m = (l+r)/2, za = r0[u][a], zb = r0[u][b];
        return range(za, zb, l, m, u*2) +
            range(a-za, b-zb, m+1, r, u*2+1);
    }
    // arr[i] in [0,sigma)
    WaveletTree(vector<int> arr, int sigma) {
        n = arr.size(); s = sigma;
        r0.resize(s*2); arrCopy = arr;
        build(arr.begin(), arr.end(), 0, s-1, 1);
    }
    // k in [1,n], [a,b) is 0-indexed, -1 if error
    int quantile(int k, int a, int b) {
        //extra conditions disabled
        if (/*a < 0 or b > n or*/ k < 1 or k > b-a)
            return -1;
        int l = 0, r = s-1, u = 1, m, za, zb;
        while (l != r) {
            m = (l+r)/2;
            za = r0[u][a]; zb = r0[u][b]; u*=2;
            if (k <= zb-za)
                a = za, b = zb, r = m;
            else
                k -= zb-za, a -= za, b -= zb,
                l = m+1, ++u;
        }
        return r;
    }
    // counts numbers in [x,y] in positions [a,b)
    int range(int x, int y, int a, int b) {
        if (y < x or b <= a)
            return 0;
        q = x; w = y;
        return range(a, b, 0, s-1, 1);
    }
    // count occurrences of x in positions [0,k)
    int rank(int x, int k) {
        int l = 0, r = s-1, u = 1, m, z;
        while (l != r) {
            m = (l+r)/2;
            z = r0[u][k]; u*=2;
            if (x <= m)
                k = z, r = m;
            else
                k -= z, l = m+1, ++u;
        }
        return k;
    }
    // x in [0,sigma)
    void push_back(int x) {
        int l = 0, r = s-1, u = 1, m, p; ++n;
        while (l != r) {
            m = (l+r)/2;
            p = (x<=m);
            r0[u].push_back(r0[u].back() + p);
            u*=2; if (p) r = m; else l = m+1, ++u;
        }
    }
    // doesn't check if empty
    void pop_back() {
        int l = 0, r = s-1, u = 1, m, p, k; --n;
        while (l != r) {
            m = (l+r)/2; k = r0[u].size();
            p = r0[u][k-1] - r0[u][k-2];
            r0[u].pop_back();
            u*=2; if (p) r = m; else l = m+1, ++u;
        }
    }
    //swap arr[i] with arr[i+1], i in [0,n-1)
    void swap_adj(int i) {
        int &x = arrCopy[i], &y = arrCopy[i+1];
        int l = 0, r = s-1, u = 1;
        while (l != r) {
            int m = (l+r)/2, p = (x<=m), q = (y<=m);
            if (p != q) {
                r0[u][i+1] ^= r0[u][i] ^ r0[u][i+2];
                break;
            }
            u*=2; if (p) r = m; else l = m+1, ++u;
        }
        swap(x, y);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    // Array values must be strictly bounded in [0, sigma)
    vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
    int sigma = 10; 
    WaveletTree wt(arr, sigma);
    // 1. Rank: Count occurrences of '1' in arr[0...4] -> {3, 1, 4, 1, 5}
    cout << wt.rank(1, 5) << "\n"; // Output: 2
    // 2. Quantile: Find the 2nd smallest element in arr[0...4] 
    // Sorted subarray is {1, 1, 3, 4, 5}. 2nd smallest is 1.
    cout << wt.quantile(2, 0, 5) << "\n"; // Output: 1
    // 3. Range: Count elements with values in [1, 4] within arr[0...4]
    // The matching elements are {3, 1, 4, 1}.
    cout << wt.range(1, 4, 0, 5) << "\n"; // Output: 4
    // 4. Updates: Dynamically append and swap
    wt.push_back(7);    // Array is now {3, 1, 4, 1, 5, 9, 2, 6, 7}
    wt.swap_adj(0);     // Array is now {1, 3, 4, 1, 5, 9, 2, 6, 7}
    return 0;
}
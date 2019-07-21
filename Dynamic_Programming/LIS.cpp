// =====================================
// LIS (Longest Increasing Subsequence)
// =====================================
// references:
// https://stackoverflow.com/questions/2631726/how-to-determine-the-longest-increasing-subsequence-using-dynamic-programming
const int MAXLEN = 1000000;
// return the length of the longest increasing (non-decreasing)
// subsequence in values
int LIS(vector<int>& values) {
    static int q[MAXLEN+1];
    int len = 0;
    q[0] = -INT_MAX; // make sure it's strictly smallest
    for (int val : values) {
        if (q[len] < val) { // use <= if non-decreasing
            q[++len] = val;
        } else {
            int l=1, r=len;
            while (l<r) {
                int m = (l+r)>>1;
                if (q[m] >= val) { // use > if non-decreasing
                    r = m;
                } else {
                    l = m+1;
                }
            }
            q[l] = val;
        }
    }
    return len;
}
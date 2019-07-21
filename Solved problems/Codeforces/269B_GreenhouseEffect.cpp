// tags: dp, LIS, longest increasing subsequence
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)

const int MAXLEN = 5000;

int LIS(vector<int>& values) {
    static int q[MAXLEN+1];
    int len = 0;
    q[0] = -INT_MAX;
    for (int val : values) {
        if (q[len] <= val) {
            q[++len] = val;
        } else {
            int l=1, r=len;
            while (l<r) {
                int m = (l+r)>>1;
                if (q[m] > val) {
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

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<int> species(n);
    rep(i,0,n-1) { double _; cin >> species[i] >> _; }
    cout << n - LIS(species) << '\n';
    return 0;
}
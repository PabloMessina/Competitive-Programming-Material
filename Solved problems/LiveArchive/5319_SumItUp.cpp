#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int N, nums[12], counts[12], counts_aux[12];
bool solve(int i, int sum) {
    if (sum == 0) {
        bool f = true;
        rep(i, 0, N) {
            rep(_,0,counts_aux[i]) {
                if (f) f = false;
                else cout << '+';
                cout << nums[i];
            }
        }
        cout << '\n';
        return true;
    }
    if (i == N) return false;   
    bool possible = false;
    invrep(x, counts[i], 0) {
        if (x * nums[i] > sum) continue;
        counts_aux[i] = x;
        possible |= solve(i+1, sum - x * nums[i]);
    }
    return possible;
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int sum, n;
    while (cin >> sum >> n) {
        map<int,int> freq;
        rep(i,0,n) { int x; cin >> x; freq[x]++; }
        N = freq.size();
        int i = N-1;
        for (auto& p : freq) {
            nums[i] = p.first;
            counts[i] = p.second;
            --i;
        }
        cout << "Sums of " << sum << ":\n";
        if (not solve(0, sum)) cout << "NONE\n";
    }
    return 0;
}
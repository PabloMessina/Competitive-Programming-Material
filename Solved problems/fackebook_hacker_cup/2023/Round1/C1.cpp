#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
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
// -------------------------------
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    rep(t,1,T+1) {
        int N, Q; string S;
        cin >> N >> S >> Q;
        vector<int> count(N, 0);
        while (Q--) {
            int i; cin >> i; --i;
            ++count[i];
        }
        // Apply flips
        rep(i,0,N) {
            if (count[i] % 2 == 0) continue;
            int k = i+1;
            for (int j = i; j < N; j+=k) {
                S[j] = 1 - (S[j] - '0') + '0'; // flip
            }
        }
        // Count number of flips to make it all 0s
        int ans = 0;
        rep(i,0,N) {
            if (S[i] == '0') continue;
            ++ans;
            int k = i+1;
            for (int j = i; j < N; j+=k) {
                S[j] = 1 - (S[j] - '0') + '0'; // flip
            }
        }
        cout << "Case #" << t << ": " << ans << "\n";
    }
    return 0;
}
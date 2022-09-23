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
    rep(_t, 1, T+1) {
        int N, K; cin >> N >> K;
        vector<int> S(N);
        vector<int> C(101, 0);
        int ones = 0, twos = 0;
        bool possible = true;
        rep(i,0,N) {
            cin >> S[i];
            C[S[i]]++;
        }
        rep(s,1,101) {
            if (!C[s]) continue;
            if (C[s] == 1) ones++;
            else if (C[s] == 2) twos++;
            else { possible = false; break; }
        }
        cout << "Case #" << _t << ": ";
        if (possible and (twos + ones/2 + (ones % 2)) <= K) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}